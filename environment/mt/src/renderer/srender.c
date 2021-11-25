#include "srender.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>

int viewport_x = 0;
int viewport_y = 0;
int viewport_w = 0;
int viewport_h = 0;

/*!
    Helper function to swap a and b numbers.
    \param a Pointer to first integer to be swapped.
    \param b Pointer to second integer to be swapped.
*/
void swap(int* a, int*b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void line_int(int x0, int y0, int x1, int y1, ssurface* surf, color* c)
{
    // Function uses alot of lines to determine additional things, but after compilation with O3 flag (O2 should work too)
    // It is going to be way faster, since we're operating only on integers and are not introducing any divisions.
    // Multiplications by 2 are fast since these can be changed to SHL instruction.
    //Line drawing uses Bresenham's line algorithm
    bool steep = false; 
    //Check if line is steep
    if (abs(x0-x1)<abs(y0-y1))
    {
        //Swap coordinates to fix line drawing
        swap(&x0, &y0); 
        swap(&x1, &y1); 
        steep = true; 
    } 
    //Check if line is going to be drawn left-to-right
    if (x0>x1)
    { 
        // make it left−to−right 
        swap(&x0, &x1); 
        swap(&y0, &y1); 
    }
    
    //calculate deltas
    int dx = x1-x0; 
    int dy = y1-y0; 
    //calculate error and delta error
    int derror2 = abs(dy)*2; 
    int error2 = 0; 
    int y = y0; 

    for(int x = x0; x<=x1; x++)
    {
        //draw depending on if line is steep or not (swapping cooridnates)
        if(steep)
        {
            *(uint32_t*)(surf->data + ((x * surf->width * surf->bpp) +  (y * surf->bpp))) = *(uint32_t*)c; 
        }
        else
        {
            *(uint32_t*)(surf->data + ((y * surf->width * surf->bpp) +  (x * surf->bpp))) = *(uint32_t*)c; 
        }

        //increase error by delta error
        error2 += derror2;
        if(error2 > dx)
        {
            //increase or decrease y by 1, depending on direction the line is supposed to go
            y += (y1 > y0 ? 1 : -1);
            //decrease error by 2 times delta x
            error2 -= dx*2;
        }
    }
}

void line_vec2i(vec2i p0, vec2i p1, ssurface* surf, color* c)
{
    // Function uses alot of lines to determine additional things, but after compilation with O3 flag (O2 should work too)
    // It is going to be way faster, since we're operating only on integers and are not introducing any divisions.
    // Multiplications by 2 are fast since these can be changed to SHL instruction.
    //Line drawing uses Bresenham's line algorithm
    bool steep = false; 
    //Check if line is steep
    if (abs(p0.x-p1.x)<abs(p0.y-p1.y))
    {
        //Swap coordinates to fix line drawing
        swap(&p0.x, &p0.y); 
        swap(&p1.x, &p1.y); 
        steep = true; 
    } 
    //Check if line is going to be drawn left-to-right
    if (p0.x>p1.x)
    { 
        // make it left−to−right 
        swap(&p0.x, &p0.x); 
        swap(&p0.y, &p1.y); 
    }
    
    //calculate deltas
    int dx = p1.x-p0.x; 
    int dy = p1.y-p0.y; 
    //calculate error and delta error
    int derror2 = abs(dy)*2; 
    int error2 = 0; 
    int y = p0.y; 

    for(int x = p0.x; x<=p1.x; x++)
    {
        //draw depending on if line is steep or not (swapping cooridnates)
        if(steep)
        {
            *(uint32_t*)(surf->data + ((x * surf->width * surf->bpp) +  (y * surf->bpp))) = *(uint32_t*)c; 
        }
        else
        {
            *(uint32_t*)(surf->data + ((y * surf->width * surf->bpp) +  (x * surf->bpp))) = *(uint32_t*)c; 
        }

        //increase error by delta error
        error2 += derror2;
        if(error2 > dx)
        {
            //increase or decrease y by 1, depending on direction the line is supposed to go
            y += (p1.y > p0.y ? 1 : -1);
            //decrease error by 2 times delta x
            error2 -= dx*2;
        }
    }
}

color blend_colors(color a, color b)
{
    color result = {(a.b * b.b)/255, (a.g * b.g)/255, (a.r * b.r)/255, (a.a * b.a)/255};
    return result;
}

static int is_vertex_visible(vec4 v)
{
    return fabs(v.x) <= v.w && fabs(v.y) <= v.w && fabs(v.z) <= v.w;
}

static int is_back_facing(vec3 ndc_coords[3])
{
    vec3 a = ndc_coords[0];
    vec3 b = ndc_coords[1];
    vec3 c = ndc_coords[2];
    float signed_area = a.x * b.y - a.y * b.x +
                        b.x * c.y - b.y * c.x +
                        c.x * a.y - c.y * a.x;
    return signed_area <= 0;
}

//Todo speed up rasterization
//TODO Divide drawing routines to vertex and fragment elements.
// Fragment drawing will rasterize triangle, vertex drawing will only calculate position, so we can determine if given pixel is visible.
// This way it should make rendering way faster, since vertex operations are way faster.
void triangle(vec4* pts, vec2i* uvs, ssurface* surf, ssurface* zbuffer, ssurface* tex, color* c)
{
    //Check if triangle is at all visible (implement better culling algorithm)
    int t1_vis = is_vertex_visible(pts[0]);
    int t2_vis = is_vertex_visible(pts[1]);
    int t3_vis = is_vertex_visible(pts[2]);
    if(!t1_vis && !t2_vis && !t3_vis) return;
    
    vec3 t[3];
    t[0] = div_vec3(pts[0].xyz, pts[0].w);
    t[1] = div_vec3(pts[1].xyz, pts[1].w);
    t[2] = div_vec3(pts[2].xyz, pts[2].w);

    if(is_back_facing(t)) return;

    t[0].x = (int)((t[0].x+1.)*(viewport_w/2.f) + viewport_x);
    t[0].y = (int)((t[0].y+1.)*(viewport_h/2.f) + viewport_y);
    t[0].z = (t[0].z + 1.f) * 0.5f;
    t[0].z = CLAMP(t[0].z, 0.0f, 1.0f); 
    
    t[1].x = (int)((t[1].x+1.)*(viewport_w/2.f) + viewport_x);
    t[1].y = (int)((t[1].y+1.)*(viewport_h/2.f) + viewport_y);
    t[1].z = (t[1].z + 1.f) * 0.5f;
    t[1].z = CLAMP(t[1].z, 0.0f, 1.0f); 
    
    t[2].x = (int)((t[2].x+1.)*(viewport_w/2.f) + viewport_x);
    t[2].y = (int)((t[2].y+1.)*(viewport_h/2.f) + viewport_y);
    t[2].z = (t[2].z + 1.f) * 0.5f;  
    t[2].z = CLAMP(t[2].z, 0.0f, 1.0f); 

    //if (t0.y==t1.y && t0.y==t2.y)

    if (t[0].y>t[1].y) swap_vec3(&t[0], &t[1]); 
    if (t[0].y>t[2].y) swap_vec3(&t[0], &t[2]); 
    if (t[1].y>t[2].y) swap_vec3(&t[1], &t[2]); 

    int total_height = t[2].y-t[0].y; 
    for (int i=0; i<total_height; i++)
    { 
        bool second_half = i > t[1].y - t[0].y || t[1].y == t[0].y; 
        int segment_height = second_half ? t[2].y - t[1].y : t[1].y - t[0].y; 
        float alpha = (float)i / total_height; 
        float beta  = (float)(i - (second_half ? t[1].y - t[0].y : 0)) / segment_height; // be careful: with above conditions no division by zero here 
        
        // Since we're doing everything in C we need to implement functions that will work in place of operators.
        // Normally in C++ I'd suggest making operator overloads for each vec type.

        //Calculate proper positions of vertices for drawing.
        vec3 A =               add_vec3(t[0], mul_vec3(sub_vec3(t[2],t[0]),alpha)); 
        vec3 B = second_half ? add_vec3(t[1], mul_vec3(sub_vec3(t[2], t[1]), beta)) : add_vec3(t[0], mul_vec3(sub_vec3(t[1], t[0]), beta)); 
        
        vec2i uvA =               add_vec2i(uvs[0], mul_vec2i_f(sub_vec2i(uvs[2],uvs[0]), alpha));
        vec2i uvB = second_half ? add_vec2i(uvs[1], mul_vec2i_f(sub_vec2i(uvs[2],uvs[1]), beta)) : add_vec2i(uvs[0], mul_vec2i_f(sub_vec2i(uvs[1], uvs[0]), beta));

        if (A.x>B.x) swap_vec3(&A, &B); 
        for (int j=(int)A.x; j<=(int)B.x; j++)
        { 
            float phi = B.x==A.x ? 1. : (float)(j-A.x)/(float)(B.x-A.x);
            vec3  p = add_vec3(A, mul_vec3(sub_vec3(B,A),phi));
            vec2i uvp =     add_vec2i(uvA, mul_vec2i_f(sub_vec2i(uvB, uvA), phi));
            //part of culling, this shouldn't be here, but works.
            if(p.x < viewport_x || p.x > viewport_w || p.y < viewport_y || p.y > viewport_h) continue;
            int index = (int)((p.x*zbuffer->bpp)+(p.y*zbuffer->width*zbuffer->bpp));
            if (p.z <= *(float*)&zbuffer->data[index])
            {
                *(float*)&zbuffer->data[index] = p.z;
                color col = blend_colors(*(color*)(tex->data + (uvp.y * tex->width * tex->bpp) + (uvp.x * tex->bpp)), *c);

                *(uint32_t*)(surf->data + (((int)p.y * surf->width * surf->bpp) +  ((int)p.x * surf->bpp))) = *(uint32_t*)&col;
            }
        } 
    }
}

//WIP
float EdgeFunc( vec3 a, vec3 b, vec3 c )
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

void triangle_bc(vec3* pts, vec2f* uvs, ssurface* zbuffer, ssurface* surf, ssurface* tex, color* c)
{
    //Create boundging box of screen size.
    vec2i bboxmin = {{{0, 0}}}; 
    vec2i bboxmax = {{{surf->width - 1, surf->height - 1}}};
    //create clamping vector
    vec2i clamp = {{{surf->width-1,  surf->height-1}}};
    //clamp values to bounding box
    
    bboxmax.x = MIN(MAX(pts[0].x, MAX(pts[1].x, pts[2].x)), clamp.x);
    bboxmin.x = MAX(MIN(pts[0].x, MIN(pts[1].x, pts[2].x)), 0);
    bboxmax.y = MIN(MAX(pts[0].y, MAX(pts[1].y, pts[2].y)), clamp.y);
    bboxmin.y = MAX(MIN(pts[0].y, MIN(pts[1].y, pts[2].y)), 0);
    
    // for (int i=0; i<3; i++)
    // { 
    //     for (int j=0; j<2; j++)
    //     { 
    //         bboxmin.elems[j] = MAX(float, 0.f, MIN(float, bboxmin.elems[j], pts[i].elems[j])); 
    //         bboxmax.elems[j] = MIN(float, clamp.elems[j], MAX(float, bboxmax.elems[j], pts[i].elems[j])); 
    //     } 
    // } 
    // //now our triangle is clamped to be inside screen.

    // calculate barycentric coordinates of pixel in triangle.
    // This allows code to find if pixel is inside our bounding box of triangle.
    vec3 p;

    for (p.x=bboxmin.x; p.x<=bboxmax.x; p.x++)
    {
        for (p.y=bboxmin.y; p.y<=bboxmax.y; p.y++)
        {
            vec3 bc_screen = barycentric(pts[0], pts[1], pts[2], p); //This might be slow
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue;
            p.z = 0;
            
            for (int i=0; i<3; i++) p.z += pts[i].elems[2] * bc_screen.elems[i];

            int index = (int)((p.x*zbuffer->bpp)+(p.y*zbuffer->width*zbuffer->bpp));
            if (*(float*)&zbuffer->data[index] < p.z)
            {
                *(float*)&zbuffer->data[index] = p.z;
                
                *(uint32_t*)(surf->data + (((int)p.y * surf->width * surf->bpp) +  ((int)p.x * surf->bpp))) = *(uint32_t*)c;
            }
        }
    }
}

void viewport(int x, int y, int w, int h)
{
    viewport_x = x;
    viewport_y = y;
    viewport_w = w;
    viewport_h = h;
}
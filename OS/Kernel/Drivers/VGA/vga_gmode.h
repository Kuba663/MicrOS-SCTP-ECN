#ifndef VGA_GMODE_H
#define VGA_GMODE_H

#include <stdint.h>

#define VGA_VRAM 0xC00A0000
#define VGA_VRAM_2 0xC00B8000
#define PITCH 320





void set3HVideoMode();

void set4HVideoMode();
void pixel_4H(unsigned char color, unsigned int x, unsigned int y);
void drawDupaIn4H(int color);

void set5HVideoMode();
void pixel_5H(unsigned char color, unsigned int x, unsigned int y);
void drawDupaIn5H(int color);

void set6HVideoMode();
void pixel_6H(unsigned char color, unsigned int x, unsigned int y);
void drawDupaIn6H(int color);

void setDHVideoMode();
void pixel_DH(unsigned char color, unsigned int x, unsigned int y);
void drawDupaInDH(int color);

void setEHVideoMode();
void pixel_EH(unsigned char color, unsigned int x, unsigned int y);
void drawDupaInEH(int color);

void setFHVideoMode();
void pixel_FH(unsigned char color, unsigned int x, unsigned int y);
void drawDupaInFH(int color);

void set10HVideoMode();
void pixel_10H(unsigned char color, unsigned int x, unsigned int y);
void drawDupaIn10H(int color);

void set11HVideoMode();
void pixel_11H(unsigned char color, unsigned int x, unsigned int y);
void drawDupaIn11H(int color);

void set12HVideoMode();
void pixel_12H(unsigned char color, unsigned int x, unsigned int y);
void drawDupaIn12H(int color);

void set13HVideoMode();
void pixel_13H(unsigned char color, unsigned int x, unsigned int y);
void drawDupaIn13H(int color);
void drawMicrOSLogoIn13H();
void drawLenaIn13H();

void setModeYVideoMode();
void pixel_ModeY(unsigned char color, unsigned int x, unsigned int y);
void drawDupaInY(int color);




char getMode();

void dumpRegs();
void printRegs();
void test13H();
void setPalette13H();

#endif
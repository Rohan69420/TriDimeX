#include "lodepng.h"

void swapLoadPNG(unsigned char** img, unsigned* w, unsigned* h, const char* filename);
void loadPNG(unsigned char** img, unsigned* w, unsigned* h, const char* filename);
void imageSwap(unsigned char *img, unsigned w, unsigned h);

#include "pngloader.c"

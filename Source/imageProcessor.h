#ifndef PROCESS_IMAGE_H
#define PROCESS_IMAGE_H

#include <stdlib.h>

typedef unsigned char *Image_Data;

typedef struct Image {
    unsigned char *img;
    unsigned w, h;
} Image;

void Create_Image(Image *Img, int w, int h);
void Create_Image_Color(Image *Img, int w, int h, unsigned char color[]);
void Delete_Image(Image *Img);
void Clone_Image(Image *Source, Image *Dest);
void Clone_Image_Shadow(Image *Source, Image *Dest, unsigned char color[]);
void Crop_Image(Image *Source, Image *Dest, int x, int y, int w, int h);
void Flip_Horizontal(Image *Source, Image *Dest);
void Flip_Vertical(Image *Source, Image *Dest);
void Rotate_180(Image *Source, Image *Dest);
void Rotate_Left(Image *Source, Image *Dest);
void Rotate_Right(Image *Source, Image *Dest);
void Mix_Image(Image *BG, Image *FG, int x, int y);
void Mix_Image_NoBG(Image *BG, Image *FG, int x, int y);
void Mix_Image_Color(Image *BG, Image *FG, int x, int y, unsigned char color[]);
void Mix_Image_Color_NoBG(Image *BG, Image *FG, int x, int y, unsigned char color[]);
void Zoom_Image(Image *Img, int Scale);
void Blur_Image(Image *Src, Image *Dst, int Radius);

#include "process_image.c"

#endif

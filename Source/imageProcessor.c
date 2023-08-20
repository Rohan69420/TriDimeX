#include "process_image.h"

void Create_Image(Image* Img, int w, int h) {
    Img->w = w;
    Img->h = h;
    int i, size = w * h, size_4 = size * 4;
    Img->img = (Image_Data)malloc(size_4);
    Image_Data img = Img->img;
    for (i = 0; i < size; i++) {
        *img++ = 255;
        *img++ = 255;
        *img++ = 255;
        *img++ = 0;
    }
}

void Create_Image_Color(Image* Img, int w, int h, unsigned char color[]) {
    Img->w = w;
    Img->h = h;
    int i, size = w * h, size_4 = size * 4;
    Img->img = (Image_Data)malloc(size_4);
    Image_Data img = Img->img;
    unsigned char color_0 = color[0], color_1 = color[1], color_2 = color[2],
        color_3 = color[3];
    for (i = 0; i < size; i++) {
        *img++ = color_0;
        *img++ = color_1;
        *img++ = color_2;
        *img++ = color_3;
    }
}

void Delete_Image(Image* Img) { free(Img->img); }

void Clone_Image(Image* Source, Image* Dest) {
    int i, size = Source->w * Source->h * 4;
    Dest->w = Source->w;
    Dest->h = Source->h;
    Dest->img = (Image_Data)malloc(size);
    Image_Data img_s = Source->img, img_d = Dest->img;
    for (i = 0; i < size; i++)
        *img_d++ = *img_s++;
}

void Clone_Image_Shadow(Image* Source, Image* Dest, unsigned char color[]) {
    int i, size = Source->w * Source->h;
    Dest->w = Source->w;
    Dest->h = Source->h;
    Dest->img = (Image_Data)malloc(size * 4);
    Image_Data img_s = Source->img, img_d = Dest->img;
    unsigned char r = color[0], g = color[1], b = color[2], a = color[3];
    for (i = 0; i < size; i++) {
        img_d[0] = r;
        img_d[1] = g;
        img_d[2] = b;
        img_d[3] = a * img_s[3] / 255;
        img_s += 4;
        img_d += 4;
    }
}

void Crop_Image(Image* Source, Image* Dest, int x, int y, int w, int h) {
    int i, j, w4 = Source->w * 4, start;
    Dest->w = w;
    Dest->h = h;
    Dest->img = (Image_Data)malloc(w * h * 4);
    Image_Data img_s = Source->img, img_d = Dest->img, img;
    start = w4 * y + x * 4;
    for (i = 0; i < h; i++) {
        img = img_s + start;
        start += w4;
        for (j = 0; j < w; j++) {
            *img_d++ = *img++;
            *img_d++ = *img++;
            *img_d++ = *img++;
            *img_d++ = *img++;
        }
    }
}

void Flip_Horizontal(Image* Source, Image* Dest) {
    int i, j, w = Source->w, h = Source->h, w4 = w * 4, start = w4 - 4;
    Dest->w = w;
    Dest->h = h;
    Dest->img = (Image_Data)malloc(w * h * 4);
    Image_Data img_s = Source->img, img_d, img = Dest->img;
    for (i = 0; i < h; i++) {
        img_d = img + start;
        for (j = 0; j < w; j++) {
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
            img_d -= 8;
        }
        start += w4;
    }
}

void Flip_Vertical(Image* Source, Image* Dest) {
    int i, j, w = Source->w, h = Source->h, w4 = w * 4, start = (h - 1) * w * 4;
    Dest->w = w;
    Dest->h = h;
    Dest->img = (Image_Data)malloc(w * h * 4);
    Image_Data img_s = Source->img, img_d, img = Dest->img;
    for (i = 0; i < h; i++) {
        img_d = img + start;
        for (j = 0; j < w; j++) {
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
        }
        start -= w4;
    }
}

void Rotate_180(Image* Source, Image* Dest) {
    int i, j, w = Source->w, h = Source->h;
    Dest->w = w;
    Dest->h = h;
    Dest->img = (Image_Data)malloc(w * h * 4);
    Image_Data img_s = Source->img, img_d = Dest->img + w * h * 4 - 4;
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
            img_d -= 8;
        }
    }
}

void Rotate_Left(Image* Source, Image* Dest) {
    int i, j, w = Source->w, h = Source->h, h4 = h * 4 + 4,
        start = (w - 1) * h * 4;
    Dest->w = h;
    Dest->h = w;
    Dest->img = (Image_Data)malloc(w * h * 4);
    Image_Data img_s = Source->img, img_d, img = Dest->img;
    for (i = 0; i < h; i++) {
        img_d = img + start;
        for (j = 0; j < w; j++) {
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
            img_d -= h4;
        }
        start += 4;
    }
}

void Rotate_Right(Image* Source, Image* Dest) {
    int i, j, w = Source->w, h = Source->h, h4 = h * 4 - 4, start = h4;
    Dest->w = h;
    Dest->h = w;
    Dest->img = (Image_Data)malloc(w * h * 4);
    Image_Data img_s = Source->img, img_d, img = Dest->img;
    for (i = 0; i < h; i++) {
        img_d = img + start;
        for (j = 0; j < w; j++) {
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
            *img_d++ = *img_s++;
            img_d += h4;
        }
        start -= 4;
    }
}

void Mix_Image(Image* BG, Image* FG, int x, int y) {
    int i, j, w_BG = BG->w, w_FG = FG->w, h_FG = FG->h;
    Image_Data img1 = BG->img + w_BG * 4 * y + x * 4, img2 = FG->img;
    unsigned char tmp;
    for (i = 0; i < h_FG; i++) {
        for (j = 0; j < w_FG; j++) {
            tmp = img1[3];
            img1[3] = img1[3] + img2[3] - img1[3] * img2[3] / 255;
            if (img1[3] != 0) {
                img1[0] = (img2[0] * img2[3] +
                    img1[0] * tmp * (255 - img2[3]) / 255) /
                    img1[3];
                img1[1] = (img2[1] * img2[3] +
                    img1[1] * tmp * (255 - img2[3]) / 255) /
                    img1[3];
                img1[2] = (img2[2] * img2[3] +
                    img1[2] * tmp * (255 - img2[3]) / 255) /
                    img1[3];
            }
            else {
                img1[0] = img2[0];
                img1[1] = img2[1];
                img1[2] = img2[2];
            }
            img1 += 4;
            img2 += 4;
        }
        img1 += (w_BG - w_FG) * 4;
    }
}

void Mix_Image_NoBG(Image* BG, Image* FG, int x, int y) {
    int i, j, w_BG = BG->w, w_FG = FG->w, h_FG = FG->h;
    Image_Data img1 = BG->img + w_BG * 4 * y + x * 4, img2 = FG->img;
    for (i = 0; i < h_FG; i++) {
        for (j = 0; j < w_FG; j++) {
            img1[0] = img2[0];
            img1[1] = img2[1];
            img1[2] = img2[2];
            img1[3] = img2[3];
            img1 += 4;
            img2 += 4;
        }
        img1 += (w_BG - w_FG) * 4;
    }
}

void Mix_Image_Color(Image* BG, Image* FG, int x, int y,
    unsigned char color[]) {
    int i, j, w_BG = BG->w, w_FG = FG->w, h_FG = FG->h;
    Image_Data img1 = BG->img + w_BG * 4 * y + x * 4, img2 = FG->img;
    unsigned char tmp;
    unsigned char color_0 = color[0], color_1 = color[1], color_2 = color[2],
        color_3 = color[3];
    for (i = 0; i < h_FG; i++) {
        for (j = 0; j < w_FG; j++) {
            tmp = img1[3];
            img1[3] = img1[3] + img2[3] - img1[3] * img2[3] / 255;
            if (img1[3] != 0) {
                img1[0] = (color_0 * img2[3] +
                    img1[0] * tmp * (255 - img2[3]) / 255) /
                    img1[3];
                img1[1] = (color_1 * img2[3] +
                    img1[1] * tmp * (255 - img2[3]) / 255) /
                    img1[3];
                img1[2] = (color_2 * img2[3] +
                    img1[2] * tmp * (255 - img2[3]) / 255) /
                    img1[3];
            }
            else {
                img1[0] = color_0;
                img1[1] = color_1;
                img1[2] = color_2;
            }
            img1[3] = img1[3] * color_3 / 255;
            img1 += 4;
            img2 += 4;
        }
        img1 += (w_BG - w_FG) * 4;
    }
}

void Mix_Image_Color_NoBG(Image* BG, Image* FG, int x, int y,
    unsigned char color[]) {
    int i, j, w_BG = BG->w, w_FG = FG->w, h_FG = FG->h;
    Image_Data img1 = BG->img + w_BG * 4 * y + x * 4, img2 = FG->img;
    unsigned char color_0 = color[0], color_1 = color[1], color_2 = color[2],
        color_3 = color[3];
    for (i = 0; i < h_FG; i++) {
        for (j = 0; j < w_FG; j++) {
            img1[0] = color_0;
            img1[1] = color_1;
            img1[2] = color_2;
            img1[3] = color_3 * img2[3] / 255;
            img1 += 4;
            img2 += 4;
        }
        img1 += (w_BG - w_FG) * 4;
    }
}

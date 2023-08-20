void swapLoadPNG(unsigned char **img, unsigned *w, unsigned *h, const char *filename) {
    lodepng_decode_file(img, w, h, filename, LCT_RGBA, 8);
    imageSwap(*img, *w, *h);
}


void loadPNG(unsigned char **img, unsigned *w, unsigned *h, const char *filename) {
    lodepng_decode_file(img, w, h, filename, LCT_RGBA, 8);
}

void imageSwap(unsigned char *img, unsigned w, unsigned h) {
    unsigned i, j, h2 = h / 2, h3 = h - 1, w2 = w * 4;
    unsigned char *tmp, *tmp2, t;
    for (i = 0; i < h2; ++i) {
        tmp = img + i * w2;
        tmp2 = img + (h3 - i) * w2;
        for (j = 0; j < w; ++j) {
            t = *tmp; *tmp = *tmp2; *tmp2 = t; ++tmp; ++tmp2;
            t = *tmp; *tmp = *tmp2; *tmp2 = t; ++tmp; ++tmp2;
            t = *tmp; *tmp = *tmp2; *tmp2 = t; ++tmp; ++tmp2;
            t = *tmp; *tmp = *tmp2; *tmp2 = t; ++tmp; ++tmp2;
        }
    }
}


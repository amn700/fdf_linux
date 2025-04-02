#include "fdf_bonus.h"

int ice_fire(int z, t_zscale *zscale) {
    float normalized = (z - zscale->min) / (float)(zscale->max - zscale->min);
    int red, green, blue;

    if (normalized < 0.5f) {
        red = 0; green = 255; blue = 255;  // Ice (Cyan)
    } else {
        red = 255; green = 69; blue = 0;  // Fire (Orange-Red)
    }

    return (red << 24) | (green << 16) | (blue << 8) | 255;
}


int classic_black_white(int z, t_zscale *zscale) {
    float normalized = (z - zscale->min) / (float)(zscale->max - zscale->min);
    int red, green, blue;

    if (normalized < 0.5f) {
        red = 0; green = 0; blue = 0;  // Black
    } else {
        red = 255; green = 255; blue = 255;  // White
    }

    return (red << 24) | (green << 16) | (blue << 8) | 255;
}

int forest_gold(int z, t_zscale *zscale) {
    float normalized = (z - zscale->min) / (float)(zscale->max - zscale->min);
    int red, green, blue;

    if (normalized < 0.5f) {
        red = 34; green = 139; blue = 34;  // Forest Green
    } else {
        red = 255; green = 215; blue = 0;  // Gold
    }

    return (red << 24) | (green << 16) | (blue << 8) | 255;
}

int warm_cool(int z, t_zscale *zscale) {
    float normalized = (z - zscale->min) / (float)(zscale->max - zscale->min);
    int red, green, blue;

    if (normalized < 0.5f) {
        red = 0; green = 128; blue = 128;  // Teal (Cool)
    } else {
        red = 255; green = 87; blue = 34;  // Orange (Warm)
    }

    return (red << 24) | (green << 16) | (blue << 8) | 255;
}


int sepia(int z, t_zscale *zscale) {
    float normalized = (z - zscale->min) / (float)(zscale->max - zscale->min);
    int red, green, blue;

    if (normalized < 0.5f) {
        red = 112; green = 66; blue = 20;  // Brown
    } else {
        red = 245; green = 222; blue = 179;  // Beige
    }

    return (red << 24) | (green << 16) | (blue << 8) | 255;
}

int neon_pink_cyan(int z, t_zscale *zscale) {
    float normalized = (z - zscale->min) / (float)(zscale->max - zscale->min);
    int red, green, blue;

    if (normalized < 0.5f) {
        red = 255; green = 20; blue = 147;  // Neon Pink
    } else {
        red = 0; green = 255; blue = 255;  // Neon Cyan
    }

    return (red << 24) | (green << 16) | (blue << 8) | 255;
}

int gold_teal(int z, t_zscale *zscale) {
    float normalized = (z - zscale->min) / (float)(zscale->max - zscale->min);
    int red, green, blue;

    if (normalized < 0.5f) {
        red = 255; green = 215; blue = 0;  // Gold
    } else {
        red = 0; green = 128; blue = 128;  // Teal
    }

    return (red << 24) | (green << 16) | (blue << 8) | 255;
}

int purple_green(int z, t_zscale *zscale) {
    float normalized = (z - zscale->min) / (float)(zscale->max - zscale->min);
    int red, green, blue;

    if (normalized < 0.5f) {
        red = 138; green = 43; blue = 226;  // Purple
    } else {
        red = 34; green = 139; blue = 34;  // Green
    }

    return (red << 24) | (green << 16) | (blue << 8) | 255;
}

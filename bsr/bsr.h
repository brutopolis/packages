#ifndef BSR_H
#define BSR_H 1


#define OLIVEC_IMPLEMENTATION
#include "olive.c"
#include "MiniFB.h"
#include "bruter-representation.h"

// olive.c RGBA to ARGB patch
// i am not sure if this patch does anything at all
// seems right, but i see no difference at all between the image generated using this patch and the original olive.c without this patch

// lets first undefine the olivec original macros
#undef OLIVEC_ALPHA
#undef OLIVEC_RED
#undef OLIVEC_GREEN
#undef OLIVEC_BLUE
#undef OLIVEC_ARGB
#undef OLIVEC_RGBA

// now redefine them to use ARGB instead of RGBA
#define OLIVEC_ALPHA(color)   (((color) & 0xFF000000) >> 24)
#define OLIVEC_RED(color)     (((color) & 0x00FF0000) >> 16)
#define OLIVEC_GREEN(color)   (((color) & 0x0000FF00) >> 8)
#define OLIVEC_BLUE(color)    (((color) & 0x000000FF) >> 0)
#define OLIVEC_ARGB(a,r,g,b)  ( ((a)<<24) | ((r)<<16) | ((g)<<8) | (b) )
#define OLIVEC_RGBA(r,g,b,a)  OLIVEC_ARGB(a, r, g, b)

#endif

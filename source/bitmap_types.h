#ifndef BITMAP_TYPES_H__
#define BITMAP_TYPES_H__

#include "bitmap.h"

// ****************************************************************
// Bitmap with dynamic memory.
// ****************************************************************
using DynamicBitmap = SimpleBitmap<std::vector<short>, short, 0, 0>;


// ****************************************************************
// Bitmap with fixed-sized memory.
// ****************************************************************
template <auto WIDTH, auto HEIGHT>
class ArrayBitmap : public SimpleBitmap<std::array<short, WIDTH * HEIGHT>, short, WIDTH, HEIGHT>
{
};

#endif

#ifndef BITMAP_UTILITIES_H__
#define BITMAP_UTILITIES_H__

#include "bitmap.h"

// ****************************************************************
// Bitmap utilities
// ****************************************************************
class BitmapUtilites
{
public:

    template <typename BITMAP> static constexpr auto IsLandscape(const BITMAP& bitmap)
    {
        const auto width = bitmap.GetWidth();
        const auto height = bitmap.GetHeight();

        return width > height;
    }

    template <typename BITMAP> static constexpr auto IsSquare(const BITMAP& bitmap)
    {
        const auto width = bitmap.GetWidth();
        const auto height = bitmap.GetHeight();

        return width == height;
    }
};

#endif

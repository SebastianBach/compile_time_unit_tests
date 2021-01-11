#ifndef BITMAP_TESTS_H__
#define BITMAP_TESTS_H__

#include "bitmap_types.h"
#include "bitmap_utilities.h"



// ****************************************************************
// Test basic functions of the StaticBitmap
// ****************************************************************
template <auto WIDTH, auto HEIGHT>
constexpr bool TestStaticBitmapBasics()
{
    constexpr ArrayBitmap<WIDTH, HEIGHT> staticBitmap {};

    if (!staticBitmap.HasSize())
        return false;

    constexpr auto width = staticBitmap.GetWidth();
    constexpr auto height = staticBitmap.GetHeight();

    static_assert(width != height);

    if (width != WIDTH)
        return false;

    if (height != HEIGHT)
        return false;

    return true;
}

template <typename BITMAP, typename F>
constexpr auto Iterate(BITMAP& bitmap, F func)
{
    const auto width = bitmap.GetWidth();
    const auto height = bitmap.GetHeight();

    for (auto x = 0u; x < width; ++x)
    {
        for (auto y = 0u; y < height; ++y)
        {
            const auto res = func(x, y);
            if (res == false)
                return false;
        }
    }

    return true;
}

// ****************************************************************
// Generic Set/Get test for the given bitmap
// ****************************************************************
template <typename BITMAP>
constexpr auto TestBitmapSetGet(BITMAP& bitmap)
{
    typename BITMAP::DataType inValue = 0;

    // set values

    const auto resSet = Iterate(bitmap, 
        [&bitmap, &inValue] (auto x, auto y)
        {
            if (!bitmap.SetPixel(x, y, inValue))
                return false;

            inValue++;
            return true;
        });

    if (!resSet)
        return false;

    // get values

    inValue = 0;

    const auto resGet = Iterate(bitmap, 
        [&bitmap, &inValue] (auto x, auto y)
        {
            short receviedValue = 0;

            if (!bitmap.GetPixel(x, y, receviedValue))
                return false;

            if (inValue != receviedValue)
                return false;

            inValue++;
            return true;
        });

    return resGet;
}

// ****************************************************************
// Tests Set/Get of StaticBitmap
// ****************************************************************
template <auto WIDTH, auto HEIGHT>
constexpr auto TestStaticBitmapSetGet()
{
    ArrayBitmap<WIDTH, HEIGHT> staticBitmap {};

    return TestBitmapSetGet(staticBitmap);
}

// ****************************************************************
// Tests the DynamicBitmap
// ****************************************************************
template <auto WIDTH, auto HEIGHT>
auto TestDynamicBitmap()
{
    DynamicBitmap dyBitmap {};
    dyBitmap.Init(WIDTH, HEIGHT);

    if (!dyBitmap.HasSize())
        return false;

    const auto width = dyBitmap.GetWidth();
    const auto height = dyBitmap.GetHeight();

    if (width != WIDTH)
        return false;

    if (height != HEIGHT)
        return false;

    return TestBitmapSetGet(dyBitmap);
}

// ****************************************************************
// Tests the Bitmap utilities
// ****************************************************************
constexpr auto TestUtilities()
{
    constexpr ArrayBitmap<32u, 64u> bitmap {};

    constexpr auto checkLandscape = BitmapUtilites::IsLandscape(bitmap);
    if (checkLandscape == true)
        return false;

    constexpr auto checkNonSquare = BitmapUtilites::IsSquare(bitmap);
    if (checkNonSquare == true)
        return false;

    constexpr ArrayBitmap<32u, 32u> squareBitmap {};

    constexpr auto checkSuqare = BitmapUtilites::IsSquare(squareBitmap);
    if (checkSuqare == false)
        return false;

    return true;
}

// ****************************************************************
// Tests the Fill() method
// ****************************************************************
template <auto WIDTH, auto HEIGHT, auto VALUE>
constexpr auto TestFill()
{
    ArrayBitmap<WIDTH, HEIGHT> bitmap {};

    // fill
    bitmap.Fill(VALUE);

    // check

    const auto resCheck = Iterate(bitmap,
        [&bitmap] (auto x, auto y)
        {
            short receviedValue = 0;

            if (!bitmap.GetPixel(x, y, receviedValue))
                return false;

            if (VALUE != receviedValue)
                return false;

            return true;
        });

    return resCheck;
}


#endif

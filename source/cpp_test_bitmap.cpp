#include <iostream>

#include "bitmap_tests.h"

int main()
{
    // test dynamic bitmap at run time

    if (!TestDynamicBitmap<32u, 64u>())
    {
        std::cout << "Dynamic Bitmap Failure" << std::endl;
        return -1;
    }

    // test static bitmap at compile time

    static_assert(TestStaticBitmapBasics<32u, 64u>(), "Static Bitmap Basics Failure");
    static_assert(TestStaticBitmapSetGet<32u, 64u>(), "Static Bitmap Set/Get Failure");
    static_assert(TestUtilities(), "Static Bitmap Utilities Failure");
    static_assert(TestFill<32u, 64u, 123>(), "Static Bitmap Fill Failure");

    return 1;
}


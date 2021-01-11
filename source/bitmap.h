#ifndef BITMAP_H__
#define BITMAP_H__

#include <array>
#include <vector>
#include <type_traits>


namespace intern
{
// ****************************************************************
// Internal utility to check if given type T is based on std::vector
// ****************************************************************
template <typename T>
struct is_std_vector
{
    static const auto is_vector = false;
};

template <typename T, typename Alloc>
struct is_std_vector<std::vector<T, Alloc>>
{
    static const auto is_vector = true;
};
}

#define ENABLE_IF_VECTOR template <typename = typename std::enable_if<intern::is_std_vector<MEMORY>::is_vector, MEMORY > > 

// ****************************************************************
// Simple Bitmap class template
//
// MEMORY		Underlying memory type (std::vector or std::array)
// DATATYPE		Pixel data type
// WIDTH		Initial width
// HEIGHt		Initial height
// ****************************************************************
template <typename MEMORY, typename DATATYPE, auto WIDTH, auto HEIGHT>
class SimpleBitmap
{
public:

    using DataType = DATATYPE;

    // ****************************************************************
    // Constructor
    // ****************************************************************
    constexpr SimpleBitmap() :
        _width(WIDTH),
        _height(HEIGHT),
        _memory()
    {
    }

    // ****************************************************************
    // Copy Constructor
    // ****************************************************************
    ENABLE_IF_VECTOR SimpleBitmap(const SimpleBitmap& src) :
        _width(src._width),
        _height(src._height),
        _memory(src._memory)
    {
    }

    // ****************************************************************
    // Init function. Only available with std::vector as data model.
    // @param[in] width		Bitmap width
    // @param[in] height	Bitmap height
    // ****************************************************************
    ENABLE_IF_VECTOR void Init(unsigned int width, unsigned int height)
    {
        _width = width;
        _height = height;

        const auto size = width * height;
        _memory.resize(size);
    }

    // ****************************************************************
    // Checks if the size of the bitmap is non zero.
    // @return		True if the bitmap is not empty
    // ****************************************************************
    constexpr auto HasSize() const
    {
        const auto size = _memory.size();
        return size > 0;
    }

    // ****************************************************************
    // Returns the bitmap width
    // @return		Bitmap width
    // ****************************************************************
    constexpr auto GetWidth() const
    {
        return _width;
    }
    // ****************************************************************
    // Returns the bitmap height
    // @return		Bitmap height
    // ****************************************************************
    constexpr auto GetHeight() const
    {
        return _height;
    }

    // ****************************************************************
    // Sets the pixel value at the given coordinates.
    // Checks the validity of the coordinates.
    // @param[in] x			X-coordinate
    // @param[in] y			Y-coordinate
    // @param[in] value		The pixel value
    // @return				True if the value was set, otherwise false
    // ****************************************************************
    constexpr auto SetPixel(unsigned int x, unsigned int y, DataType value)
    {
        const auto offset = GetOffset(x, y);
        const auto size = _memory.size();

        if (offset >= size) return false;

        _memory[offset] = value;

        return true;
    }

    // ****************************************************************
    // Gets the pixel value at the given coordinates.
    // Checks the validity of the coordinates.
    // @param[in] x			X-coordinate
    // @param[in] y			Y-coordinate
    // @param[out] value	The pixel value
    // @return				True if the value was received, otherwise false
    // ****************************************************************
    constexpr auto GetPixel(unsigned int x, unsigned int y, DataType& value) const
    {
        const auto offset = GetOffset(x, y);
        const auto size = _memory.size();

        if (offset >= size) return false;

        value = _memory[offset];

        return true;
    }

    // ****************************************************************
    // Fills the bitmap with the given value.
    // @param[in] value		The value set to every pixel
    // ****************************************************************
    constexpr void Fill(DataType value)
    {
        for (auto& v : _memory)
        {
            v = value;
        }
    }

private:

    // ****************************************************************
    // Internal function to get the memory offset.
    // @param[in] x			X-coordinate
    // @param[in] y			Y-coordinate
    // @return				The offset
    // ****************************************************************
    constexpr auto GetOffset(unsigned x, unsigned y) const
    {
        return (y * _width) + x;
    }

    // bitmap width
    unsigned int _width;

    // bitmap height
    unsigned int _height;

    MEMORY _memory;
};


#endif

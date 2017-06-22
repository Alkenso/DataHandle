/*
 * Copyright (c) 2017 Alkenso (Vashurkin Vladimir)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <vector>
#include <string>

#define TYPE_BYTE_BUFFER(BufferType) typename BufferType, typename = datarw::IsByteBuffer<BufferType>
#define TYPE_BYTE_BUFFER_IMPL(BufferType) typename BufferType, typename

namespace datarw
{
    static const bool kIsBigEndian = *(uint16_t*)"\0\xff" < 0x100;
    
    using ByteBuffer = std::vector<unsigned char>;
    using CharBuffer = std::vector<char>;
    
    template <typename T>
    struct IsByte
    {
        static const bool value =
        std::is_same<T, char>::value ||
        std::is_same<T, signed char>::value ||
#if __cplusplus > 201402L
        std::is_same<T, std::byte>::value ||
#endif
        std::is_same<T, unsigned char>::value;
    };

    template <typename T>
    using IsVector = std::is_same<T, std::vector<typename T::value_type, typename T::allocator_type>>;

    template <typename T>
    struct IsContiguousContainer
    {
        static const bool value =
        IsVector<T>::value ||
        std::is_same<T, std::string>::value;
    };
    
    template <typename Container>
    using IsByteContainer = typename std::enable_if<IsByte<typename Container::value_type>::value, Container>::type;
    
    template <typename T>
    using IsByteBuffer = typename std::enable_if<IsByte<typename T::value_type>::value && IsContiguousContainer<T>::value>::type;
    
    struct Range
    {
        uint64_t position;
        uint64_t length;
        
        Range(uint64_t _position, uint64_t _length) : position(_position), length(_length) {}
        Range() : position(0), length(0) {}
    };
}

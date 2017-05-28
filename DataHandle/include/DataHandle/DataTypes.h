//
//  DataTypes.h
//  DataHandle
//
//  Created by Alkenso on 5/9/17.
//
//

#pragma once

#include <vector>

#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)

namespace datarw
{
    using ByteBuffer = std::vector<unsigned char>;
    
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
    struct IsContiguousContainer
    {
        static const bool value =
        std::is_same<T, std::vector<typename T::value_type>>::value ||
        std::is_same<T, std::string>::value;
    };
    
    template <typename T>
    using ByteTypename = typename std::enable_if<IsByte<T>::value>::type;
    template <typename T>
    using BufferTypename = typename std::enable_if<IsByte<typename T::value_type>::value && IsContiguousContainer<T>::value, T>::type;
    
    struct Range
    {
        uint64_t position;
        uint64_t length;
        
        Range(uint64_t _position, uint64_t _length) : position(_position), length(_length) {}
        Range() : position(0), length(0) {}
    };
}

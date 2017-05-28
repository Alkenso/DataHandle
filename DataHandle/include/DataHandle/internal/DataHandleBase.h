//
//  DataHandleBase.h
//  DataHandle
//
//  Created by Alkenso on 5/9/17.
//
//

#pragma once

#include <DataHandle/DataTypes.h>

namespace datarw
{
    class DataHandleBase
    {
    public:
        virtual ~DataHandleBase() {}
        
    protected:
        virtual uint64_t tellPosition() = 0;
        
    private:
        virtual uint64_t getDataSizeImpl() = 0;
        
        /* Some data sources (e.g. streams, files) have native implementation of seeking / reading consistent data.
         * Overriding 'seekPositionOptimized' allows derived classes to ignore range.position in 'peekDataImpl' implementation.
         * That allows native seek implmenetation to be called only when needed. */
        virtual void seekPositionOptimized(const uint64_t position);
    };
    
    namespace utils
    {
        template<typename T>
        T ReverseValueByteOrder(T value);
    }
}

template<typename T>
T datarw::utils::ReverseValueByteOrder(T value)
{
    uint8_t* valuePtr = reinterpret_cast<uint8_t*>(&value);
    std::reverse(valuePtr, valuePtr + sizeof(value));
    
    return value;
}

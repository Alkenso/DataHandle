//
//  RawBytesReadHandle.h
//  DataHandle
//
//  Created by Alkenso on 5/5/17.
//
//

#pragma once

#include <DataHandle/DataReadHandle.h>

namespace datarw
{
    class RawBytesReadHandle : public DataReadHandle
    {
    public:
        template <typename T>
        RawBytesReadHandle(const T* ptr, const uint64_t sizeInBytes, bool copyData = false);
        
    private:
        virtual void peekDataImpl(const Range& range, unsigned char* buffer);
        virtual uint64_t getDataSizeImpl();
        
    private:
        const datarw::ByteBuffer m_bufferData;
        const unsigned char* m_constPtr;
        const uint64_t m_size;
    };
}

#include <DataHandle/internal/RawBytesReadHandleInternal.h>

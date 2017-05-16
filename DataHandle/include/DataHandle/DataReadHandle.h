//
//  DataReadHandle.h
//  DataHandle
//
//  Created by Alkenso on 5/9/17.
//
//

#pragma once

#include <string>

#include <DataHandle/internal/DataHandleBase.h>

namespace datarw
{
    class DataReadHandle : public DataHandleBase
    {
    public:
        virtual ~DataReadHandle() {}
        
        template <typename Data, typename = ByteTypename<Data>>
        void peekData(const Range& range, Data* data);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void peekData(const Range& range, Buffer& buffer);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void peekAppendData(const Range& range, Buffer& buffer);
        template <typename Buffer>
        BufferTypename<Buffer> peekData(const Range& range);
        
        template <typename Data, typename = ByteTypename<Data>>
        void readNextData(const uint64_t dataSize, Data* data);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void readNextData(const uint64_t dataSize, Buffer& buffer);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void appendNextData(const uint64_t dataSize, Buffer& buffer);
        template <typename Buffer>
        BufferTypename<Buffer> readNextData(const uint64_t dataSize);
        
        template <typename Data, typename = ByteTypename<Data>>
        void readAllData(Data* data);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void readAllData(Buffer& buffer);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void appendAllData(Buffer& buffer);
        template <typename Buffer>
        BufferTypename<Buffer> readAllData();
        
        template<typename T>
        T peekValue(int64_t offset);
        template<typename T>
        T peekValueFromCurrent(int64_t offset);
        template<typename T>
        T readNextValue();
        
        template<typename T>
        T peekValueBE(int64_t offset);
        template<typename T>
        T peekValueFromCurrentBE(int64_t offset);
        template<typename T>
        T readNextValueBE();
        
        void skipNextBytes(const uint64_t skipSize);
        uint64_t getRemainingSize();
        bool enshureRemainingSize(uint64_t expectedRemainingSize);
        
    private:
        virtual void peekDataImpl(const Range& range, unsigned char* buffer) = 0;
        
    private:
        void peekDataInternal(const Range& range, unsigned char* buffer, const bool usePosition);
        void readNextDataInternal(const uint64_t dataSize, unsigned char* buffer);
    };
}

#include <DataHandle/internal/DataReadHandleInternal.h>

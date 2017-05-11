//
//  DataReadHandle.h
//  DataHandle
//
//  Created by alk on 5/9/17.
//
//

#pragma once

#include <string>

#include "DataHandleBase.h"

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

template <typename Data, typename>
void datarw::DataReadHandle::peekData(const Range& range, Data* data)
{
    peekDataInternal(range, reinterpret_cast<unsigned char*>(data), false);
}

template <typename Buffer, typename>
void datarw::DataReadHandle::peekData(const Range& range, Buffer& buffer)
{
    buffer.resize(static_cast<size_t>(range.length));
    peekData(range, &buffer[0]);
}

template <typename Buffer, typename>
void datarw::DataReadHandle::peekAppendData(const Range& range, Buffer& buffer)
{
    const size_t currentBufferSize = buffer.size();
    buffer.resize(static_cast<size_t>(currentBufferSize + range.length));
    peekData(range, &buffer[currentBufferSize]);
}

template <typename Buffer>
datarw::BufferTypename<Buffer> datarw::DataReadHandle::peekData(const Range& range)
{
    Buffer buffer;
    peekData(range, buffer);
    
    return buffer;
}

template <typename Data, typename>
void datarw::DataReadHandle::readNextData(const uint64_t dataSize, Data* data)
{
    readNextDataInternal(dataSize, reinterpret_cast<unsigned char*>(data));
}

template <typename Buffer, typename>
void datarw::DataReadHandle::readNextData(const uint64_t dataSize, Buffer& buffer)
{
    buffer.resize(static_cast<size_t>(dataSize));
    readNextData(dataSize, &buffer[0]);
}

template <typename Buffer, typename>
void datarw::DataReadHandle::appendNextData(const uint64_t dataSize, Buffer& buffer)
{
    const size_t currentBufferSize = buffer.size();
    buffer.resize(static_cast<size_t>(currentBufferSize + dataSize));
    readNextData(dataSize, &buffer[currentBufferSize]);
}

template <typename Buffer>
datarw::BufferTypename<Buffer> datarw::DataReadHandle::readNextData(const uint64_t dataSize)
{
    Buffer buffer;
    readNextData(dataSize, buffer);
    
    return buffer;
}

template <typename Data, typename>
void datarw::DataReadHandle::readAllData(Data* data)
{
    peekData(datarw::Range(0, getDataSize()), data);
}

template <typename Buffer, typename>
void datarw::DataReadHandle::readAllData(Buffer& buffer)
{
    buffer.resize(getDataSize());
    readAllData(&buffer[0]);
}

template <typename Buffer, typename>
void datarw::DataReadHandle::appendAllData(Buffer& buffer)
{
    const size_t currentBufferSize = buffer.size();
    buffer.resize(static_cast<size_t>(currentBufferSize + getDataSize()));
    readAllData(&buffer[currentBufferSize]);
}

template <typename Buffer>
datarw::BufferTypename<Buffer> datarw::DataReadHandle::readAllData()
{
    Buffer buffer;
    readAllData(buffer);
    
    return buffer;
}

template<typename T>
T datarw::DataReadHandle::peekValue(int64_t offset)
{
    T value;
    memset(&value, 0, sizeof(T));
    peekData(Range(offset, sizeof(T)), reinterpret_cast<unsigned char*>(&value));
    
    return value;
}

template<typename T>
T datarw::DataReadHandle::peekValueFromCurrent(int64_t offset)
{
    return peekValue<T>(tellPosition() + offset);
}

template<typename T>
T datarw::DataReadHandle::readNextValue()
{
    T value;
    memset(&value, 0, sizeof(T));
    readNextData(sizeof(T), reinterpret_cast<unsigned char*>(&value));
    
    return value;
}

template<typename T>
T datarw::DataReadHandle::peekValueBE(int64_t offset)
{
    return utils::ReverseValueByteOrder<T>(peekValue<T>(offset));
}

template<typename T>
T datarw::DataReadHandle::peekValueFromCurrentBE(int64_t offset)
{
    return utils::ReverseValueByteOrder<T>(peekValueFromCurrent<T>(offset));
}

template<typename T>
T datarw::DataReadHandle::readNextValueBE()
{
    return utils::ReverseValueByteOrder<T>(readNextValue<T>());
}

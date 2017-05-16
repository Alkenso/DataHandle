//
//  DataReadHandleInternal.h
//  DataHandle
//
//  Created by Alkenso on 5/9/17.
//
//

#pragma once

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

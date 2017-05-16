//
//  DataWriteHandle.h
//  DataHandle
//
//  Created by Alkenso on 5/9/17.
//
//

#pragma once

#include <string>
#include <mutex>

#include <DataHandle/internal/DataHandleBase.h>

namespace datarw
{
    class DataWriteHandle : public DataHandleBase
    {
    public:
        virtual ~DataWriteHandle() {}
        
        template <typename Data, typename = ByteTypename<Data>>
        void insertData(const Data* data, const uint64_t dataSize, const uint64_t offset);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void insertData(const Buffer& buffer, int64_t offset);
        void insertString(const std::string& str, int64_t offset, const bool withNullTerminator = false);
        
        template <typename Data, typename = ByteTypename<Data>>
        void writeData(const Data* data, const uint64_t dataSize);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void writeData(const Buffer& buffer);
        void writeString(const std::string& str, const bool withNullTerminator = false);
        
        template<typename T>
        void insertValue(const T& value, const int64_t offset);
        template<typename T>
        void writeValue(const T& value);
        
        template<typename T>
        void insertValueBE(const T& value, const int64_t offset);
        template<typename T>
        void writeValueBE(const T& value);
        
    private:
        virtual void insertDataImpl(const unsigned char* data, const Range& range) = 0;
        
    private:
        void insertDataInternal(const unsigned char* data, const uint64_t dataSize, const uint64_t offset, const bool usePosition);
        
    private:
        std::once_flag m_inited;
    };
}

#include <DataHandle/internal/DataWriteHandleInternal.h>

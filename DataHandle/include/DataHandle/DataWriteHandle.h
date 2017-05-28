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
        
        uint64_t getDataSize();
        
        template <typename Data, typename = ByteTypename<Data>>
        void writeData(const Data* data, const uint64_t dataSize, const uint64_t offset);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void writeData(const Buffer& buffer, int64_t offset);
        void writeString(const std::string& str, int64_t offset, const bool withNullTerminator = false);
        
        template <typename Data, typename = ByteTypename<Data>>
        void writeData(const Data* data, const uint64_t dataSize);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void writeData(const Buffer& buffer);
        void writeString(const std::string& str, const bool withNullTerminator = false);
        
        template<typename T>
        void writeValueLE(const T& value, const uint64_t offset);
        template<typename T>
        void writeValueLE(const T& value);
        
        template<typename T>
        void writeValueBE(const T& value, const uint64_t offset);
        template<typename T>
        void writeValueBE(const T& value);
        
    protected:
        DataWriteHandle();
        virtual uint64_t tellPosition() final;
        
    private:
        virtual uint64_t getDataSizeImpl() override = 0;
        virtual void writeDataImpl(const unsigned char* data, const Range& range) = 0;
        virtual void seekPositionOptimized(const uint64_t position) override;
        
    private:
        void insertDataInternal(const unsigned char* data, const uint64_t dataSize, const uint64_t offset, const bool usePosition);
        uint64_t seekPosition(const uint64_t offset, const bool usePosition);
        void initPosition();
        
        template<typename T>
        void writeValue(const T& value, const uint64_t offset, const bool reverseByteOrder);
        template<typename T>
        void writeValue(const T& value, const bool reverseByteOrder);
        
    private:
        uint64_t m_position;
        bool m_usePositionIsSet;
        std::once_flag m_inited;
    };
}

#include <DataHandle/internal/DataWriteHandleInternal.h>

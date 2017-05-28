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
        
        uint64_t getDataSize();
        
        template <typename Data, typename = ByteTypename<Data>>
        void peekData(const Range& range, Data* data);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void peekData(const Range& range, Buffer& buffer);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void peekAppendData(const Range& range, Buffer& buffer);
        template <typename Buffer>
        BufferTypename<Buffer> peekData(const Range& range);
        
        template <typename Data, typename = ByteTypename<Data>>
        void readData(const uint64_t dataSize, Data* data);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void readData(const uint64_t dataSize, Buffer& buffer);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void appendData(const uint64_t dataSize, Buffer& buffer);
        template <typename Buffer>
        BufferTypename<Buffer> readData(const uint64_t dataSize);
        
        template <typename Data, typename = ByteTypename<Data>>
        void readAllData(Data* data);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void readAllData(Buffer& buffer);
        template <typename Buffer, typename = BufferTypename<Buffer>>
        void appendAllData(Buffer& buffer);
        template <typename Buffer>
        BufferTypename<Buffer> readAllData();
        
        template<typename T>
        T peekValueLE(int64_t offset);
        template<typename T>
        T peekValueFromCurrentLE(int64_t offset);
        template<typename T>
        T readValueLE();
        
        template<typename T>
        T peekValueBE(int64_t offset);
        template<typename T>
        T peekValueFromCurrentBE(int64_t offset);
        template<typename T>
        T readValueBE();
        
        void skipBytes(const uint64_t skipSize);
        uint64_t getRemainingSize();
        bool enshureRemainingSize(uint64_t expectedRemainingSize);
        
    protected:
        DataReadHandle();
        virtual uint64_t tellPosition() final;
        
    private:
        virtual uint64_t getDataSizeImpl() override = 0 ;
        virtual void peekDataImpl(const Range& range, unsigned char* buffer) = 0;
        virtual void seekPositionOptimized(const uint64_t position) override;
        
    private:
        void peekDataInternal(const Range& range, unsigned char* buffer, const bool usePosition);
        void readDataInternal(const uint64_t dataSize, unsigned char* buffer);
        uint64_t seekPosition(const uint64_t offset, const bool usePosition, const bool seekForce = false);
        
        template<typename T>
        T peekValue(int64_t offset, const bool reverseByteOrder);
        template<typename T>
        T peekValueFromCurrent(int64_t offset, const bool reverseByteOrder);
        template<typename T>
        T readValue(const bool reverseByteOrder);
        
    private:
        uint64_t m_sizePosition;
        uint64_t m_sizePositionIsSet;
        uint64_t m_currentPosition;
        bool m_usePositionIsSet;
    };
}

#include <DataHandle/internal/DataReadHandleInternal.h>

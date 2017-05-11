#pragma once

#include "DataWriteHandle.h"

namespace datarw
{
    namespace utils
    {
        class FileWriteHandle;
    }

    class FileWriteHandle : public DataWriteHandle
    {
    public:
        explicit FileWriteHandle(const std::string& filePath);
        ~FileWriteHandle();

    private:
        virtual void WriteDataImpl(const unsigned char* data, Range writeDataRange);
        virtual uint64_t GetDataSizeImpl();
        virtual void Resize(uint64_t newSize);

    private:
//        std::unique_ptr<datarw::utils::FileWriteHandle> m_FileWriteHandle;
        bool m_currentDataSizeIsValid;
        uint64_t m_currentDataSize;
    };
}

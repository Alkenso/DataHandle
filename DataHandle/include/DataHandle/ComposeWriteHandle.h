//
//  ComposeWriteHandle.h
//  DataHandle
//
//  Created by alk on 5/22/17.
//
//

#pragma once

#include <DataHandle/DataWriteHandle.h>

namespace datarw
{
    class ComposeWriteHandle : public DataWriteHandle
    {
    public:
        explicit ComposeWriteHandle(std::initializer_list<std::reference_wrapper<DataWriteHandle>> writers);
        
    private:
        virtual uint64_t getDataSizeImpl() final;
        virtual void writeDataImpl(const unsigned char* data, const Range& range) final;
        
    private:
        std::vector<std::reference_wrapper<DataWriteHandle>> m_writers;
    };
}

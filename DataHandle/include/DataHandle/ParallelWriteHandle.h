//
//  ParallelWriteHandle.h
//  DataHandle
//
//  Created by alk on 5/22/17.
//
//

#pragma once

#include "DataWriteHandle.h"

namespace datarw
{
    class ParallelWriteHandle : public DataWriteHandle
    {
    public:
        explicit ParallelWriteHandle(std::initializer_list<std::reference_wrapper<DataWriteHandle>> writers);
        
    private:
        virtual uint64_t getDataSizeImpl() final;
        virtual void insertDataImpl(const unsigned char* data, const Range& range) final;
        
    private:
        std::vector<std::reference_wrapper<DataWriteHandle>> m_writers;
    };
}

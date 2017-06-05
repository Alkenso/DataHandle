//
//  ComposeReadHandle.h
//  DataHandle
//
//  Created by Alkenso on 5/22/17.
//
//

#pragma once

#include <DataHandle/DataReadHandle.h>

namespace datarw
{
    class ComposeReadHandle : public DataReadHandle
    {
    public:
        explicit ComposeReadHandle(std::initializer_list<std::reference_wrapper<DataReadHandle>> readers);
        
    private:
        virtual uint64_t getDataSizeImpl() final;
        virtual void peekDataImpl(const Range& range, unsigned char* buffer) final;
        
    private:
        uint64_t updateReaderRanges();
        
    private:
        std::vector<std::reference_wrapper<DataReadHandle>> m_readers;
        std::vector<Range> m_readerRanges;
    };
}

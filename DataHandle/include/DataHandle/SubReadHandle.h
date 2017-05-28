//
//  SubReadHandle.h
//  DataHandle
//
//  Created by Alkenso on 5/5/17.
//
//

#pragma once

#include <DataHandle/DataReadHandle.h>

namespace datarw
{
    class SubReadHandle : public DataReadHandle
    {
    public:
        SubReadHandle(DataReadHandle& parentReader, const Range dataRange);
        SubReadHandle(DataReadHandle& parentReader, const uint64_t additionalOffset, const bool relativeToParent = false);

    private:
        virtual void peekDataImpl(const Range& range, unsigned char* buffer) final;
        virtual uint64_t getDataSizeImpl() final;

    private:
        DataReadHandle& m_parentReader;
        Range m_dataRange;
    };
}

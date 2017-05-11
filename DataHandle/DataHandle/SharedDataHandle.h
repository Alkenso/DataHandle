//
//  SharedDataHandle.h
//  DataHandle
//
//  Created by Alkenso on 5/5/17.
//
//

#pragma once

#include "DataReadHandle.h"
#include "DataWriteHandle.h"

namespace datarw
{
    template <typename ChildReader>
    class SharedReadHandle : public ChildReader
    {
    public:
        template <typename... Args>
        SharedReadHandle(std::shared_ptr<datarw::DataReadHandle> parentReader, Args&&... args)
        : ChildReader(*parentReader, std::forward<Args>(args)...)
        , m_parentReader(parentReader)
        {}
        
    private:
        std::shared_ptr<datarw::DataReadHandle> m_parentReader;
    };
    
    template <typename ChildWriter>
    class SharedWriteHandle : public ChildWriter
    {
    public:
        template <typename... Args>
        SharedWriteHandle(std::shared_ptr<datarw::DataWriteHandle> parentReader, Args&&... args)
        : ChildWriter(*parentReader, std::forward<Args>(args)...)
        , m_parentReader(parentReader)
        {}
        
    private:
        std::shared_ptr<datarw::DataWriteHandle> m_parentReader;
    };
}

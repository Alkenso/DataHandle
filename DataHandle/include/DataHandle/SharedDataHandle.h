/*
 * Copyright (c) 2017 Alkenso (Vashurkin Vladimir)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <DataHandle/DataReadHandle.h>
#include <DataHandle/DataWriteHandle.h>

namespace datarw
{
    template <typename ChildReader>
    class SharedReadHandle : public ChildReader
    {
    public:
        template <typename... Args>
        explicit SharedReadHandle(std::shared_ptr<datarw::DataReadHandle> parentReader, Args&&... args)
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

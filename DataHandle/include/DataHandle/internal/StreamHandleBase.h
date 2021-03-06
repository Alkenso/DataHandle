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

namespace datarw
{
    template <typename Parent, typename StreamType>
    class StreamHandleBase : public Parent
    {
    public:
        StreamHandleBase(StreamType& stream, const bool streamIsDirty);
        
        StreamHandleBase(StreamHandleBase&& r);
        StreamHandleBase& operator=(StreamHandleBase&& r);
        
        virtual ~StreamHandleBase() {}
        
    protected:
        void resetStreamIfNeeded(const bool force, const uint64_t position);
        
    private: // DataHandleBase
        virtual uint64_t getDataSizeImpl() final;
        virtual void seekPositionOptimized(const uint64_t position) final;
        
    private: // StreamHandleBase
        virtual void seek(StreamType& stream, const int64_t pos, const std::ios::seekdir dir) = 0;
        virtual int64_t tell(StreamType& stream) = 0;
        
    protected:
        std::reference_wrapper<StreamType> m_stream;
        bool m_streamIsDirty;
    };
}

template <typename Parent, typename StreamType>
datarw::StreamHandleBase<Parent, StreamType>::StreamHandleBase(StreamType& stream, const bool streamIsDirty)
: Parent()
, m_stream(stream)
, m_streamIsDirty(streamIsDirty)
{}

template <typename Parent, typename StreamType>
datarw::StreamHandleBase<Parent, StreamType>::StreamHandleBase(StreamHandleBase&& r)
: Parent(std::move(r))
, m_stream(std::move(r.m_stream))
, m_streamIsDirty(r.m_streamIsDirty)
{}

template <typename Parent, typename StreamType>
datarw::StreamHandleBase<Parent, StreamType>& datarw::StreamHandleBase<Parent, StreamType>::operator=(StreamHandleBase&& r)
{
    Parent::operator=(std::move(r));
    m_stream = std::move(r.m_stream);
    m_streamIsDirty = r.m_streamIsDirty;

    return *this;
}

template <typename Parent, typename StreamType>
void datarw::StreamHandleBase<Parent, StreamType>::resetStreamIfNeeded(const bool force, const uint64_t position)
{
    if (force || m_streamIsDirty)
    {
        StreamType& streamRef = m_stream.get();
        streamRef.clear();
        seek(streamRef, position, std::ios::beg);
    }
}

template <typename Parent, typename StreamType>
uint64_t datarw::StreamHandleBase<Parent, StreamType>::getDataSizeImpl()
{
    resetStreamIfNeeded(false, Parent::tellPosition());
    
    StreamType& streamRef = m_stream.get();
    const auto currentPos = tell(streamRef);
    seek(streamRef, 0, std::ios::end);
    const auto size = tell(streamRef);
    seek(streamRef, currentPos, std::ios::beg);
    
    return size;
}

template <typename Parent, typename StreamType>
void datarw::StreamHandleBase<Parent, StreamType>::seekPositionOptimized(const uint64_t position)
{
    resetStreamIfNeeded(false, position);
    
    seek(m_stream.get(), position, std::ios::beg);
}

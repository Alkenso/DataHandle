//
//  StreamHandleBase.h
//  DataHandle
//
//  Created by Alkenso on 5/10/17.
//
//

#pragma once

namespace datarw
{
    template <typename Parent, typename StreamType>
    class StreamHandleBase : public Parent
    {
    public:
        StreamHandleBase(StreamType& stream, const bool streamIsDirty);
        
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
        StreamType& m_stream;
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
void datarw::StreamHandleBase<Parent, StreamType>::resetStreamIfNeeded(const bool force, const uint64_t position)
{
    if (force || m_streamIsDirty)
    {
        m_stream.clear();
        seek(m_stream, position, std::ios::beg);
    }
}

template <typename Parent, typename StreamType>
uint64_t datarw::StreamHandleBase<Parent, StreamType>::getDataSizeImpl()
{
    resetStreamIfNeeded(false, Parent::tellPosition());
    
    const auto currentPos = tell(m_stream);
    seek(m_stream, 0, std::ios::end);
    const auto size = tell(m_stream);
    seek(m_stream, currentPos, std::ios::beg);
    
    return size;
}

template <typename Parent, typename StreamType>
void datarw::StreamHandleBase<Parent, StreamType>::seekPositionOptimized(const uint64_t position)
{
    resetStreamIfNeeded(false, position);
    
    seek(m_stream, position, std::ios::beg);
}

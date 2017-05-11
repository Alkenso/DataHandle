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
        using SeekFn = std::function<void(StreamType&, int64_t, std::ios::seekdir)>;
        using TellFn = std::function<int64_t(StreamType&)>;
        
        StreamHandleBase(StreamType& stream, SeekFn seekFn, TellFn tellFn, const bool streamIsDirty);
        
        virtual ~StreamHandleBase() {}
        
    protected:
        void resetStreamIfNeeded(const bool force, const uint64_t position);
        
    private:
        virtual uint64_t getDataSizeImpl() override;
        virtual void seekPositionOptimized(const uint64_t position) override;
        
    protected:
        StreamType& m_stream;
        
    private:
        SeekFn m_seekFn;
        TellFn m_tellFn;
    };
}

template <typename Parent, typename StreamType>
datarw::StreamHandleBase<Parent, StreamType>::StreamHandleBase(StreamType& stream, SeekFn seekFn, TellFn tellFn, const bool streamIsDirty)
: Parent()
, m_stream(stream)
, m_seekFn(seekFn)
, m_tellFn(tellFn)
{
    if (streamIsDirty)
    {
        resetStreamIfNeeded(true, 0);
    }
}

template <typename Parent, typename StreamType>
void datarw::StreamHandleBase<Parent, StreamType>::resetStreamIfNeeded(const bool force, const uint64_t position)
{
    if (force || Parent::getSupportExternalDataSourceChanges())
    {
        m_stream.clear();
        m_seekFn(m_stream, position, std::ios::seekdir::beg);
    }
}

template <typename Parent, typename StreamType>
uint64_t datarw::StreamHandleBase<Parent, StreamType>::getDataSizeImpl()
{
    resetStreamIfNeeded(false, Parent::tellPosition());
    
    const auto currentPos = m_tellFn(m_stream);
    m_seekFn(m_stream, 0, std::ios::seekdir::end);
    const auto size = m_tellFn(m_stream);
    m_seekFn(m_stream, currentPos, std::ios::seekdir::beg);
    
    return size;
}

template <typename Parent, typename StreamType>
void datarw::StreamHandleBase<Parent, StreamType>::seekPositionOptimized(const uint64_t position)
{
    resetStreamIfNeeded(false, position);
    
    m_seekFn(m_stream, position, std::ios::seekdir::beg);
}

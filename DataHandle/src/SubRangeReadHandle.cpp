//
//  SubRangeReadHandle.cpp
//  DataHandle
//
//  Created by Alkenso on 5/5/17.
//
//

#include "SubRangeReadHandle.h"

datarw::SubRangeReadHandle::SubRangeReadHandle(DataReadHandle& parentReader, Range dataRange)
: DataReadHandle()
, m_parentReader(parentReader)
, m_dataRange(dataRange)
{
    if ((dataRange.position + dataRange.length) > parentReader.getDataSize())
    {
        throw std::out_of_range("Data could be out of range");
    }
}

datarw::SubRangeReadHandle::SubRangeReadHandle(DataReadHandle& parentReader, const uint64_t additionalOffset, const bool relativeToParent /* = false */)
: DataReadHandle()
, m_parentReader(parentReader)
, m_dataRange()
{
    uint64_t subPosition = additionalOffset;
    if (relativeToParent)
    {
        subPosition += parentReader.getDataSize() - parentReader.getRemainingSize(); 
    }
    
    const uint64_t totalDataSize = parentReader.getDataSize();
    if (totalDataSize < subPosition)
    {
        throw std::out_of_range("Data could be out of range");
    }
    m_dataRange = datarw::Range(subPosition, totalDataSize - subPosition);
}

void datarw::SubRangeReadHandle::peekDataImpl(const Range& range, unsigned char* buffer)
{
    const Range subRange(range.position + m_dataRange.position, range.length);
    m_parentReader.peekData(subRange, buffer);
}

uint64_t datarw::SubRangeReadHandle::getDataSizeImpl()
{
    return m_dataRange.length;
}

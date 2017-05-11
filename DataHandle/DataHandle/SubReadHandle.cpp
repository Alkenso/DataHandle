#include "SubReadHandle.h"

datarw::SubReadHandle::SubReadHandle(DataReadHandle& parentReader, Range dataRange)
: DataReadHandle()
, m_parentReader(parentReader)
, m_dataRange(dataRange)
{
    if ((dataRange.position + dataRange.length) > parentReader.getDataSize())
    {
        throw std::out_of_range("Data could be out of range");
    }
}

datarw::SubReadHandle::SubReadHandle(DataReadHandle& parentReader, const uint64_t additionalOffset, const bool relativeToParent /* = false */)
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

void datarw::SubReadHandle::peekDataImpl(const Range& range, unsigned char* buffer)
{
    m_parentReader.peekData(utils::RangeWithAdditionalOffset(range, m_dataRange.position), buffer);
}

uint64_t datarw::SubReadHandle::getDataSizeImpl()
{
    return m_dataRange.length;
}

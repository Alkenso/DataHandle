#include "DataHandleUtils.h"

bool datarw::utils::RangesIntersects(const datarw::Range& range1, const datarw::Range& range2)
{
    const uint64_t intersectionLength = std::max(range1.position + range1.length, range2.position + range2.length) - std::min(range1.position, range2.position);
    const uint64_t totalLength = range1.length + range2.length;

    return totalLength > intersectionLength;
}

datarw::Range datarw::utils::RangesIntersection(const datarw::Range& range1, const datarw::Range& range2)
{
    if (!RangesIntersects(range1, range2))
    {
        return datarw::Range(-1, 0);
    }

    const uint64_t offset1 = range1.position + range1.length;
    const uint64_t offset2 = range2.position + range2.length;

    return datarw::Range(std::max(range1.position, range2.position), std::min(offset1, offset2) - std::max(range1.position, range2.position));
}

bool datarw::utils::RangesAreEqual(const datarw::Range& range1, const datarw::Range& range2)
{
    return ((range1.position == range2.position) && (range1.length ==range2.length));
}

datarw::Range datarw::utils::RangeWithAdditionalOffset(const datarw::Range& range, int64_t offset)
{
    return datarw::Range(range.position + offset, range.length);
}

#ifndef VALUE_UTILS_H
#define VALUE_UTILS_H

#include <limits>
#include <iostream>

namespace value_utils
{

template<typename T>
struct Range
{
    Range(T min_, T max_) : min(min_), max(max_) {}
    T min;
    T max;
};

template<typename T>
void limitToRange(T& rValue, const Range<T>& range)
{
    if(rValue <= range.min || rValue == std::numeric_limits<T>::max())
        rValue = range.min;
    if(rValue > range.max)
        rValue = range.max;
}

// integral version
template<typename SourceT, typename DestT>
DestT mapValue(SourceT                    value,
               const Range<SourceT>& sourceRange,
               const Range<DestT>&   destRange)
{
    const int32_t deltaVal = value - sourceRange.min;
    const int32_t sourceRangeLen = sourceRange.max - sourceRange.min;
    const int32_t destRangeLen = destRange.max - destRange.min;
    DestT ret = (deltaVal * destRangeLen / sourceRangeLen) + destRange.min;
    return ret;
}

} // namespace value_utils

#endif
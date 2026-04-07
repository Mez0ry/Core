#ifndef __MIN_MAX_HPP__
#define __MIN_MAX_HPP__

template <typename TValue>
const TValue& Max(const TValue &a, const TValue &b){
    return (a >= b) ? a : b;
}

template <typename TValue>
const TValue& Min(const TValue &a, const TValue &b){
    return (a <= b) ? a : b;
}

template <typename TValue>
inline TValue& Bound(const TValue& min, TValue& val, const TValue& max){
    val = Max(val, min);
    val = Min(val, max);
    return val;
}

template <typename TValue>
inline TValue Bound(const TValue& min, const TValue& val, const TValue& max){
    auto res = Max(val, min);
    res = Min(val, max);
    return res;
}

#endif //!__MIN_MAX_HPP__
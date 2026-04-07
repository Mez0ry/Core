#ifndef __BASE_HPP__
#define __BASE_HPP__
#include <memory>
#include <cstdint>

template <typename TObj>
using Ref = std::shared_ptr<TObj>;

template <typename TObj>
using Scope  = std::unique_ptr<TObj>;

template <typename TObj, typename ... TArgs >
constexpr auto MakeReference(TArgs&& ... args ){
    return std::make_shared<TObj>(std::forward<TArgs>(args) ...);
}

template <typename TObj, typename TDeleter>
Ref<TObj> MakeReference(TObj* ptr, TDeleter deleter) {
    return std::shared_ptr<TObj>(ptr, deleter);
}

template <typename TObj, typename ... TArgs >
constexpr auto MakeScope(TArgs&& ... args ){
    return std::make_unique<TObj>(std::forward<TArgs>(args) ...);
}

#endif //!__BASE_HPP__
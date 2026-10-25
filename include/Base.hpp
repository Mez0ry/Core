#ifndef __BASE_HPP__
#define __BASE_HPP__
#include <memory>
#include <cstdint>
#include "Opengl.hpp"

#define BASE_FWD_DECLARE_CLASS(class_name) class class_name;
#define BASE_FWD_DECLARE_STRUCT(struct_name) struct struct_name;

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

using bytes_t = const void*;

#endif //!__BASE_HPP__
#ifndef __FORMATERS_HPP__
#define __FORMATERS_HPP__

#include <spdlog/formatter.h>
#include <glm/glm.hpp>

template <>
struct fmt::formatter<glm::vec2> {
    constexpr auto parse(fmt::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const glm::vec2& v, fmt::format_context& ctx) const{
        return fmt::format_to(ctx.out(), "({}, {})", v.x, v.y);
    }
};
 
#endif //!__FORMATERS_HPP__
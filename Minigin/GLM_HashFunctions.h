#pragma once
#include <glm.hpp>
#include <functional>

namespace std {
    template <>
    struct hash<glm::vec2> {
        std::size_t operator()(const glm::vec2& v) const noexcept {
            std::hash<float> hasher;
            size_t h1 = hasher(v.x);
            size_t h2 = hasher(v.y);
            return h1 ^ (h2 << 1);
        }
    };
}

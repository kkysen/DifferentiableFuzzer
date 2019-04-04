//
// Created by Khyber on 3/16/2019.
//

#pragma once

#include "src/share/common/numbers.h"

#include <type_traits>

namespace math {
    
    template <typename T>
    constexpr const T& min(const T& a, const T& b) noexcept {
        return a < b ? a : b;
    }
    
    template <typename T>
    constexpr const T& max(const T& a, const T& b) noexcept {
        return a > b ? a : b;
    }
    
    template <typename T>
    constexpr T abs(T t) noexcept {
        return t < 0 ? -t : t;
    }
    
    template <typename A, typename B>
    constexpr std::common_type_t<A, B> gcd(A a, B b) noexcept {
        return a == 0 ? abs(b) : b == 0 ? abs(a) : gcd(b, a % b);
    }
    
    template <typename A, typename B>
    constexpr std::common_type_t<A, B> lcm(A a, B b) noexcept {
        return (a == 0 || b == 0) ? 0 : (abs(a) / gcd(a, b)) * abs(b);
    }
    
    template <typename T1, typename... T2>
    constexpr size_t lcmSizeOf() noexcept {
        return lcm(sizeof(T1), lcmSizeOf<T2...>());
    }
    
    template <typename A, typename B>
    constexpr std::common_type_t<A, B> divUp(A dividend, B divisor) noexcept {
        return (dividend / divisor) + (dividend % divisor == 0);
    }
    
    constexpr size_t minBytesForBits(size_t bits) noexcept {
        return math::divUp(bits, numBits<u8>());
    }
    
    template <typename A, typename B>
    constexpr std::common_type_t<A, B> multipleGreaterThan(A multiple, B greaterThan) noexcept {
        return multiple > greaterThan ? multiple : multiple + multipleGreaterThan(multiple, greaterThan - multiple);
    }
    
    
}

//
// Created by Khyber on 6/12/2019.
//

#pragma once

#include <string>

namespace stde::strings {
    
    template <typename T, class Traits = std::char_traits<T>, class Allocator = std::allocator<T>>
    std::basic_string<T, Traits, Allocator> operator+(std::basic_string<T, Traits, Allocator>&& lhs, std::basic_string_view<T, Traits> rhs) {
        return std::move(lhs.append(rhs.data(), rhs.size()));
    }
    
    template <typename T, class Traits = std::char_traits<T>, class Allocator = std::allocator<T>>
    std::basic_string<T, Traits, Allocator>& operator+(std::basic_string_view<T, Traits> lhs, std::basic_string<T, Traits, Allocator>&& rhs) {
        return std::move(rhs.insert(0, lhs.data(), lhs.size()));
    }
    
    template <typename T, class Traits = std::char_traits<T>, class Allocator = std::allocator<T>>
    std::basic_string<T, Traits, Allocator> operator+(const std::basic_string<T, Traits, Allocator>& lhs, std::basic_string_view<T, Traits> rhs) {
        std::basic_string<T, Traits, Allocator> s;
        s.reserve(lhs.size() + rhs.size());
        s.append(lhs);
        s.append(rhs.data(), rhs.size());
        return s;
    }
    
    template <typename T, class Traits = std::char_traits<T>, class Allocator = std::allocator<T>>
    std::basic_string<T, Traits, Allocator>& operator+(std::basic_string_view<T, Traits> lhs, const std::basic_string<T, Traits, Allocator>& rhs) {
        std::basic_string<T, Traits, Allocator> s;
        s.reserve(lhs.size() + rhs.size());
        s.append(lhs.data(), lhs.size());
        s.append(rhs);
        return s;
    }
    
}

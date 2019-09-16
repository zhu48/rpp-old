#ifndef DYNAMIC_SPAN_HPP
#define DYNAMIC_SPAN_HPP

#include <cstdint>

namespace rpp {

    template<typename T> struct dynamic_span {
        using iterator = T*;
        using const_iterator = const T*;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        iterator const    first;
        const std::size_t num;

        constexpr iterator begin() noexcept;
        constexpr const_iterator begin() const noexcept;
        constexpr const_iterator cbegin() const noexcept;

        constexpr reverse_iterator rbegin() noexcept;
        constexpr const_reverse_iterator rbegin() const noexcept;
        constexpr const_reverse_iterator crbegin() const noexcept;

        constexpr iterator end() noexcept;
        constexpr const_iterator end() const noexcept;
        constexpr const_iterator cend() const noexcept;

        constexpr reverse_iterator rend() noexcept;
        constexpr const_reverse_iterator rend() const noexcept;
        constexpr const_reverse_iterator crend() const noexcept;
    };

}

#include "dynamic_span.ipp"

#endif // #ifndef DYNAMIC_SPAN_HPP

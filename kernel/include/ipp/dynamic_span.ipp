
namespace rpp {

    template<typename T> constexpr
    typename dynamic_span<T>::iterator
    dynamic_span<T>::begin() noexcept {
        return first;
    }

    template<typename T> constexpr
    typename dynamic_span<T>::const_iterator
    dynamic_span<T>::begin() const noexcept {
        return first;
    }

    template<typename T> constexpr
    typename dynamic_span<T>::const_iterator
    dynamic_span<T>::cbegin() const noexcept {
        return first;
    }

    template<typename T> constexpr
    typename dynamic_span<T>::reverse_iterator
    dynamic_span<T>::rbegin() noexcept {
        return first + num;
    }

    template<typename T> constexpr
    typename dynamic_span<T>::const_reverse_iterator
    dynamic_span<T>::rbegin() const noexcept {
        return first + num;
    }

    template<typename T> constexpr
    typename dynamic_span<T>::const_reverse_iterator
    dynamic_span<T>::crbegin() const noexcept {
        return first + num;
    }

    template<typename T> constexpr
    typename dynamic_span<T>::iterator
    dynamic_span<T>::end() noexcept {
        return first + num;
    }

    template<typename T> constexpr
    typename dynamic_span<T>::const_iterator
    dynamic_span<T>::end() const noexcept {
        return first + num;
    }

    template<typename T> constexpr
    typename dynamic_span<T>::const_iterator
    dynamic_span<T>::cend() const noexcept {
        return first + num;
    }

    template<typename T> constexpr
    typename dynamic_span<T>::reverse_iterator
    dynamic_span<T>::rend() noexcept {
        return first - 1;
    }

    template<typename T> constexpr
    typename dynamic_span<T>::const_reverse_iterator
    dynamic_span<T>::rend() const noexcept {
        return first - 1;
    }

    template<typename T> constexpr
    typename dynamic_span<T>::const_reverse_iterator
    dynamic_span<T>::crend() const noexcept {
        return first - 1;
    }

}

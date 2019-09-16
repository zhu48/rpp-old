#ifndef DYNAMIC_SPAN_HPP
#define DYNAMIC_SPAN_HPP

#include <cstdint>

namespace rpp {

    template<typename T> struct dynamic_span {
        T* const          begin;
        const std::size_t size;
    };

}

#endif // #ifndef DYNAMIC_SPAN_HPP

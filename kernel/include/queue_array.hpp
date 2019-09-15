#ifndef QUEUE_ARRAY_HPP
#define QUEUE_ARRAY_HPP

#include <array>

namespace rpp {

    template<typename T, std::size_t Size> class queue_array : public std::array<T,Size> {
        private:
            std::size_t back_idx = 0;

        public:
            void push_back( const T& value );

            void push_back( T&& value );

            void pop_back();
    };

}

#include "queue_array.ipp"

#endif // #ifndef QUEUE_ARRAY_HPP

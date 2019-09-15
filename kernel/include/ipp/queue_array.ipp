
namespace rpp {

    template<typename T, std::size_t Size> void queue_array<T,Size>::push_back( const T& value ) {
        if ( back_idx < Size ) {
            (*this)[back_idx] = value;
            ++back_idx;
        }
    }

    template<typename T, std::size_t Size> void queue_array<T,Size>::push_back( T&& value ) {
        if ( back_idx < Size ) {
            (*this)[back_idx] = value;
            ++back_idx;
        }
    }

    template<typename T, std::size_t Size> void queue_array<T,Size>::pop_back( void ) {
        if ( back_idx > 0 ) --back_idx;
    }

}

#include <tuple>
#include <iostream>

#include "scheduler.hpp"

void print_tid( void* const arg ) {
    std::cout << "thread " << *static_cast<int*>( arg ) << std::endl;
}

int main( int argc, char* argv[] ) {
    std::array<rpp::decision_data,4> dec_arr;

    rpp::run(
        rpp::dynamic_span<rpp::decision_data>{
            &(dec_arr.data()[0]),
            std::tuple_size_v<decltype(dec_arr)>
        }
    );

    return -1;
}

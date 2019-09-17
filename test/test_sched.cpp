#include <tuple>
#include <iostream>

#include "scheduler.hpp"

void print_tid( void* const arg ) {
    std::cout << "thread " << *static_cast<int*>( arg ) << std::endl;
}

int main( int argc, char* argv[] ) {
    std::array<int,4> args = { 0, 1, 2, 3 };
    std::array<rpp::thread,4> thrd_arr = {
        rpp::thread( print_tid, &(args[0]), nullptr ),
        rpp::thread( print_tid, &(args[1]), nullptr ),
        rpp::thread( print_tid, &(args[2]), nullptr ),
        rpp::thread( print_tid, &(args[3]), nullptr )
    };
    std::array<rpp::decision_data,4> dec_arr = {
        rpp::decision_data{ &(thrd_arr[0]), 0 },
        rpp::decision_data{ &(thrd_arr[1]), 0 },
        rpp::decision_data{ &(thrd_arr[2]), 0 },
        rpp::decision_data{ &(thrd_arr[3]), 0 }
    };

    rpp::run(
        rpp::dynamic_span<rpp::decision_data>{
            &(dec_arr.data()[0]),
            std::tuple_size_v<decltype(dec_arr)>
        }
    );

    return -1;
}

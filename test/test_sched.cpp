#include <array>
#include <tuple>

#include "scheduler.hpp"

void do_work( void* const arg ) {
    int i = *reinterpret_cast<int*>( arg );
}

int main( int argc, char* argv[] ) {
    std::array<int,4> args = { 0, 1, 2, 3 };
    std::array<rpp::thread,4> thrd_arr = {
        rpp::thread( do_work, &(args[0]), &args[0] ),
        rpp::thread( do_work, &(args[1]), &args[1] ),
        rpp::thread( do_work, &(args[2]), &args[2] ),
        rpp::thread( do_work, &(args[3]), &args[3] )
    };
    std::array<rpp::decision_data,4> dec_arr = {
        rpp::decision_data{ &(thrd_arr[0]), 0 },
        rpp::decision_data{ &(thrd_arr[1]), 0 },
        rpp::decision_data{ &(thrd_arr[2]), 0 },
        rpp::decision_data{ &(thrd_arr[3]), 0 }
    };

    rpp::run( dec_arr );

    return -1;
}

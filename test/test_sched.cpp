#include <iostream>

#include "scheduler.hpp"

void print_tid( void* const arg ) {
    std::cout << "thread " << *static_cast<int*>( arg ) << std::endl;
}

int main( int argc, char* argv[] ) {
    rpp::scheduler<2> cpu0;

    decltype(cpu0)::tid_t thrd_0_id;
    thrd_0_id = cpu0.add_thread( rpp::thread( print_tid, &thrd_0_id ) );

    decltype(cpu0)::tid_t thrd_1_id;
    thrd_1_id = cpu0.add_thread( rpp::thread( print_tid, &thrd_1_id ) );

    cpu0.run();

    return -1;
}

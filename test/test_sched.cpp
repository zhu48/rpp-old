#include <iostream>

#include "scheduler.hpp"

void print_tid( void* const arg ) {
    std::cout << "thread " << *static_cast<int*>( arg ) << std::endl;
}

int main( int argc, char* argv[] ) {
    rpp::scheduler cpu0;

    std::size_t thrd_0_id = 0;
    rpp::thread thrd_0( print_tid, &thrd_0_id );
    cpu0.add_thread( thrd_0 );

    std::size_t thrd_1_id = 1;
    rpp::thread thrd_1( print_tid, &thrd_1_id );
    cpu0.add_thread( thrd_0 );

    cpu0.run();

    return -1;
}

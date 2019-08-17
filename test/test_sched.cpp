#include <iostream>

#include "scheduler.hpp"

void print_tid( void* const arg ) {
    std::cout << "thread " << *static_cast<int*>( arg ) << std::endl;
}

int main( int argc, char* argv[] ) {
    rpp::scheduler<2> cpu0;

    auto thrd_0_id = cpu0.add_thread( rpp::thread( print_tid, nullptr ) );
    auto thrd_1_id = cpu0.add_thread( rpp::thread( print_tid, nullptr ) );

    cpu0.run();

    return -1;
}

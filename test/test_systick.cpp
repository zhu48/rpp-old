#include <chrono>

#include "systick.hpp"

std::chrono::seconds uptime_s{ 0 };

void tick() {
    ++uptime_s;
}

int main( int argc, char* argv[] ) {
    portable::systick::init( portable::systick::period_base::us_3, 333333, tick );

    while (true) {
        // spin
    }
}

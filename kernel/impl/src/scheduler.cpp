#include "scheduler.hpp"

using namespace rpp;

bool scheduler::decision_data::operator==( const decision_data& rhs ) const {
    return this->prio == rhs.prio;
}

bool scheduler::decision_data::operator!=( const decision_data& rhs ) const {
    return this->prio != rhs.prio;
}

bool scheduler::decision_data::operator<( const decision_data& rhs ) const {
    return this->prio < rhs.prio;
}

bool scheduler::decision_data::operator>( const decision_data& rhs ) const {
    return this->prio > rhs.prio;
}

bool scheduler::decision_data::operator>=( const decision_data& rhs ) const {
    return this->prio >= rhs.prio;
}

bool scheduler::decision_data::operator<=( const decision_data& rhs ) const {
    return this->prio <= rhs.prio;
}

void scheduler::add_thread( thread& new_thread ) {
    data.push( decision_data{ &new_thread, 0 } );
}

[[noreturn]] void scheduler::run( void ) noexcept {
    while(true);
}

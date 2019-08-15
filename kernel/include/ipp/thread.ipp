
namespace rpp {

    constexpr thread::thread( entry_fn_t entry, void* const stack ) noexcept :
        status( status_t::ready ),
        context{ stack, stack }
    {
        // nothing
    }

};

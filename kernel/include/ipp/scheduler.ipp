namespace rpp {

    template<std::size_t MaxThreads>
    typename scheduler<MaxThreads>::tid_t
    scheduler<MaxThreads>::add_thread(
        thread&& new_thread
    ) noexcept {
        return invalid_tid;
    }

}

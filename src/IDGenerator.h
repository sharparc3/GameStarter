#pragma once

#include <iostream>
#include <atomic>
#include <functional>

// UniqueIDGenerator template
template <typename T>
struct UniqueIDGenerator {
    std::atomic<T> _id;
    std::function<const T(const T&)> _nexter;

    template <typename NEXT>
    UniqueIDGenerator(const T& init, const NEXT& nexter) {
        _id.store(init, std::memory_order::memory_order_release);
        _nexter = nexter;
    }

    const T fetch_add() {
        T oldVal;
        T newVal;
        do {
            oldVal = _id.load(std::memory_order::memory_order_acquire);
            newVal = _nexter(oldVal);
        } while (!_id.compare_exchange_weak(oldVal, newVal, std::memory_order::memory_order_release, std::memory_order::memory_order_acquire));
        return oldVal;
    }
};

// the global ID generator instance
static UniqueIDGenerator<int> globalIDGenerator(0, [](const int& currentID) -> int {
    return currentID + 1;
    });

// the global function to get unique IDs
static int getUniqueID() {
    return globalIDGenerator.fetch_add();
}
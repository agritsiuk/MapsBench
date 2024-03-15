#pragma once

#include <cstdint>

struct Key {
    std::int64_t client;
    std::int64_t account;
    std::int64_t instrument;

    bool operator==(const Key& other) const {
        return client == other.client && account == other.account && instrument == other.instrument;
    }
};

struct Value {
    std::uint64_t amountBuy;
    std::uint64_t amountSell;
};

struct Record {
    Value online;
    std::uint64_t snapshotNo;
    Value snapshot;
};

template<typename T> void hashCombine(std::size_t & seed, T const& v) {
    seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<>
struct std::hash<Key> {
    std::size_t operator()(const Key& key) const {
        std::size_t seed{};
        hashCombine(seed, key.client);
        hashCombine(seed, key.account);
        hashCombine(seed, key.instrument);
        return seed;
    }
};
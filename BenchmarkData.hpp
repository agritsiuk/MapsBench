#pragma once

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <stdexcept>

struct BenchmarkData {
    std::uint64_t min;
    std::uint64_t p50;
    std::uint64_t p90;
    std::uint64_t p95;
    std::uint64_t p99;
    std::uint64_t p999;
    std::uint64_t max;
};

template<class V>
inline BenchmarkData benchmarkData(V& samples, std::size_t expectedCount) {
    if (samples.size() != expectedCount) {
        throw std::runtime_error("Invalid count");
    }

    BenchmarkData result{};

    std::sort(samples.begin(), samples.end());
    result.min = samples.front();
    result.p50 = samples[samples.size() * 0.5];
    result.p90 = samples[samples.size() * 0.9];
    result.p95 = samples[samples.size() * 0.95];
    result.p99 = samples[samples.size() * 0.99];
    result.p999 = samples[samples.size() * 0.999];
    result.max = samples.back();

    return result;
}

inline void printBenchmarkData(const BenchmarkData& data) {
    printf(" min: %llu\n", data.min);
    printf("  50: %llu\n", data.p50);
    printf("  90: %llu\n", data.p90);
    printf("  95: %llu\n", data.p95);
    printf("  99: %llu\n", data.p99);
    printf("99.9: %llu\n", data.p999);
    printf(" max: %llu\n", data.max);
};
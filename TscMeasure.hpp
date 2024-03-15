#pragma once

#include <x86intrin.h>

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

class TscMeasure {
   public:
    TscMeasure() : _start{__rdtsc()} {}

    std::uint64_t duration() const {
        std::uint64_t finish = __rdtsc();
        std::int64_t duration = static_cast<std::int64_t>(finish - _start - _rdtscCost);
        return duration >= 0 ? duration : 0;
    }

    std::uint64_t operator()() const {
        return duration();
    }

   private:
    static std::uint64_t estimateRdtscCost() {
        std::vector<std::uint64_t> samples;

        for (int i = 0; i < 100000; ++i) {
            const auto tsc1 = __rdtsc();
            const auto tsc2 = __rdtsc();
            samples.emplace_back(tsc2 - tsc1);
        }

        std::sort(samples.begin(), samples.end());
        return samples[samples.size() / 2];
    }

   public:
    std::uint64_t _start{};
    static std::uint64_t _rdtscCost;
};

std::uint64_t TscMeasure::_rdtscCost = TscMeasure::estimateRdtscCost();
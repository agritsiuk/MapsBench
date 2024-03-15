#pragma once

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <absl/container/flat_hash_map.h>

#include "BenchmarkData.hpp"
#include "Constants.hpp"
#include "Data.hpp"
#include "TscMeasure.hpp"

class AbseilFlatHashMapBench {
   public:
    void run() {
        std::vector<std::uint64_t> samples;
        samples.reserve(kTotalRecords);
        _map.reserve(kTotalRecords);
        TscMeasure measure{};
        _totalDuration = {};

        printf("AbseilFlatHashMap\n-------------------\n");
        printf("- populate:\n");
        for (std::int64_t i = 0; i < kTotalRecords; ++i) {
            Key key{1, 2, i};
            measure = {};

            auto [iter, inserted] = _map.try_emplace(key);
            if (inserted) {
                auto& record = iter->second.online;
                record.amountBuy = i;
                record.amountSell = i + 2;
            } else {
                abort();
            }

            samples.emplace_back(measure.duration());
        }
        printBenchmarkData(benchmarkData(samples, kTotalRecords));
        samples.clear();

        printf("- update:\n");
        for (std::int64_t i = 0; i < kTotalRecords; ++i) {
            Key key{1, 2, i};
            measure = {};
            const auto iter = _map.find(key);
            if (iter != _map.end()) {
                auto& record = iter->second.online;

                if (record.amountBuy != i || record.amountSell != i + 2) {
                    abort;
                }

                record.amountBuy = i * 2;
                record.amountSell = i * 3;
            } else {
                abort();
            }
            samples.emplace_back(measure.duration());
        }
        printBenchmarkData(benchmarkData(samples, kTotalRecords));
        samples.clear();

        printf("- traversal:\n");
        for (std::int64_t i = 0; i < kTotalRecords; ++i) {
            Key key{1, 2, i};
            measure = {};
            const auto iter = _map.find(key);

            if (iter == _map.end()) {
                abort();
            }

            auto& record = iter->second.online;

            if (record.amountBuy != i * 2 || record.amountSell != i * 3) {
                abort();
            }

            samples.emplace_back(measure.duration());
        }
        printBenchmarkData(benchmarkData(samples, kTotalRecords));
        samples.clear();

        printf("- total duration: %llu\n\n", _totalDuration());
    }

   private:
    absl::flat_hash_map<Key, Record> _map{};
    TscMeasure _totalDuration{};
};
#pragma once

#include <cstdint>
#include <cstdio>
#include <immer/map.hpp>
#include <immer/map_transient.hpp>
#include <iostream>

#include "BenchmarkData.hpp"
#include "Constants.hpp"
#include "Data.hpp"
#include "TscMeasure.hpp"

class ImmerBench {
   public:
    void run() {
        std::vector<std::uint64_t> samples;
        samples.reserve(kTotalRecords);
        TscMeasure measure{};
        _totalDuration = {};

        printf("Immer\n-------------------\n");

        printf("- initial insert:\n");

        auto transient = _map.transient();
        for (std::int64_t i = 0; i < kTotalRecords; ++i) {
            Key key{1, 2, i};
            measure = {};
            transient.insert({key, Value(i, i + 2)});
            samples.emplace_back(measure.duration());
        }
        printBenchmarkData(benchmarkData(samples, kTotalRecords));
        samples.clear();

        measure = {};
        _map = transient.persistent();
        printf("- persistent duration: %llu\n", measure.duration());

        measure = {};
        transient = _map.transient();
        printf("- transient duration: %llu\n", measure.duration());

        printf("- update:\n");
        for (std::int64_t i = 0; i < kTotalRecords; ++i) {
            Key key{1, 2, i};
            measure = {};
            auto* value = transient.find(key);

            if (value) {
                transient.update(key, [i](auto copy) {
                    copy.amountBuy = i * 2;
                    copy.amountSell = i * 3;
                    return copy;
                });
            } else {
                std::printf("key for %lld not found\n", key.instrument);
                abort();
            }

            samples.emplace_back(measure.duration());
        }
        printBenchmarkData(benchmarkData(samples, kTotalRecords));
        samples.clear();

        measure = {};
        _map = transient.persistent();
        printf("- persistent duration: %llu\n", measure.duration());

        printf("- traversal:\n");
        for (std::int64_t i = 0; i < kTotalRecords; ++i) {
            Key key{1, 2, i};
            measure = {};
            const auto* value = _map.find(key);

            if (value) {
                if (value->amountBuy != i * 2 || value->amountSell != i * 3) {
                    printf(
                        "Value mismatch, expected amountBuy: %lld, actual amountBuy: %llu, expected amountSell: %lld, "
                        "actual amountSell %llu\n",
                        i * 2, value->amountBuy, i * 3, value->amountSell);
                    abort();
                }
            } else {
                printf("Not found\n");
                abort();
            }

            samples.emplace_back(measure.duration());
        }
        printBenchmarkData(benchmarkData(samples, kTotalRecords));
        samples.clear();

        printf("- total duration: %llu\n\n", _totalDuration());
    }

   private:
    immer::map<Key, Value> _map{};
    TscMeasure _totalDuration{};
};
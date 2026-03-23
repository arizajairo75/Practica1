#pragma once
#include <chrono>

using TimePoint = std::chrono::high_resolution_clock::time_point;

TimePoint startTimer() {
    return std::chrono::high_resolution_clock::now();
}

double stopTimer(TimePoint start) {
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
}
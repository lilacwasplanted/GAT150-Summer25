#pragma once
#include <cstdlib>
#include <random>
using namespace std;

namespace viper::random {
    inline mt19937& generator() {
        static random_device rd;
        static mt19937 gen(rd());
        return gen;
    }

    inline void seed(unsigned int value) {
        generator().seed(value);
    }

    inline int getInt(int min, int max) {
        uniform_int_distribution<> dist(min, max);
        return dist(generator());
    }

    inline int getInt(int max) {
        return getInt(0, max - 1);
    }

    inline int getInt() {
        static uniform_int_distribution<> dist;
        return dist(generator());
    }

    template <typename T = float>
    inline T getReal(T min, T max) {
        uniform_real_distribution<T> dist(min, max);
        return dist(generator());
    }

    template <typename T = float>
    inline T getReal(T max) {
        return getReal(static_cast<T>(0), static_cast<T>(max));
    }

    template <typename T = float>
    inline T getReal() {
        static uniform_real_distribution<T> dist(static_cast<T>(0), static_cast<T>(1));
        return dist(generator());
    }

    inline bool getBool() {
        static bernoulli_distribution dist(0.5);
        return dist(generator());
    }
}
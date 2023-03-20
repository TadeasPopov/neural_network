#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <utility>

inline float get_random_float(float from = 0.f, float to = 1.f) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(from, to);
	return distribution(gen);
}

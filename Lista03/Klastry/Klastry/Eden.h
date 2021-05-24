#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>
#include <climits>
#include <cmath>
#include <math.h>
#include <string>
#include <stdint.h>


class Eden
{
	const size_t N;
	const size_t NN;
	size_t STEPS = 1000;
	size_t TOTAL_ITER = 100000;
	double offset = std::sqrt(std::sqrt(2));
	double offsetMultiplier = offset;
	std::vector<std::vector<bool>> arr;
	//std::unique_ptr<bool[]> arr;
	void write_bmp(const char* path, const unsigned width, const unsigned height, const bool* const data);
	void write_bmp_2D(const char* path, const unsigned width, const unsigned height, const std::vector<std::vector<bool>> data);
public:
	Eden(size_t N);
	void Licz();
};


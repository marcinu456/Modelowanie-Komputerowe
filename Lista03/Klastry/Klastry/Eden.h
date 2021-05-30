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
#include "Cell.h"

class Eden
{
	const size_t N;
	size_t STEPS = 1000;
	size_t TOTAL_ITER = 100000;
	double offset = std::sqrt(std::sqrt(2));
	double offsetMultiplier = offset;
	std::vector<std::vector<bool>> arr;
	std::vector<std::vector<int>> cluster;
	std::vector<int> liveCell;
	void write_bmp(const char* path, const unsigned width, const unsigned height, const bool* const data);
	void write_bmp_2D(const char* path, const unsigned width, const unsigned height, const std::vector<std::vector<bool>> data);
	void write_bmp_2D_int(const char* path, const unsigned width, const unsigned height, const std::vector<std::vector<int>> data);
	double find_r();
	
public:
	Eden(size_t N);
	void Licz();
};


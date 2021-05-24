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




class Snow
{
	size_t TOTAL_ITER = 500;
	double offset = std::sqrt(std::sqrt(2));
	double offsetMultiplier = offset;
	void write_bmp(const char* path, const unsigned width, const unsigned height, const bool* const data);
public:
	Snow();
	void Licz(const size_t MODE) ;
};

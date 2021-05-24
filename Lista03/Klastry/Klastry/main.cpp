#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>
#include <climits>
#include <cmath>
#include <math.h>
#include <string>
#include <stdint.h>
#include "Eden.h"
# define M_PI           3.14159265358979323846  /* pi */

// task_0 code
void write_bmp(const char* path, const unsigned width, const unsigned height, const int* const data) {
	const unsigned pad = (4 - (3 * width) % 4) % 4, filesize = 54 + (3 * width + pad) * height; // horizontal line must be a multiple of 4 bytes long, header is 54 bytes
	char header[54] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0, 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };
	for (unsigned i = 0; i < 4; i++) {
		header[2 + i] = (char)((filesize >> (8 * i)) & 255);
		header[18 + i] = (char)((width >> (8 * i)) & 255);
		header[22 + i] = (char)((height >> (8 * i)) & 255);
	}
	char* img = new char[filesize];
	for (unsigned i = 0; i < 54; i++) img[i] = header[i];
	for (unsigned y = 0; y < height; y++) {
		for (unsigned x = 0; x < width; x++) {
			const int color = data[x + (height - 1 - y) * width];
			const int i = 54 + 3 * x + y * (3 * width + pad);
			img[i] = (char)(color & 255);
			img[i + 1] = (char)((color >> 8) & 255);
			img[i + 2] = (char)((color >> 16) & 255);
		}
		for (unsigned p = 0; p < pad; p++) img[54 + (3 * width + p) + y * (3 * width + pad)] = 0;
	}
	std::ofstream file(path, std::ios::out | std::ios::binary);
	file.write(img, filesize);
	file.close();
	delete[] img;
}

void write_bmp(const char* path, const unsigned width, const unsigned height, const bool* const data) {
	const unsigned pad = (4 - (3 * width) % 4) % 4, filesize = 54 + (3 * width + pad) * height; // horizontal line must be a multiple of 4 bytes long, header is 54 bytes
	char header[54] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0, 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };
	for (unsigned i = 0; i < 4; i++) {
		header[2 + i] = (char)((filesize >> (8 * i)) & 255);
		header[18 + i] = (char)((width >> (8 * i)) & 255);
		header[22 + i] = (char)((height >> (8 * i)) & 255);
	}
	char* img = new char[filesize];
	for (unsigned i = 0; i < 54; i++) img[i] = header[i];
	for (unsigned y = 0; y < height; y++) {
		for (unsigned x = 0; x < width; x++) {
			const int color = (data[x + (height - 1 - y) * width] ? ((((255) << 8) + 255) << 8) + 255 : 0);
			const int i = 54 + 3 * x + y * (3 * width + pad);
			img[i] = (char)(color & 255);
			img[i + 1] = (char)((color >> 8) & 255);
			img[i + 2] = (char)((color >> 16) & 255);
		}
		for (unsigned p = 0; p < pad; p++) img[54 + (3 * width + p) + y * (3 * width + pad)] = 0;
	}
	std::ofstream file(path, std::ios::out | std::ios::binary);
	file.write(img, filesize);
	file.close();
	delete[] img;
}













// task_1 code
void task_1() {
	//size_t D = 2;
	const size_t N = 1000;
	const size_t NN = N * N;
	size_t STEPS = 1000;
	size_t TOTAL_ITER = 100000;
	size_t MODE = 2;
	size_t GENERATOR = 3;
	size_t CRAWLER = 1;
	bool GENERATE_IMAGES = 1;
	bool GENERATE_DATA = 1;
	bool IGNORE_EXISTING_IMAGES = 0;
	bool IGNORE_EXISTING_FILES = 0;

	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dist(0.0, 1.0);

	double offset = std::sqrt(std::sqrt(2));
	double offsetMultiplier = offset;

	bool arr[NN] = { false };


	arr[N / 2 + NN / 2] = true;
	if (MODE == 1) {
		arr[N / 2 + 1 + NN / 2] = true;
		arr[N / 2 + 1 + NN / 2 + N] = true;
		arr[N / 2 + NN / 2 + N] = true;
	}
	else if (MODE == 2) {
		arr[N / 2 + 1 + NN / 2] = true;
		arr[N / 2 + 1 + NN / 2 + N] = true;
		arr[N / 2 + NN / 2 + N] = true;

		arr[N / 2 - 1 + NN / 2 - N] = true;
		arr[N / 2 - 1 + NN / 2] = true;
		arr[N / 2 - 1 + NN / 2 + N] = true;
		arr[N / 2 + NN / 2 - N] = true;
		arr[N / 2 + 1 + NN / 2 - N] = true;

	}


	std::string dirName_0 = "data/";
	std::filesystem::create_directory(dirName_0.c_str());
	std::string dirName_1 = dirName_0 + "dla_img_mode" + std::to_string(MODE) + "_gen" + std::to_string(GENERATOR) + "_crawl" + std::to_string(CRAWLER) + "/";
	std::filesystem::create_directory(dirName_1.c_str());

	std::string fileName = "dlaGrowth_M" + std::to_string(MODE) + "G" + std::to_string(GENERATOR) + "C" + std::to_string(CRAWLER) + ".txt";
	std::ofstream ofs;
	if (!std::filesystem::exists((dirName_0 + fileName).c_str())) ofs.open((dirName_0 + fileName).c_str(), std::ofstream::out);
	for (size_t iter = 0; iter < TOTAL_ITER; iter++) {

		double x;
		double y;
		if (GENERATOR == 0) {
			if ((iter - 2) < N / 2) {
				do {
					x = dist(gen) * (iter - 2) + (iter) / 2;
					y = dist(gen) * (iter - 2) + (iter) / 2;
				} while (arr[static_cast<size_t>(y) * N + static_cast<size_t>(x)]);
			}
			else {
				do {
					x = dist(gen) * (N - 4) + 2;
					y = dist(gen) * (N - 4) + 2;
				} while (arr[static_cast<size_t>(y) * N + static_cast<size_t>(x)]);
			}
		}
		else if (GENERATOR == 1) {
			double alpha = dist(gen) * 2 * M_PI;
			x = cos(alpha) * (N / 2 - 1) + N / 2;
			y = sin(alpha) * (N / 2 - 1) + N / 2;
		}
		else if (GENERATOR == 2) {
			switch (static_cast<size_t>(dist(gen) * 4)) {
			case 0:
				x = dist(gen) * (N - 3) + 1.5;
				y = 2;
				break;
			case 1:
				x = N - 3;
				y = dist(gen) * (N - 3) + 1.5;
				break;
			case 2:
				x = dist(gen) * (N - 3) + 1.5;
				y = N - 3;
				break;
			case 3:
				x = 2;
				y = dist(gen) * (N - 3) + 1.5;
				break;
			}
		}
		else if (GENERATOR == 3) {
			static const double translate = (1000 - sqrt(3) * 500);
			switch (static_cast<size_t>(dist(gen) * 3)) {
			case 0:
				x = dist(gen) * (N - 3) + 1.5;
				y = translate;
				break;
			case 1:
				x = dist(gen) * (N - 3) / 2 + 1.5;
				y = sqrt(3) * x + translate;
				break;
			case 2:
				x = dist(gen) * (N - 3) / 2 + 1.5 + (N - 3) / 2;
				y = -sqrt(3) * x + 1000 * sqrt(3) + translate;
				break;
			}
		}
		else if (GENERATOR == 4) {
			switch (static_cast<size_t>(dist(gen) * 2)) {
			case 0:
				x = 2;
				y = 2;
				break;
			case 1:
				x = (N - 3);
				y = (N - 3);
				break;
			}
		}

		while (static_cast<size_t>(
			arr[(static_cast<size_t>(y) - 1) * N + static_cast<size_t>(x)] +
			arr[(static_cast<size_t>(y) - 1) * N + static_cast<size_t>(x) + 1] +
			arr[(static_cast<size_t>(y)) * N + static_cast<size_t>(x) + 1] +
			arr[(static_cast<size_t>(y) + 1) * N + static_cast<size_t>(x) + 1] +
			arr[(static_cast<size_t>(y) + 1) * N + static_cast<size_t>(x)] +
			arr[(static_cast<size_t>(y) + 1) * N + static_cast<size_t>(x) - 1] +
			arr[(static_cast<size_t>(y)) * N + static_cast<size_t>(x) - 1] +
			arr[(static_cast<size_t>(y) + -1) * N + static_cast<size_t>(x) - 1]
			) < MODE + 1
			) {

			if (CRAWLER == 0) {
				double temp_x = 0;
				double temp_y = 0;
				do {
					switch (static_cast<size_t>(dist(gen) * 4)) {
					case 0:
						temp_x = x + 1;
						break;
					case 1:
						temp_y = y + 1;
						break;
					case 2:
						temp_x = x - 1;
						break;
					case 3:
						temp_y = y - 1;
						break;
					}
				} while (temp_x < 2 || temp_x > N - 3 || temp_y < 2 || temp_y > N - 3 || arr[static_cast<size_t>(y) * N + static_cast<size_t>(x)]);
				x = temp_x;
				y = temp_y;
			}
			else if (CRAWLER == 1) {
				double d = std::sqrt(pow(x - N / 2, 2) + pow(y - N / 2, 2));
				double alpha = std::asin((x - N / 2) / d);
				double beta = std::asin((y - N / 2) / d);

				double tetha = dist(gen) * M_PI * (3.0 / 4.0) - M_PI * (3.0 / 8.0);
				x -= sin(alpha + tetha);
				y -= sin(beta - tetha);
			}
		}

		arr[static_cast<size_t>(y) * N + static_cast<size_t>(x)] = true;





		if (!((iter + 1) % static_cast<long>(offset))) {
			offset *= offsetMultiplier;
			if (GENERATE_DATA) {
				/*
				unsigned long r0 = 0;
				unsigned long r1 = 0;
				unsigned long r2 = 0;
				unsigned long r3 = 0;
				while( !arr[(r0)*N + N/2]) r0++;
				while( !arr[(N/2)*N + N-1-r1]) r1++;
				while( !arr[(N-1-r2)*N + N/2]) r2++;
				while( !arr[(N/2)*N + r3]) r3++;

				unsigned long r01 = 0;
				unsigned long r12 = 0;
				unsigned long r23 = 0;
				unsigned long r30 = 0;
				while( !arr[(r01)*N + r01]) r01++;
				while( !arr[(r12)*N + N-1-r12]) r12++;
				while( !arr[(N-1-r23)*N + N-1-r23]) r23++;
				while( !arr[(N-1-r30)*N + r30]) r30++;
				double r = (2/N * (r0+r1+r2+r3) + (2*N-(r01+r12+r23+r30))*std::sqrt(2))/8.0;
				*/

				double max_radius = 0.0;
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						if (arr[i * N + j]) {
							double r = std::sqrt(pow(i - static_cast<int>(N / 2), 2) + pow(j - static_cast<int>(N / 2), 2));
							if (max_radius < r) max_radius = r;
							//std::cout << r << " " << max_radius << std::endl;
						}
					}
				}

				ofs << iter + 2 << " " << max_radius << "\n";
			}
			if (GENERATE_IMAGES) {
				std::string imgName = "dla_M" + std::to_string(MODE) + "G" + std::to_string(GENERATOR) + "C" + std::to_string(CRAWLER) + "(" + std::to_string(iter) + ").bmp";
				if (!IGNORE_EXISTING_IMAGES) {
					if (!std::filesystem::exists((dirName_1 + imgName).c_str())) {
						write_bmp((dirName_1 + imgName).c_str(), N, N, arr);
					}
				}
				else {
					write_bmp((dirName_1 + imgName).c_str(), N, N, arr);
				}
			}
		}
	}
	ofs.close();
}










// task_2 code 
void task_2() {
	const size_t N = 1000;
	const size_t NN = N * N;
	size_t STEPS = 1000;
	size_t TOTAL_ITER = 490;
	size_t MODE = 2;
	bool GENERATE_IMAGES = 1;
	bool GENERATE_DATA = 0;
	bool IGNORE_EXISTING_IMAGES = 1;
	bool IGNORE_EXISTING_FILES = 0;

	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dist(0.0, 1.0);

	double offset = std::sqrt(std::sqrt(2));
	double offsetMultiplier = offset;

	bool arr[NN] = { false };


	arr[N / 2 + NN / 2] = true;
	if (MODE == 2) {
		arr[N / 2 + 1 + NN / 2] = true;
		arr[N / 2 + 1 + NN / 2 + N] = true;
		arr[N / 2 + NN / 2 + N] = true;
	}

	std::string dirName_0 = "data/";
	std::filesystem::create_directory(dirName_0.c_str());
	std::string dirName_1 = dirName_0 + "snow_img_mode" + std::to_string(MODE) + "/";
	std::filesystem::create_directory(dirName_1.c_str());

	std::string fileName = "snowGrowth_" + std::to_string(MODE) + ".txt";
	std::ofstream ofs;
	if (!std::filesystem::exists((dirName_0 + fileName).c_str())) ofs.open((dirName_0 + fileName).c_str(), std::ofstream::out);
	for (size_t iter = 0; iter < TOTAL_ITER; iter++) {


		std::vector<bool*> potent;
		for (int i = 1; i < N - 1; i++) {
			for (int j = 1; j < N - 1; j++) {
				size_t neighbors = static_cast<size_t>(
					arr[i * N + j + 1] +
					arr[i * N + j - 1] +
					arr[(i - 1) * N + j] +
					arr[(i + 1) * N + j] +
					arr[(i - 1) * N + j + (i % 2 ? 1 : -1)] +
					arr[(i + 1) * N + j + (i % 2 ? 1 : -1)]
					);

				if (MODE == 0) { if (neighbors == 1) { potent.push_back(&arr[i * N + j]); } }
				if (MODE == 1) { if (neighbors == 2) { potent.push_back(&arr[i * N + j]); } }
				if (MODE == 2) { if (neighbors > 0) { potent.push_back(&arr[i * N + j]); } }
				

			}
		}

		for (int i = 0; i < potent.size(); i++) {
			*potent[i] = true;
		}



		if (!((iter + 1) % static_cast<long>(offset))) {
			offset *= offsetMultiplier;
			if (GENERATE_DATA) {

			}
			if (GENERATE_IMAGES) {
				std::string imgName = "snow(" + std::to_string(iter) + ").bmp";
				if (IGNORE_EXISTING_FILES) {
					if (!std::filesystem::exists((dirName_1 + imgName).c_str())) {
						write_bmp((dirName_1 + imgName).c_str(), N, N, arr);
					}
				}
				else {
					write_bmp((dirName_1 + imgName).c_str(), N, N, arr);
				}
			}
		}
	}
	ofs.close();
}







int main() {
	const int TASK_PART = 0;

	Eden eden(1000);
	eden.Licz();
	//eden.run();

	//if (TASK_PART == 0) task_0();
	if (TASK_PART == 1) task_1();
	if (TASK_PART == 2) task_2();

	return 0;
}
#include "Eden.h"

Eden::Eden(size_t N):
	N(N), NN(N*N)//, arr(std::make_unique<bool[]>(NN))
{
	arr.reserve(NN);
	for (int i = 0; i < NN; i++)
	{
			arr[i].reserve(N);		
	}
	/*	for (int i = 0; i < NN; i++)
	{
			arr[i] = false;
	}*/
}

void Eden::write_bmp(const char* path, const unsigned width, const unsigned height, const bool* const data) {
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

void Eden::write_bmp_2D(const char* path, const unsigned width, const unsigned height, const std::vector<std::vector<bool>> data) {
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

void Eden::Licz()
{
	/*
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dist(0.0, 1.0);

	std::vector<bool*> alive;
	alive.reserve(NN);
	alive.resize(NN);
	size_t potentCount = 0;
	size_t matureIndex = NN - 1;

	alive[potentCount++] = &arr[N / 2 + NN / 2];
	*alive[0] = true;

	std::string dirName_0 = "data/";
	std::filesystem::create_directory(dirName_0.c_str());
	std::string dirName_1 = dirName_0 + "eden_img/";
	std::filesystem::create_directory(dirName_1.c_str());

	std::string fileName = "edenGrowth.txt";
	std::ofstream ofs((dirName_0 + fileName).c_str(), std::ofstream::out);
	for (size_t iter = 0; iter < TOTAL_ITER; iter++) {
		bool foundPotent = false;
		int potent;
		do {
			potent = dist(gen) * potentCount;
			bool* neighbour_U = (alive[potent] - N * sizeof(bool));
			bool* neighbour_D = (alive[potent] + N * sizeof(bool));
			bool* neighbour_L = (alive[potent] - sizeof(bool));
			bool* neighbour_R = (alive[potent] + sizeof(bool));
			if (!(*neighbour_U && *neighbour_D && *neighbour_L && *neighbour_R)) {
				foundPotent = true;
				bool* neighbours[4];
				int neighbourCount = 0;
				if (!*neighbour_U) {
					neighbours[neighbourCount++] = neighbour_U;
				}
				if (!*neighbour_D) {
					neighbours[neighbourCount++] = neighbour_D;
				}
				if (!*neighbour_L) {
					neighbours[neighbourCount++] = neighbour_L;
				}
				if (!*neighbour_R) {
					neighbours[neighbourCount++] = neighbour_R;
				}
				int i = dist(gen) * neighbourCount;
				*neighbours[i] = true;
				alive[potentCount++] = neighbours[i];

			}
			else {
				alive[matureIndex--] = alive[potent];
				alive[potent] = alive[--potentCount];
			}
		} while (!foundPotent);


		if (!((iter + 1) % static_cast<long>(offset))) {
			offset *= offsetMultiplier;
			if (true) {
				int x = [&]() {
					int ret = 0;
					for (int i = 0; i < N; i++) {
						for (int j = 0; j < N; j++) {
							ret += (arr[i * N + j] ? j : 0);
						}
					}
					int c = potentCount + NN - matureIndex - 1;
					return ret / (c ? c : 1);
				}();

				int y = [&]() {
					int ret = 0;
					for (int i = 0; i < N; i++) {
						for (int j = 0; j < N; j++) {
							ret += (arr[i * N + j] ? i : 0);
						}
					}
					int c = potentCount + NN - matureIndex - 1;
					return ret / (c ? c : 1);
				}();

				unsigned long r0 = 0;
				unsigned long r1 = 0;
				unsigned long r2 = 0;
				unsigned long r3 = 0;
				while (arr[(y + r0) * N + x]) r0++;
				while (arr[(y)*N + x + r1]) r1++;
				while (arr[(y - r2) * N + x]) r2++;
				while (arr[(y)*N + x - r3]) r3++;

				unsigned long r01 = 0;
				unsigned long r12 = 0;
				unsigned long r23 = 0;
				unsigned long r30 = 0;
				while (arr[(y + r01) * N + x + r01]) r01++;
				while (arr[(y - r12) * N + x + r12]) r12++;
				while (arr[(y - r23) * N + x - r23]) r23++;
				while (arr[(y + r30) * N + x - r30]) r30++;
				double r = (r0 + r1 + r2 + r3 + (r01 + r12 + r23 + r30) * std::sqrt(2)) / 8.0;

				ofs << iter + 2 << " " << r << "\n";
			}
			if (true) {
				std::string imgName = "eden(" + std::to_string(iter) + ").bmp";
				write_bmp_2D((dirName_1 + imgName).c_str(), N, N, arr);

			}

		}
	}
	ofs.close();*/
}
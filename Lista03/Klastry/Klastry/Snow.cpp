#include "Snow.h"

Snow::Snow()
{
}

void Snow::write_bmp(const char* path, const unsigned width, const unsigned height, const bool* const data) {
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



void Snow::Licz(const size_t MODE)
{
	const size_t N = 1000;
	const size_t NN = N * N;
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dist(0.0, 1.0);
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
			std::string imgName = "snow(" + std::to_string(iter) + ").bmp";
			write_bmp((dirName_1 + imgName).c_str(), N, N, arr);
		}
	}
	ofs.close();
}

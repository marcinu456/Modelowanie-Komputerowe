#include "Eden.h"

Eden::Eden(size_t N):
	N(N)
{
	arr.resize(N);
	for (int i = 0; i < N; i++)
	{
		arr[i].resize(N);
	}
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
			const int color = (data[x][y] ? ((((255) << 8) + 255) << 8) + 255 : 0);
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

void Eden::write_bmp_2D_int(const char* path, const unsigned width, const unsigned height, const std::vector<std::vector<int>> data)
{
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
			const int color = data[x][y];
			if (color > 100)
			{
				int i = color;
			}
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
	
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dist(0.0, 1.0);

	std::vector<Cell> alive;
	Cell cell;
	alive.push_back(cell);

	alive[0].currentState = true;
	alive[0].activeNeighbors = 0;
	alive[0].posX = N / 2;
	alive[0].posY = N / 2;

	std::string dirName_0 = "data/";
	std::filesystem::create_directory(dirName_0.c_str());
	std::string dirName_1 = dirName_0 + "eden_img/";
	std::filesystem::create_directory(dirName_1.c_str());

	std::string fileName = "edenGrowth.txt";
	std::ofstream ofs((dirName_0 + fileName).c_str(), std::ofstream::out);
	int currentlive = 0;
	for (size_t iter = 0; iter < TOTAL_ITER; iter++) {
		std::uniform_int_distribution<int> dupa(0.0, currentlive);
		bool done = true;
		while (done)
		{
			int srng = (dupa(rd));

				if (alive[srng].currentState == true)
				{
					Cell srell;
					int posX = alive[srng].posX;
					int posY = alive[srng].posY;
					int rng = abs(dist(rd)) * 4;
					switch (rng)
					{
					case 0:
					{
						if (!arr[posX + 1][posY])
						{
							arr[posX + 1][posY] = true;
							alive.push_back(srell);
							alive[alive.size() - 1].currentState = true;
							alive[alive.size() - 1].activeNeighbors++;
							alive[alive.size() - 1].posX = posX+1;
							alive[alive.size() - 1].posY = posY;

							alive[srng].activeNeighbors++;


							if (alive[srng].activeNeighbors == 4)
							{
								alive[srng].currentState = false;
							}
							done = false;
							currentlive++;
							std::vector<int> helper{ posX + 1,posY };
							cluster.push_back(helper);
						}
						break;
					}
					case 1:
					{
						if (!arr[posX - 1][posY])
						{
							arr[posX - 1][posY] = true;
							alive.push_back(srell);
							alive[alive.size() - 1].currentState = true;
							alive[alive.size() - 1].activeNeighbors++;
							alive[alive.size() - 1].posX = posX - 1;
							alive[alive.size() - 1].posY = posY;

							alive[srng].activeNeighbors++;


							if (alive[srng].activeNeighbors == 4)
							{
								alive[srng].currentState = false;
							}
							done = false;
							currentlive++;
							std::vector<int> helper{ posX - 1,posY };
							cluster.push_back(helper);
						}
						break;
					}
					case 2:
					{
						if (!arr[posX][posY + 1])
						{
							arr[posX][posY + 1] = true;
							alive.push_back(srell);
							alive[alive.size() - 1].currentState = true;
							alive[alive.size() - 1].activeNeighbors++;
							alive[alive.size() - 1].posX = posX;
							alive[alive.size() - 1].posY = posY + 1;

							alive[srng].activeNeighbors++;


							if (alive[srng].activeNeighbors == 4)
							{
								alive[srng].currentState = false;
							}
							done = false;
							currentlive++;
							std::vector<int> helper{ posX,posY + 1 };
							cluster.push_back(helper);
						}
						break;
					}
					case 3:
					{
						if (!arr[posX][posY - 1])
						{
							arr[posX][posY - 1] = true;
							alive.push_back(srell);
							alive[alive.size() - 1].currentState = true;
							alive[alive.size() - 1].activeNeighbors++;
							alive[alive.size() - 1].posX = posX;
							alive[alive.size() - 1].posY = posY - 1;

							alive[srng].activeNeighbors++;


							if (alive[srng].activeNeighbors == 4)
							{
								alive[srng].currentState = false;
							}
							done = false;
							currentlive++;
							std::vector<int> helper{ posX,posY - 1 };
							cluster.push_back(helper);
						}
						break;
					}
					}
				}

		}

		if (!((iter + 1) % static_cast<long>(offset))) {
			offset *= offsetMultiplier;
			ofs << iter + 2 << " " << find_r() << "\n";
			std::string imgName = "eden(" + std::to_string(iter) + ").bmp";
			write_bmp_2D((dirName_1 + imgName).c_str(), N, N, arr);
		}
	}
	ofs.close();
}


double Eden::find_r()
{
	int sum_x = 0;
	int sum_y = 0;
	for (int i = 0; i < cluster.size(); i++)
	{
		sum_x += cluster[i][0];
		sum_y += cluster[i][1];
	}
	int s_x = sum_x / cluster.size();
	int s_y = sum_y / cluster.size();
	double r = 0.f;
	for (int i = 1; i < cluster.size(); i++)
	{
		int x = cluster[i][0];
		int y = cluster[i][1];
		int pos_x = x - s_x;
		int pos_y = y - s_y;
		double c_r = sqrt(pos_x * pos_x + pos_y * pos_y);
		if (c_r > r)
			r = c_r;
	}
	return r;

}
#include "DLA.h"

DLA::DLA(size_t N) :
	N(N)
{
	arr.resize(N);
	for (int i = 0; i < N; i++)
	{
		arr[i].resize(N);
	}
}

void DLA::write_bmp(const char* path, const unsigned width, const unsigned height, const bool* const data) {
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

void DLA::write_bmp_2D(const char* path, const unsigned width, const unsigned height, const std::vector<std::vector<bool>> data) {
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

void DLA::write_bmp_2D_int(const char* path, const unsigned width, const unsigned height, const std::vector<std::vector<int>> data)
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


void DLA::Licz()
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(-1, 1);
	std::uniform_int_distribution<int> dsh(0, 3);
	static std::uniform_real_distribution<double> dist(0.0, 1.0);
	static std::uniform_int_distribution<int> czeko(5, 120);
	std::uniform_real_distribution<double> movedir(0.0, 1.0);
	double chanceToMoveX = .5;

	std::vector<Cell> alive;
	Cell cell;
	alive.push_back(cell);
	liveCell.push_back(0);
	alive[0].currentState = true;
	alive[0].activeNeighbors = 0;
	alive[0].posX = N / 2;
	alive[0].posY = N / 2;
	arr[alive[0].posX][alive[0].posY] = true;
	std::string dirName_0 = "data/";
	std::filesystem::create_directory(dirName_0.c_str());
	std::string dirName_1 = dirName_0 + "dla_img/";
	std::filesystem::create_directory(dirName_1.c_str());

	std::string fileName = "dlaGrowth.txt";
	
	int currentlive = 0;

	std::vector<Cell> cellvector;

	int numberWedr = N * 6;
	for (int j = 0; j < numberWedr; j++)
	{
		Cell srell;
		srell.currentState = true;
		//double alpha = dist(gen) * 2 * M_PI;
		//srell.posX = cos(alpha) * (N / 2 - 1) + N / 2;
		//srell.posY = sin(alpha) * (N / 2 - 1) + N / 2;
		switch (static_cast<size_t>(dist(gen) * 4)) {
			case 0:
				srell.posX = (N / 2) + (find_r() + czeko(rd));
				srell.posY = (N / 2) + (find_r() + czeko(rd));
				break;
			case 1:
				srell.posX = (N / 2) - (find_r() + czeko(rd));
				srell.posY = (N / 2) + (find_r() + czeko(rd));
				break;
			case 2:
				srell.posX = (N / 2) + (find_r() + czeko(rd));
				srell.posY = (N / 2) - (find_r() + czeko(rd));
				break;
			case 3:
				srell.posX = (N / 2) - (find_r() + czeko(rd));
				srell.posY = (N / 2) - (find_r() + czeko(rd));
				break;
		}

		cellvector.push_back(srell);
	}


	for (size_t iter = 0; iter < TOTAL_ITER; iter++) {
		std::uniform_int_distribution<int> distro(0.0, liveCell.size() - 1);
		bool done = true;


		int to_much = 0;
		int connect = 0;
	while (connect<6)
		{
			for (int j = 0; j < numberWedr; j++)
			{
				/*if (movedir(rd) < chanceToMoveX)
				{
					cellvector[j].posX += dis(rd);
				}
				else
				{
					cellvector[j].posY += dis(rd);
				}
				*/
				switch (static_cast<size_t>(dist(gen) * 4)) {
				case 0:
					cellvector[j].posX += 1;
					if (cellvector[j].posX > N)
						cellvector[j].posX = 0;
					break;
				case 1:
					cellvector[j].posX -= 1;
					if (cellvector[j].posX < 0)
						cellvector[j].posX = N - 1;
					break;
				case 2:
					cellvector[j].posY += 1;
					if (cellvector[j].posY > N)
						cellvector[j].posY = 0;
					break;
				case 3:
					cellvector[j].posY -= 1;
					if (cellvector[j].posY < 0)
						cellvector[j].posY = N - 1;
					break;
				}

				for (auto& srng : liveCell)
				{
						if (cellvector[j].posX + 1 == alive[srng].posX && cellvector[j].posY == alive[srng].posY)
						{
							arr[cellvector[j].posX][cellvector[j].posY] = true;
							alive.push_back(cellvector[j]);
							alive[srng].activeNeighbors++;
							if (alive[srng].activeNeighbors >= 4)
							{
								alive[srng].currentState = false;
								liveCell.erase(std::remove(liveCell.begin(), liveCell.end(), srng), liveCell.end());
							}
							auto t = alive.size() - 1;
							if (alive[t].posX + 1 == alive[srng].posX && alive[t].posY == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}
							if (alive[t].posX - 1 == alive[srng].posX && alive[t].posY == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}
							if (alive[t].posX == alive[srng].posX && alive[t].posY + 1 == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}
							if (alive[t].posX == alive[srng].posX && alive[t].posY - 1 == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}

							currentlive++;
							liveCell.push_back(currentlive);

							connect++;
							switch (static_cast<size_t>(dist(gen) * 4)) {
							case 0:
								cellvector[j].posX = (N / 2) + (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) + (find_r() + czeko(rd));
								break;
							case 1:
								cellvector[j].posX = (N / 2) - (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) + (find_r() + czeko(rd));
								break;
							case 2:
								cellvector[j].posX = (N / 2) + (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) - (find_r() + czeko(rd));
								break;
							case 3:
								cellvector[j].posX = (N / 2) - (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) - (find_r() + czeko(rd));
								break;
							}
							break;
						}
						else if (cellvector[j].posX - 1 == alive[srng].posX && cellvector[j].posY == alive[srng].posY)
						{
							arr[cellvector[j].posX][cellvector[j].posY] = true;
							alive.push_back(cellvector[j]);
							alive[srng].activeNeighbors++;
							if (alive[srng].activeNeighbors >= 4)
							{
								alive[srng].currentState = false;
								liveCell.erase(std::remove(liveCell.begin(), liveCell.end(), srng), liveCell.end());
							}

							currentlive++;
							liveCell.push_back(currentlive);

							auto t = alive.size() - 1;
							if (alive[t].posX + 1 == alive[srng].posX && alive[t].posY == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}
							if (alive[t].posX - 1 == alive[srng].posX && alive[t].posY == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}
							if (alive[t].posX == alive[srng].posX && alive[t].posY + 1 == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}
							if (alive[t].posX == alive[srng].posX && alive[t].posY - 1 == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}

							connect++;
							double alpha = dist(gen) * 2 * M_PI;
							switch (static_cast<size_t>(dist(gen) * 4)) {
							case 0:
								cellvector[j].posX = (N / 2) + (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) + (find_r() + czeko(rd));
								break;
							case 1:
								cellvector[j].posX = (N / 2) - (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) + (find_r() + czeko(rd));
								break;
							case 2:
								cellvector[j].posX = (N / 2) + (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) - (find_r() + czeko(rd));
								break;
							case 3:
								cellvector[j].posX = (N / 2) - (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) - (find_r() + czeko(rd));
								break;
							}
							break;
						}
						else if (cellvector[j].posX == alive[srng].posX && cellvector[j].posY + 1 == alive[srng].posY)
						{
							arr[cellvector[j].posX][cellvector[j].posY] = true;
							alive.push_back(cellvector[j]);
							if (alive[srng].activeNeighbors >= 4)
							{
								alive[srng].currentState = false;
								liveCell.erase(std::remove(liveCell.begin(), liveCell.end(), srng), liveCell.end());
							}

							currentlive++;
							liveCell.push_back(currentlive);

							auto t = alive.size() - 1;
							if (alive[t].posX + 1 == alive[srng].posX && alive[t].posY == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}
							if (alive[t].posX - 1 == alive[srng].posX && alive[t].posY == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}
							if (alive[t].posX == alive[srng].posX && alive[t].posY + 1 == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}
							if (alive[t].posX == alive[srng].posX && alive[t].posY - 1 == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}

							connect++;
							double alpha = dist(gen) * 2 * M_PI;
							switch (static_cast<size_t>(dist(gen) * 4)) {
							case 0:
								cellvector[j].posX = (N / 2) + (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) + (find_r() + czeko(rd));
								break;
							case 1:
								cellvector[j].posX = (N / 2) - (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) + (find_r() + czeko(rd));
								break;
							case 2:
								cellvector[j].posX = (N / 2) + (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) - (find_r() + czeko(rd));
								break;
							case 3:
								cellvector[j].posX = (N / 2) - (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) - (find_r() + czeko(rd));
								break;
							}
							break;
						}
						else if (cellvector[j].posX == alive[srng].posX && cellvector[j].posY - 1 == alive[srng].posY)
						{
							arr[cellvector[j].posX][cellvector[j].posY] = true;
							alive.push_back(cellvector[j]);
							alive[srng].activeNeighbors++;
							if (alive[srng].activeNeighbors >= 4)
							{
								alive[srng].currentState = false;
								liveCell.erase(std::remove(liveCell.begin(), liveCell.end(), srng), liveCell.end());
							}

							currentlive++;
							liveCell.push_back(currentlive);

							auto t = alive.size() - 1;
							if (alive[t].posX + 1 == alive[srng].posX && alive[t].posY == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}
							if (alive[t].posX - 1 == alive[srng].posX && alive[t].posY == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}
							if (alive[t].posX == alive[srng].posX && alive[t].posY + 1 == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}
							if (alive[t].posX == alive[srng].posX && alive[t].posY - 1 == alive[srng].posY)
							{
								alive[t].activeNeighbors++;
							}

							connect++;
							double alpha = dist(gen) * 2 * M_PI;
							switch (static_cast<size_t>(dist(gen) * 4)) {
							case 0:
								cellvector[j].posX = (N / 2) + (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) + (find_r() + czeko(rd));
								break;
							case 1:
								cellvector[j].posX = (N / 2) - (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) + (find_r() + czeko(rd));
								break;
							case 2:
								cellvector[j].posX = (N / 2) + (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) - (find_r() + czeko(rd));
								break;
							case 3:
								cellvector[j].posX = (N / 2) - (find_r() + czeko(rd));
								cellvector[j].posY = (N / 2) - (find_r() + czeko(rd));
								break;
							}
							break;
						}
					
				}
			}


			to_much++;
			if (to_much >= N)
			{
				for (int j = 0; j < numberWedr; j++)
				{
					switch (static_cast<size_t>(dist(gen) * 4)) {
					case 0:
						cellvector[j].posX = (N / 2) + (find_r() + czeko(rd));
						cellvector[j].posY = (N / 2) + (find_r() + czeko(rd));
						break;
					case 1:
						cellvector[j].posX = (N / 2) - (find_r() + czeko(rd));
						cellvector[j].posY = (N / 2) + (find_r() + czeko(rd));
						break;
					case 2:
						cellvector[j].posX = (N / 2) + (find_r() + czeko(rd));
						cellvector[j].posY = (N / 2) - (find_r() + czeko(rd));
						break;
					case 3:
						cellvector[j].posX = (N / 2) - (find_r() + czeko(rd));
						cellvector[j].posY = (N / 2) - (find_r() + czeko(rd));
						break;
					}
				}

			}

		}



		/*if (!((iter + 1) % static_cast<long>(offset))) {
			offset *= offsetMultiplier;
			std::ofstream ofs((dirName_0 + fileName).c_str(), std::ios::app);
			ofs << iter + 2 << " " << find_r() << "\n";
			std::string imgName = "dla(" + std::to_string(iter) + ").bmp";
			write_bmp_2D((dirName_1 + imgName).c_str(), N, N, arr);
			ofs.close();
		}*/
		if ((iter+1)%10==0) {
			offset *= offsetMultiplier;
			std::ofstream ofs((dirName_0 + fileName).c_str(), std::ios::app);
			ofs << iter + 2 << " " << find_r() << "\n";
			std::string imgName = "dla(" + std::to_string(iter) + ").bmp";
			write_bmp_2D((dirName_1 + imgName).c_str(), N, N, arr);
			ofs.close();
		}
		std::cout << "iter nr:" << iter << std::endl;
	}
	//ofs.close();
}


double DLA::find_r()
{
	/*int sum_x = 0;
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
	}*/
	double max_radius = 0.0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (arr[i][j]) {
				double r = std::sqrt(pow(i - static_cast<int>(N / 2), 2) + pow(j - static_cast<int>(N / 2), 2));
				if (max_radius < r) max_radius = r;
			}
		}
	}

	return max_radius;

}
#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>
#include <climits>
#include <cmath>
#include <string>
template <unsigned int D>
void randMove(const double* pos0, double* pos1) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<size_t> dist_index(0, D - 1);
    static std::uniform_int_distribution<uint16_t> dist_sign(0, 1);

    size_t direction_index = dist_index(gen);
    uint16_t direction_sign = dist_sign(gen);

    for (int i = 0; i < D; i++) {
        pos1[i] = pos0[i];
    }

    pos1[direction_index] = pos1[direction_index] + (direction_sign == 1 ? 1 : -1);
}


void zad4() {
    constexpr size_t STEPS = 1000;
    constexpr size_t D = 3;
    constexpr size_t TOTAL_ITER = 100000;
    constexpr bool OFS_TITLES = false;
    const static std::string SEP = " ";

    size_t backTostartCount[STEPS] = { 0 };

    std::string dirName = "spacery/";
    std::string fileName = "PowrotnaStart.txt";
    std::ofstream myfile;
    myfile.open(dirName + fileName);

    for (int iter = 0; iter < TOTAL_ITER; iter++) {
        double arr0[D] = { 0 };
        double arr1[D] = { 0 };
        double* first;
        double* second;
        first = arr0;
        second = arr1;

        for (int i = 0; i < STEPS; i++) {
            randMove<D>(first, second);
            [&]() {
                for (int j = 0; j < D; j++) {
                    if (second[j] != 0) return;
                }
                backTostartCount[i] += 1;
            }();
            std::swap(first, second);
        }
    }

    for (int i = 0; i < STEPS; i++) {
        myfile << backTostartCount[i] << "\n";
    }
    myfile.close();
}

int main()
{
    zad4();
    return 0;
}
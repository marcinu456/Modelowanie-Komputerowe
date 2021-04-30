#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>
#include <climits>
#include <cmath>
#include <string>
#include <numeric>
#include <numbers>
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

// task_5 code 
template <unsigned int D>
void randMove_diagonal(const double* pos0, double* pos1) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<size_t> dist_index(0, D - 1);
    static std::uniform_int_distribution<uint16_t> dist_sign(0, 1);

    bool isMoved = false;

    for (int i = 0; i < D; i++) {
        pos1[i] = pos0[i];
        if (dist_sign(gen) == 0) {
            isMoved = true;
            pos1[i] += (dist_sign(gen) == 1 ? 1 : -1);
        }
    }
    if (!isMoved) {
        size_t direction_index = dist_index(gen);
        uint16_t direction_sign = dist_sign(gen);
        pos1[direction_index] += (direction_sign == 1 ? 1 : -1);
    }
}

void zad6() {
    constexpr size_t STEPS = 10000;
    constexpr size_t D = 2;
    constexpr size_t TOTAL_ITER = 10000;
    constexpr bool OFS_TITLES = false;
    const static std::string SEP = " ";

    double x[STEPS] = { 0 };
    double x2[STEPS] = { 0 };

    std::string dirName = "walks/";
    std::string fileName = "shift_" + std::to_string(D) + "D.txt";
    std::ofstream ofs((dirName + fileName).c_str(), std::ofstream::out);

    if constexpr (OFS_TITLES) {
        ofs << "x" << SEP << "x^2" << SEP << "sqrt(x^2)" << "\n";
    }

    for (int iter = 0; iter < TOTAL_ITER; iter++) {
        double arr0[D] = { 0 };
        double arr1[D] = { 0 };
        double* first;
        double* second;
        first = arr0;
        second = arr1;

        for (int i = 0; i < STEPS; i++) {
            randMove<D>(first, second);
            int xx = [&]() {
                int value = first[0] * first[0];
                for (int d = 1; d < D; d++) {
                    value += first[0] * first[0];
                }
                return value;
            }();
            double sqrxx = std::sqrt(xx);

            x[i] += sqrxx;
            x2[i] += xx;

            std::swap(first, second);
        }
    }

    for (int i = 0; i < STEPS; i++) {
        ofs << x[i] / TOTAL_ITER << SEP << x2[i] / TOTAL_ITER << SEP << sqrt(x2[i] / TOTAL_ITER) << "\n";
    }



    std::string dirName_diagonal = "walks/";
    std::string fileName_diagonal = "shift_" + std::to_string(D) + "D_diagonal.txt";
    std::ofstream ofs_diagonal((dirName_diagonal + fileName_diagonal).c_str(), std::ofstream::out);

    double x_diagonal[STEPS] = { 0 };
    double x2_diagonal[STEPS] = { 0 };

    if constexpr (OFS_TITLES) {
        ofs_diagonal << "x" << SEP << "x^2" << SEP << "sqrt(x^2)" << "\n";
    }

    for (int iter = 0; iter < TOTAL_ITER; iter++) {
        double arr0[D] = { 0 };
        double arr1[D] = { 0 };
        double* first;
        double* second;
        first = arr0;
        second = arr1;

        for (int i = 0; i < STEPS; i++) {
            randMove_diagonal<D>(first, second);
            int xx = [&]() {
                int value = first[0] * first[0];
                for (int d = 1; d < D; d++) {
                    value += first[0] * first[0];
                }
                return value;
            }();
            double sqrxx = std::sqrt(xx);

            x_diagonal[i] += sqrxx;
            x2_diagonal[i] += xx;

            std::swap(first, second);
        }
    }

    for (int i = 0; i < STEPS; i++) {
        ofs_diagonal << x_diagonal[i] / TOTAL_ITER << SEP << x2_diagonal[i] / TOTAL_ITER << SEP << sqrt(x2_diagonal[i] / TOTAL_ITER) << "\n";
    }
}

int main()
{
    std::cout<<std::midpoint(1, 3)<<" \n";
    std::numbers::sqrt2;
    //zad6();
    return 0;
}
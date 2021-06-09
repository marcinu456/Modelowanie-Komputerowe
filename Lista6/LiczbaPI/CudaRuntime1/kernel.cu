
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

#include <iostream>

#include <random>
#include <iomanip> 

int main(int argc, char* argv[]) {



    std::random_device rd{};
    std::mt19937 engine{ rd() };
    std::uniform_real_distribution<double> dis(0.0, DBL_MAX);
    long long N = 1'000'000'000;
    long long i;
    double x, y, n = 0, recv;

    cudaMallocManaged(&x);

    for (i = 1; i < N; i++) {
        x = (dis(rd) / (DBL_MAX));
        y = (dis(rd) / (DBL_MAX));
        if (x * x + y * y <= 1) n++;
    }

    std::cout << "PI  = " << std::setprecision(10) << 4.0 * n / N << "\n";

    return 0;
}

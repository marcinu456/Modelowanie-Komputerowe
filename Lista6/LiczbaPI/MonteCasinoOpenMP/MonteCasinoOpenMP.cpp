#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <omp.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include<iostream>
#include <iomanip> 
#include <random>

#define N 5'147'000'000


int main()
{
    std::random_device rd{};
    std::mt19937_64 engine{ rd() };
    std::uniform_real_distribution<double> dis(-1.0, 1);
    double count = 0;
    double pi;

    //Init Parallelazation with reduction techinue
#pragma omp parallel for reduction(+: count)
    for (long long i = 0; i < N; i++) {



        double x, y;
        x = dis(rd);
        y = dis(rd);

        if (x * x + y * y <= 1 && x * x + y * y >= -1) 
            count++;


    }

    //Calcuting the ratio and as a result the pi
    pi = (count / N) * 4.0;

    printf("OpenMP : # of trials = %14ld , estimate of pi is %1.16f AND an absolute error of %g\n", N, pi, fabs(pi - M_PI));
    std::cout << "PI  = " << std::setprecision(10) << pi << "\n";

    return 0;
}
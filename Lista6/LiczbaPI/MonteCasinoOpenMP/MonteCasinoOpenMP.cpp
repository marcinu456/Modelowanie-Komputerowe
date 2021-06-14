#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <chrono>
#include <fstream>
#include <filesystem>
#define _USE_MATH_DEFINES
#include <math.h>
int samplesInsideCircle(const long long numSamples)
{
    //std::random_device rd{};
    //std::mt19937 engine{ rd() };

    std::default_random_engine rd;
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    rd.seed(seed);
    std::uniform_real_distribution<double> dis(-1.0, 1);


    long long counter = 0;
    for (long long s = 0; s != numSamples; s++)
    {
        auto x = dis(rd);
        auto y = dis(rd);

        if (x * x + y * y < 1)
        {
            counter++;
        }
    }

    return counter;
}


double parallelPi(const long long  numTotalSamples = 100'000'000'000)
{

    //const long long  numTotalSamples = 100'000'000'000;
    //const long long  numTotalSamples = 20'000'000;
    long long numChunks = 64;
    long long chunk = numTotalSamples / numChunks;

    long long counter = 0;

#pragma omp parallel for shared(numChunks, chunk) reduction(+:counter)
    for (long long i = 0; i < numChunks; i++)
    {
        counter += samplesInsideCircle(chunk);
    }

    const double calculationPi = 4.0 * counter / numTotalSamples;

    std::cout << "numbers of N: " << numTotalSamples << "\n";
    std::cout << "Pi = " << std::setprecision(12) << M_PI << "\n";
    std::cout << "calculation.: " << std::setprecision(12) << calculationPi << std::endl;
    return calculationPi;
}

std::vector<double> npPi()
{
    std::random_device rd{};
    std::mt19937_64 engine{ rd() };
    //std::default_random_engine rd;
    //int seed = std::chrono::system_clock::now().time_since_epoch().count();
    //rd.seed(seed);
    std::uniform_real_distribution<double> dis(-1.0, 1);
    std::vector<double> calculationPi;
    long long  numTotalSamples = 1'000'000'000;
    long long  maxnumTotalSamples = 5'000'000'000;

    long long chunk = numTotalSamples;

    long long counter = 0;


    for (long long i = 0; i < numTotalSamples; i++)
    {
        auto x = dis(rd);
        auto y = dis(rd);
        //auto x = ((double)rand() / (RAND_MAX));
        //auto y = ((double)rand() / (RAND_MAX));


        if (x * x + y * y < 1)
        {
            counter++;
        }
    }
    std::ofstream ofs_energy;
    ofs_energy.open("cppMT1997s.txt");
    long long oile = 5'000'000;
    for (numTotalSamples; numTotalSamples < maxnumTotalSamples; numTotalSamples += oile)
    {
        auto tmp = numTotalSamples + oile;


        for (long long i = numTotalSamples; i < tmp; i++)
        {
            auto x = dis(rd);
            auto y = dis(rd);
            //auto x = ((double)rand() / (RAND_MAX));
            //auto y = ((double)rand() / (RAND_MAX));
            if (x * x + y * y < 1)
            {
                counter++;
            }
        }

        calculationPi.push_back(4.0 * counter / tmp);
        std::cout << "numbers of N: " << tmp << "\n";
        std::cout << "Pi = " << std::setprecision(12) << M_PI << "\n";
        std::cout << "calculation.: " << std::setprecision(12) << calculationPi.back() << std::endl;
        ofs_energy << tmp << " " << std::setprecision(12) << calculationPi.back() << std::endl;
    }
    //std::cout << "number of samples: " << numTotalSamples << "\n";
    //std::cout << "real Pi: 3.141592653589..." << "\n";
    //std::cout << "calculation.: " << std::setprecision(12) << calculationPi << std::endl;
    return calculationPi;
}

int main()
{
   // std::ofstream ofs_energy;
   // ofs_energy.open("cpp.txt");
    using millis = std::chrono::milliseconds;
    using std::chrono::duration_cast;
    using std::chrono::steady_clock;

   /* for (long long i = 1'000'000'000; i < 5'000'000'000; i+=10'000'000)
    {

        auto t_par_1 = steady_clock::now();
        ofs_energy << i << " " << std::setprecision(12) << parallelPi(i) << std::endl;
        auto t_par_2 = steady_clock::now();

        auto time2 = duration_cast<millis>(t_par_2 - t_par_1).count();
        std::cout << "Time: " << time2 << " millisecons.\n" << std::endl;
    }*/

    auto tmp = npPi();
    for (auto& tn : tmp)
    {
        //ofs_energy << std::setprecision(12) << tn << std::endl;
    }
 

    return 0;
}
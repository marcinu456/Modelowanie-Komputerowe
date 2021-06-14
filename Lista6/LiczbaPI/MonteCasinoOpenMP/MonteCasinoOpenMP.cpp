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

    const double approxPi = 4.0 * counter / numTotalSamples;

    std::cout << "number of samples: " << numTotalSamples << "\n";
    std::cout << "real Pi: 3.141592653589..." << "\n";
    std::cout << "approx.: " << std::setprecision(12) << approxPi << std::endl;
    return approxPi;
}

int main()
{
    std::ofstream ofs_energy;
    ofs_energy.open("cpp.txt");
    using millis = std::chrono::milliseconds;
    using std::chrono::duration_cast;
    using std::chrono::steady_clock;

    for (long long i = 10'000'000; i < 5'000'000'000; i+= 10'000'000)
    {

        auto t_par_1 = steady_clock::now();
        ofs_energy << i << " " << std::setprecision(12) << parallelPi(i) << std::endl;
        auto t_par_2 = steady_clock::now();

        auto time2 = duration_cast<millis>(t_par_2 - t_par_1).count();
        std::cout << "Time: " << time2 << " millisecons.\n" << std::endl;
    }
    return 0;
}
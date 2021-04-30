#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>


int main() {
    const unsigned long int loops = 100000000;
    const int range = 10000;
    int randHist[range + 1] = { 0 };
    int mt19937Hist[range + 1] = { 0 };

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    int seed = time(NULL);
    srand(seed);

    for (unsigned long int i = 0; i < loops; i++) {
        randHist[(unsigned long int)(floor(((double)rand() / (double)RAND_MAX) * range))]++;
        mt19937Hist[(unsigned long int)(floor(dist(gen) * range))]++;
    }

    std::ofstream myfile; 
    myfile.open("random.txt");

    unsigned long int sumRd = 0;
    unsigned long int sumMt = 0;
    for (int i = 0; i < range; i++) {
        sumRd += randHist[i];
        sumMt += mt19937Hist[i];
        myfile << i << " " << randHist[i] << " " << mt19937Hist[i] << "\n";
    }
    myfile.close();

    std::cout << "sumRd:\t" << sumRd << "\tsumMt:\t" << sumMt << "\n";

    return 0;
}

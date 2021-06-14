#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>

void Dimension1() {
    const size_t STEPS = 1000;
    size_t TOTAL_ITER = 1;


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-1, 1);

    std::string dirName = "spacery/";
    std::string fileName = "odlegloscPo1000.txt";
    std::ofstream myfile;
    myfile.open(dirName + fileName);

    for (int iter = 0; iter < TOTAL_ITER; iter++) {
        int arr[STEPS][1] = { 0 };
        for (int i = 1; i < STEPS; i++) {
            int krok = arr[i - 1][0] + dis(rd);
            //std::cout << krok << "dis\n";
            arr[i][0] = krok;
            myfile << krok << "\n";
        }
       // myfile << arr[STEPS-1][0] << "\n";
       
    }
    myfile.close();
}


int main()
{
    Dimension1();
    return 0;
}
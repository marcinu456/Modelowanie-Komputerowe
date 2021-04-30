#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>

void Dimension1() {
    const size_t STEPS = 1000;
    size_t TOTAL_ITER = 5;

    int arr[STEPS][1] = { 0 };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-1, 1);


    for (int iter = 0; iter < TOTAL_ITER; iter++) {
        std::string dirName = "spacery/1D/";
        std::filesystem::create_directory(dirName.c_str());
        std::string fileName = "spacer(" + std::to_string(iter) + ").txt";
        std::ofstream myfile;
        myfile.open(dirName+fileName);

        myfile << 0 << " " << arr[1][0] << "\n";
        for (int i = 1; i < STEPS; i++) {
            int krok = arr[i - 1][0] + dis(rd);
            //std::cout << krok << "dis\n";
            arr[i][0] = krok;
            myfile << i << " " << arr[i][0] << "\n";
        }
        
        myfile.close();
    }
}

void Dimension2() {
    const size_t STEPS = 1000;
    size_t TOTAL_ITER = 5;

    int arr[STEPS][2] = { 0 };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-1, 1);
    std::uniform_real_distribution<double> movedir(0.0, 1.0);
    double chanceToMoveX = .5;

    for (int iter = 0; iter < TOTAL_ITER; iter++) {
        std::string dirName = "spacery/2D/";
        std::filesystem::create_directory(dirName.c_str());
        std::string fileName = "spacer(" + std::to_string(iter) + ").txt";
        std::ofstream myfile;
        myfile.open(dirName + fileName);

        myfile << arr[1][0] << " " << arr[1][1] << "\n";
        for (int i = 1; i < STEPS; i++) {
            if (movedir(rd) < chanceToMoveX) {
                int krokx = arr[i - 1][0] + dis(rd);
                int kroky = arr[i - 1][1];
                //std::cout << krok << "dis\n";
                arr[i][0] = krokx;
                arr[i][1] = kroky;
                myfile << arr[i][0] << " " << arr[i][1] << "\n";
            }
            else {
                int krokx = arr[i - 1][0];
                int kroky = arr[i - 1][1] + dis(rd);
                //std::cout << krok << "dis\n";
                arr[i][0] = krokx;
                arr[i][1] = kroky;
                myfile << arr[i][0] << " " << arr[i][1] << "\n";
            }
        }

        myfile.close();
    }
}

int main() 
{
    Dimension1();
    Dimension2();
    return 0;
}
#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>


void Dimension3() {
    const size_t STEPS = 1000;
    size_t TOTAL_ITER = 5;

    int arr[STEPS][3] = { 0 };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-1, 1);
    std::uniform_real_distribution<double> movedir(0.0, 1.0);
    double chanceToMoveX = 1./3.;
    double chanceToMoveY = 2./3.;

    for (int iter = 0; iter < TOTAL_ITER; iter++) {
        std::string dirName = "spacery/3D/";
        std::filesystem::create_directory(dirName.c_str());
        std::string fileName = "spacer(" + std::to_string(iter) + ").txt";
        std::ofstream myfile;
        myfile.open(dirName + fileName);

        myfile << arr[1][0] << " " << arr[1][1] << " " << arr[1][2] << "\n";
        for (int i = 1; i < STEPS; i++) {
            double whatmove = movedir(rd);
            if (whatmove < chanceToMoveX) {
                int krokx = arr[i - 1][0] + dis(rd);
                int kroky = arr[i - 1][1];
                int krokz = arr[i - 1][2];
                arr[i][0] = krokx;
                arr[i][1] = kroky;
                arr[i][2] = krokz;
                myfile << arr[i][0] << " " << arr[i][1] << " " << arr[i][2] << "\n";
            }
            else if (whatmove < chanceToMoveY) {
                int krokx = arr[i - 1][0];
                int kroky = arr[i - 1][1] + dis(rd);
                int krokz = arr[i - 1][2];
                arr[i][0] = krokx;
                arr[i][1] = kroky;
                arr[i][2] = krokz;
                myfile << arr[i][0] << " " << arr[i][1] << " " << arr[i][2] << "\n";
            }
            else {
                int krokx = arr[i - 1][0];
                int kroky = arr[i - 1][1];
                int krokz = arr[i - 1][2] + dis(rd);
                arr[i][0] = krokx;
                arr[i][1] = kroky;
                arr[i][2] = krokz;
                myfile << arr[i][0] << " " << arr[i][1] << " " << arr[i][2] << "\n";
            }
        }

        myfile.close();
    }
}

int main()
{
    Dimension3();
    return 0;
}
#include <iostream>
#include <mpi.h>
#include <random>
#include <iomanip> 

int main(int argc, char* argv[]) {


        MPI_Init(&argc, &argv);

        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);


        int numprocs;
        MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

        std::random_device rd{};
        std::mt19937 engine{ rd() };
        std::uniform_real_distribution<double> dis(-1.0, 1);
        long long N = 10'000'000'000;
        long long i;
        double x, y, n = 0, recv;

        for (i = 1; i < N / numprocs; i++) {
            x = dis(rd);
            y = dis(rd);
            if (x * x + y * y <= 1 && x * x + y * y >=-1) n++;
        }

        MPI_Reduce(&n, &recv, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 0)
            std::cout << "PI  = " << std::setprecision(10) << 4.0 * recv / N << "\n";
    
        MPI_Finalize();
    
    return 0;
}

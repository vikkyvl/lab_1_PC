#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>

#define N 10
#define MIN 1
#define MAX 5

int matrix[N][N];

int getRandomNumber()
{
    return MIN + (rand() % (MAX - MIN + 1));
}

void fillingMatrix() {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = getRandomNumber();
        }
    }
}

void calculatingProductOfColumn(const int col)
{
    int product = 1;

    for(int row = 0; row < N; row++)
    {
        product *= matrix[row][col];
    }

    matrix[N - 1 - col][col] = product;
}

void sequentialCalculation()
{
    for(int col = 0; col < N; col++)
    {
        calculatingProductOfColumn(col);
    }
}

void columnsDistribution(const int thread_id, const int step)
{
    for(int col = thread_id; col < N; col+=step)
    {
        calculatingProductOfColumn(col);
    }
}

void parallelCalculation(const int threads_N)
{
    std::vector<std::thread> threads(threads_N);

    for(int thread_id = 0; thread_id < threads_N; thread_id++)
    {
        threads[thread_id] = std::thread(columnsDistribution, thread_id, threads_N);
    }

    for(int thread_id = 0; thread_id < threads_N; thread_id++)
    {
        threads[thread_id].join();
    }
}

void printMatrix()
{
    for(int row = 0; row < N; row++)
    {
        for(int col = 0; col < N; col++)
        {
            std::cout << std::setw(10) << matrix[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    srand(time(NULL));

    //std::cout << "Initial Matrix" << std::endl;
    fillingMatrix();
    //printMatrix();

    auto sequential_begin = std::chrono::high_resolution_clock::now();
    //std::cout << "New Matrix" << std::endl;
    sequentialCalculation();
    //printMatrix();
    auto sequential_end = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(sequential_end - sequential_begin);
    std::cout << elapsed.count() * 1e-9 << " s" << std::endl;

    //std::cout << "Initial Matrix" << std::endl;
    fillingMatrix();
    //printMatrix();

    //std::cout << "New Matrix" << std::endl;
    parallelCalculation(4);
    //printMatrix();

    return 0;
}



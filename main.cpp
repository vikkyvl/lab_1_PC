#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>

#define N 5
#define MIN 1
#define MAX 5

int matrix[N][N];
int initial_matrix[N][N];

int getRandomNumber()
{
    return MIN + (rand() % (MAX - MIN + 1));
}

void fillingMatrix()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = getRandomNumber();
            initial_matrix[i][j] = matrix[i][j];
        }
    }
}

void restoringMatrix()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = initial_matrix[i][j];
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

void resultSequentialCalculation()
{
    fillingMatrix();

    auto sequential_begin = std::chrono::high_resolution_clock::now();
    sequentialCalculation();
    auto sequential_end = std::chrono::high_resolution_clock::now();
    //printMatrix();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(sequential_end - sequential_begin);
    std::cout << "Time: " << elapsed.count() * 1e-9 << " s" << std::endl;
}

void resultParallelCalculation(int physical_cores, int logical_cores)
{
    restoringMatrix();
    std::vector<int> threads_N = {
        physical_cores / 2, physical_cores, logical_cores, logical_cores * 2,
        logical_cores * 4, logical_cores * 8, logical_cores * 16
    };

    for(int i : threads_N)
    {
        restoringMatrix();
        auto parallel_begin = std::chrono::high_resolution_clock::now();
        parallelCalculation(i);
        auto parallel_end = std::chrono::high_resolution_clock::now();
        //printMatrix();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(parallel_end - parallel_begin);
        std::cout << "Threads: " << i << " Time: " << elapsed.count() * 1e-9 << " s" << std::endl;
    }
}

int main()
{
    srand(time(NULL));

    int physical_cores = 2;
    int logical_cores = 4;

    std::cout << "\nResult of Matrix Calculation (Size: " << N << "x" << N << "):\n" << std::endl;
    std::cout << "* Sequential: *" << std::endl;
    resultSequentialCalculation();

    std::cout << "* Parallel: *" << std::endl;
    resultParallelCalculation(physical_cores, logical_cores);

    return 0;
}



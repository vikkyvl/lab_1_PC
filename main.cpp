#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

#define N 10
#define MIN 1
#define MAX 10

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

void calculatingProductOfColumn(int col)
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

/*void printMatrix()
{
    for(int row = 0; row < N; row++)
    {
        for(int col = 0; col < N; col++)
        {
            std::cout << std::setw(10) << matrix[row][col] << " ";
        }
        std::cout << std::endl;
    }
}*/

int main() {
    srand(time(NULL));

    //std::cout << "Initial Matrix" << std::endl;
    fillingMatrix();
    //printMatrix();

    //std::cout << "New Matrix" << std::endl;
    sequentialCalculation();
    //printMatrix();

    return 0;
}



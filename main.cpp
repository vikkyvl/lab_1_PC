#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

#define N 100
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

int main()
{
    srand(time(NULL));

}



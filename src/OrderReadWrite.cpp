#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

const int ARRAY_SIZE = 100000000;

void generateIntArray(int *intArr)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> intDist(1, 1000);

    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        intArr[i] = intDist(gen);
    }
}

void generateFloatArray(float *floatArr)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> floatDist(1.00, 1000.00);

    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        floatArr[i] = floatDist(gen);
    }
}

void readIntArray(int *intArr)
{
    auto start = high_resolution_clock::now();
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        int val = intArr[i];
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Order Read Int Array Time: " << duration.count() << "ms" << endl;
}

void writeIntArray(int *intArr)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> intDist(1, 1000);

    auto start = high_resolution_clock::now();
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        intArr[i] = intDist(gen);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Order Write Int Array Time: " << duration.count() << "ms" << endl;
}

void readFloatArray(float *floatArr)
{
    auto start = high_resolution_clock::now();
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        float val = floatArr[i];
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Order Read Float Array Time: " << duration.count() << "ms" << endl;
}

void writeFloatArray(float *floatArr)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> floatDist(1.00, 1000.00);

    auto start = high_resolution_clock::now();
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        floatArr[i] = floatDist(gen);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Order Write Float Array Time: " << duration.count() << "ms" << endl;
}

int main()
{
    int *intArr = new int[ARRAY_SIZE];
    float *floatArr = new float[ARRAY_SIZE];

    generateIntArray(intArr);
    generateFloatArray(floatArr);

    writeIntArray(intArr);
    readIntArray(intArr);
    writeFloatArray(floatArr);
    readFloatArray(floatArr);

    delete[] intArr;
    delete[] floatArr;

    return 0;
}

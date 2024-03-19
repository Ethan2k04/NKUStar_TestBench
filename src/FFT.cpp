//
// Created by Kaiser Tan on 2024/3/9.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <complex>

#define pi 3.1415926

using namespace std;

vector<complex<double>> fft1d(vector<complex<double>> a)
{
    int n = a.size();
    if (n == 1)
        return a;

    vector<complex<double>> even, odd;
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
            even.push_back(a[i]);
        else
            odd.push_back(a[i]);
    }

    even = fft1d(even);
    odd = fft1d(odd);

    double angle = 2 * pi / n;
    complex<double> w(1, 0), wn(cos(angle), sin(angle));

    vector<complex<double>> y(n);
    for (int k = 0; k < n / 2; k++)
    {
        y[k] = even[k] + w * odd[k];
        y[k + n / 2] = even[k] - w * odd[k];
        w *= wn;
    }

    return y;
}

void fft2d(vector<vector<complex<double>>> image)
{
    int rows = image.size();
    int cols = image[0].size();

    vector<vector<complex<double>>> temp(rows);
    for (int i = 0; i < rows; i++)
    {
        temp[i] = fft1d(image[i]);
    }

    vector<vector<complex<double>>> temp2(cols, vector<complex<double>>(rows));
    for (int i = 0; i < cols; i++)
    {
        vector<complex<double>> temp3;
        for (int j = 0; j < rows; j++)
        {
            temp3.push_back(temp[j][i]);
        }
        temp3 = fft1d(temp3);
        for (int j = 0; j < rows; j++)
        {
            temp2[i][j] = temp3[j];
        }
    }
}

void fft_test()
{
    random_device rd;
    default_random_engine gen = default_random_engine(rd());
    uniform_real_distribution<double> dist(0, 255);

    vector<vector<complex<double>>> image(200, vector<complex<double>>(200, dist(gen)));

    auto start = chrono::high_resolution_clock::now();
    fft2d(image);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "FFT Time: " << duration.count() << "ms" << endl;
}

int main()
{
    fft_test();

    return 0;
}
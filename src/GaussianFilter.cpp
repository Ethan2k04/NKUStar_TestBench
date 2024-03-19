//
// Created by Kaiser Tan on 2024/3/9.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <complex>

using namespace std;

void gaussianFilter(const vector<vector<double>> src, vector<vector<double>> dst, int ksize, double sigma)
{
    vector<vector<double>> templateMatrix;

    int origin = ksize / 2;
    double x2, y2;
    double sum = 0;

    templateMatrix.resize(ksize, vector<double>(ksize, 0));

    for (int i = 0; i < ksize; i++)
    {
        x2 = pow(i - origin, 2);
        for (int j = 0; j < ksize; j++)
        {
            y2 = pow(j - origin, 2);
            double g = exp(-(x2 + y2) / (2 * sigma * sigma));
            sum += g;
            templateMatrix[i][j] = g;
        }
    }

    for (int i = 0; i < ksize; i++)
    {
        for (int j = 0; j < ksize; j++)
        {
            templateMatrix[i][j] /= sum;
        }
    }

    int rows = src.size();
    int cols = src[0].size();
    int channels = src[0].size();

    dst.resize(rows, vector<double>(cols, 0));

    int border = ksize / 2;

    for (int i = border; i < rows - border; i++)
    {
        for (int j = border; j < cols - border; j++)
        {
            vector<double> sum(channels, 0);

            for (int a = -border; a <= border; a++)
            {
                for (int b = -border; b <= border; b++)
                {
                    for (int k = 0; k < channels; k++)
                    {
                        sum[k] += templateMatrix[border + a][border + b] * src[i + a][j + b];
                    }
                }
            }

            for (int k = 0; k < channels; k++)
            {
                dst[i][j] = min(max(sum[k], 0.0), 255.0);
            }
        }
    }
}

void gaussianFilter_float_test()
{
    random_device rd;
    default_random_engine gen = default_random_engine(rd());
    uniform_real_distribution<double> dist(0, 255);

    vector<vector<double>> image(200, vector<double>(200, dist(gen)));

    auto start = chrono::high_resolution_clock::now();

    gaussianFilter(image, image, 5, 0.8);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Gaussian Filter Time: " << duration.count() << "ms" << endl;
}

int main()
{
    gaussianFilter_float_test();

    return 0;
}

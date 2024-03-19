//
// Created by Kaiser Tan on 2024/3/9.
//
// Monte Carlo Integration
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <complex>

using namespace std;

typedef double (*Func)(double x, double x_min, double x_max);

typedef struct Limit
{
    double lVal, rVal;

    Limit(double l, double r) : lVal(l), rVal(r) {}
} Limit;

Limit getLimit(Func func, double x_min, double x_max)
{
    double y_min = func(x_min, x_min, x_max);
    double y_max = func(x_max, x_min, x_max);

    Limit limit(min(y_min, y_max), max(y_min, y_max));
    double delte = 1e-5;
    double last_X, last_Y, y;
    int i = 0;
    for (double x = x_min; x <= x_max; x += delte)
    {
        y = func(x, x_min, x_max);
        if (i == 0)
        {
            last_X = x;
            last_Y = y;
            i++;
            continue;
        }
        else
        {
            double tx = (last_X + x) / 2;
            double ty = (last_Y + y) / 2;
            if (fabs(last_Y) > fabs(y))
            {
                if (fabs(last_Y) < fabs(ty))
                {
                    last_X = tx;
                    last_Y = ty;
                    if (ty < 0 && limit.lVal > ty)
                        limit.lVal = ty;
                    if (ty > 0 && limit.rVal < ty)
                        limit.rVal = ty;
                }
            }
            else if (fabs(y) > fabs(last_Y))
            {
                if (fabs(y) < fabs(ty))
                {
                    last_X = tx;
                    last_Y = ty;
                    if (ty < 0 && limit.lVal > ty)
                        limit.lVal = ty;
                    else if (ty >= 0 && limit.rVal <= ty)
                        limit.rVal = ty;
                }
            }
        }
    }
    if (limit.lVal > 0)
        limit.lVal = 0;
    if (limit.rVal < 0)
        limit.rVal = 0;

    return limit;
}

void caculate(Func func, int N, double x_min, double x_max)
{
    random_device rd;
    default_random_engine gen = default_random_engine(rd());
    uniform_real_distribution<double> dist(0, 1);

    Limit limit = getLimit(func, x_min, x_max);
    double x, y, y0;
    int cntA = 0, cntB = 0;
    for (int i = 0; i < N; i++)
    {
        x = x_min + (x_max - x_min) * dist(gen);
        y = limit.lVal + (limit.rVal - limit.lVal) * dist(gen);
        y0 = func(x, x_min, x_max);
        if (y0 >= 0 && y0 >= y && y >= 0)
        {
            cntA++;
        }
        else if (y0 < 0 && y0 <= y && y < 0)
        {
            cntB++;
        }
    }

    double result = (cntA - cntB) * (x_max - x_min) * (limit.rVal - limit.lVal) / N;
}

inline double f1(double x, double xmin, double xmax)
{
    if (x >= xmin && x <= xmax)
        return x * x * sqrt(1 + x * x * x) - 1;
}

// 极限：[0, 0.693147180559945]
inline double f2(double x, double xmin, double xmax)
{
    if (x >= xmin && x <= xmax)
        return x * log(1 + x);
}

// 极限：[0, 1]
inline double f3(double x, double xmin, double xmax)
{
    if (x >= xmin && x <= xmax)
        return sqrt(1 - x * x);
}

// 极限：[-0.35969769413186028259906339255702, 0.1]
inline double f4(double x, double xmin, double xmax)
{
    if (x >= xmin && x <= xmax)
        return cos(x) - 0.9;
}

void MonteCarloIntegration_test()
{
    auto start = chrono::high_resolution_clock::now();
    Func fs[] = {f1, f2, f3, f4};
    int N = 1e7;
    for (int i = 0; i < 4; i++)
    {
        caculate(fs[i], N, 0, 1);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Monte Carlo Integration Time: " << duration.count() << "ms" << endl;
}

int main()
{
    MonteCarloIntegration_test();
    return 0;
}
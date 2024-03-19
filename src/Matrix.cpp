#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;

// 用于初始化矩阵的函数，使用随机值
void initializeMatrix(std::vector<std::vector<double>> &matrix, int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            matrix[i][j] = rand() % 100; // 为简单起见，给矩阵赋予随机值
        }
    }
}

// 用于打印矩阵的函数
void printMatrix(const std::vector<std::vector<double>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (double val : row)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

// 矩阵相加的函数
std::vector<std::vector<double>> matrixAddition(const std::vector<std::vector<double>> &matrix1,
                                                const std::vector<std::vector<double>> &matrix2)
{
    int rows = matrix1.size();
    int cols = matrix1[0].size();

    std::vector<std::vector<double>> result(rows, std::vector<double>(cols));

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    return result;
}

// 矩阵相减的函数
std::vector<std::vector<double>> matrixSubtraction(const std::vector<std::vector<double>> &matrix1,
                                                   const std::vector<std::vector<double>> &matrix2)
{
    int rows = matrix1.size();
    int cols = matrix1[0].size();

    std::vector<std::vector<double>> result(rows, std::vector<double>(cols));

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }

    return result;
}

// 矩阵转置的函数
std::vector<std::vector<double>> matrixTranspose(const std::vector<std::vector<double>> &matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();

    std::vector<std::vector<double>> result(cols, std::vector<double>(rows));

    for (int i = 0; i < cols; ++i)
    {
        for (int j = 0; j < rows; ++j)
        {
            result[i][j] = matrix[j][i];
        }
    }

    return result;
}

// 逐元素矩阵相乘（Hadamard乘积）的函数
std::vector<std::vector<double>> elementWiseMatrixMultiplication(const std::vector<std::vector<double>> &matrix1,
                                                                 const std::vector<std::vector<double>> &matrix2)
{
    int rows = matrix1.size();
    int cols = matrix1[0].size();

    std::vector<std::vector<double>> result(rows, std::vector<double>(cols));

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            result[i][j] = matrix1[i][j] * matrix2[i][j];
        }
    }

    return result;
}

// 矩阵相乘的函数
std::vector<std::vector<double>> matrixMultiplication(const std::vector<std::vector<double>> &matrix1,
                                                      const std::vector<std::vector<double>> &matrix2)
{
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int cols2 = matrix2[0].size();

    std::vector<std::vector<double>> result(rows1, std::vector<double>(cols2, 0));

    for (int i = 0; i < rows1; ++i)
    {
        for (int j = 0; j < cols2; ++j)
        {
            for (int k = 0; k < cols1; ++k)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

// 矩阵乘法测试的函数
void matrix_multiplication_test()
{
    const int rows = 1000;
    const int cols = 1000;
    // 初始化矩阵
    std::vector<std::vector<double>> matrix1(rows, std::vector<double>(cols));
    std::vector<std::vector<double>> matrix2(rows, std::vector<double>(cols));
    initializeMatrix(matrix1, rows, cols);
    initializeMatrix(matrix2, rows, cols);

    // 计时开始
    auto start = chrono::high_resolution_clock::now();

    // 执行矩阵相加
    auto result_addition = matrixAddition(matrix1, matrix2);
    // 执行矩阵相减
    auto result_subtraction = matrixSubtraction(matrix1, matrix2);
    // 执行矩阵转置
    auto result_transpose = matrixTranspose(matrix1);
    // 执行逐元素矩阵相乘（Hadamard乘积）
    auto result_elementwise_multiplication = elementWiseMatrixMultiplication(matrix1, matrix2);
    // 执行矩阵相乘
    auto result_multiplication = matrixMultiplication(matrix1, matrix2);

    // 计时结束
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Matrix Operations Time: " << duration.count() << "ms" << endl;
}

int main()
{
    matrix_multiplication_test();
    return 0;
}

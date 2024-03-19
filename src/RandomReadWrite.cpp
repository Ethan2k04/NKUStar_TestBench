#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 定义文件大小（字节数）
const int FILE_SIZE = 1000000000; // 文件大小为 100 MB

// 定义随机读写次数
const int NUM_ITERATIONS = 10000; // 读写次数为 1000 次

// 函数声明
void randomReadFile(const string &filename);
void randomWriteFile(const string &filename);

int main()
{
    // 创建一个大文件并初始化内容
    ofstream file("test_file.bin", ios::binary);
    if (!file)
    {
        cerr << "Failed to Create File." << endl;
        return 1;
    }

    char *buffer = new char[FILE_SIZE];
    fill(buffer, buffer + FILE_SIZE, 'A');
    file.write(buffer, FILE_SIZE);
    file.close();

    // 随机读取文件，并计算所需时间
    auto start_read = high_resolution_clock::now();
    for (int i = 0; i < NUM_ITERATIONS; ++i)
    {
        randomReadFile("test_file.bin");
    }
    auto end_read = high_resolution_clock::now();
    auto duration_read = duration_cast<milliseconds>(end_read - start_read);
    cout << "Random Reading Files Time: " << duration_read.count() << "ms" << endl;

    // 随机写入文件，并计算所需时间
    auto start_write = high_resolution_clock::now();
    for (int i = 0; i < NUM_ITERATIONS; ++i)
    {
        randomWriteFile("test_file.bin");
    }
    auto end_write = high_resolution_clock::now();
    auto duration_write = duration_cast<milliseconds>(end_write - start_write);
    cout << "Random Writing Files Time: " << duration_write.count() << "ms" << endl;

    // 删除文件并释放内存
    delete[] buffer;
    remove("test_file.bin");

    return 0;
}

// 随机读取文件函数
void randomReadFile(const string &filename)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, FILE_SIZE - 1);

    ifstream file(filename, ios::binary);
    if (!file)
    {
        cerr << "Failed to Open File." << endl;
        return;
    }

    int pos = dis(gen);
    file.seekg(pos);
    char data;
    file.read(&data, 1);
    file.close();
}

// 随机写入文件函数
void randomWriteFile(const string &filename)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, FILE_SIZE - 1);

    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file)
    {
        cerr << "Failed to Open File." << endl;
        return;
    }

    int pos = dis(gen);
    file.seekp(pos);
    char data = 'B';
    file.write(&data, 1);
    file.close();
}

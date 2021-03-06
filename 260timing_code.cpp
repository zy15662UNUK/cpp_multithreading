#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
using namespace std;

double calculatePi(int term, int start, int skip)
{
    double sum = 0.0;
    for (int i = start; i < term; i += skip)
    {
        int sign = pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }
    return sum * 4;
}
int main()
{
    vector<shared_future<double>> futures;
    const int CORE_NUM = thread::hardware_concurrency();
    auto start = chrono::steady_clock::now();
    for (int i = 0; i < CORE_NUM; i ++) 
    {
        // distribute the cal by different start point, for each start point we have a step which equals the num of thread we create
        shared_future<double> f = async(launch::async, calculatePi, 1e8, i, CORE_NUM);
        futures.push_back(f);
    }
    double sum = 0.0;
    for (auto f : futures)
    {
        sum += f.get();
    }
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << setprecision(15) << sum << endl;
    cout << "duration is " << duration << endl;
    return 0;
}
#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>
#include <chrono>
using namespace std;

int main()
{
    cout << thread::hardware_concurrency() << endl;
    return 0;
}
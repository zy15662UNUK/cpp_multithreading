#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>
using namespace std;

double calculatePi(int term)
{
    if (term < 1)
    {
        throw runtime_error("term should > 1");
    }
    double sum = 0.0;
    for (int i = 0; i < term; ++i)
    {
        int sign = pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }
    return sum * 4;
}

int main()
{
    // No need to use the wrapper lambda function as the promise do
    packaged_task<double(int)> task1(calculatePi);
    future<double> future1 = task1.get_future();
    thread t1(ref(task1), 0);
    try
    {
        cout << setprecision(15) << future1.get() << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    t1.join();
    return 0;
}
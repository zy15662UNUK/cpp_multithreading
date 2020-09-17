#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>
using namespace std;

double calculatePi(int term)
{
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
    // promise is used to collect the return value from the thread;
    promise<double> promise;
    auto func = [&](int term){
        double res = calculatePi(term);
        // store the value
        promise.set_value(res);
    };
    thread t1(func, 1e6);
    // promise pass the value to the future. future will wait the result return and then continue.otherwise it will just pause here
    future<double> future = promise.get_future();
    cout << setprecision(15) << future.get() << endl;
    t1.join();
    return 0;
}
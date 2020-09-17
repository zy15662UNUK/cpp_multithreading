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
    // promise is used to collect the return value from the thread;
    promise<double> promise;
    auto func = [&](int term) {
        // raise exception if illegal input para
        try
        {
            double res = calculatePi(term);
            // store the value
            promise.set_value(res);
        }
        catch(const std::exception& e)
        {
            // raise exception from the promise
            promise.set_exception(current_exception());
        }

        
    };
    thread t1(func, 0);
    // promise pass the value to the future. future will wait the result return and then continue.otherwise it will just pause here
    try
    {
        future<double> future = promise.get_future();
        cout << setprecision(15) << future.get() << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    t1.join();
    return 0;
}
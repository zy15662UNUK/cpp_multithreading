# include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double calculatePi(int term) 
{
    double sum = 0.0;
    for (int i = 0;i < term; ++i)
    {
        int sign = pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }
    return sum * 4;
}

int main()
{
    cout << setprecision(15) << calculatePi(1e6) << endl;
    return 0;
}
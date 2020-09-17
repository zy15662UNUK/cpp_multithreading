#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;



class App 
{
private:
    const int ITERATIONS = 1E6;
    mutex mt;
    int count = 0;
public:
// here we overload the call operator. that's what the class will do when called
    void operator()()
    {
        for (int i = 0; i < ITERATIONS; i++)
        {
            // when entering this for loop scope, lock_guard will try to acquire the mutex. It will release the mutex when exit the scope
            const lock_guard<mutex> guard(mt);
            // unique_lock does the same thing with more functionality
            // unique_lock<mutex>guard(mt);
            ++count;
        }
    }
    int getCount()
    {
        return count;
    }
};

int main()
{
    // here the thread can also be passed in a callable object. the object can be considered as a function
    App app;
    // must use ref here inorder to pass a ref
    thread t1(ref(app));
    thread t2(ref(app));
    t1.join();
    t2.join();
    cout << app.getCount() << endl;
    return 0;
}

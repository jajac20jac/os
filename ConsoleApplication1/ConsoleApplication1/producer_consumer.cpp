#include <thread>
#include <condition_variable>
#include <iostream>
#include <mutex>

using namespace std;

int num;
bool finded = false;
mutex m;
condition_variable cv;


void FindNextPrime(int n) {
    unique_lock<mutex> guard(m);
    num = n + 1;
    int tempn = num;
    while (!finded) {
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                num++;
                break;
            }
        }
        if (num == tempn) {
            finded = true;
        }
        else {
            tempn = num;
        }

    }
    guard.unlock();
    cv.notify_one();
}


void PrintThread() {
    unique_lock<mutex> guard(m);
    while (finded == false) {
        cv.wait(guard);
    }
    cout << num;
}

int main()
{
    int n;
    cin >> n;
    thread thr1(FindNextPrime, n);
    thread thr2(PrintThread);
    thr1.join();
    thr2.join();
}

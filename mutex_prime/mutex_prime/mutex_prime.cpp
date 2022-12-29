#include <iostream>
#include <mutex>
#include <vector>

using namespace std;

mutex m;

int amount = 0;

bool IsPrime(int num) {
    if (num == 0 || num == 1) {
        return false;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}
void CheckPrime(vector <int>& vec, int& position) {
    int temp;
    while (1) {
        unique_lock<mutex> guard(m);
        if (position == vec.size()) {
            return;
        }
        else {
            position++;
            temp = position;
        }
        guard.unlock();
        if (IsPrime(vec[temp - 1]))
            amount++;
    }
}

int main()
{
    int size;
    int position = 0;
    cout << "¬ведите размер вектора: \n";
    cin >> size;
    vector<int> vec(size);
    cout << "¬ведите элементы вектора: \n";
    for (int i = 0; i < size; i++) {
        cin >> vec[i];
    }
    vector<thread> thr;
    for (int i = 0; i < size; i++) {
        thr.emplace_back([&vec, &position]() {
            CheckPrime(vec, position);
        });
    }
    for (int i = 0; i < size; i++) {
        thr[i].join();
    }
    cout << amount;

}


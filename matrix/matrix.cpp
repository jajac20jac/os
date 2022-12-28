#include <iostream>
#include <vector>
#include <thread>
using namespace std;

int multi(vector<vector<int>>& vec1, vector<vector<int>>& vec2, int row, int col) {
    int fin = 0;
    for (int i = 0; i < vec1[0].size(); i++) {
        fin += vec1[i][row] * vec2[i][col];
    }
    return fin;
}

int main() {

    int size1, size2, size3, size4, temp;
    cout << "input the dimensions of the first matrix \n";
    cin >> size1 >> size2;


    vector<vector<int>> mat1(size1, vector<int>(size2));
    cout << "input first matrix";
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            cin >> temp;
            mat1[i][j] = temp;
        }
    }
    cout << "input the dimensions of the second matrix \n";
    cin >> size3 >> size4;
    vector<vector<int>> mat2(size3, vector<int>(size4));
    cout << "input second matrix";
    for (int i = 0; i < size3; i++) {
        for (int j = 0; j < size4; j++) {
            cin >> temp;
            mat2[i][j] = temp;
        }
    }
    //    for (int i = 0; i < size; i++){
    //        for (int j = 0; j < size; j++){
    //            cout << mat1[i][j] << " ";
    //        }
    //        cout << endl;
    //    }
    //    for (int i = 0; i < size; i++){
    //        for (int j = 0; j < size; j++){
    //            cout << mat2[i][j] << " ";
    //        }
    //        cout << endl;
    //    }
    vector<vector<int>> finalmat(size1, vector<int>(size4));
    vector <thread> thr;
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size4; j++) {
            thr.emplace_back([&finalmat, &mat1, &mat2, i, j]() {
                finalmat[i][j] = multi(mat1, mat2, i, j);
            });
        }
    }
//    cout << "12312321";
    for (int i = 0; i < thr.size(); i++) {
        thr[i].join();
    }
    cout << "finalmatrix is:";
    for (int i = 0; i < finalmat.size(); i++) {
        for (int j = 0; j < finalmat[i].size(); j++) {
            cout << finalmat[i][j] << " ";
        }
        cout << endl;
    }
}

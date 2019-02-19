//
// Created by howiemalowie on 2/19/19.
//
#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;

int main(int argc, char** argv){

    string file1 = argv[1];
    string file2 = argv[2];
    string myString;

    int my_rank;
    int comm_sz;

    int n, m, k, r;
    string a, b, c;
    string input;
    int inputSize;
    int stringLength;

    vector<vector<int>> S;
    vector<int> F;
    vector<tuple<int, int, int>> I;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


    ifstream infile1(file1);
    string line1;
    if (infile1.is_open()) {
        getline(infile1, line1);
        n = stoi(line1);
        getline(infile1, line1);
        m = stoi(line1);
        getline(infile1, line1);
        k = stoi(line1);
        S.resize(k);
        getline(infile1, line1);
        r = stoi(line1);
        for (int i = 0; i < k; i++) {
            S[i].resize(k);
            for (int j = 0; j < k; j++) {
                infile1 >> a >> b >> c;
                S[stoi(a)][stoi(b)] = stoi(c);
            }

        }
        for (int i = 0; i < r; i++) {
            getline(infile1, line1);
            F.push_back(stoi(line1));
        }
        for (int i = 0; i < m; i++) {
            infile1 >> a >> b >> c;
            I.push_back(make_tuple(stoi(a), stoi(b), stoi(c)));
        }
    }
    infile1.close();

    if(my_rank == 0){
        ifstream infile2(file2);
        if(infile2.is_open()) {
            getline(infile2, input);
        }
        infile2.close();
        inputSize = input.size();
        stringLength = inputSize / comm_sz;
        MPI_Bcast(&inputSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

        for(int i=1; i<comm_sz; i++){
            myString = input.substr(i*stringLength, stringLength);
            MPI_Send(&myString, stringLength, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
        myString = input.substr(0, stringLength);
    }
    else{
        MPI_Bcast(&inputSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
        stringLength = inputSize / comm_sz;

        myString.resize(stringLength);

        MPI_Recv(&myString, stringLength, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    int mySum = 1;
    int counter = 0;
    for (int i=comm_sz*stringLength; i<comm_sz*stringLength+stringLength; i++){
        if (myString[counter] == '0'){
            mySum = mySum * get<1>(I[i]);
        }
        else{
            mySum = mySum * get<2>(I[i]);
        }
    }
    int tempSum;
    if(my_rank == 0){
        for(int i=1; i<comm_sz; i++){
            MPI_Recv(&tempSum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            mySum = mySum * tempSum;
        }

        if(find(F.begin(), F.end(), mySum) != F.end()){
            cout << '1';
        }
        else{
            cout << '0';
        }
    }
    else{
        tempSum = mySum;
        MPI_Send(&tempSum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}

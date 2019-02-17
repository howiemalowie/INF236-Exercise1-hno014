/* 
Copyright 2019 Haavard Notland 

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<bitset>
#include<vector>
#include <algorithm>
#include <fstream>
#include<cmath>

using namespace std;


string buildString(vector<string> board, int j, int k, int dim) {

    string b;

            if (j == 0) {

                if (k == 0) {
                    b.push_back(board[dim - 1][dim - 1]);
                    b.push_back(board[dim - 1][k]);
                    b.push_back(board[dim - 1][k + 1]);

                    b.push_back(board[j][dim - 1]);
                    b.push_back(board[j][k]);
                    b.push_back(board[j][k + 1]);

                    b.push_back(board[j + 1][dim - 1]);
                    b.push_back(board[j + 1][k]);
                    b.push_back(board[j + 1][k + 1]);
                } else if (k == dim - 1) {
                    b.push_back(board[dim - 1][k - 1]);
                    b.push_back(board[dim - 1][k]);
                    b.push_back(board[dim - 1][0]);

                    b.push_back(board[j][k - 1]);
                    b.push_back(board[j][k]);
                    b.push_back(board[j][0]);

                    b.push_back(board[j + 1][k - 1]);
                    b.push_back(board[j + 1][k]);
                    b.push_back(board[j + 1][0]);

                } else {
                    b.push_back(board[dim - 1][k - 1]);
                    b.push_back(board[dim - 1][k]);
                    b.push_back(board[dim - 1][k + 1]);

                    b.push_back(board[j][k - 1]);
                    b.push_back(board[j][k]);
                    b.push_back(board[j][k + 1]);

                    b.push_back(board[j + 1][k - 1]);
                    b.push_back(board[j + 1][k]);
                    b.push_back(board[j + 1][k + 1]);
                }
            } else if (j == dim - 1) {

                if (k == 0) {
                    b.push_back(board[j - 1][dim - 1]);
                    b.push_back(board[j - 1][k]);
                    b.push_back(board[j - 1][k+1]);

                    b.push_back(board[j][dim - 1]);
                    b.push_back(board[j][k]);
                    b.push_back(board[j][k + 1]);

                    b.push_back(board[0][dim - 1]);
                    b.push_back(board[0][k]);
                    b.push_back(board[0][k + 1]);
                } else if (k == dim - 1) {
                    b.push_back(board[j-1][k - 1]);
                    b.push_back(board[j-1][k]);
                    b.push_back(board[j-1][0]);

                    b.push_back(board[j][k - 1]);
                    b.push_back(board[j][k]);
                    b.push_back(board[j][0]);

                    b.push_back(board[0][k - 1]);
                    b.push_back(board[0][k]);
                    b.push_back(board[0][0]);

                } else {
                    b.push_back(board[j - 1][k - 1]);
                    b.push_back(board[j - 1][k]);
                    b.push_back(board[j - 1][k + 1]);

                    b.push_back(board[j][k - 1]);
                    b.push_back(board[j][k]);
                    b.push_back(board[j][k + 1]);

                    b.push_back(board[0][k - 1]);
                    b.push_back(board[0][k]);
                    b.push_back(board[0][k + 1]);

                }
            }   else{

                    if(k==0){
                        b.push_back(board[j - 1][dim-1]);
                        b.push_back(board[j - 1][k]);
                        b.push_back(board[j - 1][k + 1]);

                        b.push_back(board[j][dim - 1]);
                        b.push_back(board[j][k]);
                        b.push_back(board[j][k + 1]);

                        b.push_back(board[j + 1][dim - 1]);
                        b.push_back(board[j + 1][k]);
                        b.push_back(board[j + 1][k + 1]);

                    } else if(k==dim-1){

                        b.push_back(board[j - 1][k - 1]);
                        b.push_back(board[j - 1][k]);
                        b.push_back(board[j - 1][0]);

                        b.push_back(board[j][k - 1]);
                        b.push_back(board[j][k]);
                        b.push_back(board[j][0]);

                        b.push_back(board[j + 1][k - 1]);
                        b.push_back(board[j + 1][k]);
                        b.push_back(board[j + 1][0]);
                    }
                    else{
                        b.push_back(board[j - 1][k - 1]);
                        b.push_back(board[j - 1][k]);
                        b.push_back(board[j - 1][k + 1]);

                        b.push_back(board[j][k - 1]);
                        b.push_back(board[j][k]);
                        b.push_back(board[j][k + 1]);

                        b.push_back(board[j + 1][k - 1]);
                        b.push_back(board[j + 1][k]);
                        b.push_back(board[j + 1][k + 1]);
                    }
            }
                return b;
            }


int binConv(string binary)
{
    int decimal = 0;
    int indexCounter = 0;
    cout << "Binary: " << binary;

    //TODO: CONVERT TO DECIMAL
    for(int i = binary.length()-1; i >= 0; i--)
    {

        if(binary[i] == '1')
        {
            decimal += pow(2, indexCounter);
        }
        indexCounter++;
    }

    printf(" Decimal: %d", decimal);
    cout << '\n';
    return (decimal);
}


int main(int argsv, char** argsc) {
    int dim;
    vector<string> rules;
    vector<string> board;

    string file2 = "/home/howiemalowie/INF236-Exercise1-hno014/ProblemSet1/2-Sequential/blinker.txt";
    int t = 1;


    ifstream infile(file2);
    string line;

    getline(infile, line);
    dim = atoi(line.c_str());
    cout << dim << "\n";
    for(int i=0; i< dim;i++){
        (getline(infile, line));
        board.push_back(line);
    }
    infile.close();

    for (int i = 0; i < 512; i++) {
        string binary = bitset<9>(i).to_string(); //to binary
        size_t n = count(binary.begin(), binary.end(), '1');
        if (binary[4] == '0') {
            if (n == 3) {
                binary += " 1";
            } else {
                binary += " 0";
            }
        } else {
            if (n > 2 && n < 5) {
                binary += " 1";
            } else {
                binary += " 0";
            }

        }
        rules.push_back(binary);
    }

    vector<string> newBoard = board;

    string b;
    for (int i = 0; i < t; i++) {

        for (int j = 0; j < dim; j++) {
            for (int k = 0; k < dim; k++) {
                b = buildString(board, j, k, dim);

                int index = binConv(b);

                newBoard[j][k] = rules[index].back();
            }
        }
        board = newBoard;
    }

    for (int i = 0; i < dim; ++i)
    {
        cout << board[i] << endl;
    }
    cout << '\n';

    return 0;
}


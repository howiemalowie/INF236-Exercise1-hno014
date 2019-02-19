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

#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <tuple>
#include <algorithm>


using namespace std;

int main(int argc, char** argv){
    string file1 = argv[1];
    string file2 = argv[2];

    int n, m, k, r;
    string a, b, c;
    string input;

    vector<vector<int>> S;
    vector<int> F;
    vector<tuple<int, int, int>> I;

    ifstream infile1(file1);
    string line1;
    if(infile1.is_open()){
        getline(infile1, line1);
        n = stoi(line1);
        getline(infile1, line1);
        m = stoi(line1);
        getline(infile1, line1);
        k = stoi(line1);
        S.resize(k);
        getline(infile1, line1);
        r = stoi(line1);
        for(int i=0; i<k; i++){
            S[i].resize(k);
            for(int j=0; j<k; j++){
                infile1 >> a >> b >> c;
                S[stoi(a)][stoi(b)] = stoi(c);
            }

        }
        for(int i=0; i<r; i++){
            getline(infile1, line1);
            F.push_back(stoi(line1));
        }
        for(int i=0; i<m; i++){
            infile1 >> a >> b >> c;
            I.push_back(make_tuple(stoi(a), stoi(b), stoi(c)));
        }
    }

    infile1.close();

    ifstream infile2(file2);
    getline(infile2, input);
    vector<int> branch;
    int sum = 1;
    for(int i=0; i<m; i++){
        if(input[i] == '0'){
           branch.push_back(get<1>(I[i]));
           sum = sum * get<1>(I[i]);
        }
        else{
            branch.push_back(get<2>(I[i]));
            sum = sum * get<2>(I[i]);
        }
    }
    if(find(F.begin(), F.end(), sum) != F.end()) {
        return 1;
    }
    return 0;
}
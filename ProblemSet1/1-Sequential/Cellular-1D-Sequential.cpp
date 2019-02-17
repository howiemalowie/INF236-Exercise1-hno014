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


#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef map<string, char> Map;

int Cellular1DSequential(string file1, string file2, int t){

    vector<vector<char>> matrix;
    int length;
    //Read file1
    ifstream myReadFile(file1);
    Map rules;
    map<string, char>::iterator it;
    if (myReadFile.is_open()) {
        string a;
        char b;
        while (myReadFile >> a >> b) {
            rules.insert(pair<string, char>(a,b));
        }
    }
    myReadFile.close();


    //Read file2
    ifstream myReadFile2(file2);
    vector<char> booleanstring;
    if(myReadFile2.is_open()){
        myReadFile2 >> length;
        char ch;
        for(int i=0; i<length; i++){
            myReadFile2 >> ch;
            booleanstring.push_back(ch);
        }
    }
    myReadFile2.close();

    char inp[3];
    for(int i=0; i<t; i++){

        matrix.push_back(booleanstring);

        vector<char> newbooleanstring(booleanstring);

        for(int j=0; j<booleanstring.size();j++){

            inp[1] = booleanstring[j];
            if(j==0){
                inp[0] = booleanstring[booleanstring.size()-1];
                inp[2] = booleanstring[j+1];
            }
            else if(j == booleanstring.size()-1){
                inp[0] = booleanstring[j-1];
                inp[2] = booleanstring[0];
            }
            else{
                inp[0] = booleanstring[j-1];
                inp[2] = booleanstring[j+1];
            }

            char changeTo = rules.find(inp)->second;


            //Make change to new string
            newbooleanstring[j] = changeTo;
        }

        //Overwrite old string before iterating
        booleanstring = newbooleanstring;
    }
    //Push the last config to matrix
    matrix.push_back(booleanstring);

    for(auto elem : matrix){
        for(int i=0; i< elem.size(); i++){
            if(elem[i] == '1'){
                printf("\u25A0");
            }
            else{
                printf(" ");
            }

        }
        cout << '\n';
    }


    return 0;
}

int main(){

    int n = Cellular1DSequential("/home/howiemalowie/INF236-Exercise1-hno014/ProblemSet1/1-Sequential/mod2.txt", "/home/howiemalowie/INF236-Exercise1-hno014/ProblemSet1/1-Sequential/middle30.txt", 100);

    return n;
}

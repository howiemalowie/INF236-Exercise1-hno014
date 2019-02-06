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
            cout << elem[i];
        }
        cout << '\n';
    }


    return 0;
}

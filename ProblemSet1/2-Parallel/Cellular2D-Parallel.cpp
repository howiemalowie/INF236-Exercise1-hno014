//
// Created by howiemalowie on 2/5/19.
//

#include<mpi.h>
#include<vector>
#include<string>
#include<fstream>
#include<cmath>

using namespace std;

void buildString(char* builtString, char partition[], int counter, int x, int y, int dim){

    //TODO: Create string of nearby elements
    char up,down,left,right,upleft,downright,upright,downleft;


    if(x==0){
        if(y==0){

        }
    }




}

int main(int argc, char** argv){

    const int ruleLength = 11;
    int my_rank;
    int comm_sz;
    int dim;
    int rules_size, board_size;
    int* sendbuf;
    int part;
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    vector<vector<char>> rules;
    vector<vector<char>> board;
    char temp_board[dim*dim];

    string file1 = argv[1];
    string file2 = argv[2];
    int t = atoi(argv[3]);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


    if(my_rank == 0){
        ifstream infile1(file1);
        string line1;

        while(getline(infile1, line1)){
            vector<char> line1_char(line1.begin(), line1.end());
            rules.push_back(line1_char);
        }
        infile1.close();

        rules_size = rules.size();


        ifstream infile2(file2);
        string line2;

        getline(infile2, line2);
        dim = atoi(line2.c_str());
        for(int i=0; i< dim;i++){
            (getline(infile2, line2));
            vector<char> line2_char(line2.begin(), line2.end());
            board.push_back(line2_char);
        }
        infile2.close();

        //Create temporary 1D-version of board

        int counter = 0;
        for(vector<char> v : board){
            for(char c : v){
                temp_board[counter] = c;
                counter++;
            }
        }

        part = dim*dim/comm_sz;


        MPI_Bcast(&part, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&rules_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&rules[0][0], rules_size, MPI_CHAR, 0, MPI_COMM_WORLD);
    }

    else{
        MPI_Bcast(&part, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&rules_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
        rules.resize(rules_size, vector<char>(ruleLength));
        MPI_Bcast(&rules[0][0], rules_size, MPI_CHAR, 0, MPI_COMM_WORLD);
    }

    sendbuf = (int *)malloc(part*sizeof(char));
    MPI_Scatter(&temp_board, part, MPI_CHAR, sendbuf, part, MPI_CHAR, 0, MPI_COMM_WORLD);

    //Find the x and y coordinate on the board for each partition's start and end point
    dim = sqrt(part*comm_sz);
    xStart = my_rank * part/dim;
    yStart = (my_rank * part) % dim;
    xEnd = xStart + part/dim;
    yEnd = (yStart + part-1) % dim;

    int x = xStart;
    int y = yStart;
    char newString[part];
    char builtString[9];
    int counter = 0;
    for(char c : temp_board){

        char up=c, down=c, left=c, right=c;
        int rankOfProcessBelow = my_rank + (dim+counter)/part;
        if(rankOfProcessBelow > comm_sz-1){
            rankOfProcessBelow -= comm_sz;
        }
        int rankOfProcessAbove = my_rank - (dim/part);
        if(rankOfProcessAbove < 0){
            rankOfProcessAbove += comm_sz;
        }
        MPI_Send(&up, 1, MPI_CHAR, rankOfProcessBelow, 0, MPI_COMM_WORLD);
        MPI_Send(&down, 1, MPI_CHAR, rankOfProcessAbove, 0, MPI_COMM_WORLD);

        if(counter==0 && comm_sz != 1){

        }

        buildString(builtString, temp_board, counter, x, y, dim);

        if(y == dim-1){
            x++;
            y = 0;
        }
        else{
            y++;
        }
        counter++;
    }



    MPI_Finalize();
}
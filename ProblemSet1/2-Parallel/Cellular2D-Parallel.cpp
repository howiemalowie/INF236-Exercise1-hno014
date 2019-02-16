//
// Created by howiemalowie on 2/5/19.
//

#include<mpi.h>
#include<vector>
#include<string>
#include<fstream>
#include<cmath>
#include<iostream>
#include <ctime>

using namespace std;

void buildString(char* builtString, vector<vector<char>> myLines, vector<char> firstLine,
        vector<char> lastLine, int x, int y, int n){

    int d = myLines.size()-1;
    //Control edge cases
    if(x==0){
        if(y==0){
            builtString[0] = firstLine[n-1];
            builtString[1] = firstLine[y];
            builtString[2] = firstLine[y+1];

            builtString[3] = myLines[x][n-1];
            builtString[4] = myLines[x][y];
            builtString[5] = myLines[x][y+1];

            builtString[6] = myLines[x+1][n-1];
            builtString[7] = myLines[x+1][y];
            builtString[8] = myLines[x+1][y+1];
        }
        else if(y==n-1){
            builtString[0] = firstLine[y-1];
            builtString[1] = firstLine[y];
            builtString[2] = firstLine[0];

            builtString[3] = myLines[x][y-1];
            builtString[4] = myLines[x][y];
            builtString[5] = myLines[x][0];

            builtString[6] = myLines[x+1][y-1];
            builtString[7] = myLines[x+1][y];
            builtString[8] = myLines[x+1][0];
        }
        else {
            builtString[0] = firstLine[y - 1];
            builtString[1] = firstLine[y];
            builtString[2] = firstLine[y + 1];

            builtString[3] = myLines[x][y-1];
            builtString[4] = myLines[x][y];
            builtString[5] = myLines[x][y+1];

            builtString[6] = myLines[x+1][y-1];
            builtString[7] = myLines[x+1][y];
            builtString[8] = myLines[x+1][y+1];
        }
    }
    else if(x == d){
        if(y==0){
            builtString[0] = myLines[x-1][n-1];
            builtString[1] = myLines[x-1][y];
            builtString[2] = myLines[x-1][y+1];

            builtString[3] = myLines[x][n-1];
            builtString[4] = myLines[x][y];
            builtString[5] = myLines[x][y+1];

            builtString[6] = lastLine[n-1];
            builtString[7] = lastLine[y];
            builtString[8] = lastLine[y+1];
        }
        else if(y==n-1){
            builtString[0] = myLines[x-1][y-1];
            builtString[1] = myLines[x-1][y];
            builtString[2] = myLines[x-1][0];

            builtString[3] = myLines[x][y-1];
            builtString[4] = myLines[x][y];
            builtString[5] = myLines[x][0];

            builtString[6] = lastLine[y-1];
            builtString[7] = lastLine[y];
            builtString[8] = lastLine[0];
        }
        else {
            builtString[0] = myLines[x-1][y-1];
            builtString[1] = myLines[x-1][y];
            builtString[2] = myLines[x-1][y+1];

            builtString[3] = myLines[x][y-1];
            builtString[4] = myLines[x][y];
            builtString[5] = myLines[x][y+1];

            builtString[6] = lastLine[y - 1];
            builtString[7] = lastLine[y];
            builtString[8] = lastLine[y + 1];
        }

    } else{
        if(y==0){
            builtString[0] = myLines[x-1][n-1];
            builtString[1] = myLines[x-1][y];
            builtString[2] = myLines[x-1][y+1];

            builtString[3] = myLines[x][n-1];
            builtString[4] = myLines[x][y];
            builtString[5] = myLines[x][y+1];

            builtString[6] = myLines[x+1][n-1];
            builtString[7] = myLines[x+1][y];
            builtString[8] = myLines[x+1][y+1];
        }
        else if(y == n-1){
            builtString[0] = myLines[x-1][y-1];
            builtString[1] = myLines[x-1][y];
            builtString[2] = myLines[x-1][0];

            builtString[3] = myLines[x][y-1];
            builtString[4] = myLines[x][y];
            builtString[5] = myLines[x][0];

            builtString[6] = myLines[x+1][y-1];
            builtString[7] = myLines[x+1][y];
            builtString[8] = myLines[x+1][0];
        }
        else{
            builtString[0] = myLines[x-1][y-1];
            builtString[1] = myLines[x-1][y];
            builtString[2] = myLines[x-1][y+1];

            builtString[3] = myLines[x][y-1];
            builtString[4] = myLines[x][y];
            builtString[5] = myLines[x][y+1];

            builtString[6] = myLines[x+1][y-1];
            builtString[7] = myLines[x+1][y];
            builtString[8] = myLines[x+1][y+1];
        }
    }
}

int binConv(char* binary)
{
    int decimal = 0;
    int indexCounter = 0;

    for(int i = 8; i >= 0; i--)
    {

        if(binary[i] == '1')
        {
            decimal += pow(2, indexCounter);
        }
        indexCounter++;
    }
    return (decimal);
}

int main(int argc, char **argv){

    string file1 = argv[1];
    string file2 = argv[2];
    int t = atoi(argv[3]);


    clock_t start;
    double time;
    int my_rank;
    int comm_sz;
    int part;
    int n;
    vector<vector<char>> rules;
    vector <vector<char>> board;
    vector <vector<char>> myLines;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


    //All processes read the rules
    ifstream infile1(file1);
    string line1;
    if(infile1.is_open()){
        while(getline(infile1, line1)){
            vector<char> line1_char(line1.begin(), line1.end());
            rules.push_back(line1_char);
        }
    }

    infile1.close();



        //Root process reads random board
        if (my_rank == 0) {

            ifstream infile2(file2);
            string line2;
            if (infile2.is_open()) {
                getline(infile2, line2);
                n = stoi(line2);
                //cout << n;
                while (getline(infile2, line2)) {
                    vector<char> line2_char(line2.begin(), line2.end());
                    board.push_back(line2_char);
                }
            }

            part = n / comm_sz;

            //Broadcast how many lines each process receives
            MPI_Bcast(&part, 1, MPI_INT, 0, MPI_COMM_WORLD);

            start = clock();
            //Give lines to root process
            for (int i = 0; i < part; i++) {
                myLines.push_back(board.at(i));
            }


            //Distribute lines to other processes
            int lineToSend = part;
            vector<char> line;
            for (int i = 1; i < comm_sz - 1; i++) {
                for (int j = 0; j < part; j++) {
                    line = board[lineToSend];
                    //cout << "\nTrying to send to process " << i;
                    MPI_Send(&line[0], n, MPI_CHAR, i, 0, MPI_COMM_WORLD);
                    lineToSend++;
                }
            }

            //Send remaining lines to last process
            while (lineToSend < n) {
                line = board[lineToSend];
                //cout << "\nTrying to send to process " << comm_sz - 1;
                MPI_Send(&line[0], n, MPI_CHAR, comm_sz - 1, 0, MPI_COMM_WORLD);
                lineToSend++;
            }

        } else {
            MPI_Bcast(&part, 1, MPI_INT, 0, MPI_COMM_WORLD);

            n = part * comm_sz;
            vector<char> line(n);
            for (int j = 0; j < part; j++) {
                MPI_Recv(&line[0], n, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                myLines.push_back(line);
            }


            if (my_rank == comm_sz - 1) {
                for (int i = 0; i < n % comm_sz; i++) {
                    MPI_Recv(&line[0], n, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    myLines.push_back(line);
                }
            }
        }

        //Update board k times
        for (int k = 0; k < t; k++) {


            //Send and receive neighbour lines
            vector<char> lastLine = myLines[0];
            vector<char> firstLine = myLines[myLines.size() - 1];
            int rankAbove = my_rank - 1;
            int rankBelow = my_rank + 1;

            if (my_rank == 0) {
                rankAbove = comm_sz - 1;
            } else if (my_rank == comm_sz - 1) {
                rankBelow = 0;
            }

            //cout << "\n" << my_rank << " trying to send to process " << rankAbove;
            MPI_Send(&lastLine[0], n, MPI_CHAR, rankAbove, 0, MPI_COMM_WORLD);
            //cout << "\n" << my_rank << " trying to send to process " << rankBelow;
            MPI_Send(&firstLine[0], n, MPI_CHAR, rankBelow, 0, MPI_COMM_WORLD);

            MPI_Recv(&lastLine[0], n, MPI_CHAR, rankBelow, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&firstLine[0], n, MPI_CHAR, rankAbove, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            //Update cells
            vector<vector<char>> newLines = myLines;
            int bin;
            char builtString[9];
            int d = myLines.size();
            for (int i = 0; i < d; i++) {
                for (int j = 0; j < n; j++) {
                    buildString(builtString, myLines, firstLine, lastLine, i, j, n);


                    bin = binConv(builtString);

                    newLines[i][j] = rules[bin].back();
                }
            }

            //Gather final board
            if(k == t-1){
                vector<char> line(n);
                if (my_rank == 0) {
                    //Receive updated lines
                    for (int i = 1; i < comm_sz - 1; i++) {
                        for (int j = 0; j < part; j++) {
                            MPI_Recv(&line[0], n, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                            newLines.push_back(line);
                        }
                    }

                    //Receive additional lines from last process
                    for (int i = 0; i < n % comm_sz; i++) {
                        MPI_Recv(&line[0], n, MPI_CHAR, comm_sz - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        newLines.push_back(line);
                    }

                    time = (clock() - start) / (double) CLOCKS_PER_SEC;
                    printf("Time to compute step %d with boardsize %d and %d processes: %.6f seconds.\n", t, n, comm_sz, time);

                    board = newLines;
                } else {
                    //Send updated cells to root
                    int d = newLines.size();
                    for (int i = 0; i < d; i++) {
                        line = newLines[i];
                        MPI_Send(&line[0], n, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
                    }
                }
            }
        }


    MPI_Finalize();

    return 0;
}
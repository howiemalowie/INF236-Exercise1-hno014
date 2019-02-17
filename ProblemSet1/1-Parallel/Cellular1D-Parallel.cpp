#include <mpi.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>

using namespace std;

typedef map<string, char> Map;

int main(int argc, char **argv) {


    string file = argv[1];
    int t = atoi(argv[2]);
    int stringSize;
    int comm_sz;
    int my_rank;
    clock_t start;
    double time;

    //Read file
    ifstream myReadFile(file);
    Map rules;
    map<string, char>::iterator it;
    if (myReadFile.is_open()) {
        string a;
        char b;
        while (myReadFile >> a >> b) {
            rules.insert(pair<string, char>(a, b));
        }
    }
    myReadFile.close();

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    for(int k=10; k<=20; k++) {


        if(my_rank==0){
            vector<char> booleanstring(k, '0');
            booleanstring.push_back('1');
            booleanstring.insert(booleanstring.end(), booleanstring.begin(), booleanstring.end());
            booleanstring.pop_back();
            booleanstring.pop_back();
            stringSize = booleanstring.size();
            MPI_BCast(&stringSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_BCast(&booleanstring[0], stringSize, MPI_CHAR, 0, MPI_COMM_WORLD);
        }
        else{
            MPI_BCast(&stringSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_BCast(&booleanstring[0], stringSize, MPI_CHAR, 0, MPI_COMM_WORLD);
        }


        //Find index of partition for process
        int partSize = booleanstring.size() / comm_sz;
        int st = partSize * (my_rank);
        int end;

        //Check if it is the last process
        //The process will have to take all elements remaining in string
        if (my_rank == comm_sz - 1) {
            end = booleanstring.size() - 1;
        } else {
            end = st + partSize - 1;
        }


        if (my_rank == 0) {
            start = clock();
        }

        for (int i = 0; i < t; i++) {

            char sendBack = booleanstring[st];
            char sendForward = booleanstring[end];
            vector<char> myString(end - st + 1);



            if(comm_sz == 1) {
                MPI_Send(&sendBack, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
                MPI_Send(&sendForward, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

                MPI_Recv(&sendBack, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&sendForward, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            } else if (my_rank == 0) {
                MPI_Send(&sendBack, 1, MPI_CHAR, comm_sz - 1, 0, MPI_COMM_WORLD);
                MPI_Send(&sendForward, 1, MPI_CHAR, my_rank + 1, 0, MPI_COMM_WORLD);

                MPI_Recv(&sendBack, 1, MPI_CHAR, my_rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&sendForward, 1, MPI_CHAR, comm_sz - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            } else if (my_rank == comm_sz - 1) {
                MPI_Send(&sendBack, 1, MPI_CHAR, my_rank - 1, 0, MPI_COMM_WORLD);
                MPI_Send(&sendForward, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

                MPI_Recv(&sendBack, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&sendForward, 1, MPI_CHAR, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            } else {
                MPI_Send(&sendBack, 1, MPI_CHAR, my_rank - 1, 0, MPI_COMM_WORLD);
                MPI_Send(&sendForward, 1, MPI_CHAR, my_rank + 1, 0, MPI_COMM_WORLD);

                MPI_Recv(&sendBack, 1, MPI_CHAR, my_rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&sendForward, 1, MPI_CHAR, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }


            char inp[3];
            int count = 1;
            for (int j = st + 1; j < end; j++) {
                inp[0] = booleanstring[j - 1];
                inp[1] = booleanstring[j];
                inp[2] = booleanstring[j + 1];

                char changeTo = rules.find(inp)->second;

                //Make change to new string
                myString[count] = changeTo;
                count++;
            }



            //Check if each partition is just 1 element
            if (st == end) {
                inp[0] = sendForward;
                inp[1] = booleanstring[st];
                inp[2] = sendBack;

                char changeTo = rules.find(inp)->second;

                //Make change to new string
                myString[0] = changeTo;
            } else {
                inp[0] = sendForward;
                inp[1] = booleanstring[st];
                inp[2] = booleanstring[st + 1];

                char changeTo = rules.find(inp)->second;

                //Make change to new string
                myString[0] = changeTo;

                inp[0] = booleanstring[end - 1];
                inp[1] = booleanstring[end];
                inp[2] = sendBack;

                changeTo = rules.find(inp)->second;

                //Make change to new string
                myString[myString.size() - 1] = changeTo;
            }

            if(comm_sz == 1){
                booleanstring = myString;

            } else if (my_rank == 0) {

                vector<char> newString;

                newString.insert(newString.end(), myString.begin(), myString.end());

                for (int i = 1; i < comm_sz - 1; i++) {
                    MPI_Recv(&myString[0], myString.size(), MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    newString.insert(newString.end(), myString.begin(), myString.end());
                }

                int mySize;
                MPI_Recv(&mySize, 1, MPI_INT, comm_sz - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                myString.resize(mySize);

                MPI_Recv(&myString[0], myString.size(), MPI_CHAR, comm_sz - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                newString.insert(newString.end(), myString.begin(), myString.end());

                booleanstring = newString;
                //Broadcast updated string
                MPI_Bcast(booleanstring.data(), booleanstring.size(), MPI_CHAR, 0, MPI_COMM_WORLD);

            } else if (my_rank == comm_sz - 1) {

                int mySize = myString.size();
                MPI_Send(&mySize, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

                MPI_Send(&myString[0], mySize, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

                MPI_Bcast(booleanstring.data(), booleanstring.size(), MPI_CHAR, 0, MPI_COMM_WORLD);
            } else {

                MPI_Send(&myString[0], myString.size(), MPI_CHAR, 0, 0, MPI_COMM_WORLD);

                MPI_Bcast(booleanstring.data(), booleanstring.size(), MPI_CHAR, 0, MPI_COMM_WORLD);

            }
            //Wait until all processes have updated the string to continue
            MPI_Barrier(MPI_COMM_WORLD);

        }

        if (my_rank == 0) {
            time = (clock() - start) / (double) CLOCKS_PER_SEC;
            printf("Time to compute step %d with m of size %d and %d processes: %.4f seconds.\n", t, k, comm_sz, time);
        }
    }



    MPI_Finalize();

    return 0;
}
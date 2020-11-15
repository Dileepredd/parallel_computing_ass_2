#include<iostream>
#include<bits/stdc++.h>
#include<mpi/mpi.h>
using namespace std;

void random_number_generator(int array[],int start,int end)
{
    srand(time(NULL));
    for (int i=start;i<end;i++)
    {
        int temp = rand()%10;
        array[i] = temp;
    }
}

int main(int argc,char** argv)
{
    int rank/*rank of the current process in the world*/;
    int np/*number of processes in the world*/;
    int n = atoi(argv[1])/*number of elements in the array*/;
    MPI_Init(&argc,&argv)/*initialize mpi environment*/;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank)/*rank initialization in the world*/;
    MPI_Comm_size(MPI_COMM_WORLD,&np)/*number of processes in the world*/;
    int array[n]/*data to be sent*/;
    int data[n]/*data to be received*/;
    random_number_generator(array,0,n);
    int next = (rank+1)%np;
    int prev = (rank+np-1)%np;
    MPI_Status info; 
    if(rank%2 == 0)
    {
        MPI_Send(array,n,MPI_INT,next,0,MPI_COMM_WORLD);
        MPI_Recv(data,n,MPI_INT,prev,0,MPI_COMM_WORLD,&info);
    }
    else
    {
        MPI_Recv(data,n,MPI_INT,prev,0,MPI_COMM_WORLD,&info);
        MPI_Send(array,n,MPI_INT,next,0,MPI_COMM_WORLD);
    }
    // print
    for(int i=0;i<n;i++)
    {
        cout<<"data item in rank "<<rank<<" is "<<array[i]<<endl;
    }
    MPI_Finalize();
    return 0;
}
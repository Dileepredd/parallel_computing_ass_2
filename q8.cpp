#include <bits/stdc++.h>
#include <mpi/mpi.h>
#include <chrono>
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
    int rank/*rank of the current process*/,np/*number of processes in the world*/;
    int sum = 0;/*sum of the array elements in the current process*/
    int total_sum = 0;/*sum of total elements present in all processes*/
    int n = atoi(argv[1]);/*number of elements in the array*/
    int array1[n];/*data for computation*/
    int array2[n];
    MPI_Init(&argc,&argv);/*initialize the mpi environment*/
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    int start,end; /*sum of array subproblem for indices [start,end)*/
    if(rank < n%np)
    {
        start = rank*(n/np) + rank;
        end = start + n/np + 1;
    }
    else
    {
        start = rank*(n/np) + n%np;
        end = start + n/np;
    }
    random_number_generator(array1,start,end);
    random_number_generator(array2,start,end);

    for(int i=start;i<end;i++)
    {
        sum += array1[i]*array2[i];
    }
    MPI_Reduce(&sum,&total_sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank == 0)
    {
        cout<<"total sum is: "<<total_sum<<endl;
    }
    MPI_Finalize();/*finalizing the mpi environment*/
    return 0;
}
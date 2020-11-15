#include <bits/stdc++.h>
#include <mpi/mpi.h>
using namespace std;
int main(int argc, char **argv)
{
    int rank, np;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    int n = atoi(argv[1]);
    int array[n];
    int size = 0;
    int flag = atoi(argv[2]);
    int L;
    if (flag == 1)
    {
        L = n/np + ((n%np == 0)?0:1);
        int start = rank*L;
        int end = (start + L >= n)? n: start+L;
        size = end-start; 
        int i = 0;
        for(int i=0;i<size;i++)
        {
            array[i] = start+i;
        }
    }
    else if(flag==2)
    {
        int j=0;
        size=0;
        for(int i=rank;i<n;i+=np)
        {
            array[j] = i;
            j++;
            size++;
        }
    }
    else
    {
        int j=0;
        size=0;
        int r = 2;/*block size*/
        for(int i=r*rank;i<n;i+=np*r)
        {
            for(int k=0;k<r&&(i+k<n);k++)
            {
                array[j] = i+k;
                j++;
                size++;
            }
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    int local_sum = 0;
    for (int i=0;i<size;i++)
        local_sum += array[i];
    int total_sum = 0;
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("Total Sum:%d\n", total_sum);
    }
    MPI_Finalize();
}
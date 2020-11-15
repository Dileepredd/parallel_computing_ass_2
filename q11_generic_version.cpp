#include<bits/stdc++.h>
// #include<thread>
#include<mpi/mpi.h>
#include<omp.h>
using namespace std;

int threadcounter;
int proccounter;
int i=1;

void iittp_barrier()
{
    int rank,np;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    int tid,ntd;
    tid = omp_get_thread_num();
    ntd = omp_get_num_threads();
    if(rank==0&&tid==0)
    {
        MPI_Send(&i,1,MPI_INT,1,1,MPI_COMM_WORLD);
        //printf("%d\n",rank);
        MPI_Recv(&i,1,MPI_INT,np-1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    }
    else if(tid==0)
    {
        MPI_Recv(&i,1,MPI_INT,rank-1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Send(&i,1,MPI_INT,(rank+1)%np,1,MPI_COMM_WORLD);
    }
    if(tid==0)
    {
        MPI_Bcast(&i,1,MPI_INT,0,MPI_COMM_WORLD);
    }
    #pragma omp critical
    {
        threadcounter++;
    }
    while(threadcounter<ntd);
}

int main(int argc, char **argv)
{
    MPI_Init(&argc,&argv);
    #pragma omp parallel
    {
        iittp_barrier();
    }
    MPI_Finalize();
}
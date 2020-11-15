#include<bits/stdc++.h>
#include<mpi/mpi.h>
using namespace std;
void random_number_generator(int array[],int start,int end,int rank)
{
    srand(time(NULL));
    for (int i=start;i<end;i++)
    {
        int temp = rand()%10;
        // array[i] = temp;
        array[i] = rank;
    }
}
int main(int argc,char** argv)
{
    int rank;
    int np;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int array[n];
    random_number_generator(array,0,n,rank);
    int iter = 0;
    int x = 0;
    int newx ;
    while(iter<m)
    {
        if(rank == x)
        {
            newx = (rand()%np);
        }
        MPI_Bcast(&newx,1,MPI_INT,x,MPI_COMM_WORLD);
        if(x == newx)
        {
            iter++;
            continue;
        }
        if(x==rank)
        {
            MPI_Send(array,n,MPI_INT,newx,1,MPI_COMM_WORLD);
        }
        if(rank==newx)
        {
            MPI_Recv(array,n,MPI_INT,x,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        }
        x=newx;
        iter++;
        MPI_Barrier(MPI_COMM_WORLD);
    }
    for(int i=0;i<np;i++)
    {
        if(i==rank)
        {
            cout<<"rank: "<<rank<<endl;
            for(int i=0;i<n;i++)
            {
                cout<<array[i]<<" ";
            }
            cout<<endl;
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
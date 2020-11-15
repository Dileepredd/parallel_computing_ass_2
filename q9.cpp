#include<omp.h>
#include<bits/stdc++.h>
using namespace std;

int main(int argc,char** argv)
{
    int m,n,p;
    m=atoi(argv[1]);
    n=atoi(argv[2]);
    p=atoi(argv[3]);
    int matrixA[m][n];
    srand(time(NULL));
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            int temp = rand()%10;
            matrixA[i][j] = temp;
        }
    }
    int matrixB[n][p];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<p;j++)
        {
            int temp = rand()%10;
            matrixB[i][j] = temp;
        }
    }
    int matrixC[m][p];
    int k;
    #pragma omp parallel for collapse(2) private(k)
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<p;j++)
        {
            matrixC[i][j] = 0;
            for(k=0;k<n;k++)
            {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    // print
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<p;j++)
        {
            cout<<matrixC[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
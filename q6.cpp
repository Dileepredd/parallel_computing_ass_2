#include<bits/stdc++.h>
#include<omp.h>
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
    int n = atoi(argv[1]);
    int array[n];
    random_number_generator(array,0,n);
    int totalsum=0;
    /*set environment variable for number of threads*/
    #pragma omp parallel for reduction(+:totalsum)
    for(int i=0;i<n;i++)
    totalsum += array[i];
    
    cout<<"total sum: "<<totalsum<<endl;
    return 0;
}
#include<bits/stdc++.h>
#include<thread>
using namespace std;

void random_number_generator(vector<int>& array,int start,int end)
{
    srand(time(NULL));
    for (int i=start;i<end;i++)
    {
        int temp = rand()%10;
        array.push_back(temp);
    }
}

void compute_sum(vector<int>& array,vector<int>& sum,int tid)
{
    int n = array.size();
    int np = sum.size();
    int rank = tid;
    int start,end; /*sum of array subproblem for indices [start,end)*/
    if(rank < n%np)
    {
        start = rank*(n/np) + rank;
        end = start + n/np + 1;
        // cout<<"rank: "<<rank<<", "<<start<<", "<<end<<endl;/*verify load balance*/
    }
    else
    {
        start = rank*(n/np) + n%np;
        end = start + n/np;
        // cout<<"rank: "<<rank<<", "<<start<<", "<<end<<endl;/*verify load balance*/
    }
    for(int i=start;i<end;i++)
    {
        sum[tid] += array[i];
    }
}

int main(int argc,char** argv)
{
    if(argc < 3)
    {
        cout<<"error:\ncommand: ./a.out int[#threads] int[#arrayelements]"<<endl;
        exit(-1);
    }
    int nt = atoi(argv[1]);/*number of theads*/
    int n = atoi(argv[2]);/*number of elements in array*/
    vector<thread> threads;/*threads array*/
    vector<int> array;/*data array*/
    random_number_generator(array,0,n);/*initialization*/
    vector<int> sum(nt,0);/*sum of each thread array*/
    for(int i=0;i<nt;i++)
    {
        threads.push_back(thread(compute_sum,ref(array),ref(sum),i));
    }
    for(auto &th : threads)
    {
        th.join();
    }
    int totalsum = 0;/*total sum*/
    for(int i=0;i<nt;i++)
    {
        totalsum+=sum[i];
    }
    cout<<"total sum: "<<totalsum<<endl;
    return 0;
}
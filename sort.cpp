#include<iostream>
#include<bits/stdc++.h>

using namespace std;

int negate(int a)
{    
    return(-1*a);
}

int retain(int a)
{
    return(a);
}

void selectionSort(int arr[], int n,int (*lambda)(int))  
{  
    int i, j, min_idx,tmp;  
  
    for (i = 0; i < n-1; i++)  
    {  
        min_idx = i;  
        for (j = i+1; j < n; j++)  
        if (lambda(arr[j]) < lambda(arr[min_idx]))  
            min_idx = j;     
        tmp=arr[i];
        arr[i]=arr[min_idx];
        arr[min_idx]=tmp;
    }  
}  

int main(int argc, char *argv[])
{
    if(argc<3)
    {
        cout<<"insufficient arguments\n";
        return(1);
    }    

    int size=atoi(argv[1]),mode=atoi(argv[2]), arr[size];

    if(size<0){    
        cout<<"Array size must be positive!\n";
        return(1);
    }
    else if(argc!=size+3)
    {
        cout<<"array size doesn't match given size!\n";
        return(1);
    }
    
    else if(mode!=1 && mode!=0){
        cout<<"Mode must be 1 for asc and 0 for desc!\n";
        return(1);
    }

    int (*lambda)(int) = mode?(::retain):(::negate);
    
    for(int i=0; i<size;i++)
    {
        arr[i] = atoi(argv[3+i]);
        if(arr[i]==0 && strcmp(argv[3+i],"0"))
        {
        	cout<<"Pls use only digits!\n";
        	return(1);
        }
    }
    
    selectionSort(arr,size,lambda);

    for(int i=0; i<size;i++)
    {
        printf("%d ",arr[i]);
    }
}

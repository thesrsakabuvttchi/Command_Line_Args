#include<iostream>
#include<bits/stdc++.h>
#include<regex>

using namespace std;

double negate(double a)
{    
    return(-1*a);
}

double retain(double a)
{
    return(a);
}

void selectionSort(int arr[], int n,double (*lambda)(double))  
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

void selectionSort(char arr[], int n,double (*lambda)(double))  
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

void selectionSort(double arr[], int n,double (*lambda)(double))  
{  
    int i, j, min_idx;
    double tmp;  
  
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

int test_type(char *tst)
{
    if(regex_match(tst,regex("[0-9]+")))
        return(1);
    else if(strlen(tst)==1)
        return(2);
    else if(regex_match(tst,regex("[0-9]+.[0-9]+")))
        return(3);

    return(0);    
}

int main(int argc, char *argv[])
{
    if(argc<3)
    {
        cout<<"insufficient arguments\n";
        return(1);
    }    

    int size=atoi(argv[1]),mode=atoi(argv[2]);
    int  arr[size];
    double arrf[size];
    char arrc[size];

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

    double (*lambda)(double) = mode?(::retain):(::negate);
    

    int type = test_type(argv[3]);

    for(int i=0; i<size;i++)
    {
        if(type == 1)
            arr[i] = atoi(argv[i+3]);
        else if(type == 2)
            arrc[i] = argv[i+3][0];
        else if(type == 3)
            arrf[i] = atof(argv[i+3]);
        else
            return(printf("Type is not int/char/float!\n"));

        if(type != test_type(argv[i+3]))
            return(printf("Inconsistent types!\n"));
    }

    if(type == 1)
    {
        selectionSort(arr,size,lambda);
        for(int i=0; i<size;i++)
        {
            printf("%d ",arr[i]);
        }
    }
    else if(type == 2)
    {
        selectionSort(arrc,size,lambda);
        for(int i=0; i<size;i++)
        {
            printf("%c ",arrc[i]);
        }
    }
    else
    {
        selectionSort(arrf,size,lambda);
        for(int i=0; i<size;i++)
        {
            printf("%lf ",arrf[i]);
        }
    }
    printf("\n");
}

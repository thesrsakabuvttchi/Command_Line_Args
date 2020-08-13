/* mode 3 not working yet, pls don't add first argument as a directory*/

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <dirent.h>
#include <sys/stat.h> 
#include <signal.h>

int mode1 ( int argc, char *argv[] )
{
    FILE *file1,*file2;//File pointers for copy
    char c,bin[128],*dump;


    //Copy function checks for first argument as file
    file1=fopen(argv[1],"rb");
    if(!file1)
        return(printf("error, unable to open file..................does the file exist?\n"));


    //Checks if last character of the second arg is / or not to find if its a directory 
    if(argv[2][strlen(argv[2])-1] != '/')  
    {
        //Open file 2
        file2=fopen(argv[2],"wb");
        if(!file2)
        {
            return(printf("unable to find the file........pls check the path and retry!\n"));
        }
    }
    else
    {
        DIR* dir = opendir(argv[2]);
        if(!dir)
        {
            return(printf("error, directory doesn't exist...........please create the directory before copying\n"));  
        }
        
        if(argv[2][strlen(argv[2])-1]=='/')
        {
            strcpy(bin,argv[1]);
            dump=strtok(bin,"/");
            while(dump)
            {
                strcpy(bin,dump);
                dump=strtok(NULL,"/");
            }
            strcat(argv[2],bin);
        }
        else if(argv[1][0]!='/') 
            strcat(argv[2],argv[1]);

         printf("\n%s %s\n", argv[1],argv[2]);   

        file2=fopen(argv[2],"wb");
        if(!file2)
        {
            return(printf("error, directory doesn't exist...........please create the directory before copying\n"));
        }
    }  

    int n;
    while ((n = fread(bin, 1, 128, file1)) > 0) 
    {
        fwrite(bin,1, n, file2);    
    }

    fclose(file1);
    fclose(file2);
}

int mode2( int argc, char *argv[] )
{
    //printf("%c\n",argv[argc-1][strlen(argv[argc-1])-1]);
    if(argv[argc-1][strlen(argv[argc-1])-1]!='/')
        return(printf("Please give a directory as the last argument!\n"));

    return(printf(""));
    char *new[3];
    for(int i=1;i<argc-1;i++)
    {
        new[1] = argv[i];
        strcpy(new[2],argv[argc-1]);
        mode1(3, new);
    }
}

int mode3( int argc, char *argv[] )
{
    DIR* dir = opendir(argv[1]);
    struct dirent* in_files;
    
    if (NULL == (dir = opendir(argv[1])))
    {
        return(printf("Unable to open directory..........does the directory exist?"));
    }
    
    char *new[3],tmp[2][128];

    while (in_files = readdir(dir))
    {
        strcpy(tmp[1],argv[2]);
        new[2]=tmp[1];

        if (in_files->d_type!=DT_REG)
            continue;    

        strcpy(tmp[0],argv[1]);
        strcat(tmp[0],in_files->d_name);
        new[1]=tmp[0];

        printf("%s\t%s\n",new[1],new[2]);
        mode1(3,new);
    }
}

int main( int argc, char *argv[] )  
{
    //Checks number of command line arguments
    if((argc==3) && (argv[1][strlen(argv[1])-1] != '/'))
        mode1(argc,argv); 
    else if((argc==3) && (argv[2][strlen(argv[2])-1] == '/'))
        mode3(argc,argv); 
    else if(argc>3)
        mode2(argc,argv);
    
    return(0);
}
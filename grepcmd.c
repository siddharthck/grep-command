/*
author: Siddharth C kulkarni

purpose: imitate the grep cmd in linux


following functionality!!
following are the command line arguments!:
-c : This prints only a count of the lines that match a pattern
-h : Display the matched lines, but do not display the filenames.
-i : Ignores, case for matching
-l : Displays list of a filenames only.
-n : Display the matched lines and their line numbers.
-v : This prints out all the lines that do not matches the pattern

*/



// we want to use the non standard functions like getline() , so we use #define _GNU_SOURCE
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>   //If you only need the OS types, say for the prototypes of your functions, then just #include <sys/types.h>.
#include <sys/stat.h>    //this header defines the structure of the data returned by the functions fstat(), lstat(), and stat().
#include <unistd.h>    // if you need the function definitions, then you #include <unistd.h> or any of the other system headers, as needed.
#include <dirent.h>   /*DIR data type representing directory stream It also defines the structure dirent which includes the following members:


ino_t  d_ino       file serial number
char   d_name[]    name of entry  
*/
//#include<regex.h>

int findString(char str[100], char search[20]){

    int count1 = 0, count2 = 0, i, j, flag;

 


    while (str[count1] != '\0')

        count1++;

    while (search[count2] != '\0')

        count2++;

    for (i = 0; i <= count1 - count2; i++)

    {

        for (j = i; j < i + count2; j++)

        {

            flag = 1;

            if (str[j] != search[j - i])

            {

                flag = 0;

                break;

            }

        }

        if (flag == 1)

            break;

    }

   return flag;
}

int findStringi(char str[100], char search[20]){
    
    int count1 = 0, count2 = 0, i, j, flag;


 


    while (str[count1] != '\0')

        count1++;

    while (search[count2] != '\0')

        count2++;

    for (i = 0; i <= count1 - count2; i++)

    {

        for (j = i; j < i + count2; j++)

        {

            flag = 1;

            if (tolower(str[j]) != tolower(search[j - i]))

            {

                flag = 0;

                break;

            }

        }

        if (flag == 1)

            break;

    }

   return flag;
}




void handleFile(char path[],char par,char pattern[]){

if(findString(path,".txt")||findString(path,".c")||findString(path,".cpp")||findString(path,".html")||findString(path,".py")){

    FILE *f=fopen(path,"r");
    if(f!=NULL){
 
       
    char * line = NULL;
    int len = 0;
    int read;
int line_count=0;
int match_count=0;

    f = fopen(path, "r");
   
switch(par){
case 'c'://This prints only a count of the lines that match a pattern
{
int start=1;
int toprint=0;
 //printf("file name: %s\n",path );
    while ((read = getline(&line, &len, f)) != -1) {
line_count+=1;
  
  
if(findString(line,pattern)){
   if(start==1){
        printf("file name: %s\n",path );
        start=0;toprint=1;}
    match_count+=1;
 
}

    }if(toprint){
     printf("%d\n",match_count);toprint=0;}
    }
break;
case 'h'://Display the matched lines, but do not display the filenames.
    while ((read = getline(&line, &len, f)) != -1) {
line_count+=1;
  

if(findString(line,pattern)){
    
 
  printf("%d.%s",line_count, line);
}

    }
break;
case 'i'://Ignores, case for matching
{int start=1;
    while ((read = getline(&line, &len, f)) != -1) {
line_count+=1;
  
  
if(findStringi(line,pattern)){
     if(start==1){
        printf("file name: %s\n",path );
        start=0;}
  printf("%d.%s",line_count, line);
}

    }}
break;

case 'n'://Displays line with number
{ int start=1;
    while ((read = getline(&line, &len, f)) != -1) {
line_count+=1;
  

if(findString(line,pattern)){
    
    if(start==1){
        printf("file name: %s\n",path );
        start=0;}
  printf("%d.%s",line_count, line);
}

    }}
break;


case 'v'://This prints out all the lines that do not match the pattern
   {int start=1;
    while ((read = getline(&line, &len, f)) != -1) {
line_count+=1;
  
  
if(!findString(line,pattern)){
     if(start==1){
        printf("file name: %s\n",path );
        start=0;}
  printf("%d.%s",line_count, line);
}

    }}
break;
case 'l':
{ int start=1;
    while ((read = getline(&line, &len, f)) != -1) {
line_count+=1;
  

if(findString(line,pattern)){
    
    if(start==1){
        printf("file name: %s\n",path );
        start=0;break;}

}

    }}

break;
default:
printf("argv[1] not valid\n");
break;

}




    fclose(f);
    if (line)
        free(line);

    }else{
        printf("can not open file!! or file does not exist \n");
    }

}else{return;}}

void traverseDir(char *dir, int depth,char par,char pattern[])
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    int spaces = depth*4;// for listing the file, we have to show what is depth of directory 0 if same directory

    if((dp = opendir(dir)) == NULL) {
       // fprintf(stderr,"cannot open directory: %s\n", dir);
        handleFile(dir,par,pattern);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
        /*

        lstat() - execute (search) permission is required on all of the directories in path that lead to the file.

stat() stats the file pointed to by path and fills in buf.

lstat() is identical to stat(), except that if path is a symbolic link, then the link itself is stat-ed, not the file that it refers to.

        */
        if(S_ISDIR(statbuf.st_mode)) {//  This function return information about a file( 1 if it is directory, i.e. recursion case), in the buffer pointed to by statbuf.
            /* Found a directory, but ignore . and .. (current directory and parent dir*/
            if(strcmp(".",entry->d_name) == 0 || 
                strcmp("..",entry->d_name) == 0)
                continue;
            printf("%*s%s/\n",spaces,"",entry->d_name);
           
            /* Recurse at a new indent level */
            traverseDir(entry->d_name,depth+1,par,pattern);
        }
        else //printf("\n%*s%s\n",spaces,"",entry->d_name); base case if it is not directory!!
        handleFile(entry->d_name,par,pattern);
    }
    chdir(".."); 
    closedir(dp);
}


int main(int argc, char* argv[])
{


    if(argc!=4){
printf("invalid command line arguments!!!\n");
exit(1);

}


    char par=argv[1][1];
if(!(par=='l' ||par=='n'||par=='c'||par=='h'||par=='i'||par=='v')){
    printf("invalid argv[1]\n");
    exit(1);
}
    char *topdir;
 
        topdir=argv[3];

   // printf("Directory scan of %s\n",topdir);
    traverseDir(topdir,0,par,argv[2]);
   // printf("done.\n");

    return 0;
}

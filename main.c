#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <string.h>
#include <math.h>
int main(int argc, char const *argv[]) {
  DIR * opened=opendir(".");
  int size=0;
  char directories[1000]="Directories:";
  char files[1000]="Regular Files:";
  if(opened!=NULL){
    struct dirent * read=readdir(opened);
    printf("Statistics for Current Directory:\n");
    while(read != NULL){
      struct stat readfile;
      int items=stat(read->d_name, &readfile);
      if(items==-1){
        printf("Error: %s\n",strerror(errno));
      }else{
        if((readfile.st_mode & S_IFMT) == S_IFDIR){
          strcat(directories,"\n\t");
          strcat(directories,read->d_name);
        }else{
          strcat(files,"\n\t");
          strcat(files,read->d_name);
        }
      }
      size+=readfile.st_size;
      read=readdir(opened);
    }
  }else{
    printf("Error %s\n",strerror(errno));
  }
  if(size>=1000000000){
    double newsize=size/1000000000.0;
    printf("Total Current Directory Size: %.2f GB\n",newsize);
  }
  else if(size>=1000000){
    double newsize=size/1000000.0;
    printf("Total Current Directory Size: %.2f MB\n",newsize);
  }
  else if(size>=1000){
    float newsize=size/1000.0;
    printf("Total Current Directory Size: %.2f KB\n",newsize);
  }
  else{
    printf("Total Current Directory Size: %d Bytes\n",size);
  }
  printf("%s\n\n",directories);
  printf("%s\n",files);
  return 0;
}

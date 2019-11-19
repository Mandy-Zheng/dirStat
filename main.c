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
  DIR * opened;
  char * buf;
  if(argc>1){
    opened=opendir(argv[1]);
    printf("\nStatistics for Directory with Path %s:\n",argv[1]);
  }else{
    opened=opendir(".");
    printf("\nStatistics for Current Directory:\n");
  }
  int size=0;
  char directories[1000]="Directories:";
  char files[1000]="Regular Files:";
  if(opened!=NULL){
    struct dirent * read=readdir(opened);
    while(read != NULL){
      struct stat readfile;
      char newpath[2000]="";
      if(argc>1){
        strcpy(newpath,argv[1]);
        strcat(newpath,"/");
      }
      strcat(newpath,read->d_name);
      int items=stat(newpath, &readfile);
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
      //printf("\n %s: %d", );
      read=readdir(opened);
    }
  }else{
    printf("Error %s\n",strerror(errno));
  }
  if(size>=1073741824){
    float newsize=(size * 100) / 1073741824.0 /100.0;
    printf("Total Current Directory Size: %.2f GB\n",newsize);
  }
  else if(size>=1048576){
    float newsize=(size * 100) / 1048576.0 /100.0;
    printf("Total Current Directory Size: %.2f MB\n",newsize);
  }
  else if(size>=1024){
    float newsize=(size * 100) / 1024 /100.0;
    printf("Total Current Directory Size: %.2f KB\n",newsize);
  }
  else{
    printf("Total Current Directory Size: %d Bytes\n",size);
  }
  printf("%s\n\n",directories);
  printf("%s\n",files);
  return 0;
}

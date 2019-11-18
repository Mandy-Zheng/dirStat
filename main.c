#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
int main(int argc, char const *argv[]) {
  DIR * opened=opendir(".");
  int size=0;
  if(opened!=NULL){
    struct dirent * read=readdir(opened);
    printf("Statistics for Current Directory\n\n");
    while(read != NULL){
      struct stat readfile;
      if(stat(read->d_name, &readfile)==-1){
        printf("Error: %s\n",strerror(errno));
      }else{
        if(read->d_type == DT_DIR){
          printf("Directory %s \n",read->d_name/*,read->d_type*/);
        }else{
          printf("File %s \n",read->d_name/*,read->d_type*/);
        }
      }
      size+=readfile.st_size;
      read=readdir(opened);
    }
  }else{
    printf("Error %s\n",strerror(errno));
  }

  printf("\n Current Directory Size: %d Bytes\n",size );
  return 0;
}

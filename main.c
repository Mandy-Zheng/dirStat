#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
int main(int argc, char const *argv[]) {
  DIR * opened=opendir(".");
  if(opened!=NULL){
    struct dirent * read=readdir(opened);
    while(read != NULL){
      printf("%s : \n",read->d_name/*,read->d_type*/);
      read=readdir(opened);
    }
  }else{
    printf("Error %s\n",strerror(errno));
  }


  return 0;
}

#include "user.h"
#include "../kernel/fcntl.h"
#include "../kernel/fs.h"
#include "../kernel/stat.h"


void find(char* directory_name,char* filename){
  if(strcmp(directory_name,"./") == 0) return;
  if(strcmp(directory_name,"../") == 0) return;
  int fd;
  if((fd = open(directory_name,O_RDONLY)) < 0) {
    printf("could not open directory: %s\n",directory_name);
    return;
  }
  struct stat stat_struct;
  struct dirent directory_entry;
  if(fstat(fd,&stat_struct) < 0) {
    printf("could not stat %s\n",directory_name);
    close(fd);
    return;
  }

  if(stat_struct.type != T_DIR){
    close(fd);
    return;
  }

  while(read(fd,&directory_entry,sizeof(directory_entry)) == sizeof(directory_entry)){
    //read the directory entry
    if(directory_entry.inum == 0)continue;
    if(strcmp(directory_entry.name,".")==0) continue;
    if(strcmp(directory_entry.name,"..")==0) continue;
    char* directory_entry_name = (char*)malloc(sizeof(char)*strlen(directory_name) + strlen(directory_entry.name) + 1);
    strcpy(directory_entry_name,directory_name);
    directory_entry_name[strlen(directory_name)] = '/';
    strcpy(&directory_entry_name[strlen(directory_name)+1],directory_entry.name);

    if(stat(directory_entry_name,&stat_struct) < 0){
      printf("could not stat %s\n",directory_entry_name);
      continue;
    }
    switch(stat_struct.type){
      case T_FILE:
        if(strcmp(directory_entry.name,filename) == 0){
          printf("%s/%s\n",directory_name,filename);
        }
        break;
      case T_DIR:
        find(directory_entry_name,filename);
    }
  }

  return;
}

int main(int argc,char* argv[]){
  if(argc!=3){
    printf("usage: find <dir> <filename>\n");
    exit(-1);
  }
  find(argv[1],argv[2]);
  exit(0);
}
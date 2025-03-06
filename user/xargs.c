#include "user.h"

int main(int argc,char* argv[]){
  if(argc < 2) {
    printf("usage: xargs <command>\n");
    exit(-1);
  }
  char* command = argv[1];
  char* arguments[32];
  int pointer = 0;
  // got actual args
  for(int i=1;i<argc;i++) {
    arguments[pointer++] = argv[i];
  }


  char buf[1];
  while(read(0,&buf,1) > 0) {
    char arg[32];
    int p = 0;
    while(buf[0] != '\n'){
      arg[p++] = buf[0];
      read(0,&buf,1);
    }
    if(p==0) break;
    arguments[pointer++] = arg;
  }

  int children[1];
  children[0] = fork();
  if(children[0]==0){
    //child
    exec(command,arguments);
  }
  wait(children);
  exit(0);
}
#include "user.h"



int main(int argc,char* argv[]){
  if(argc==0){
    printf("usage : sleep <time>");
    exit(-1);
  }
  int time = atoi(argv[1]);
  sleep(time);
  exit(0);
}
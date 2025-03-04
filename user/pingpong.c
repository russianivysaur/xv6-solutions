#include "user.h"


int main(int argc,char* argv[]) {
  int pid = getpid();
  int descriptors[2];
  pipe(&descriptors[0]);
  int desc[2];
  pipe(&desc[0]);
  int childId = fork();
  if(childId==0){
    // i am child
    int myPID = getpid();
    char buf[1];
    char data = 't';
    read(descriptors[0],&buf,1);
    printf("%d: received ping\n",myPID);
    write(desc[1],&data,1);
    exit(0);
  }
  char t = 'h';
  write(descriptors[1],&t,1);
  char buf[1];
  read(desc[0],&buf,1);
  printf("%d: received pong\n",pid);
}
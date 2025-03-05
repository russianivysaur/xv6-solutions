#include "user.h"


int main(int argc,char* argv[]){
  int descriptors[2];
  pipe(&descriptors[0]);
  for(int i=2;i<=280;i++){
    write(descriptors[0],&i,4);
  }
}
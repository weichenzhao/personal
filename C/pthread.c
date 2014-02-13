#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct { 
  int first, second;
} two_ints_t;

void fprintPt( pthread_t pt) {
  unsigned char *ptc = (unsigned char*)(void*)(&pt);
  for (size_t i=0; i<sizeof(pt); i++) {
    printf("%02x", (unsigned)(ptc[i]));
  }
  printf("\n");
}

void *server(void *arg) {
  two_ints_t *p = (two_ints_t *)arg;
  // perform service
  printf("server: %d, %d\n", p->first, p->second);
  return (0);
}

int main(){
  pthread_t thread; 
  int i;
  two_ints_t in={0, 0};
  for (i=0; i<5; i++){ 
    in.second+=1;
    pthread_create(
            &thread, // thread ID
            0, // default attributes
            server, // start routine
            &in); // argument
    //fprintPt(thread);
    pthread_join(thread, 0);
  }
  return 0;
}


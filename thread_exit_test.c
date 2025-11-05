#include "types.h"
#include "user.h"

void
child(void *arg)
{
  // immediate exit from thread
  exit();
}

int
main(void)
{
  int t;

  t = thread_create(child, 0);
  if(t < 0){
    printf(1, "thread_create failed\n");
    exit();
  }

  if(thread_join() < 0){
    printf(1, "thread_join failed\n");
    exit();
  }

  printf(1, "thread_exit_test PASS\n");
  exit();
}
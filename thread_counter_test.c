#include "types.h"
#include "user.h"

#define NTHREADS 8
#define ITERS 10000

static lock_t lk;
static volatile uint counter;

void
worker(void *arg)
{
  int i;
  for(i = 0; i < ITERS; i++){
    lock_acquire(&lk);
    counter++;
    lock_release(&lk);
  }
  // thread exit: use exit() (your kernel is thread-safe)
  exit();
}

int
main(void)
{
  int i;
  int tid;

  lock_init(&lk);
  counter = 0;

  for(i = 0; i < NTHREADS; i++){
    tid = thread_create(worker, (void*)(uint)i);
    if(tid < 0){
      printf(1, "thread_create failed\n");
      exit();
    }
  }

  for(i = 0; i < NTHREADS; i++){
    if(thread_join() < 0){
      printf(1, "thread_join failed\n");
      exit();
    }
  }

  if(counter != NTHREADS * ITERS){
    printf(1, "FAIL counter=%d expected=%d\n", counter, NTHREADS * ITERS);
  } else {
    printf(1, "PASS counter=%d\n", counter);
  }

  exit();
}
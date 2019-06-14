#include "concurrency.h"

extern DATA DataObj[];

void
print_result(struct timeval begin, struct timeval end, int nthread)
{
  long usec;
  double sec;

  usec = (end.tv_sec - begin.tv_sec) * 1000 * 1000 + (end.tv_usec - begin.tv_usec);
  sec = (double)usec / 1000.0 / 1000.0;
  printf("%d, %f\n",MAX_TRANSACTION*nthread, (double)sec );
  printf("Throughput: %f (trans/sec)\n", (double)(MAX_TRANSACTION*nthread) / sec);
}

int
comp(int data, int ndive)
{
	if (ndive == MAX_OPERATION)	return data;
	data += rand() % 3;
	return comp(data, ++ndive);
}

/* Read modify write */
void
task_alpha(int data_id)
{
	int val;
  // printf("data id %d -> %d\n", data_id, DataObj[data_id].val);
	val = DataObj[data_id].val; // read

}

void
task_beta(int data_id)
{
	int val = DataObj[data_id].val;
  // printf("data id %d -> %d ->", data_id, DataObj[data_id].val);
  val = comp(val, 0);         // modify
	DataObj[data_id].val = val; // write
  // printf("%d\n", DataObj[data_id].val);
	usleep(100*1000);
}

int lock(int id)
{
  // int ret = pthread_mutex_lock(&DataObj[id].mutex);
  // int error = pthread_mutex_trylock(&DataObj[id].mutex);
  // if (error == 0) {
  //   printf("granted lock for data %d\n",id);
  // }
  int ret = pthread_mutex_trylock(&DataObj[id].mutex);
  if (ret == 0) {
    // printf("granted lock for data -> %d\n",id);
  }
  if (ret != 0) {
    if (ret == EBUSY) {
      // printf("failed to get the lock because another thread holds lock. Kill the transaction!%d\n",id);
      // die(id);
    } else{
      // puts("some other as yet undocumented failure reason\n");
      exit(0);
    }

  }
  return ret;
}
void
die(int id){
  printf("\nI am going to die -> %d, bye bye \n",id );
  pthread_mutex_destroy(&DataObj[id].mutex);  //
  int ret = pthread_mutex_init(&DataObj[id].mutex, NULL);
  if (ret < 0) ERR;
  else puts("alive again!! yeaaay");
  lock(id);
}

void
unlock(int id)
{
	if (pthread_mutex_unlock(&DataObj[id].mutex)) ERR;
  // else  printf("granted unlock -> %d\n",id );
}

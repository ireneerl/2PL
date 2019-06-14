#include "concurrency.h"

DATA DataObj[MAX_OBJ];
TRANSACTION transaction[MAX_TRANSACTION];


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

static void *
worker(void *arg)
{
  TRANSACTION *tx= (TRANSACTION*)arg;
  int list_locked[MAX_OPERATION];

  // int trial = 0;
  // qsort(transaction[j].operation, MAX_OPERATION, sizeof(OPERATION), compare);

  for (int i = 0; i < MAX_OPERATION; i++) {
    list_locked[i] = tx->operation[i].data_.val;
  }

  qsort(list_locked, MAX_OPERATION, sizeof(int), cmpfunc);


  for (int i = 0; i < MAX_OPERATION; i++) {
    lock(list_locked[i]);
    task_alpha(tx->operation[i].data_.val);
    task_beta(tx->operation[i].data_.val);
  }

  for (int i = 0; i < MAX_OPERATION; i++) {
    unlock(list_locked[i]);
  }
  return NULL;
}

int compare(const void *s1, const void *s2)
{
  return (((OPERATION*)s1)->data_.val - ((OPERATION*)s2)->data_.val);
}


extern int
main(int argc, char *argv[])
{
  int i, nthread = 4;
  struct timeval begin, end;
  pthread_t *thread;

  if (argc == 2) nthread = atoi(argv[1]);
  thread = (pthread_t *)calloc(nthread, sizeof(pthread_t));
  if (!thread) ERR;


  //initialization of transaction
  for (int j = 0; j < MAX_TRANSACTION; j++){
    // printf("the transaction : %d\n", j);
    for(int i = 0; i < MAX_OPERATION; i++){
      int rand_data = rand() % MAX_OBJ;
      int transaction_type = rand() % 2;
      transaction[j].operation[i].data_.val = rand_data;
      transaction[j].operation[i].rw = transaction_type;
      // printf("operation-> %d -> %d\n", transaction[j].operation[i].data_.val, transaction[j].operation[i].rw);
    }
  }
  for (int j = 0; j < MAX_TRANSACTION; j++){
    for(int i = 0; i < MAX_OPERATION; i++){
    // int ret = pthread_mutex_init(&DataObj[i].mutex, NULL);
      int ret = pthread_mutex_init(&transaction[j].operation[i].data_.mutex, NULL);
      if (ret < 0) ERR;
    }
  }

	gettimeofday(&begin, NULL);
	for (i = 0; i < nthread; i++) {
	  int ret = pthread_create(&(thread[i]), NULL, &worker, (void *)&transaction);
	  if (ret < 0) ERR;
	}
	for (i = 0; i < nthread; i++) {
	  int ret = pthread_join(thread[i], NULL);
		if (ret < 0) ERR;
	}
	gettimeofday(&end, NULL);
  print_result(begin, end, nthread);
  free(thread);

  return 0;
}

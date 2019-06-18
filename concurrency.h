#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include "debug.h"
#include <iostream>
using namespace std;

#define MAX_OBJ (1000000)
#define MAX_OPERATION (10) //number of operation
#define MAX_TRANSACTION (10000) //number of transaction
//#define MAX_OPERATION (10)

/* Data Area */
typedef struct _DATA {
  int val;
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t mutex_wait;
} DATA;

typedef struct _OPERATION{
  DATA data_;
  int rw; // 0-> read; 1-> write
} OPERATION;

typedef struct _TRASACTION{
	int id;
	OPERATION operation[MAX_OPERATION];
} TRANSACTION;

void print_result(struct timeval begin, struct timeval end, int nthread);
int comp(int data, int ndive);
void task_alpha(int data_id);
void task_beta(int data_id);
int lock(int id);
void unlock(int id);
void die(int id);
void q_sort(int input[], int low, int high);
void merge_sort(int input[], int left, int right);
void bubble_sort(int input[], int size);
void insertion_sort(int input[], int size);
void printArray(int input[], int size);
void try_to_sort(int arr[]);

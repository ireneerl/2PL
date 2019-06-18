#include "concurrency.h"

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int input[], int low, int high){
  int pivot = input[high];
  int i = (low - 1);

  for(int j=low; j <= high-1; j++){
    if(input[j] <= pivot){
      i++;
      swap(&input[i], &input[j]);
    }
  }
  swap(&input[i+1], &input[high]);
  return (i+1);
}

void q_sort(int input[], int low, int high){
  if(low < high){
    int part_idx = partition(input, low, high);
    q_sort(input, low, part_idx - 1);
    q_sort(input, part_idx + 1, high);
  }
}

void merge(int input[], int left, int med, int right){
  int i, j, k;
  int n1 = med - left + 1;
  int n2 = right - med;

  int Left_in[n1], Right_in[n2];

  for (i = 0; i < n1; i++)
      Left_in[i] = input[left + i];
  for (j = 0; j < n2; j++)
      Right_in[j] = input[med + 1+ j];

  /*merge the arrays*/
  i = 0, j = 0, k = left;
  while (i < n1 &&  j < n2){
    if(Left_in[i] < Right_in[i]){
      input[k] = Left_in[i];
      i++;
    }else{
      input[k] = Right_in[j];
      j++;
    } k++;
  }

  while (i < n1) {
    input[k] = Left_in[i];
    i++;
    k++;
  }
  while (j < n2) {
    input[k] = Right_in[j];
    j++;
    k++;
  }

}

void merge_sort(int input[], int left, int right){
  if(left < right){
    int med = left+(right-left)/2;

    merge_sort(input, left, med);
    merge_sort(input, med+1, right);

    merge(input, left, med, right);
  }
}

void printArray(int input[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", input[i]);
    printf("\n");
}

void insertion_sort(int input[], int size){
  int i, j, key;
  for (i = 1; i < size; i++){
    key = input[i];
    j = i - 1;
    while (j >= 0 && input[j] > key) {
      input[j+1] = input[j];
      j = j - 1;
    }
    input[j + 1] = key;
  }
}

void bubble_sort(int input[], int size){
   int i, j;
   for (i = 0; i < size-1; i++)

       // Last i elements are already in place
       for (j = 0; j < size-i-1; j++)
           if (input[j] > input[j+1])
              swap(&input[j], &input[j+1]);
}

int getMax(int input[], int size)
{
    int mx = input[0];
    for (int i = 1; i < size; i++)
        if (input[i] > mx)
            mx = input[i];
    return mx;
}

void countSort(int input[], int size, int exp)
{
    int output[size]; // output array
    int i, count[10] = {0};

    for (i = 0; i < size; i++)
        count[ (input[i]/exp)%10 ]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = size - 1; i >= 0; i--)
    {
        output[count[ (input[i]/exp)%10 ] - 1] = input[i];
        count[ (input[i]/exp)%10 ]--;
    }

    for (i = 0; i < size; i++)
        input[i] = output[i];
}

void radix_sort(int input[], int size)
{
    int m = getMax(input, size);
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(input, size, exp);
}


void try_to_sort(int arr2[]){
  int arr[] = {12, 11, 13, 5, 6, 7};
  int arr_size = sizeof(arr)/sizeof(arr[0]);

  // /*Quick Sort*/
  // printf("Given array is \n");
  // printArray(arr, arr_size);
  //
  // q_sort(arr, 0, arr_size - 1);
  //
  // printf("\nSorted array is \n");
  // printArray(arr, arr_size);

  // /*Merge Sort*/
  // printf("%d\n", arr_size);
  //
  // printf("Given array is \n");
  // printArray(arr, arr_size);
  //
  // merge_sort(arr, 0, arr_size - 1);
  //
  // printf("\nSorted array is \n");
  // printArray(arr, arr_size);


  // /*insertionSort Sort*/
  // insertion_sort(arr, arr_size);

  // /*Bubblesort Sort*/
  // bubble_sort(arr, arr_size);

  // /*Radix Sort*/
  radix_sort(arr, arr_size);
  printArray(arr, arr_size);
}

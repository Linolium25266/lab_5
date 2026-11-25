#define _CRT_SECURE_NO_WARNINGS

#include "tasks.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100
#define MERGE_SIZE 10
#define VECTOR_SIZE 50
#define MAX_PERCENT_STEP 10

static void clearInput(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

static bool readInt(const char *prompt, int *value) {
  printf("%s", prompt);
  bool ok = scanf("%d", value) == 1;
  clearInput();
  return ok;
}

static bool readIntElement(const char *name, int index, int *value) {
  printf("enter %s[%d]:", name, index);
  bool ok = scanf("%d", value) == 1;
  clearInput();
  return ok;
}

static void printDomainError(void) {
  puts("the argument is outside the domain of the function's permissible "
       "values.");
}

static void printInputError(void) { puts("invalid input."); }

/* Task 51: A[0] != 0 is given, A[i] = A[i div 2] + A[i - 1]. */
void task51(void) {
  int n = 0;
  int first = 0;

  if (!readInt("enter N (1..100):", &n) || n < 1 || n > MAX_SIZE) {
    printDomainError();
    return;
  }

  if (!readInt("enter A[0] (not zero):", &first) || first == 0) {
    printDomainError();
    return;
  }

  long long a[MAX_SIZE];
  a[0] = first;

  for (int i = 1; i < n; i++) {
    a[i] = a[i / 2] + a[i - 1];
  }

  puts("the array:");

  for (int i = 0; i < n; i++) {
    printf("A[%d] = %lld\n", i, a[i]);
  }
}

/* Task 58: merge two ascending vectors of 10 elements into one of 20. */
void task58(void) {
  int x[MERGE_SIZE];
  int y[MERGE_SIZE];
  int c[2 * MERGE_SIZE];

  puts("enter the first vector in ascending order.");

  for (int i = 0; i < MERGE_SIZE; i++) {
    if (!readIntElement("x", i + 1, &x[i])) {
      printInputError();
      return;
    }
    if (i > 0 && x[i] < x[i - 1]) {
      puts("the vector must be sorted in ascending order.");
      return;
    }
  }

  puts("enter the second vector in ascending order.");

  for (int i = 0; i < MERGE_SIZE; i++) {
    if (!readIntElement("y", i + 1, &y[i])) {
      printInputError();
      return;
    }
    if (i > 0 && y[i] < y[i - 1]) {
      puts("the vector must be sorted in ascending order.");
      return;
    }
  }

  int i = 0;
  int j = 0;
  int k = 0;

  while (i < MERGE_SIZE && j < MERGE_SIZE) {
    if (x[i] <= y[j]) {
      c[k++] = x[i++];
    } else {
      c[k++] = y[j++];
    }
  }
  while (i < MERGE_SIZE) {
    c[k++] = x[i++];
  }
  while (j < MERGE_SIZE) {
    c[k++] = y[j++];
  }

  puts("the merged vector:");

  for (int t = 0; t < 2 * MERGE_SIZE; t++) {
    printf("c[%d] = %d\n", t + 1, c[t]);
  }
}

/* Task 77: sequence ends with -1; is there a multiple of 7, and where. */
void task77(void) {
  int a[MAX_SIZE];
  int size = 0;
  int number = 0;

  puts("enter integers, -1 ends the sequence.");

  while (true) {
    if (!readInt("enter number:", &number)) {
      printInputError();
      return;
    }
    if (number == -1) {
      break;
    }
    if (size == MAX_SIZE) {
      puts("the sequence is too long.");
      return;
    }
    a[size++] = number;
  }

  if (size == 0) {
    puts("the sequence must not be empty.");
    return;
  }

  for (int i = 0; i < size; i++) {
    if (a[i] % 7 == 0) {
      printf("yes, the first multiple of 7 is %d, its position: %d\n", a[i],
             i + 1);
      return;
    }
  }

  puts("no, there are no numbers divisible by 7.");
}

/* Task 114: insert (a[5] + a[10])^2 at the k-th place of the array. */
void task114(void) {
  int n = 0;

  if (!readInt("enter n (10..99):", &n) || n < 10 || n >= MAX_SIZE) {
    printDomainError();
    return;
  }

  long long a[MAX_SIZE];

  for (int i = 0; i < n; i++) {
    int value = 0;

    if (!readIntElement("a", i + 1, &value)) {
      printInputError();
      return;
    }
    a[i] = value;
  }

  int k = 0;

  if (!readInt("enter k:", &k) || k < 1 || k > n + 1) {
    printDomainError();
    return;
  }

  long long sum = a[4] + a[9];
  long long inserted = sum * sum;

  for (int i = n; i > k - 1; i--) {
    a[i] = a[i - 1];
  }
  a[k - 1] = inserted;
  n++;

  printf("the inserted element: %lld\n", inserted);
  puts("the new array:");

  for (int i = 0; i < n; i++) {
    printf("a[%d] = %lld\n", i + 1, a[i]);
  }
}

/* Task 175: random array whose neighbours differ by at most 10%. */
void task175(void) {
  static bool seeded = false;
  int n = 0;

  if (!readInt("enter n (1..100):", &n) || n < 1 || n > MAX_SIZE) {
    printDomainError();
    return;
  }

  if (!seeded) {
    srand((unsigned int)time(NULL));
    seeded = true;
  }

  int a[MAX_SIZE];
  a[0] = 100 + rand() % 101;

  for (int i = 1; i < n; i++) {
    int maxStep = a[i - 1] * MAX_PERCENT_STEP / 100;
    int step = rand() % (2 * maxStep + 1) - maxStep;
    a[i] = a[i - 1] + step;
  }

  puts("the array:");

  for (int i = 0; i < n; i++) {
    if (i == 0) {
      printf("a[%d] = %d\n", i, a[i]);
    } else {
      printf("a[%d] = %d (%+.2f%%)\n", i, a[i],
             100.0 * (a[i] - a[i - 1]) / a[i - 1]);
    }
  }
}

/* Task 56: length of a vector of 50 elements. */
void task56(void) {
  double z[VECTOR_SIZE];

  for (int i = 0; i < VECTOR_SIZE; i++) {
    printf("enter z[%d]:", i + 1);
    if (scanf("%lf", &z[i]) != 1) {
      clearInput();
      printInputError();
      return;
    }
    clearInput();
  }

  double sum = 0;

  for (int i = 0; i < VECTOR_SIZE; i++) {
    sum += z[i] * z[i];
  }

  printf("the length: %g\n", sqrt(sum));
}

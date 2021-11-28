#include <stdio.h>
int main() {

  int i, n=30;

  // initialize the first 3 terms
  int t1 = 0, t2 = 1;
  int nextTerm = t1 + t2;

  
  // print the first two terms 
  printf("Fibonacci Series: %d, %d, ", t1, t2);

  // calculate and print 3rd to nth terms
  for (i = 3; i <= n; ++i) {
    printf("%d, ", nextTerm);
    t1 = t2;
    t2 = nextTerm;
    nextTerm = t1 + t2;
  }

  return 0;
}

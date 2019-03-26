#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>


int abs(int i){
  if(i < 0)
    return (i*-1);

  else
    return i;
}
// result[i]=j; means queen at i-th row is placed at j-th column.
// Queens placed at (x1, y1) and (x2,y2)
// x1==x2 means same rows, y1==y2 means same columns, |x2-x1|==|y2-y1| means
// they are placed in diagonals.
int canPlace(int x2, int y2, int *result) {
	// This function will check if queen can be placed (x2,y2), or we can
	// say that Can queen at x2 row is placed at y2 column.
	// for finding the column for x2 row, we will check all the columns for
	// all the rows till x2-1.
	for (int i = 0; i < x2; i++) {
		//result[i] == y2 => columns are same
		//|i - x2| == |result[i] - y2| => in diagonals.
		if ((result[i] == y2)	|| (abs(i - x2) == abs(result[i] - y2))) {
			return 0;
		}
	}
	return 1;
}

void print(int * result){
  for(int i = 0; i < 6; i++){
    printf("%d\n", result[i]);
  }
}

void placeQueens(int x, int size, int * result) {
	for (int i = 0; i < size; i++) {
		//check if queen at xth row can be placed at i-th column.
		if (canPlace(x, i, result)) {
			result[x] = i; // place the queen at this position.
			if (x == size - 1) {
          printf("Solution found:\n");
          print(result);
			}
			placeQueens(x + 1, size, result);
		}
	}
}

int main() {
	int n = 6;
	int result[n];
  result[0] = 3;
	placeQueens(0, n, result);
}

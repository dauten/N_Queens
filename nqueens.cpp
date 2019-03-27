#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

static int count = 0;

int absVal(int i){
  if(i < 0)
    return (i*-1);

  else
    return i;
}

int legal(int x2, int y2, int *result) {
	for (int i = 0; i < x2; i++) {

		if ((result[i] == y2)	|| (absVal(i - x2) == absVal(result[i] - y2))) {
			return 0;
      result[i] = -1;
		}
	}
	return 1;
}

int legalBoard(int * result, int length){
  int valid = 1;
  for(int x = 0; x < length; x++){

    if( !legal(x, result[x], result) ){
      return 0;
    }
  }
  return 1;
}

//given blank board, fill it with queens randomly.
//conflicts matrix is filled with number of queens that
//threaten that particular space
int generateBoard(int * result, int ** conflicts){

}




void printSolution(int * result, int size){
  for(int i = 0; i < size; i++){
    for(int y = 0; y < result[i]; y++){
      printf(". ");
    }
    printf("%d ", result[i]);
    for(int y = result[i]+1; y < size; y++){
      printf(". ");
    }
    printf("\n");
  }
}


void placeQueens(int x, int size, int * result, int first) {
	for (int i = 0; i < size; i++) {

		if (legal(x, i, result)) {
			result[x] = i;
			if (x == size - 1) {
          printf("Solution found:\n");
          printSolution(result, size);
          count++;
          printf("legal?%d\n", legalBoard(result, size));
          if(count > 2){

            exit(0);
          }
			}
			placeQueens(x + 1, size, result, first);
		}
	}
}

/*
procedure AC-1
Q ← {(V i , V j ) ∈ arcs(G), i ≠ j};
repeat
  CHANGE ← false;
  for each (V i , V j ) ∈ Q do
    CHANGE ← (REVISE(V i , V j ) or CHANGE);
  endfor;
until not(CHANGE);
end_AC
*/

int main() {
  int n, q;
  printf("Insert n size:\n");
  std::cin >> n;
  printf("Insert first Queen Location:\n");
  std::cin >> q;
	int result[n];
  result[0] = q;
  printf("%d\n",legalBoard(result, n));
  placeQueens(1, n, result, 0);

}

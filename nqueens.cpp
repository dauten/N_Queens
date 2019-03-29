#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>


static int count = 0;

int absVal(int i){
  if(i < 0)
    return (i*-1);

  else
    return i;
}
int conflict(int x1, int y1, int result[], int size){
  int c, x, y = 0;
  c=0;
//  printf("c is now %d\n", c);
  for(x = 0; x < size; x++){
    if(x != x1){
      //if this is a different space (we don't want to cound collisions wit ourself)
      if(x == x1 || y1 == result[x] || absVal(x-x1)==absVal(result[x]-y1)){
        c++;
  //      printf("c is now %d\n", c);
      }
    }
  }
  //printf("c is %d\n", c);
  return c;
}
void printSolution(int result[], int size){
  for(int i = 0; i < size; i++){
    for(int y = 0; y < result[i]; y++){
      printf(". ");
    }
    if(conflict(i, result[i], result, size))
      printf("X ");
    else
      printf("%d ", result[i]);
    for(int y = result[i]+1; y < size; y++){
      printf(". ");
    }
    printf("\n");
  }
}

void matrixHackA(int result[], int size){
  for(int i = size-1; i >= 0; i--){
    for(int y = 0; y < result[i]; y++){
      printf(". ");
    }
    if(conflict(i, result[i], result, size))
      printf("X ");
    else
      printf("%d ", result[i]);
    for(int y = result[i]+1; y < size; y++){
      printf(". ");
    }
    printf("\n");
  }
}

void matrixHackB(int result[], int size){
  for(int i = size-1; i >= 0; i--){
    for(int y = size-1; y > result[i]; y--){
      printf(". ");
    }
    if(conflict(i, result[i], result, size))
      printf("X ");
    else
      printf("%d ", result[i]);
    for(int y = result[i]-1; y >= 0; y--){
      printf(". ");
    }
    printf("\n");
  }
}


int legal(int x2, int y2, int result[]) {
	for (int i = 0; i < x2; i++) {

		if ((result[i] == y2)	|| (absVal(i - x2) == absVal(result[i] - y2))) {
			return 0;
      result[i] = -1;
		}
	}
	return 1;
}


int legalBoard(int result[], int length){
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
int generateBoard(int result[], int size){
  int i;
  for(i = 0; i < size; i++ ){
    result[i] = i;
  }

  int a, b;
  for(i = 0; i < size; i++){
    a = rand();
    a = a % size;
    b = rand();
    b = b % size;

    int temp = result[a];
    result[a] = result[b];
    result[b] = temp;
  }
}


//returns the column of result[row] with the fewest conflicts
int safestCol(int result[], int size, int row){
  int min = 1000000;
  int best = result[row];
  for(int col = 0; col < size; col++){
    int t = conflict(row, col, result, size);
    if( t < min ){
      min = t;
      best = col;
    }
  }
  return best;
}


int main() {
  int n, q, x, y;
  srand(time(NULL));   // Initialization, should only be called once.
  printf("Insert n size:\n");
  std::cin >> n;
  printf("Insert first Queen Location:\n");
  //std::cin >> q;
  int result[n];
//  result[n];


  int a;
  while(1){
    generateBoard(result, n);
    int patience = 500;
    while(!legalBoard(result, n) && patience--){
      a = rand() % n;
      //printf("safest column of %dth row would be %d\n", a, safestCol(result, n, a));
      result[a] = safestCol(result, n, a);
      //printSolution(result, n);

    }

    if(legalBoard(result, n)){
      printSolution(result, n);
      printf("=====\n");
      matrixHackA(result, n);
      printf("=====\n");
      matrixHackB(result, n);
      printf("We did it!\n");
      return 0;
    }
    else{
      printf("Giving up and starting over...!\n");
    }
  }

}

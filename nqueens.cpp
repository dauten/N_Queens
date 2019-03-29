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
      printf(".");
    }

    printf("O", result[i]);


    for(int y = result[i]+1; y < size; y++){
      printf(".");
    }
    printf("\n");
  }
}

std::ofstream fout("nqueen.out");

void print1solution(int result[], int size, int num)
{
	fout << num << std::endl;
	for (int r=1;r<=size;r++)
	{
	  for (int c=1;c<=size;c++)
		  if (result[r]==c)
			  fout << "O";
		  else
			  fout << ".";
	  fout << std::endl;
	}
	fout << std::endl << std::endl;

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


//given blank board, fill it with queens greedily.
//conflicts matrix is filled with number of queens that
//threaten that particular space
void generateBoard(int result[], int size, int initx, int inity){
  int i;

  result[initx] = inity;

  int a, b;

  for(i = 0; i < initx; i++){
    //assign value to result[i] with fewest conflicts
    result[i] = safestCol(result, size, i);
  }
  for(i = initx+1; i < size; i++){
    //assign value to result[i] with fewest conflicts
    result[i] = safestCol(result, size, i);
  }
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



int main() {
  int n, q, x, y;
  srand(time(NULL));   // Initialization, should only be called once.
  printf("Insert n size:\n");
  std::cin >> n;
  printf("Insert first Queen Location's x:\n");
  std::cin >> x >> y;
  int result[n];
//  result[n];

  int solutions = 0;
  int a;
  while(solutions < 3){
    generateBoard(result, n, x, y);
    int patience = 1000;
    while(!legalBoard(result, n) && patience--){
      a = rand() % n;
      //printf("safest column of %dth row would be %d\n", a, safestCol(result, n, a));
      if(a != x){
  //      printf("a is %d x is %d y is %d\n", a, x, y);
        result[a] = safestCol(result, n, a);
      }

      result[x] = y;
            //printSolution(result, n);

    }

    if(legalBoard(result, n)){
      printSolution(result, n);
      solutions++;
      print1solution(result, n, solutions);
      printf("=====\n");

    }
    else{
    //  printf("Giving up and starting over...!\n");
    }
  }

}

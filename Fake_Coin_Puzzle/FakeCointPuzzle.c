#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>

/*C program that solves the fake coin puzzle.*/

int *fillArray(int size)
{
  // 0 = fake coin, 1 = real coin
  // First, allocate memory for the coin array
  int *coins = (int*)malloc(size * sizeof(int));

  // Second, randomly locate the fake coin in the array.

  int fakeCoinPosition = rand() % (size);
  printf("Fake coin position: %d\n", fakeCoinPosition);
  coins[fakeCoinPosition] = 0;

  // Third, fill the rest of the array with real coins.

  for(int i = 0; i < size; i++)
  {
    if(i == fakeCoinPosition)
    {
      continue;
    }

    coins[i] = 1;
  }

  return coins;
}

void printArray(int * coins, int size)
{
  printf("Coins: ");
  for(int i = 0; i < size; i++)
  {
    printf("%d ", coins[i]);
  }

  printf("\n");
}

// Will be a recursize algorithm.
void algorithm(int * coins, int size)
{

  // First, divide the array in half.
  // Second, alloacte memory for three different arrays. Two might only be necessary.

  int * setOne;
  int * setTwo;
  int * setThree;
  int half = size / 2;
  int remainder = size % 2;
  int setTwoCount = 0;
  int setOneWeight = 0;
  int setTwoWeight = 0;

  if(remainder == 1)
  {
    // Create arrays to contain coins.
    setOne = (int*)malloc(half * sizeof(int));
    setTwo = (int*)malloc(half * sizeof(int));
    setThree = (int*)malloc(sizeof(int));

    // Fill arrays using the orignal array

    for(int i = 0; i < size; i++)
    {
      if(i < (size / 2))
      {
        setOne[i] = coins[i];
      }else if(i >= (size / 2) && i != (size - 1))
      {
        setTwo[setTwoCount] = coins[i];
        setTwoCount++;
      }
    }

    setThree[0] = coins[size - 1];

    printf("Set One ==> ");
    printArray(setOne, size/2);
    printf("\n");

    printf("Set Two ==> ");
    printArray(setTwo, size/2);
    printf("\n");

    printf("Set Three ==> ");
    printArray(setThree, 1);
    printf("\n");

  }else
  {
    // Create arrays to contain coins.
    setOne = (int*)malloc(half * sizeof(int));
    setTwo = (int*)malloc(half * sizeof(int));

    // For loop that fills both arrays.
    for(int i = 0; i < size; i++)
    {
      if(i < (size / 2))
      {
        setOne[i] = coins[i];
      }else if(i >= (size /2))
      {
        setTwo[setTwoCount] = coins[i];
        setTwoCount++;
      }
    }

    printf("Set One ==> ");
    printArray(setOne, size/2);
    printf("\n");

    printf("Set Two ==> ");
    printArray(setTwo, size/2);
    printf("\n");

  }

  // After putting the coins in there seperate sets, now weigh set one and set two.

  for(int i = 0; i < size / 2; i++)
  {
    setOneWeight += setOne[i];
    setTwoWeight += setTwo[i];
  }

  printf("Set one weight: %d\n", setOneWeight);
  printf("Set two weight: %d\n", setTwoWeight);

  // Now compare weights

  if(setOneWeight == setTwoWeight) // If set one and set two are equal, that means that fake coin is in set three.
  {
    printf("Located in set three.\n");
    return;
  }else if(setOneWeight < setTwoWeight) // If set one weighs less than set two, that means that the fake coin is set one.
  {
    if(half == 1)
    {
      printf("Found fake coin in set one!\n");
    }else
    {
      algorithm(setOne, size/2);
    }
  }else  // If set two weighs less than set two, that means that the fake coin is set two.
  {
    if(half == 1)
    {
      printf("Found fake coin in set two!\n");
    }else
    {
      algorithm(setTwo, size/2);
    }
  }

  free(setOne); free(setTwo); free(setThree);
}

int main(int argc, char**argv)
{
  printf("  __________________\n");
  printf("  |Fake Coin Puzzle|\n");
  printf("  |________________|\n");
  printf("Author: Dylan Silva-Rivas");
  printf("\n");

  srand(time(0));

  int upperLimit = 100;
  int lowerLimit = 10;

  int sizeOfArray = rand() % (upperLimit - lowerLimit + 1) + lowerLimit;
  printf("size: %d\n", sizeOfArray);

  int *coins = fillArray(sizeOfArray);

  printArray(coins, sizeOfArray);

  algorithm(coins, sizeOfArray);

  free(coins);

  return 0;
}

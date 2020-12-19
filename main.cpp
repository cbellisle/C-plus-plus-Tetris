/*
Caleb Bellisle
December 2020

Idea inspired by Javidx9(https://www.youtube.com/watch?v=8OK8_tHeCIA)
Wanted to see if I could implement my own version, using my current skillset in C++

Making my own tetris game engine


Things I'm going to need

Rotations
Collisions
game loop

color changer for fun
next block preview



*/

#include "SSDL.h"


enum {ROWS = 22, CLMS = 12};

enum Items {WALL = 10, BLOCK = 11, EMPTY = 12};

// initialize board
void initialize(Items Board[ROWS][CLMS]);

void display(Items Board[ROWS][CLMS]);

void drawBlock(Items Board[ROWS][CLMS], int block, int nextBlock);

void changeDirection(Items Board[ROWS][CLMS], int& currentX, int& currentY, int& currentRotation);

int rotate(Items Board[ROWS][CLMS], int& px, int& py, int& r);

int color(); // returns 0-2 1 = red 2 = green 3 = blue

int blockType();

int main(int argc, char** argv)
{
	srand(time(nullptr));
	// set the window size to how many tetris blox +2 for borders and + 1 for height
	SSDL_SetWindowSize(251, 440);// 251, 440

	Items Board[ROWS][CLMS];

	int block = blockType();
	int nextBlock = blockType();

	initialize(Board);

	drawBlock(Board, block, nextBlock);

	display(Board);


	int currentRotation = 0;
	int currentPiece = 0;
	int currentX = 5;
	int currentY = 1;



	bool playing = true;
	SSDL_SetFramesPerSecond(60);

	while (playing == true)
	{

		changeDirection(Board, currentX, currentY, currentRotation);


		//if (SSDL_IsKeyPressed('q'))
		//{
		//	rotate(Board, currentX, currentY, currentRotation);
		//}


		SSDL_RenderClear();

		display(Board);



		SSDL_WaitKey();
	}



	int fuck = color();
	
	//sout << Board[0][0];


	SSDL_WaitKey();
	return 0;
}

void initialize(Items Board[ROWS][CLMS]) // some shit is broken in this i got no damn clue wtf
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (i != 0 && j != 0)
			{
				Board[i][j] = EMPTY;
			}
			if (i == 0 || i == 20)
			{
				Board[i][j] = WALL;
			}
			if (j == 0 || j == 11)
			{
				Board[i][j] = WALL;
			}
		}
	}
}

void display(Items Board[ROWS][CLMS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < CLMS; j++)
		{
			if (Board[i][j] == WALL)
			{
				SSDL_RenderDrawRect(j * 21, i * 21, 20, 20);
			}
			if (Board[i][j] == BLOCK)
			{
				SSDL_SetRenderDrawColor(RED);
				SSDL_RenderDrawRect(j * 21, i * 21, 20, 20);
				SSDL_SetRenderDrawColor(WHITE);
			}
		}
	}
}

void drawBlock(Items Board[ROWS][CLMS],  int block, int nextBlock)
{
	// middle is Board[1][5] and [1][6]
	switch (block)
	{
	case 0:	// straight block
		Board[1][5] = BLOCK;
		Board[2][5] = BLOCK;
		Board[3][5] = BLOCK;
		Board[4][5] = BLOCK;
		break;
	case 1: // L shaped block
		Board[1][5] = BLOCK;
		Board[3][6] = BLOCK;
		Board[2][5] = BLOCK;
		Board[3][5] = BLOCK;
		break;

	case 2:	// J Block
		Board[1][6] = BLOCK;
		Board[2][6] = BLOCK;
		Board[3][6] = BLOCK;
		Board[3][5] = BLOCK;
		break;
	case 3:	// T block
		Board[1][4] = BLOCK;
		Board[1][5] = BLOCK;
		Board[1][6] = BLOCK;
		Board[2][5] = BLOCK;
		break;
	case 4: // Z block
		Board[1][4] = BLOCK;
		Board[1][5] = BLOCK;
		Board[2][5] = BLOCK;
		Board[2][6] = BLOCK;
		break;
	case 5: // CUBE
		Board[1][5] = BLOCK;
		Board[1][6] = BLOCK;
		Board[2][5] = BLOCK;
		Board[2][6] = BLOCK;
		break;
	case 6:	// s
		Board[1][5] = BLOCK;
		Board[1][6] = BLOCK;
		Board[2][5] = BLOCK;
		Board[2][4] = BLOCK;
		break;
	}
}


void changeDirection(Items Board[ROWS][CLMS], int& currentX, int& currentY, int& currentRotation)
{
	if (SSDL_IsKeyPressed('s'))
	{
		for (int i = ROWS; i > 0; i--)
		{
			for (int j = 0; j < CLMS; j++)
			{
				if (Board[i][j] == BLOCK && Board[i + 1][j] != WALL && Board[i + 1][j] != BLOCK)
				{
					Board[i + 1][j] = BLOCK;
					Board[i][j] = EMPTY;
					currentY += 1;

				}
			}
		}
	}
	if (SSDL_IsKeyPressed('a'))
	{
		for (int i = ROWS; i > 0; i--)
		{
			for (int j = 0; j < CLMS; j++)
			{
				if (Board[i][j] == BLOCK && Board[i][j - 1] != WALL && Board[i][j - 1] != BLOCK)
				{
					Board[i][j-1] = BLOCK;
					Board[i][j] = EMPTY;
					currentX -= 1;
				}


			}
		}
	}
	if (SSDL_IsKeyPressed('d'))
	{
		for (int i = ROWS; i > 0; i--) 
		{
			for (int j = CLMS; j > 0; j--)
			{
				if (Board[i][j] == BLOCK && Board[i][j + 1] != WALL && Board[i][j + 1] != BLOCK)
				{

					Board[i][j + 1] = BLOCK;
					Board[i][j] = EMPTY;
					currentX += 1;
				}


			}
		}
	}
	if (SSDL_IsKeyPressed('q'))
	{
		Board[currentX][currentY] = EMPTY;
		Board[currentY][currentX * -1] = BLOCK;



		rotate(Board, currentX, currentY, currentRotation);
		if (currentRotation == 3)
			currentRotation = 0;
		else
			currentRotation += 1;
	}

}

int rotate(Items Board[ROWS][CLMS], int& px, int& py, int& r)
{
	int pi = 0;
	switch (r % 4)
	{
	case 0: // 0 degrees			// 0  1  2  3
		pi = py * 4 + px;			// 4  5  6  7
		break;						// 8  9 10 11
									//12 13 14 15

	case 1: // 90 degrees			//12  8  4  0
		pi = 12 + py - (px * 4);	//13  9  5  1
		break;						//14 10  6  2
									//15 11  7  3

	case 2: // 180 degrees			//15 14 13 12
		pi = 15 - (py * 4) - px;	//11 10  9  8
		break;						// 7  6  5  4
									// 3  2  1  0

	case 3: // 270 degrees			// 3  7 11 15
		pi = 3 - py + (px * 4);		// 2  6 10 14
		break;						// 1  5  9 13
	}								// 0  4  8 12

	return pi;
}


int blockType()
{
	int num = rand() % 7;
	
	return num;
}

int color()
{
	int num = rand() % 3;

	return num;
}
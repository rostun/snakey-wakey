#include <iostream>
#include <conio.h>

using namespace std;
bool gameOver;
const int width = 20;
const int height = 10;
int snakeX, snakeY, fruitX, fruitY, score;
int tailX[100], tailY[100];
enum class eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void _generateFruit()
{
	fruitX = rand() % width + 1;
	fruitY = rand() % height + 1;
}

void Setup()
{
	gameOver = false;
	dir = eDirection::STOP;
	snakeX = width / 2;
	snakeY = height / 2;
	score = 0;
	_generateFruit();
}
void Draw()
{
	system("cls");
	//first line
	for (int colx = 0; colx < width + 2; colx++)
		cout << "#";
	cout << endl;
	for (int rowy = 1; rowy < height + 1; rowy++)
	{
		for (int colx = 0; colx < width + 2; colx++)
		{
			string symbol = " ";
			//tail
			for (int tail = 0; tail < score; tail++)
			{
				if (colx == tailX[tail] && rowy == tailY[tail])
					symbol = '+';
			}
			//border
			if (colx == 0 || colx == width + 1)
				symbol = "#";
			//snake
			else if (colx == snakeX && rowy == snakeY)
				symbol = "S";
			//fruit
			else if (colx == fruitX && rowy == fruitY)
				symbol = "O";
			cout << symbol;
		}
		cout << endl;
	}
	for (int colx = 0; colx < width + 2; colx++)
	{
		cout << "#";
	}	
	//score
	cout << endl;
	cout << "Score: " << score << endl;
	cout << "[SNAKE] rowx: " << snakeX << " [SNAKE] coly: " << snakeY << endl;
	cout << "[FRUIT] rowx: " << fruitX << " [FRUIT] coly: " << fruitY << endl;
	cout << "[TAILX-1]: " << tailX[0] << " [TAILY-1]: " << tailY[0] << endl;
}
void Input()
{
	if (_kbhit)
	{
		switch (_getch())
		{
			case 'a':
				dir = eDirection::LEFT;
				break;
			case 'w':
				dir = eDirection::UP;
				break;
			case 'd':
				dir = eDirection::RIGHT;
				break;
			case 's':
				dir = eDirection::DOWN;
				break;
			case 'q':
				gameOver = true;
				break;
		}
	}
}
void Logic()
{
	//if bounds are hit
	if (snakeX > width || snakeY > height || snakeX < 1 || snakeY < 1)
		gameOver = true;
	//move snake based on player direction
	switch (dir)
	{
		case eDirection::LEFT:
			snakeX--;
			break;
		case eDirection::UP:
			snakeY--;
			break;
		case eDirection::RIGHT:
			snakeX++;
			break;
		case eDirection::DOWN:
			snakeY++;
			break;
		default:
			break;
	}
	//if fruit is eaten
	if (snakeX == fruitX && snakeY == fruitY)
	{
		tailX[score] = fruitX;
		tailY[score] = fruitY;
		score++;
		_generateFruit();
	}
	//move tail based on player direction
	switch (dir)
	{
		case eDirection::LEFT:
			for (int t = 0; t < score; t++)
			{
				tailX[t]--;
			}
			break;
		case eDirection::UP:
			break;
		case eDirection::RIGHT:
			for (int t = 0; t < score; t++)
			{
				tailX[t]++;
			}
			break;
		case eDirection::DOWN:
			break;
		default:
			break;
	}
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		//Sleep(10);
	}
	return 0;
}
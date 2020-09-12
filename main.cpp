#include <iostream>
#include <conio.h>

using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int snakeX, snakeY, fruitX, fruitY, score;
enum class eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = eDirection::STOP;
	snakeX = width / 2;
	snakeY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw()
{
	system("cls");
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//border
			if (j == 0 || j == width - 1)
				cout << "#";
			//snake
			else if (i == snakeY && j == snakeX)
				cout << "S";
			//fruit
			else if (i == fruitY && j == fruitX)
				cout << "O";
			//empty space
			else
				cout << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++)
	{
		cout << "#";
	}	
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
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
	fruitX = rand() % width;
	fruitY = rand() % height;
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
	for (int col = 0; col < width + 2; col++)
		cout << "#";
	cout << endl;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width + 2; col++)
		{
			string symbol = " ";
			//border
			if (col == 0 || col == width + 1)
				symbol = "#";
			//snake
			else if (row == snakeX && col == snakeY)
				symbol = "S";
			//fruit
			else if (row == fruitX && col == fruitY)
				symbol = "O";
			//tail
			//else
			/*{
				for (int t = 0; t < score; t++) 
				{
					if (i == tailX[t] && j == tailY[t])
						symbol = '-';
				}
			}*/
			
			cout << symbol;
		}
		cout << endl;
	}
	for (int col = 0; col < width + 2; col++)
	{
		cout << "#";
	}	
	//score
	cout << endl;
	cout << "Score: " << score << endl;
	cout << "x: " << fruitX << " y: " << fruitY << endl;
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
	//if bounds are hit
	if (snakeX > width || snakeY > height + 2)
		gameOver = true;
	//if fruit is eaten
	if (snakeX == fruitX && snakeY == fruitY)
	{
		tailX[score] = fruitX;
		tailY[score] = fruitY;
		score++;
		_generateFruit();
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
#include <iostream>
#include <conio.h> //input
#include <time.h> //true random number
#include <vector>

using namespace std;

struct Point
{
	int X, Y;
};
std::vector<Point> availableXY;
std::vector<Point> nonavailableXY;

bool gameOver;
const int width = 20, height = 10;
int snakeX, snakeY, 
	prevSnakeX, prevSnakeY, 
	fruitX, fruitY, 
	tailX[100], tailY[100],
	score;
enum class eDirection 
{ 
	STOP = 0, 
	LEFT, 
	RIGHT, 
	UP, 
	DOWN 
};

eDirection dir;

void _generateFruit()
{
	fruitX = rand() % width + 1;
	fruitY = rand() % height + 1;
}

void Setup()
{
	srand(time(NULL));
	gameOver = false;
	dir = eDirection::STOP;
	snakeX = width / 2;
	snakeY = height / 2;
	prevSnakeX = snakeX;
	prevSnakeY = snakeY;
	score = 0;
	
	//fill in available and non available coordinates
	for (int x = 1; x < 21; x++) {
		for (int y = 1; y < 11; y++) {
			struct Point p = { x, y };
			(x == snakeX && y == snakeY) ? nonavailableXY.push_back(p) : availableXY.push_back(p);
		}
	}

	//generate fruit within available coordinates
	_generateFruit();

}
void Debug()
{
	cout << endl;
	cout << "Score: " << score << endl;
	cout << "[FRUIT] rowx: " << fruitX << " [FRUIT] coly: " << fruitY << endl;
	cout << "[SNAKE] rowx: " << snakeX << " [SNAKE] coly: " << snakeY << endl;
	cout << "[P_SNAKE] rowx: " << prevSnakeX << " [P_SNAKE] coly: " << prevSnakeY << endl;
	for (int place = 0; place < score; place++)
	{
		cout << "[TAIL] [" << place << "] [X]: " << tailX[place] << " [Y]: " << tailY[place] << endl;
	}
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

	Debug();
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
	//store snake head position
	prevSnakeX = snakeX;
	prevSnakeY = snakeY;

	//change snake head position based on player direction
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

	//move tail based on player direction
	int prevX = prevSnakeX;
	int prevY = prevSnakeY;

	//if snake head overlaps body and it's not a fruit
	for (int t = 0; t < score; t++)
	{
		if (snakeX == tailX[t] && snakeY == tailY[t])
		{
			Draw();
			gameOver = true;
		}
	}

	//move each coordinate to next
	for (int t = 0; t < score; t++)
	{
		int currX = tailX[t];
		int currY = tailY[t];
		tailX[t] = prevX;
		tailY[t] = prevY;
		prevX = currX;
		prevY = currY;
	}

	//if fruit is eaten
	if (snakeX == fruitX && snakeY == fruitY)
	{
		tailX[score] = fruitX;
		tailY[score] = fruitY;
		score++;
		_generateFruit();
	}

	//if bounds are hit
	if (snakeX > width || snakeY > height || snakeX < 1 || snakeY < 1)
	{
		Draw();
		gameOver = true;
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
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <vector>

class Snake
{
public:
	Snake (int a):height{ a }, width{ a }
	{
		gameOver = false;
		x = a / 2 - 1;
		y = a / 2 - 1;
		div = Stop;
		fx = std::rand() % a;
		fy = std::rand() % a;
		score = 0;
		x_l.resize(100);
		y_l.resize(100);
	}
	void Drow()
	{
		std::system("cls");//"clear"
		for (int i = 0; i < width; ++i)
		{
			std::cout << "#";
		}
		std::cout << std::endl;
		for (int i = 0; i <= height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if (j == 0 || j == width - 1) { std::cout << "#"; }
				else if (i == x && j == y) { std::cout << "*"; }
				else if (i == fx && j == fy) { std::cout << "$"; }
				else 
				{
					bool print = true;
					for (int k = 0; k < score; ++k) 
					{
						if (x_l[k] == i && y_l[k] == j) 
						{
							print = false;
							std::cout << "*";
						}
					}
					if (print)
					{
						std::cout << " ";
					}
				}
			}
			std::cout << std::endl;
		}
		for (int i = 0; i < width; ++i)
		{
			std::cout << "#";
		}
		std::cout << std::endl;
		std::cout << "My score :: " << score << std::endl ;
	}
	void Input()
	{
		if (_kbhit())
		{
				if (_getch() == 'a') { div = Left; }
				else if (_getch() == 'd') { div = Right; }
				else if (_getch() == 'w') { div = Up; }
				else if (_getch() == 's') { div = Down; }
				else if (_getch() == 'x') { gameOver = true; }
		}
	}
	void Logic()
	{
		int prevx = x_l[0];
		int prevy = y_l[0];
		int prev2x, prev2y;
		x_l[0] = x;
		y_l[0] = y;
		for (int i = 1; i < score; ++i) 
		{
			prev2x = x_l[i];
			prev2y = y_l[i];
			x_l[i] = prevx;
			y_l[i] = prevy;
			prevx = prev2x;
			prevy = prev2y;
		}
		if (div == Left) { y--; }
		else if (div == Right) { y++; }
		else if (div == Up) { x--; }
		else if (div == Down) { x++; }

		if (x <0 || x > height || y < 0 || y > width) 
		{ 
			std::cout << "Game Over:: your score " << score;
			exit(1);
		}
		else if (x == fx && y == fy) 
		{
			score++;
			fx = std::rand() % height;
			fy = std::rand() % width;

		}
		for (int i = 0; i < score; ++i) 
		{
			if (x_l[i] == x && y_l[i] == y) { gameOver = true; }
		}
	}
	bool gameOver;
	enum eDirection { Stop = 0, Left, Right, Up, Down };
private:
	const int height;
	const int width;
	int x, y, fx, fy, score;
	eDirection div;
	std::vector<int>x_l;
	std::vector<int>y_l;
};
int main()
{
	Snake a(40);
	while (!a.gameOver)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		a.Drow();
		a.Input();
		a.Logic();
	}
}

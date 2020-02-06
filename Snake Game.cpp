#include <iostream>
#include <ctime>
#include<conio.h>
#include<Windows.h>
using namespace std;
//-----------------------Proberties--------------------//
enum Direction{ Top = 1,Down,Right,Left };
struct Map { int Width, Height, FruitX, FruitY; };
struct Snake { int HeadX, HeadY, Tail_N, Tail_X[50],Tail_Y[50]; char Dir;};
struct Player{ int Score; bool lose;};
//----------------------------------------------------//
Map Map1; Snake Snake1; Player Player1;
void GenerateFruit() {
	srand(time(NULL));
	Map1.FruitX = rand() % (Map1.Width - 2) + 1; // 1 ~ 38
	Map1.FruitY = rand() % (Map1.Height - 2) + 1; // 1 ~ 18
}
void ShiftRight(int arr[], int size) {
	for (int i = size - 2; i >= 0; i--) {
		arr[i + 1] = arr[i];
	}
}
void Setup() {
	Map1.Width = 40;
	Map1.Height = 20;
	GenerateFruit();
	//-------------------------------
	Snake1.HeadX = Map1.Width / 2;
	Snake1.HeadY = Map1.Height / 2;
	Snake1.Tail_N = 0;
	//--------------------------------
	Player1.Score = 0;
	Player1.lose = false;
	//----------------------------------
}
void DrawFunc() {
	system("cls"); //system clear
	for (int i = 0; i < Map1.Height; i++){
		for (int j = 0; j < Map1.Width; j++){
			if (i == 0 || i == Map1.Height - 1 ){cout << "*";}
			else if (j == 0 || j == Map1.Width - 1){ cout << "*"; }
			else if (i == Snake1.HeadY&&j == Snake1.HeadX){ cout << "0"; }
			else if (i == Map1.FruitY&&j == Map1.FruitX){ cout << "$"; }
			else{
				bool print = false;
				for (int z = 0; z < Snake1.Tail_N; z++){
					if (Snake1.Tail_X[z] == j && Snake1.Tail_Y[z] == i){
						cout << "o";
						print = true;
						break;
					}
				}
				if (!print) { cout << " ";}
			}
		}cout << endl;
	}
	cout << "Player Score : " << Player1.Score << endl;
}
void Input() {
	if (!(_kbhit() == 0)){
		char c = _getch();
		switch (c)
		{
		case'w':Snake1.Dir = Top; break;
		case's':Snake1.Dir = Down; break;
		case'd':Snake1.Dir = Right; break;
		case'a':Snake1.Dir = Left; break;
		case'x':exit(0);
		}
	}
}
void Move() {
	ShiftRight(Snake1.Tail_X, 50);
	ShiftRight(Snake1.Tail_Y, 50);
	Snake1.Tail_X[0] = Snake1.HeadX;
	Snake1.Tail_Y[0] = Snake1.HeadY;
	switch (Snake1.Dir)
	{
	case Top: Snake1.HeadY--; break;
	case Down:Snake1.HeadY++; break;
	case Right:Snake1.HeadX++; break;
	case Left:Snake1.HeadX--; break;
	}
	if (Snake1.HeadY >= Map1.Height || Snake1.HeadY <= 0 || Snake1.HeadX >= Map1.Width || Snake1.HeadX <= 0){
		Player1.lose = true;
	}if (Snake1.HeadX == Map1.FruitX && Snake1.HeadY == Map1.FruitY){
		GenerateFruit();
		Player1.Score += 1;
		Snake1.Tail_N++;
	}
}
int main() {
	Setup();
	while (!Player1.lose){
		DrawFunc();
		Input();
		Move();
		Sleep(30);
	}

	system("pause");
	return 0;
};
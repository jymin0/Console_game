// #include
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

// #define
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 // ����(�����̽���)


#define PLAYER '2'
#define WATER '3'
#define FOOD '4'

// color seting
enum {
	black,
	blue,
	green,
	cyan,
	red,
	purple,
	brown,
	lightgray,
	darkgray,
	lightblue,
	lightgreen,
	lightcyan,
	lightred,
	lightpurple,
	yellow,
	white
};
char maps[10][32][32];
char initmap[32][32] = {
	// 0: �����, 1: ��, *; ��, #: ��(��o), @: ��(��x), +:ǥ�ü�
	// ���� �� ���� [2][2]~[29][29]
	{"0000000000000#***#0000000000000"},
	{"0111111111111#@@@#1111111111110"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"##000000000000000000000000000##"},
	{"*@000000000000000000000000000@*"},
	{"*@000000000000000000000000000@*"},
	{"*@000000000000000000000000000@*"},
	{"##000000000000000000000000000##"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0100000000000000000000000000010"},
	{"0111111111111#@@@#1111111111110"},
	{"0000000000000#***#0000000000000"},
};
short pX;
short pY;

// funcions list
void init();
void gotoxy(short, short);
void setColor(short, short);
void titleDraw();
short menuDraw();
short keyControl();
void infoDraw();
void randomObjectMaking(char, char *);
void creatmap(short);
void drawMap(short);

// main function
int main()
{
	int menuCode = -1;
	init();
	while (1)
	{
		titleDraw();
		menuCode = menuDraw();

		if (menuCode == 0)
		{
			creatmap(0);
			Sleep(500);
			drawMap(0);
			_getch();
		}
		else if (menuCode == 1)
		{
			infoDraw();
		}
		else if (menuCode == 2)
		{
			break;
		}
		menuCode = -1;
		system("cls");
	}
	gotoxy(12, 16);
	printf("������ ����Ǿ����ϴ�!!!");
	return _getch();
}

// function seting
void init()
{
	system("mode con cols=104 lines=40 | title survival game");
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}
void gotoxy(short x, short y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
void setColor(short forground, short background)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}
void titleDraw()
{

}
short menuDraw()
{
	int x = 24;
	int y = 12;
	gotoxy(x - 2, y); // -2 �� ������ > �� ����ؾ��ϱ� ������  
	printf("> ���ӽ���");
	gotoxy(x, y + 1);
	printf("��������");
	gotoxy(x, y + 2);
	printf("  ����  ");
	while (1) { // ���ѹݺ�  
		int n = keyControl(); // Ű���� �̺�Ʈ�� Ű������ �޾ƿ���  
		switch (n) {
		case UP: { // �Էµ� Ű�� ���� UP�ΰ�� (w) 
			if (y > 12) { // y�� 12~14������ �̵�  
				gotoxy(x - 2, y); // x-2 �ϴ� ������ ">"�� ��ĭ ������ ����ϱ�����  
				printf(" "); // ���� ��ġ�� �����  
				gotoxy(x - 2, --y); // ���� �̵��� ��ġ�� �̵��Ͽ�  
				printf(">"); // �ٽ� �׸���  
			}
			break;
		}

		case DOWN: { // �Էµ� Ű�� ���� DOWN�ΰ�� (s) 
			if (y < 14) { // �ִ� 14  
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case SUBMIT: {
			return y - 12; // �����̽���(����)�Ǿ��� ��� y-12
			// y ���� ��ġ�� 12�����Ƿ� y-12 �� �ϸ� 0, 1, 2 �� ���ڸ� ���� �� �ִ�. 
		}
		}
	}
}
short keyControl() {
	char temp = _getch();

	if (temp == 'w' || temp == 'W')
	{
		return UP;
	}
	else if (temp == 'a' || temp == 'A')
	{
		return LEFT;
	}
	else if (temp == 's' || temp == 'S')
	{
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D')
	{
		return RIGHT;
	}
	else if (temp == ' ')
	{ // �����̽���(����)�� ���� ��ư  
		return SUBMIT;
	}
}
void infoDraw()
{

}
void creatmap(short index)
{
	memcpy(maps[index], initmap, sizeof(initmap));
	srand(time(NULL));
	char* changePoint = (char*)&maps + index * 32 * 32;
	for (int i = 0; i < 4; i++)
	{
		randomObjectMaking(WATER, changePoint);
	}
	for (int i = 0; i < 4; i++)
	{
		randomObjectMaking(FOOD, changePoint);
	}
	randomObjectMaking(PLAYER, changePoint);

}
void randomObjectMaking(char object, char *map)
{
	short posx, posy;
	while (1)
	{
		srand(rand());
		posx = 2 + rand() % 28;
		posy = 2 + rand() % 28;
		char *p = map+posx * 32;
		if (p[posy] == '0')
			p[posy] = object;
			break;
	}
}
void drawMap(short pos)
{
	system("cls");
	int h, w;
	char temp;
	for (h = 0; h < 32; h++)
	{
		for (w = 0; w < 32; w++)
		{
			temp = maps[pos][h][w];
			if (temp == '0')
			{
				setColor(black, black);
				printf("   ");
			}
			else if (temp == '1')
			{
				setColor(white, white);
				printf("   ");
			}
			else if (temp == PLAYER)
			{
				//�÷��̾� X,Y ��ġ ����
				pX = w;
				pY = h;
				setColor(cyan, black);
				printf(" @ ");
			}
			else if (temp == WATER)
			{
				setColor(black, cyan);
				printf(" W ");
			}
			else if (temp == FOOD)
			{
				setColor(black, lightgreen);
				printf(" F ");
			}
			else
			{
				setColor(white, white);
				printf("   ");
			}
		}
		setColor(black, black);
		printf("\n");
	}
	setColor(white, black);
}
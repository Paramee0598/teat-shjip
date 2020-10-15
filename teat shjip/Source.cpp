#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

void score(int, int);
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf(" <^-0-^> ");
}
void erase_ship(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("         ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y); printf("^");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
void draw_star(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("*");
}
void clear_star(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf(" ");
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}


char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
}

int random_between(int min, int max)
{
	int r = (rand() / (float)RAND_MAX) * (max + 1) + min;
	return r > max ? max : r;
}
int number = 0;

int main()
{setcursor(0);
	srand(time(NULL));
	char ch = ' ';
	int x = 38, y = 20;
	int bx, by, i;
	int bullet = 0;
	int star = 0; 
	
	draw_ship(x, y);

	
	setcursor(0);
		srand(time(NULL));  // ล้างค่าrandom
	

	do {
		for (; star <= 21; star++)
		{ 
			draw_star(random_between(10, 70), random_between(2, 5));
		}
		score(2, 2);
		 

			if (_kbhit()) {
				ch = _getch();
				if (ch == 'a')
				{
					draw_ship(--x, y);
					if (x <= 0) {
						{ draw_ship(++x, y); }
					}
				}

				if (ch == 'd')
				{
					draw_ship(++x, y);
					if (x >= 71) {
						{ draw_ship(--x, y); }

					}
				}
				if (bullet == 0 && ch == ' ') {
					bullet = 1; bx = x + 4;  by = y - 1;
				}
				///

				fflush(stdin);
			}


			if (bullet == 1) {

				if (cursor(bx, by - 1) == '*') {  // การเช็คค่าว่ามันโดน * ไหม

					bullet = 0;								// เซ้ทค่าเพื่อให้ให้ค่า มันเป็น 1 เหมือนเดิม เพราะไม่งั้น เมื่อชนแล้วลูกษรนี้ ^ ก็ยังไม่หายไป
					clear_star(bx, by);
					clear_bullet(bx, by - 1);
					Beep(960,200);  //ให้เกิดเสียง
					star--;
					number = number + 1;  // เมื่อยิงโดน ให้เพิ่มค่าscore ทีละ 1 
					continue;
				}
				else {

					//raw_bullet(bx, by); //จาก  position_y[i] - 1 ถ้ามันยังไม่น้อยกว่า 0 (ต่อข้อความข่างล่าง)
					clear_bullet(bx, by);								// มันก็จะวาดอันใหม่ที่ตำแหน่งโดนลบไป 1 แล้วจากด้านบนที่ลบไป

				}

				if (by < 2){ bullet = 0; }
				else {
					draw_bullet(bx, --by);

					bullet = 1;


				}

			


			Sleep(100);

			}

		
	} while (ch != 'x');
	return 0;
}


void score(int x, int y) {  // กระดานคะแนนข้างขวา 
	//setcolor(7, 4);
	gotoxy(70, 0);
	printf("SCORE : %d ", number); //ให้คะแนนเพิ่มขึ้นเมื่อยินโดน

}


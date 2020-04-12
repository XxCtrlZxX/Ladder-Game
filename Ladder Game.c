#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <string.h>

#define HEIGHT 25

void printLadder(int n);
void printExtra(int n);
void printResult(int n);
void paint(int x, int y, char ch[4]);
void cursor(int n); // 커서 없애기

void gotoxy(int x, int y) { // 좌표 이동
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int ladder[31][HEIGHT + 1] = { 0, };
char name[31][20];
char result[30][20];
char stu1_5[27][10] = {
"고은초롱",
"박서영",
"이채원",
"권수현",
"김경완",
"김민웅",
"김세진",
"김영운",
"김재현",
"김제유",
"김준서",
"김형규",
"모현성",
"서호영",
"송은우",
"심  준",
"엄희성",
"우동관",
"이예찬",
"이종우",
"장유덕",
"정찬우",
"정해성",
"차민우",
"황두영",
"황윤상"
};
int stu_rand[27] = { 0, };
int winner[27] = { 0, };
int res[27];

int main()
{
	int num = 0, selected = 0, input = 0, tmp = 0, random = 0, win;

	printf("참여 인원 수 (최대 26) >> ");
	scanf_s("%d", &num);
	if (num > 26) num = 26;
	printf("당첨 인원 수 >> ");
	scanf_s("%d", &win);
	if (win > num) win = num;

	srand((unsigned int)time(NULL));

	// 당첨 위치 랜덤
	int a = 0;
	while (a < win)
	{
		random = rand() % num;
		if (winner[random] == 1) continue;
		winner[random] = 1;
		a++;
	}

	// 학생 랜덤 지정
	a = 0;
	while (a < num) {
		tmp = 0;
		random = rand() % 26;
		for (int j = 0; j < a; j++)
			if (random == stu_rand[j]) {
				tmp = 1;
				break;
			}
		if (tmp == 1)
			continue;
		stu_rand[a] = random;
		a++;
	}

	// 사다리 초기화
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < num - 1; j++)
		{
			random = rand() % 3;
			if (random == 1 && ladder[i][j + 1] != 1 && ladder[i][j - 1] != 1)
				ladder[i][j] = 1;
		}
		ladder[i][num - 1] = 0;
	}

	// 결과 미리 저장
	for (int i = 0; i < num; i++)
	{
		selected = i;
		for (int j = 0; j < HEIGHT; j++)
			if (ladder[j][selected] == 1)
				selected++;
			else if (ladder[j][selected - 1] == 1)
				selected--;
		res[i] = selected;
	}

	do {
		system("mode con cols=240 lines=40"); // 콘솔창 크기 조절
		printLadder(num);
		gotoxy(5, HEIGHT + 6);
		printf("(결과 모두 보기...0)");
		gotoxy(5, HEIGHT + 7);
		printf("몇 번째 사다리? >> ");
		scanf_s("%d", &input);
		if (input == 0)
			printResult(num);
		else if (input >= 1 && input <= num)
		{
			cursor(0); // cursor(0);은 커서 숨기기, cursor(1);은 커서 보이기
			selected = --input;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // 빨간색

			paint(selected * 9 + 4, 2, "││");

			for (int i = 0; i < HEIGHT; i++)
			{
				paint(selected * 9 + 4, i + 3, "││");

				if (ladder[i][selected] == 1)
				{
					paint(selected * 9 + 4, i + 3, "│─");
					for (int j = selected * 9 + 6; j < (selected + 1) * 9 + 5; j++)
						paint(j, i + 3, "─");
					selected++;
					paint(selected * 9 + 3, i + 3, "─││");
				}
				else if (ladder[i][selected - 1] == 1)
				{
					for (int j = selected * 9 + 3; j > (selected - 1) * 9 + 4; j--)
						paint(j, i + 3, "─");
					selected--;
					paint(selected * 9 + 4, i + 3, "│");
				}
			}
			paint(selected * 9 + 4, HEIGHT + 3, "││");

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 흰색

			gotoxy(5, HEIGHT + 9);
			printf("%s -> %d번째 사다리 : ", stu1_5[stu_rand[input]], selected + 1);
			if (winner[selected] == 1) printf("당첨!");
			else printf("꽝!");
			gotoxy(5, HEIGHT + 11);
		}
		else
			break;

		printf("계속하려면 아무키");
		cursor(1);
		_getch();
	} while (1);
	gotoxy(5, HEIGHT + 11);
	printf("아무 키를 누르면 종료됩니다\n");
	_getch();
}

void printLadder(int n)
{
	system("cls");
	printf(" ");
	for (int i = 0; i < n; i++)
		printf("%5d    ", i + 1);

	printf("\n");
	for (int i = 0; i < n; i++)
		printf("%8s ", stu1_5[stu_rand[i]]);

	printf("\n");
	printExtra(n);
	for (int i = 0; i < HEIGHT; i++)
	{
		printf("    ");
		for (int j = 0; j < n - 1; j++)
		{
			printf("│");
			if (ladder[i][j] == 1)
				printf("────────");
			else
				printf("        ");
		}
		printf("│\n");
	}
	printExtra(n);
	printf(" ");
	// 사다리 밑 번호 출력
	/*for (int i = 0; i < n; i++)
	printf("%5d    ", i + 1);*/

	// 당첨 & 꽝 출력
	for (int i = 0; i < n; i++) {
		if (winner[i] == 1)
			printf("  %4s   ", "당첨");
		else
			printf("  %4s   ", "꽝");
	}
	printf("\n");
}

void printResult(int n)
{
	system("cls");
	system("mode con cols=150 lines=55"); // 콘솔창 크기 조절
	for (int i = 0; i < n; i++)
	{
		printf("\n");
		printf("    %s → ", stu1_5[stu_rand[i]]);
		if (winner[res[i]] == 1)
			printf("당첨(%d번째 사다리)!\n", res[i] + 1);
		else
			printf("꽝(%d번째 사다리)!\n", res[i] + 1);
	}
	gotoxy(5, n * 2 + 2);
}

void printExtra(int n)
{
	printf("    ");
	for (int i = 0; i < n; i++)
		printf("│        ");
	printf("\n");
}

void paint(int x, int y, char ch[4])
{
	gotoxy(x, y);
	printf("%s", ch);
	Sleep(70);
}

void cursor(int n) // 커서 보이기 & 숨기기
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = n;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
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
void cursor(int n); // Ŀ�� ���ֱ�

void gotoxy(int x, int y) { // ��ǥ �̵�
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int ladder[31][HEIGHT + 1] = { 0, };
char name[31][20];
char result[30][20];
char stu1_5[27][10] = {
"�����ʷ�",
"�ڼ���",
"��ä��",
"�Ǽ���",
"����",
"��ο�",
"�輼��",
"�迵��",
"������",
"������",
"���ؼ�",
"������",
"������",
"��ȣ��",
"������",
"��  ��",
"����",
"�쵿��",
"�̿���",
"������",
"������",
"������",
"���ؼ�",
"���ο�",
"Ȳ�ο�",
"Ȳ����"
};
int stu_rand[27] = { 0, };
int winner[27] = { 0, };
int res[27];

int main()
{
	int num = 0, selected = 0, input = 0, tmp = 0, random = 0, win;

	printf("���� �ο� �� (�ִ� 26) >> ");
	scanf_s("%d", &num);
	if (num > 26) num = 26;
	printf("��÷ �ο� �� >> ");
	scanf_s("%d", &win);
	if (win > num) win = num;

	srand((unsigned int)time(NULL));

	// ��÷ ��ġ ����
	int a = 0;
	while (a < win)
	{
		random = rand() % num;
		if (winner[random] == 1) continue;
		winner[random] = 1;
		a++;
	}

	// �л� ���� ����
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

	// ��ٸ� �ʱ�ȭ
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

	// ��� �̸� ����
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
		system("mode con cols=240 lines=40"); // �ܼ�â ũ�� ����
		printLadder(num);
		gotoxy(5, HEIGHT + 6);
		printf("(��� ��� ����...0)");
		gotoxy(5, HEIGHT + 7);
		printf("�� ��° ��ٸ�? >> ");
		scanf_s("%d", &input);
		if (input == 0)
			printResult(num);
		else if (input >= 1 && input <= num)
		{
			cursor(0); // cursor(0);�� Ŀ�� �����, cursor(1);�� Ŀ�� ���̱�
			selected = --input;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // ������

			paint(selected * 9 + 4, 2, "����");

			for (int i = 0; i < HEIGHT; i++)
			{
				paint(selected * 9 + 4, i + 3, "����");

				if (ladder[i][selected] == 1)
				{
					paint(selected * 9 + 4, i + 3, "����");
					for (int j = selected * 9 + 6; j < (selected + 1) * 9 + 5; j++)
						paint(j, i + 3, "��");
					selected++;
					paint(selected * 9 + 3, i + 3, "������");
				}
				else if (ladder[i][selected - 1] == 1)
				{
					for (int j = selected * 9 + 3; j > (selected - 1) * 9 + 4; j--)
						paint(j, i + 3, "��");
					selected--;
					paint(selected * 9 + 4, i + 3, "��");
				}
			}
			paint(selected * 9 + 4, HEIGHT + 3, "����");

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // ���

			gotoxy(5, HEIGHT + 9);
			printf("%s -> %d��° ��ٸ� : ", stu1_5[stu_rand[input]], selected + 1);
			if (winner[selected] == 1) printf("��÷!");
			else printf("��!");
			gotoxy(5, HEIGHT + 11);
		}
		else
			break;

		printf("����Ϸ��� �ƹ�Ű");
		cursor(1);
		_getch();
	} while (1);
	gotoxy(5, HEIGHT + 11);
	printf("�ƹ� Ű�� ������ ����˴ϴ�\n");
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
			printf("��");
			if (ladder[i][j] == 1)
				printf("����������������");
			else
				printf("        ");
		}
		printf("��\n");
	}
	printExtra(n);
	printf(" ");
	// ��ٸ� �� ��ȣ ���
	/*for (int i = 0; i < n; i++)
	printf("%5d    ", i + 1);*/

	// ��÷ & �� ���
	for (int i = 0; i < n; i++) {
		if (winner[i] == 1)
			printf("  %4s   ", "��÷");
		else
			printf("  %4s   ", "��");
	}
	printf("\n");
}

void printResult(int n)
{
	system("cls");
	system("mode con cols=150 lines=55"); // �ܼ�â ũ�� ����
	for (int i = 0; i < n; i++)
	{
		printf("\n");
		printf("    %s �� ", stu1_5[stu_rand[i]]);
		if (winner[res[i]] == 1)
			printf("��÷(%d��° ��ٸ�)!\n", res[i] + 1);
		else
			printf("��(%d��° ��ٸ�)!\n", res[i] + 1);
	}
	gotoxy(5, n * 2 + 2);
}

void printExtra(int n)
{
	printf("    ");
	for (int i = 0; i < n; i++)
		printf("��        ");
	printf("\n");
}

void paint(int x, int y, char ch[4])
{
	gotoxy(x, y);
	printf("%s", ch);
	Sleep(70);
}

void cursor(int n) // Ŀ�� ���̱� & �����
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = n;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
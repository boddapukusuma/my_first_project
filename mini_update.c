#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void save_game(int, int);
void conert_number_to_string(int, char);
void generate_rand(int, int);
void save_to_leaderboard(int, char, int);


struct lboard_data
{
	char dat[50];
	char names[50];
	char board[10];
	int move;
}l;

int gameover_check(int a[4][4], int b[4][4], int size)
{
	int s = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (a[i][j] == b[i][j])
				s = s + 1;
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			b[i][j] = a[i][j];
	}

	if (s == (size*size))
		return 1;
	else
		return 0;
}

int find(int num, int size, int arr[])
{
	int i = 0;
	for (i = 0; i < 2 * (size*size); i++)
	{
		if (arr[i] == num)
		{
			return 1;
			break;
		}
	}
	return 0;
}

void display(int size, int a[4][4])
{
	int flag = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%d  ", a[i][j]);
		}
		printf("\n");
	}
}

void generatefib(int arr[], int size)
{
	int  x1 = 0, x3 = 0, x2 = 1, n = 2;
	arr[0] = 0;
	arr[1] = 1;
	while (n<(2 * size*size))
	{
		x3 = x1 + x2;
		arr[n] = x3;
		x1 = x2;
		x2 = x3;
		n = n + 1;
	}
}

void adddown(int size, int a[4][4], int i, int arr[])
{
	int j = 0, k, l;
	k = size - 1;
	for (j = size - 1; j > 0; j--)
	{
		if (find(a[j][i] + a[j - 1][i], 4, arr) == 1)
		{
			a[k][i] = a[j][i] + a[j - 1][i];
			l = j - 1;
			while (l>0)
			{
				a[l][i] = a[l - 1][i];
				l = l - 1;
			}
			a[l][i] = 0;
		}
		k = k - 1;
	}

}

void down(int a[4][4], int arr[], int size)
{
	int k, j;
	for (int i = size - 1; i >= 0; i--)
	{
		for (int j = 1; j <= size - 1; j++)
		{
			if (a[j][i] == 0)
			{
				k = j;
				while (k>0)
				{
					a[k][i] = a[k - 1][i];
					k = k - 1;
				}
				a[k][i] = 0;
			}
		}
		adddown(size, a, i, arr);
	}


}

void addtop(int size, int a[4][4], int i, int arr[])
{
	int j = 0, k, l;
	k = 0;
	for (j = 0; j<size - 1; j++)
	{
		if (find(a[j][i] + a[j + 1][i], 4, arr) == 1)
		{
			a[k][i] = a[j][i] + a[j + 1][i];
			l = j + 1;
			while (l<size - 1)
			{
				a[l][i] = a[l + 1][i];
				l = l + 1;
			}
			a[l][i] = 0;
		}
		k = k + 1;
	}

}

void top(int a[4][4], int arr[], int size)
{
	int k, j;
	for (int i = size - 1; i >= 0; i--)
	{
		for (int j = size - 2; j >= 0; j--)
		{
			if (a[j][i] == 0)
			{
				k = j;
				while (k<size - 1)
				{
					a[k][i] = a[k + 1][i];
					k = k + 1;
				}
				a[k][i] = 0;
			}
		}
		addtop(size, a, i, arr);
	}

}

void addleft(int size, int a[4][4], int i, int arr[])
{
	int j = 0, k, l;
	k = 0;
	for (j = 0; j<size - 1; j++)
	{
		if (find(a[i][j] + a[i][j + 1], 4, arr) == 1)
		{
			a[i][k] = a[i][j] + a[i][j + 1];
			l = j + 1;
			while (l<size - 1)
			{
				a[i][l] = a[i][l + 1];
				l = l + 1;
			}
			a[i][l] = 0;
		}
		k = k + 1;
	}
}

void left(int a[4][4], int arr[], int size)
{
	int k, j;
	for (int i = size - 1; i >= 0; i--)
	{
		for (int j = size - 2; j >= 0; j--)
		{
			if (a[i][j] == 0)
			{
				k = j;
				while (k<size - 1)
				{
					a[i][k] = a[i][k + 1];
					k = k + 1;
				}
				a[i][k] = 0;
			}
		}
		addleft(size, a, i, arr);
	}
}

void addright(int size, int a[4][4], int i, int arr[])
{
	int j = 0, k, l;
	k = size - 1;
	for (j = size - 1; j > 0; j--)
	{
		if (find(a[i][j] + a[i][j - 1], 4, arr) == 1)
		{
			a[i][k] = a[i][j] + a[i][j - 1];
			l = j - 1;
			while (l>0)
			{
				a[i][l] = a[i][l - 1];
				l = l - 1;
			}
			a[i][l] = 0;
		}
		k = k - 1;
	}

}

void right(int a[4][4], int arr[], int size)
{
	int k, j;
	for (int i = size - 1; i >= 0; i--)
	{
		for (int j = 1; j <= size - 1; j++)
		{
			if (a[i][j] == 0)
			{
				k = j;
				while (k>0)
				{
					a[i][k] = a[i][k - 1];
					k = k - 1;
				}
				a[i][k] = 0;
			}
		}
		addright(size, a, i, arr);
	}

}

void save_to_leaderboard(int moves, char name[50], int size)
{
	FILE *f;
	time_t t;
	char m[50];
	int i;
	printf("%s win the game with %d moves \n", name, moves);
	f = fopen("lboard.txt", "a+");
	time(&t);
	for (i = 0; ctime(&t)[i] != '\0'; i++)
		l.dat[i] = ctime(&t)[i];
	l.dat[i] = '\0';
	for (i = 0; name[i] != '\0'; i++)
		l.names[i] = name[i];
	l.names[i] = '\0';
	l.board[0] = size + '0';
	l.board[1] = 'x';
	l.board[2] = size + '0';
	l.board[3] = '\0';
	l.move = moves;
	fputs(l.dat, f);
	fputs(l.names, f);
	fputs("\n", f);
	fputs(l.board, f);
	fputs("\n", f);
	conert_number_to_string(moves, m);
	fputs(m, f);
	fputs("\n", f);
}



void play_game(int a[4][4], int size, int arr[], int moves, char name[50])
{
	int b[4][4], i, j, s = 0, c = 0;
	while (1)
	{
		scanf("%c", &c);
		if (c == 's')
		{
			down(a, arr, size);
			system("cls");
			display(size, a);
			system("cls");
			generate_rand(a, size);
			display(size, a);
			moves = moves + 1;
			save_game(a, size, name, moves);
		}
		else if (c == 'w')
		{
			top(a, arr, size);

			system("cls");
			display(size, a);
			system("cls");
			generate_rand(a, size);
			display(size, a);
			moves = moves + 1;
			save_game(a, size, name, moves);
		}
		else if (c == 'a')
		{
			left(a, arr, size);
			system("cls");
			display(size, a);
			system("cls");
			generate_rand(a, size);
			display(size, a);
			moves = moves + 1;
			save_game(a, size, name, moves);
		}
		else if (c == 'd')
		{
			right(a, arr, size);
			system("cls");
			display(size, a);
			system("cls");
			generate_rand(a, size);
			display(size, a);
			moves = moves + 1;
			save_game(a, size, name, moves);
		}
		else if (c == 'q')
		{
			break;
		}
		s = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				b[i][j] = a[i][j];
				if (a[i][j] == arr[(2 * size*size) - 1])
					s = s + 1;
			}
		}
		if (s >= 1)
		{
			save_to_leaderboard(moves, name, size);
			break;
		}
		s = 0;
		left(b, arr, size);
		s = s + gameover_check(a, b, size);
		right(b, arr, size);
		s = s + gameover_check(a, b, size);
		top(b, arr, size);
		s = s + gameover_check(a, b, size);
		down(b, arr, size);
		s = s + gameover_check(a, b, size);
		if (s == 4)
		{
			printf("%s \b loss the game with %d moves\n", name, moves);
			system("pause");
			break;
		}
	}
}

void conert_number_to_string(int n, char s[50])
{
	char *s1 = (char*)malloc(20 * sizeof(char));
	int i = 0, j = 0, r;
	while (n != 0)
	{
		r = n % 10;
		s1[i] = r + '0';
		i = i + 1;
		n = n / 10;
	}
	i = i - 1;
	while (i >= 0)
	{
		s[j] = s1[i];
		j++;
		i--;
	}
	s[j] = '\0';
}

void save_game(int a[4][4], int size, char name[50], int moves)
{
	char *s = (char*)malloc(20 * sizeof(char));
	FILE *f1;
	int i = 0, j = 0, r;
	f1 = fopen("lgame.txt", "w");
	fputs(name, f1);
	fputs("\n", f1);
	conert_number_to_string(moves, s);
	fputs(s, f1);
	fputs("\n", f1);
	conert_number_to_string(size, s);
	fputs(s, f1);
	fputs("\n", f1);
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			conert_number_to_string(a[i][j], s);
			fputs(s, f1);
			fputs("\n", f1);
		}
	}
}

void last_saved_game(int a[4][4], int *size, char name[50], int *moves)
{
	FILE *f1;
	int b[16], i = 0, s, j = 0, k = 0;
	char *t = (char*)malloc(100 * sizeof(char));
	f1 = fopen("lgame.txt", "r");
	fgets(t, 100, f1);
	for (i = 0; t[i] != '\n'; i++)
		name[i] = t[i];
	name[i] = '\0';
	while (fgets(t, 100, f1) != NULL)
	{
		i = 0;
		s = 0;
		while (t[i] != '\n')
		{
			s = s * 10 + (t[i] - '0');
			i = i + 1;
		}
		b[j] = s;
		j = j + 1;
	}
	*moves = b[k];
	k = k + 1;
	*size = b[k];
	k = k + 1;
	for (i = 0; i < *size; i++)
	{
		for (j = 0; j < *size; j++)
		{
			a[i][j] = b[k];
			k++;
		}
	}
}

void view_leaderboard()
{
	FILE *f;
	char s[50];
	f = fopen("lboard.txt", "r");
	int c = 1, t = 1;
	printf("SNo\tDate\t\t\t\tName\t\t\tBoard\t\t\tMoves\n");
	while (fgets(s, 50, f) != NULL)
	{
		int i = 0;
		while (s[i] != '\n')
			i = i + 1;
		s[i] = '\0';
		if (c % 4 == 1)
		{
			printf("\n%d\t", t);
			printf("%s\t", s);
			t = t + 1;
		}
		else
			printf("%s\t\t\t", s);
		c = c + 1;
	}
	system("pause");
}

void generate_rand(int a[4][4], int size)
{
	int i = 500;
	while (i--)
	{
		int c = 0;
		int temp1 = rand() % size;
		int temp2 = rand() % size;
		if (a[temp1][temp2] == 0)
		{
			a[temp1][temp2] = 1;
			break;
		}
	}
}

int main()
{
	int a[4][4], b[4][4], i, j, s = 0, temp1, temp2, moves = 0;
	char c, name[50];
	int arr[50], size = 0, n;
	printf("1.play Game\n");
	printf("2.Replay last saved Game\n");
	printf("3.View Leader\n");
	printf("select 1 or 2 or 3\n");
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		printf("enter your name\n");
		scanf("%s", name);
		printf("enter the size of the board you want to play\n");
		scanf("%d", &size);
		for (i = 0; i<4; i++)
		{
			for (j = 0; j<4; j++)
			{
				a[i][j] = 0;
			}
		}
		generatefib(arr, size);
		a[rand() % size][rand() % size] = 1;
		a[rand() % size][rand() % size] = 1;
		system("cls");
		printf("for resuming your game press z\n");

		display(size, a);
		play_game(a, size, arr, moves, name);
		break;
	case 2:
		last_saved_game(a, &size, name, &moves);
		system("cls");
		generatefib(arr, size);
		display(size, a);
		play_game(a, size, arr, moves, name);
		break;
	case 3:
		view_leaderboard();
		break;
	default:
		printf("\nplease select 1 or 2 or 3\n");
		main();
		break;
	}
	return 0;
}

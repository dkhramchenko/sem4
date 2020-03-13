#include <iostream>
using namespace std;

void print(int** a, int n)
{
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

void floyd(int** a, int n)
{
	for (int k = 1; k <= n; ++k)
	{
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				int prom = a[i][k] + a[k][j];
				if (prom < a[i][j])
				{
					a[i][j] = prom;
				}
			}
		}
		print(a, n);
		cout << endl;
	}
}

int main()
{
	int n = 8;
	int** a = new int*[n + 1];
	for (int i = 0; i <= n; ++i)
	{
		a[i] = new int[n + 1];
	}

	int m = 99;

	a[1][1] = 0; a[1][2] = 5; a[1][3] = m; a[1][4] = m;
	a[1][5] = m; a[1][6] = m; a[1][7] = m; a[1][8] = 22;

	a[2][1] = 5; a[2][2] = 0; a[2][3] = 12; a[2][4] = 22;
	a[2][5] = m; a[2][6] = m; a[2][7] = m; a[2][8] = m;

	a[3][1] = m; a[3][2] = 12; a[3][3] = 0; a[3][4] = 53;
	a[3][5] = m; a[3][6] = 50; a[3][7] = m; a[3][8] = 14;

	a[4][1] = m; a[4][2] = 22; a[4][3] = 53; a[4][4] = 0;
	a[4][5] = 33; a[4][6] = m; a[4][7] = 25; a[4][8] = m;

	a[5][1] = m; a[5][2] = m; a[5][3] = m; a[5][4] = 33;
	a[5][5] = 0; a[5][6] = 20; a[5][7] = m; a[5][8] = m;

	a[6][1] = m; a[6][2] = m; a[6][3] = 50; a[6][4] = m;
	a[6][5] = 20; a[6][6] = 0; a[6][7] = 61; a[6][8] = 16;

	a[7][1] = m; a[7][2] = m; a[7][3] = m; a[7][4] = 25;
	a[7][5] = m; a[7][6] = 61; a[7][7] = 0; a[7][8] = m;

	a[8][1] = 22; a[8][2] = m; a[8][3] = 14; a[8][4] = m;
	a[8][5] = m; a[8][6] = 16; a[8][7] = m; a[8][8] = 0;

	print(a, n);
	cout << endl;
	floyd(a, n);

	for (int i = 0; i < n + 1; ++i)
	{
		delete[] a[i];
	}
	delete[] a;

	return 0;
}
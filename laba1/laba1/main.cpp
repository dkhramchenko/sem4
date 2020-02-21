#include <iostream>

using namespace std;

int det(int** a)
{
	//return a[0][3] * a[1][2] * a[2][1] * a[3][0] - ....;
	return 1;
}

int main()
{
	double x[12] = {-3.1, -2.3, -1.5, -0.7, 0.1, 0.9, 1.7, 2.5, 3.3, 4.1, 4.9, 5.7};
	double y[12] = { 6.07, 5.88, 5.61, 5.34, 5.17, 4.89, 4.65, 4.41, 4.12, 2.91, 3.65, 3.47 };
	double c[7];
	double b[4];
	for (int k = 0; k < 7; k++)
	{
		c[k] = 0;
		for (int i = 0; i < 12; i++)
		{
			c[k] += pow(x[i], k);
		}
	}
	for (int k = 0; k < 4; k++)
	{
		b[k] = 0;
		for (int i = 0; i < 12; i++)
		{
			b[k] += pow(y[i], k);
		}
	}
	/*
	double m[4][4] = { {c[0], c[1], c[2], c[3]}, {}, {}, {} };
	double m0[4][4] = 
	double m1[4][4] =
	double m2[4][4] =
	double m3[4][4] =
	double a[4];
	a[0] = det(m0) / det(m);
	a[1] = det(m1) / det(m);
	a[2] = det(m2) / det(m);
	a[3] = det(m3) / det(m);

	double delta = 0;
	for (int i = 0; i < 12; ++i)
	{
		double temp =  
			y[i] - (a[3] * pow(x[i], 3) + a[2] * pow(x[i], 2) + a[1] * x[i] + a[0]);
		delta += temp * temp;
	}
	delta = sqrt(1.0 / 12.0 * delta);
	*/
	return 0;
}
#include <iostream>
#include "Image.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");
	cout << "����� 1:" << endl;
	cout << "������� 1:" << endl;
	cout << "����� Image ���������� � �������� ����" << endl;

	cout << "������� 2:" << endl;
	cout << "��� �������� ������ ������ RGBQUAD" << endl;

	cout << "������� 3:" << endl;
	Image img1("image.bmp");
	Image img2();
	img2.loadimage("image.bmp");

	cout << "������� 4:" << endl;
	Image img3(60, 32, 480, 600);

	cout << "������� 5:" << endl;
	Image img4("image.bmp");
	img4.writeimage("image1.bmp");

	cout << "������� 6:" << endl;
	Image img5;

	cout << "������� 7:" << endl;
	Image img6("image.bmp");
	Image img7 = img6;

	cout << "������� 8:" << endl;
	cout << "���������� ���������� � �������� ����" << endl;

	// ����� 2
	Image original("original.bmp");
	Image scaled = original /= 2;
	scaled.writeimage("scaled.bmp");
	Image depth1bit = original / 1;
	depth1bit.writeimage("depth1bit.bmp");
	Image depth8bit = original / 8;
	depth8bit.writeimage("depth8bit.bmp")

	return 0;
}
#include <iostream>
#include "Image.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");
	cout << "Часть 1:" << endl;
	cout << "Задание 1:" << endl;
	cout << "Класс Image реализован в листинге кода" << endl;

	cout << "Задание 2:" << endl;
	cout << "Для хранения данных выбран RGBQUAD" << endl;

	cout << "Задание 3:" << endl;
	Image img1("image.bmp");
	Image img2();
	img2.loadimage("image.bmp");

	cout << "Задание 4:" << endl;
	Image img3(60, 32, 480, 600);

	cout << "Задание 5:" << endl;
	Image img4("image.bmp");
	img4.writeimage("image1.bmp");

	cout << "Задание 6:" << endl;
	Image img5;

	cout << "Задание 7:" << endl;
	Image img6("image.bmp");
	Image img7 = img6;

	cout << "Задание 8:" << endl;
	cout << "Деструктор реализован в листинге кода" << endl;
	return 0;
}
#include "Image.h"
#include <iostream>

using namespace std;

Image::Image(char Mode, unsigned short BCount, int Width, int Height)
{
    /* »нинциализаци€ заголовка изображени€, все параметры задаютс€ стандартного или
    вычисл€ютс€ на основании BCount, Width и Height, дл€ палитровых изображений вычисление
        некоторых переменных может отличатьс€*/
    BMInfoHeader.Size = 40;
    BMInfoHeader.Width = Width;
    /*
    ...
    ...
    ...
    */
    BMInfoHeader.ColorUsed = 0;
    /* ¬ данной реализации предусмотрено хранение данных изображени€ как в RGBTRIPLE, так и
    в RGBQUAD*/
    if (BMInfoHeader.BitCount == 24)
    {
        // ¬ыделение пам€ти дл€ двумерного массива размером Height*Width типа RGBTRIPLE
        Rgbtriple = new RGBTRIPLE * [BMInfoHeader.Height];
        for (int i = 0; i < BMInfoHeader.Height; i++)
            Rgbtriple[i] = new RGBTRIPLE[BMInfoHeader.Width];
        // «аполнение данных изображени€
        for (int i = 0; i < BMInfoHeader.Height; i++)
            for (int j = 0; j < BMInfoHeader.Width; j++)
            {
                Rgbtriple[i][j].Red = Mode;
                Rgbtriple[i][j].Green = Mode;
                Rgbtriple[i][j].Blue = Mode;
            }
    }
    /*
    if (BMInfoHeader.BitCount == 32)
    {
        Rgbquad = new RGBQUAD * [BMInfoHeader.Height];
        for (int i = 0; i < BMInfoHeader.Height; i++)
            Rgbquad[i] = new RGBQUAD[BMInfoHeader.Width];
        for (int i = 0; i < BMInfoHeader.Height; i++)
            for (int j = 0; j < BMInfoHeader.Width; j++)
            {
                Rgbquad[i][j].Red = Mode;
                Rgbquad[i][j].Green = Mode;
                Rgbquad[i][j].Blue = Mode;
                Rgbquad[i][j].Reserved = 0;
            }
    }
    */
}

//  онструктор объекта изображени€ из файла
Image::Image(char* fileName)
{
    BITMAPFILEHEADER BMFileHeader;
    BITMAPINFOHEADER BMInfoHeader;
    FILE* f;
    f = fopen(fileName, "rb"); // необходимо открывать бинарный файл
    fread(&BMFileHeader, sizeof(BITMAPFILEHEADER), 1, f);
    fread(&BMInfoHeader, sizeof(BITMAPINFOHEADER), 1, f);
}
#include "Image.h"
#include <iostream>

using namespace std;

Image::Image(char Mode, unsigned short BCount, int Width, int Height)
{
    /* �������������� ��������� �����������, ��� ��������� �������� ������������ ���
    ����������� �� ��������� BCount, Width � Height, ��� ���������� ����������� ����������
        ��������� ���������� ����� ����������*/
    BMInfoHeader.Size = 40;
    BMInfoHeader.Width = Width;
    /*
    ...
    ...
    ...
    */
    BMInfoHeader.ColorUsed = 0;
    /* � ������ ���������� ������������� �������� ������ ����������� ��� � RGBTRIPLE, ��� �
    � RGBQUAD*/
    if (BMInfoHeader.BitCount == 24)
    {
        // ��������� ������ ��� ���������� ������� �������� Height*Width ���� RGBTRIPLE
        Rgbtriple = new RGBTRIPLE * [BMInfoHeader.Height];
        for (int i = 0; i < BMInfoHeader.Height; i++)
            Rgbtriple[i] = new RGBTRIPLE[BMInfoHeader.Width];
        // ���������� ������ �����������
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

// ����������� ������� ����������� �� �����
Image::Image(char* fileName)
{
    BITMAPFILEHEADER BMFileHeader;
    BITMAPINFOHEADER BMInfoHeader;
    FILE* f;
    f = fopen(fileName, "rb"); // ���������� ��������� �������� ����
    fread(&BMFileHeader, sizeof(BITMAPFILEHEADER), 1, f);
    fread(&BMInfoHeader, sizeof(BITMAPINFOHEADER), 1, f);
}
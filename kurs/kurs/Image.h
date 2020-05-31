#pragma once

struct BITMAPFILEHEADER
{
    unsigned short Type; // �BM� 0x4D42
    unsigned long Size; // ������ ����� � ������, BitCount*Height*Width+ OffsetBits
    unsigned short Reserved1; // ��������������; ������ ���� ����
    unsigned short Reserved2; // ��������������; ������ ���� ����
    unsigned long OffsetBits; // �������� ������ �� ������ ����� � ������
   // = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)
};

struct BITMAPINFOHEADER
{
    unsigned long Size; // ����� ������ ����������� ��� ��������� = 40
    unsigned long Width; // ������ ��������� ������� � ��������
    unsigned long Height; // ������ ��������� ������� � ��������
    unsigned short Planes; // ����� ���������� �������� ���������� = 1
    unsigned short BitCount; // ������� �����, ����� ��� �� ����� = 0,1,4,8,16,24,32
    unsigned long Compression; // ��� ������ = 0 ��� ��������� �����������
    unsigned long SizeImage; // ������ ����������� � ������ BitCount*Height*Width
    unsigned long XPelsPerMeter; // ����������� ����������� �� �����������
    unsigned long YPelsPerMeter; // ����������� ����������� �� ���������
    unsigned long ColorUsed; // ����� �������� ������������ ������. ���� ��� ����� = 0
    unsigned long ColorImportant; // ����� ����������� ������ = 0
};


struct RGBTRIPLE
{
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
};

struct RGBQUAD
{
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
    unsigned char Reserved;
};

class Image {
    BITMAPINFOHEADER BMInfoHeader;
    RGBTRIPLE** Rgbtriple;
    // RGBQUAD** Rgbquad;
    /* ������ ����� ��������� � � ���������� ������� RGBTRIPLE *Rgbtriple, ��� ����
    ���������� ������ ��������� � ������� Rgbtriple[i * Width + j] ������ Rgbtriple[i][j]
        RGBQUAD** Rgbquad;*/
public:
    Image(char Mode, unsigned short BCount, int Width, int Height); // ����������� �������� �����������
    Image(char* fileName); // ����������� ������� ����������� �� �����
    Image(); // ����������� ��� ����������, ������� ������ ��������� ��� �����������
    Image(const Image& i); // ����������� �����
    ~Image(); // ����������
    int loadimage(char* fileName); // ����� �������� ����������� ����������� ������������
    void writeimage(char* fileName); // ����� ������ ����������� � ����
    Image operator = (Image Inp); // ���������� ��������� =
    // �
};


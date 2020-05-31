#pragma once

struct BITMAPFILEHEADER
{
    unsigned short Type; // ‘BM’ 0x4D42
    unsigned long Size; // Размер файла в байтах, BitCount*Height*Width+ OffsetBits
    unsigned short Reserved1; // Зарезервирован; должен быть нуль
    unsigned short Reserved2; // Зарезервирован; должен быть нуль
    unsigned long OffsetBits; // Смещение данных от начала файла в байтах
   // = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)
};

struct BITMAPINFOHEADER
{
    unsigned long Size; // Число байтов необходимое для структуры = 40
    unsigned long Width; // Ширина точечного рисунка в пикселях
    unsigned long Height; // Высота точечного рисунка в пикселях
    unsigned short Planes; // Число плоскостей целевого устройства = 1
    unsigned short BitCount; // Глубина цвета, число бит на точку = 0,1,4,8,16,24,32
    unsigned long Compression; // Тип сжатия = 0 для несжатого изображения
    unsigned long SizeImage; // Размер изображения в байтах BitCount*Height*Width
    unsigned long XPelsPerMeter; // Разрешающая способность по горизонтали
    unsigned long YPelsPerMeter; // Разрешающая способность по вертикали
    unsigned long ColorUsed; // Число индексов используемых цветов. Если все цвета = 0
    unsigned long ColorImportant; // Число необходимых цветов = 0
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
    /* данные могут храниться и в одномерном массиве RGBTRIPLE *Rgbtriple, при этом
    изменяется способ обращения к пикселу Rgbtriple[i * Width + j] вместо Rgbtriple[i][j]
        RGBQUAD** Rgbquad;*/
public:
    Image(char Mode, unsigned short BCount, int Width, int Height); // Конструктор создания изображения
    Image(char* fileName); // Конструктор объекта изображения из файла
    Image(); // Конструктор без параметров, создает пустой контейнер под изображение
    Image(const Image& i); // Конструктор копии
    ~Image(); // Деструктор
    int loadimage(char* fileName); // метод загрузки изображения аналогичный конструктору
    void writeimage(char* fileName); // метод записи изображения в файл
    Image operator = (Image Inp); // Перегрузка оператора =
    // …
};


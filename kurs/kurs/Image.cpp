#include "Image.h"
#include <iostream>
#include <string>

using namespace std;

BITMAPINFOHEADER::BITMAPINFOHEADER() {}

void Image::initialize()
{
    Rgbquad = NULL;
    Palette = NULL;
    BMInfoHeader.Size = 40;
    BMInfoHeader.Width = 0;
    BMInfoHeader.Height = 0;
    BMInfoHeader.Planes = 0;
    BMInfoHeader.BitCount = 0;
    BMInfoHeader.Compression = 0;
    BMInfoHeader.SizeImage = 0;
    BMInfoHeader.XPelsPerMeter = 0;
    BMInfoHeader.YPelsPerMeter = 0;
    BMInfoHeader.ColorUsed = 0;
    BMInfoHeader.ColorImportant = 0;
}

//  онструктор без параметров, создает пустой контейнер под изображение
Image::Image()
{
    cout << " онструктор без параметров отработал успешно!" << endl;
}

//  онструктор создани€ изображени€
Image::Image(char Mode, unsigned short BCount, int Width, int Height)
{
    FILE* file = fopen("image.bmp", "wb");
    if (BCount >= 24)
    {
        BITMAPFILEHEADER* bitmapfileheader = new BITMAPFILEHEADER;
        bitmapfileheader->Size = (BCount * Height * Width) + bitmapfileheader->OffsetBits;
        fwrite(&bitmapfileheader->Type, sizeof(bitmapfileheader->Type), 1, file);
        fwrite(&bitmapfileheader->Size, sizeof(bitmapfileheader->Size), 1, file);
        fwrite(&bitmapfileheader->Reserved1, sizeof(bitmapfileheader->Reserved1), 1, file);
        fwrite(&bitmapfileheader->Reserved2, sizeof(bitmapfileheader->Reserved2), 1, file);
        fwrite(&bitmapfileheader->OffsetBits, sizeof(bitmapfileheader->OffsetBits), 1, file);
        BMInfoHeader.BitCount = BCount;
        BMInfoHeader.Size = 40;
        BMInfoHeader.Width = Width;
        BMInfoHeader.Height = Height;
        BMInfoHeader.SizeImage = BCount * Width * Height;
        fwrite(&BMInfoHeader.Size, sizeof(BMInfoHeader.Size), 1, file);
        fwrite(&BMInfoHeader.Width, sizeof(BMInfoHeader.Width), 1, file);
        fwrite(&BMInfoHeader.Height, sizeof(BMInfoHeader.Height), 1, file);
        fwrite(&BMInfoHeader.Planes, sizeof(BMInfoHeader.Planes), 1, file);
        fwrite(&BMInfoHeader.BitCount, sizeof(BMInfoHeader.BitCount), 1, file);
        fwrite(&BMInfoHeader.Compression, sizeof(BMInfoHeader.Compression), 1, file);
        fwrite(&BMInfoHeader.SizeImage, sizeof(BMInfoHeader.SizeImage), 1, file);
        fwrite(&BMInfoHeader.XPelsPerMeter, sizeof(BMInfoHeader.XPelsPerMeter), 1, file);
        fwrite(&BMInfoHeader.YPelsPerMeter, sizeof(BMInfoHeader.YPelsPerMeter), 1, file);
        fwrite(&BMInfoHeader.ColorUsed, sizeof(BMInfoHeader.ColorUsed), 1, file);
        fwrite(&BMInfoHeader.ColorImportant, sizeof(BMInfoHeader.ColorImportant), 1, file);
        delete bitmapfileheader;
        unsigned char size = 0;
        if (BMInfoHeader.BitCount == 24)
        {
            Rgbtriple = new RGBTRIPLE[BMInfoHeader.Height * BMInfoHeader.Width];
            size = sizeof(Rgbtriple->Blue);
            for (int i = 0; i < BMInfoHeader.Height; ++i)
            {
                for (int j = 0; j < BMInfoHeader.Width; ++j)
                {
                    Rgbtriple[i * BMInfoHeader.Width + j].Red = Mode;
                    Rgbtriple[i * BMInfoHeader.Width + j].Green = Mode;
                    Rgbtriple[i * BMInfoHeader.Width + j].Blue = Mode;
                    fwrite(&Rgbtriple[i * BMInfoHeader.Width + j].Red, size, 1, file);
                    fwrite(&Rgbtriple[i * BMInfoHeader.Width + j].Green, size, 1, file);
                    fwrite(&Rgbtriple[i * BMInfoHeader.Width + j].Blue, size, 1, file);
                }
            }
        }

        if (BMInfoHeader.BitCount == 32)
        {
            size = sizeof(Rgbquad->Blue);
            Rgbquad = new RGBQUAD[BMInfoHeader.Height * BMInfoHeader.Width];
            for (int i = 0; i < BMInfoHeader.Height; ++i)
            {
                for (int j = 0; j < BMInfoHeader.Width; ++j)
                {
                    Rgbquad[i * BMInfoHeader.Width + j].Red = Mode;
                    Rgbquad[i * BMInfoHeader.Width + j].Green = Mode;
                    Rgbquad[i * BMInfoHeader.Width + j].Blue = Mode;
                    fwrite(&Rgbquad[i * BMInfoHeader.Width + j].Red, size, 1, file);
                    fwrite(&Rgbquad[i * BMInfoHeader.Width + j].Green, size, 1, file);
                    fwrite(&Rgbquad[i * BMInfoHeader.Width + j].Blue, size, 1, file);
                    fwrite(&Rgbquad->Reserved, size, 1, file);
                }
            }
        }
    }

    if (BCount == 8)
    {
        BITMAPFILEHEADER* bitmapfileheader = new BITMAPFILEHEADER;
        bitmapfileheader->OffsetBits += 256 * 5;
        bitmapfileheader->Size = (BCount * Height * Width) + bitmapfileheader->OffsetBits;
        BMInfoHeader.ColorUsed = 256;
        Palette = new RGBQUAD[256];
        Rgbquad = new RGBQUAD[BMInfoHeader.Height * BMInfoHeader.Width];
        fwrite(&bitmapfileheader->Type, sizeof(bitmapfileheader->Type), 1, file);
        fwrite(&bitmapfileheader->Size, sizeof(bitmapfileheader->Size), 1, file);
        fwrite(&bitmapfileheader->Reserved1, sizeof(bitmapfileheader->Reserved1), 1, file);
        fwrite(&bitmapfileheader->Reserved2, sizeof(bitmapfileheader->Reserved2), 1, file);
        fwrite(&bitmapfileheader->OffsetBits, sizeof(bitmapfileheader->OffsetBits), 1, file);
        BMInfoHeader.BitCount = BCount;
        BMInfoHeader.Size = 40;
        BMInfoHeader.Width = Width;
        BMInfoHeader.Height = Height;
        BMInfoHeader.SizeImage = BCount * Width * Height;
        fwrite(&BMInfoHeader.Size, sizeof(BMInfoHeader.Size), 1, file);
        fwrite(&BMInfoHeader.Width, sizeof(BMInfoHeader.Width), 1, file);
        fwrite(&BMInfoHeader.Height, sizeof(BMInfoHeader.Height), 1, file);
        fwrite(&BMInfoHeader.Planes, sizeof(BMInfoHeader.Planes), 1, file);
        fwrite(&BMInfoHeader.BitCount, sizeof(BMInfoHeader.BitCount), 1, file);
        fwrite(&BMInfoHeader.Compression, sizeof(BMInfoHeader.Compression), 1, file);
        fwrite(&BMInfoHeader.SizeImage, sizeof(BMInfoHeader.SizeImage), 1, file);
        fwrite(&BMInfoHeader.XPelsPerMeter, sizeof(BMInfoHeader.XPelsPerMeter), 1, file);
        fwrite(&BMInfoHeader.YPelsPerMeter, sizeof(BMInfoHeader.YPelsPerMeter), 1, file);
        fwrite(&BMInfoHeader.ColorUsed, sizeof(BMInfoHeader.ColorUsed), 1, file);
        fwrite(&BMInfoHeader.ColorImportant, sizeof(BMInfoHeader.ColorImportant), 1, file);
        for (int i = 0; i < 256; ++i)
        {
            Palette[i].Red = i;
            Palette[i].Green = i;
            Palette[i].Blue = i;
            Palette[i].Reserved = 0;
            fwrite(&Palette[i].Red, 1, 1, file);
            fwrite(&Palette[i].Green, 1, 1, file);
            fwrite(&Palette[i].Blue, 1, 1, file);
            fwrite(&Palette[i].Reserved, 1, 1, file);
        }
        unsigned char* position = new unsigned char[256];
        for (int i = 0; i < 256; ++i)
        {
            position[i] = i;
            fwrite(&position[i], 1, 1, file);
        }
        for (int i = 0; i < BMInfoHeader.Height; ++i)
        {
            for (int j = 0; j < BMInfoHeader.Width; ++j)
            {
                fwrite(&position[Mode], 1, 1, file);
            }
        }
        if (BCount == 8)
    {
        BITMAPFILEHEADER* bitmapfileheader = new BITMAPFILEHEADER;
        bitmapfileheader->OffsetBits += 256 * 5;
        bitmapfileheader->Size = (BCount * Height * Width) + bitmapfileheader->OffsetBits;
        BMInfoHeader.ColorUsed = 256;
        Palette = new RGBQUAD[256];
        Rgbquad = new RGBQUAD[BMInfoHeader.Height * BMInfoHeader.Width];
        fwrite(&bitmapfileheader->Type, sizeof(bitmapfileheader->Type), 1, file);
        fwrite(&bitmapfileheader->Size, sizeof(bitmapfileheader->Size), 1, file);
        fwrite(&bitmapfileheader->Reserved1, sizeof(bitmapfileheader->Reserved1), 1, file);
        fwrite(&bitmapfileheader->Reserved2, sizeof(bitmapfileheader->Reserved2), 1, file);
        fwrite(&bitmapfileheader->OffsetBits, sizeof(bitmapfileheader->OffsetBits), 1, file);
        BMInfoHeader.BitCount = BCount;
        BMInfoHeader.Size = 40;
        BMInfoHeader.Width = Width;
        BMInfoHeader.Height = Height;
        BMInfoHeader.SizeImage = BCount * Width * Height;
        fwrite(&BMInfoHeader.Size, sizeof(BMInfoHeader.Size), 1, file);
        fwrite(&BMInfoHeader.Width, sizeof(BMInfoHeader.Width), 1, file);
        fwrite(&BMInfoHeader.Height, sizeof(BMInfoHeader.Height), 1, file);
        fwrite(&BMInfoHeader.Planes, sizeof(BMInfoHeader.Planes), 1, file);
        fwrite(&BMInfoHeader.BitCount, sizeof(BMInfoHeader.BitCount), 1, file);
        fwrite(&BMInfoHeader.Compression, sizeof(BMInfoHeader.Compression), 1, file);
        fwrite(&BMInfoHeader.SizeImage, sizeof(BMInfoHeader.SizeImage), 1, file);
        fwrite(&BMInfoHeader.XPelsPerMeter, sizeof(BMInfoHeader.XPelsPerMeter), 1, file);
        fwrite(&BMInfoHeader.YPelsPerMeter, sizeof(BMInfoHeader.YPelsPerMeter), 1, file);
        fwrite(&BMInfoHeader.ColorUsed, sizeof(BMInfoHeader.ColorUsed), 1, file);
        fwrite(&BMInfoHeader.ColorImportant, sizeof(BMInfoHeader.ColorImportant), 1, file);
        for (int i = 0; i < 256; ++i)
        {
            Palette[i].Red = i;
            Palette[i].Green = i;
            Palette[i].Blue = i;
            Palette[i].Reserved = 0;
            fwrite(&Palette[i].Red, 1, 1, file);
            fwrite(&Palette[i].Green, 1, 1, file);
            fwrite(&Palette[i].Blue, 1, 1, file);
            fwrite(&Palette[i].Reserved, 1, 1, file);
        }
        unsigned char* position = new unsigned char[256];
        for (int i = 0; i < 256; ++i)
        {
            position[i] = i;
            fwrite(&position[i], 1, 1, file);
        }
        for (int i = 0; i < BMInfoHeader.Height; ++i)
        {
            for (int j = 0; j < BMInfoHeader.Width; ++j)
            {
                fwrite(&position[Mode], 1, 1, file);
            }
        }
    }
        else if (BCount == 4)
        {
            BITMAPFILEHEADER* bitmapfileheader = new BITMAPFILEHEADER;
            bitmapfileheader->OffsetBits += 256 * 5;
            bitmapfileheader->Size = (BCount * Height * Width) + bitmapfileheader->OffsetBits;
            BMInfoHeader.ColorUsed = 256;
            Palette = new RGBQUAD[256];
            Rgbquad = new RGBQUAD[BMInfoHeader.Height * BMInfoHeader.Width];
            fwrite(&bitmapfileheader->Type, sizeof(bitmapfileheader->Type), 1, file);
            fwrite(&bitmapfileheader->Size, sizeof(bitmapfileheader->Size), 1, file);
            fwrite(&bitmapfileheader->Reserved1, sizeof(bitmapfileheader->Reserved1), 1, file);
            fwrite(&bitmapfileheader->Reserved2, sizeof(bitmapfileheader->Reserved2), 1, file);
            fwrite(&bitmapfileheader->OffsetBits, sizeof(bitmapfileheader->OffsetBits), 1, file);
            BMInfoHeader.BitCount = BCount;
            BMInfoHeader.Size = 40;
            BMInfoHeader.Width = Width;
            BMInfoHeader.Height = Height;
            BMInfoHeader.SizeImage = BCount * Width * Height;
            fwrite(&BMInfoHeader.Size, sizeof(BMInfoHeader.Size), 1, file);
            fwrite(&BMInfoHeader.Width, sizeof(BMInfoHeader.Width), 1, file);
            fwrite(&BMInfoHeader.Height, sizeof(BMInfoHeader.Height), 1, file);
            fwrite(&BMInfoHeader.Planes, sizeof(BMInfoHeader.Planes), 1, file);
            fwrite(&BMInfoHeader.BitCount, sizeof(BMInfoHeader.BitCount), 1, file);
            fwrite(&BMInfoHeader.Compression, sizeof(BMInfoHeader.Compression), 1, file);
            fwrite(&BMInfoHeader.SizeImage, sizeof(BMInfoHeader.SizeImage), 1, file);
            fwrite(&BMInfoHeader.XPelsPerMeter, sizeof(BMInfoHeader.XPelsPerMeter), 1, file);
            fwrite(&BMInfoHeader.YPelsPerMeter, sizeof(BMInfoHeader.YPelsPerMeter), 1, file);
            fwrite(&BMInfoHeader.ColorUsed, sizeof(BMInfoHeader.ColorUsed), 1, file);
            fwrite(&BMInfoHeader.ColorImportant, sizeof(BMInfoHeader.ColorImportant), 1, file);
            for (int i = 0; i < 256; ++i)
            {
                Palette[i].Red = i;
                Palette[i].Green = i;
                Palette[i].Blue = i;
                Palette[i].Reserved = 0;
                fwrite(&Palette[i].Red, 1, 1, file);
                fwrite(&Palette[i].Green, 1, 1, file);
                fwrite(&Palette[i].Blue, 1, 1, file);
                fwrite(&Palette[i].Reserved, 1, 1, file);
            }
            unsigned char* position = new unsigned char[256];
            for (int i = 0; i < 256; ++i)
            {
                position[i] = i;
                fwrite(&position[i], 1, 1, file);
            }
            for (int i = 0; i < BMInfoHeader.Height; ++i)
            {
                for (int j = 0; j < BMInfoHeader.Width; ++j)
                {
                    fwrite(&position[Mode], 1, 1, file);
                }
            }
    cout << " онструктор отработал успешно!" << endl;
}

// метод загрузки изображени€ аналогичный конструктору
int Image::loadimage(char* fileName)
{
    FILE* file;
    file = fopen(fileName, "rb");
    FILE* image;
    image = fopen("image.bmp", "r+b");
    BITMAPFILEHEADER* bitmapfileheader = new BITMAPFILEHEADER();

    if (file == NULL)
    {
        cout << "файл отсутствует!" << endl;
        return 0;
    }
    else
    {
        unsigned long size = 0;
        unsigned char bitcount = 0;
        unsigned long width = 0;
        unsigned long height = 0;
        fseek(file, 2, SEEK_SET);
        fread(&size, sizeof(size), 1, file);
        fseek(file, 28, SEEK_SET);
        fread(&bitcount, sizeof(bitcount), 1, file);
        fseek(file, 18, SEEK_SET);
        fread(&width, sizeof(width), 1, file);
        fseek(file, 22, SEEK_SET);
        fread(&height, sizeof(height), 1, file);
        BMInfoHeader.Width = width;
        BMInfoHeader.Size = 40;
        BMInfoHeader.Height = height;
        BMInfoHeader.SizeImage = 4 * BMInfoHeader.Width * height;
        bitmapfileheader->Size = (height * BMInfoHeader.Width * sizeof(RGBQUAD)) + 54;
        fwrite(&bitmapfileheader->Type, sizeof(bitmapfileheader->Type), 1, image);
        fwrite(&bitmapfileheader->Size, sizeof(bitmapfileheader->Size), 1, image);
        fwrite(&bitmapfileheader->Reserved1, sizeof(bitmapfileheader->Reserved1), 1, image);
        fwrite(&bitmapfileheader->Reserved2, sizeof(bitmapfileheader->Reserved2), 1, image);
        fwrite(&bitmapfileheader->OffsetBits, sizeof(bitmapfileheader->OffsetBits), 1, image);
        fwrite(&BMInfoHeader.Size, sizeof(BMInfoHeader.Size), 1, image);
        fwrite(&BMInfoHeader.Width, sizeof(BMInfoHeader.Width), 1, image);
        fwrite(&BMInfoHeader.Height, sizeof(BMInfoHeader.Height), 1, image);
        fwrite(&BMInfoHeader.Planes, sizeof(BMInfoHeader.Planes), 1, image);
        fwrite(&BMInfoHeader.BitCount, sizeof(BMInfoHeader.BitCount), 1, image);
        fwrite(&BMInfoHeader.Compression, sizeof(BMInfoHeader.Compression), 1, image);
        fwrite(&BMInfoHeader.SizeImage, sizeof(BMInfoHeader.SizeImage), 1, image);
        fwrite(&BMInfoHeader.XPelsPerMeter, sizeof(BMInfoHeader.XPelsPerMeter), 1, image);
        fwrite(&BMInfoHeader.YPelsPerMeter, sizeof(BMInfoHeader.YPelsPerMeter), 1, image);
        fwrite(&BMInfoHeader.ColorUsed, sizeof(BMInfoHeader.ColorUsed), 1, image);
        fwrite(&BMInfoHeader.ColorImportant, sizeof(BMInfoHeader.ColorImportant), 1, image);
        if (bitcount == 32)
        {
            Rgbquad = new RGBQUAD[BMInfoHeader.Height * BMInfoHeader.Width];
            fseek(file, 54, SEEK_SET);
            for (int i = 0; i < BMInfoHeader.Width; ++i)
            {
                for (int j = 0; i < BMInfoHeader.Height; ++j)
                {
                    fread(&Rgbquad[i * BMInfoHeader.Height + j].Red, 1, 1, file);
                    fwrite(&Rgbquad[i * BMInfoHeader.Height + j].Red, 1, 1, image);
                    fread(&Rgbquad[i * BMInfoHeader.Height + j].Green, 1, 1, file);
                    fwrite(&Rgbquad[i * BMInfoHeader.Height + j].Green, 1, 1, image);
                    fread(&Rgbquad[i * BMInfoHeader.Height + j].Blue, 1, 1, image);
                    fwrite(&Rgbquad[i * BMInfoHeader.Height + j].Blue, 1, 1, image);
                    fread(&Rgbquad[i * BMInfoHeader.Height + j].Reserved, 1, 1, file);
                    fwrite(&Rgbquad[i * BMInfoHeader.Height + j].Reserved, 1, 1, image);
                }
            }
        }
        else if (bitcount == 24)
        {
            Rgbquad = new RGBQUAD[BMInfoHeader.Height * BMInfoHeader.Width];
            size = 1;
            fseek(file, 54, SEEK_SET);
            for (int i = 0; i < BMInfoHeader.Width; ++i)
            {
                for (int j = 0; i < BMInfoHeader.Height; ++j)
                {
                    fread(&Rgbquad[i * BMInfoHeader.Height + j].Red, 1, 1, file);
                    fwrite(&Rgbquad[i * BMInfoHeader.Height + j].Red, 1, 1, image);
                    fread(&Rgbquad[i * BMInfoHeader.Height + j].Green, 1, 1, file);
                    fwrite(&Rgbquad[i * BMInfoHeader.Height + j].Green, 1, 1, image);
                    fread(&Rgbquad[i * BMInfoHeader.Height + j].Blue, 1, 1, file);
                    fwrite(&Rgbquad[i * BMInfoHeader.Height + j].Blue, 1, 1, image);
                    fwrite(&Rgbquad->Reserved, 1, 1, image);
                }
                unsigned char shift = (4 - (width * 24 / 8) % 4) % 4;
                fseek(file, shift, SEEK_CUR);
            }
        }
    }
    cout << "ћетод загрузки изображени€, аналогичный конструктору отработал успешно" << endl;
}

// метод записи изображени€ в файл
void Image::writeimage(char* fileName)
{
    loadimage(fileName);
    cout << "ћетод записи изображени€ в файл отработал успешно!" << endl;
}

Image Image::operator/=(Image InpImage)
{
    FILE* file = fopen("image.bmp", "w+b");
    BITMAPFILEHEADER* bitmapfileheader = new BITMAPFILEHEADER;
    bitmapfileheader->Size = InpImage.BMInfoHeader.Width * InpImage.BMInfoHeader.Height * BMInfoHeader.BitCount + bitmapfileheader->OffsetBits;
    BMInfoHeader.SizeImage = InpImage.BMInfoHeader.Width * InpImage.BMInfoHeader.Height * BMInfoHeader.BitCount;
    fwrite(&bitmapfileheader->Type, sizeof(bitmapfileheader->Type), 1, file);
    fwrite(&bitmapfileheader->Size, sizeof(bitmapfileheader->Size), 1, file);
    fwrite(&bitmapfileheader->Reserved1, sizeof(bitmapfileheader->Reserved1), 1, file);
    fwrite(&bitmapfileheader->Reserved2, sizeof(bitmapfileheader->Reserved2), 1, file);
    fwrite(&bitmapfileheader->OffsetBits, sizeof(bitmapfileheader->OffsetBits), 1, file);
    fwrite(&BMInfoHeader.Size, sizeof(BMInfoHeader.Size), 1, file);
    fwrite(&InpImage.BMInfoHeader.Width, sizeof(BMInfoHeader.Width), 1, file);
    fwrite(&InpImage.BMInfoHeader.Height, sizeof(BMInfoHeader.Height), 1, file);
    fwrite(&BMInfoHeader.Planes, sizeof(BMInfoHeader.Planes), 1, file);
    fwrite(&BMInfoHeader.BitCount, sizeof(BMInfoHeader.BitCount), 1, file);
    fwrite(&BMInfoHeader.Compression, sizeof(BMInfoHeader.Compression), 1, file);
    fwrite(&InpImage.BMInfoHeader.SizeImage, sizeof(BMInfoHeader.SizeImage), 1, file);
    fwrite(&BMInfoHeader.XPelsPerMeter, sizeof(BMInfoHeader.XPelsPerMeter), 1, file);
    fwrite(&BMInfoHeader.YPelsPerMeter, sizeof(BMInfoHeader.YPelsPerMeter), 1, file);
    fwrite(&BMInfoHeader.ColorUsed, sizeof(BMInfoHeader.ColorUsed), 1, file);
    fwrite(&BMInfoHeader.ColorImportant, sizeof(BMInfoHeader.ColorImportant), 1, file);
    double h = double(InpImage.BMInfoHeader.Width) / BMInfoHeader.Width - 1;
    double v = double(InpImage.BMInfoHeader.Height) / BMInfoHeader.Height - 1;
    double h1 = h;
    double v1 = v;
    fseek(file, 54, SEEK_SET);
    for (int i = 0; i < BMInfoHeader.Width; ++i)
    {
        for (int j = 0; j < BMInfoHeader.Height; ++j)
        {
            if (h >= 0)
            {
                while (h1 >= 1)
                {
                    fputc(Rgbquad[i * BMInfoHeader.Height + j].Red, file);
                    fputc(Rgbquad[i * BMInfoHeader.Height + j].Green, file);
                    fputc(Rgbquad[i * BMInfoHeader.Height + j].Blue, file);
                    fputc(Rgbquad[i * BMInfoHeader.Height + j].Reserved, file);
                    --h1;
                }
                fputc(Rgbquad[i * BMInfoHeader.Height + j].Red, file);
                fputc(Rgbquad[i * BMInfoHeader.Height + j].Green, file);
                fputc(Rgbquad[i * BMInfoHeader.Height + j].Blue, file);
                fputc(Rgbquad[i * BMInfoHeader.Height + j].Reserved, file);
                ++h1;
            }
        }

        while (v >= 1)
        {
            for (int j = 0; j < BMInfoHeader.Width; ++j)
            {
                fputc(Rgbquad[i * BMInfoHeader.Height + j].Red, file);
                fputc(Rgbquad[i * BMInfoHeader.Height + j].Green, file);
                fputc(Rgbquad[i * BMInfoHeader.Height + j].Blue, file);
                fputc(Rgbquad[i * BMInfoHeader.Height + j].Reserved, file);
            }
            --v1;
        }
        v1 += v;
    }
};

// деструктор
Image::~Image()
{
    if (Palette != NULL)
    {
        delete[] Palette;
        Palette = NULL;
    }
    delete[] Rgbquad;
    delete[] Rgbtriple;
    Rgbquad = NULL;
    Rgbtriple = NULL;
};
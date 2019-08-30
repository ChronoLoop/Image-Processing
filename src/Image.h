#pragma once
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::vector;

struct Header
{
    char idLength;
    char colorMapType;
    char  dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char  colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char  bitsPerPixel;
    char  imageDescriptor;
};

struct Pixel
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

struct Image
{
    vector<Pixel> imagePixels;
    unsigned int totalPixels;
    Image()
    {
        totalPixels = 0;
    }
    Image (const Image &rhs)
    {
        imagePixels = rhs.imagePixels;
        totalPixels = rhs.totalPixels;
    }
    Image &operator=(const Image &rhs)
    {
        if (this != &rhs)
        {
            imagePixels = rhs.imagePixels;
            totalPixels = rhs.totalPixels;
        }
        return *this;
    }

    ~Image()
    {

    }
};

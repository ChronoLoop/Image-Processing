#include "ImageProcessor.h"

void ImageProcessor::Display()
{
    cout << "ID Length: " << (int) headerData.idLength << endl;
    cout << "Color Map Type: " << (int) headerData.colorMapType << endl;
    cout << "Data type code: " << (int) headerData.dataTypeCode << endl;
    cout << "Color Map origin: " << (int) headerData.colorMapOrigin << endl;
    cout << "Color Map length: " << (int) headerData.colorMapLength << endl;
    cout << "Color Map Depth: " << (int) headerData.colorMapDepth << endl;
    cout << "X origin: " << (int) headerData.xOrigin << endl;
    cout << "Y origin: " << (int) headerData.yOrigin << endl;
    cout << "width: " << (int) headerData.width << endl;
    cout << "height: " << (int) headerData.height << endl;
    cout << "bits per pixel: " << (int) headerData.bitsPerPixel<< endl;
    cout << "Image Descriptor: " << (int) headerData.imageDescriptor<< endl;
}
Header& ImageProcessor::getHeader()
{
    return headerData;
}
void ImageProcessor::clampRGB(int &colorValue)
{
    if (colorValue > 255)
    {
        colorValue = 255;
    }
    else if (colorValue < 0)
    {
        colorValue = 0;
    }
}
Image ImageProcessor::setData(const string &filename)
{
    ifstream inFile;
    inFile.open(filename, ios::binary);
    Image myImage;
    Pixel pixelObject;
    if (inFile.is_open())
    {
        //id length, color maptype, image type//
        inFile.read(&headerData.idLength, 1);
        inFile.read(&headerData.colorMapType, 1);
        inFile.read(&headerData.dataTypeCode, 1);
        //color map specs
        inFile.read((char*) &headerData.colorMapOrigin, 2);
        inFile.read((char*) &headerData.colorMapLength, 2);
        inFile.read(&headerData.colorMapDepth, 1);
        //image specs
        inFile.read((char*) &headerData.xOrigin, 2);
        inFile.read((char*) &headerData.yOrigin, 2);
        inFile.read((char*) &headerData.width, 2);
        inFile.read((char*) &headerData.height, 2);
        inFile.read(&headerData.bitsPerPixel, 1);
        inFile.read(&headerData.imageDescriptor, 1);

        //color data
        myImage.totalPixels = (unsigned int) headerData.width * (unsigned int) headerData.height;
        if (myImage.totalPixels > totalPixels)
        {
            totalPixels = myImage.totalPixels;
        }
        for (unsigned int i = 0; i < myImage.totalPixels; i++)
        {
            inFile.read((char*) &pixelObject.blue, 1);
            inFile.read((char*) &pixelObject.green, 1);
            inFile.read((char*) &pixelObject.red, 1);
            myImage.imagePixels.push_back(pixelObject);
        }
        inFile.close();
    }
    myImages.push_back(myImage);
    numOFImages++;
   return myImage;
}

void ImageProcessor::writeData(const string &filename, Image &finalImage)
{
    ofstream outFile(filename, ios::binary);
    if (outFile.is_open())
    {
        outFile.write(&headerData.idLength, 1);
        outFile.write(&headerData.colorMapType, 1);
        outFile.write(&headerData.dataTypeCode, 1);
        //color map specs
        outFile.write((char*) &headerData.colorMapOrigin, 2);
        outFile.write((char*) &headerData.colorMapLength, 2);
        outFile.write(&headerData.colorMapDepth, 1);
        //image specs
        outFile.write((char*) &headerData.xOrigin, 2);
        outFile.write((char*) &headerData.yOrigin, 2);
        outFile.write((char*) &headerData.width, 2);
        outFile.write((char*) &headerData.height, 2);
        outFile.write(&headerData.bitsPerPixel, 1);
        outFile.write(&headerData.imageDescriptor, 1);
        for (unsigned int i=0; i < totalPixels; i++)
        {
            outFile.write((char*) &finalImage.imagePixels[i].blue, 1);
            outFile.write((char*) &finalImage.imagePixels[i].green, 1);
            outFile.write((char*) &finalImage.imagePixels[i].red, 1);
        }
        outFile.close();
    }
}

ImageProcessor::ImageProcessor()
{
    totalPixels = 0;
    numOFImages = 0;
}
ImageProcessor::ImageProcessor(const ImageProcessor &rhs)
{
    headerData = rhs.headerData;
    myImages = rhs.myImages;
    numOFImages = rhs.numOFImages;
    totalPixels = rhs.totalPixels;
}
ImageProcessor& ImageProcessor::operator=(const ImageProcessor &rhs)
{
    if (this != &rhs)
    {
        headerData = rhs.headerData;
        myImages = rhs.myImages;
        numOFImages = rhs.numOFImages;
        totalPixels = rhs.totalPixels;
    }
    return *this;
}
ImageProcessor::~ImageProcessor()
{

}

///////////////Image Manipulation////////////////
Image ImageProcessor::multiplyImages(const Image &firstImage, const Image &secondImage)
{
    float tempBlue = 0;
    float tempGreen = 0;
    float tempRed = 0;
    Pixel tempPixel;
    Image tempImage;

    for (unsigned int i = 0; i < totalPixels; i++)
    {
        tempBlue = calculateMultiplication((float)firstImage.imagePixels[i].blue, (float)secondImage.imagePixels[i].blue);
        tempGreen = calculateMultiplication((float)firstImage.imagePixels[i].green, (float)secondImage.imagePixels[i].green);
        tempRed = calculateMultiplication((float)firstImage.imagePixels[i].red, (float)secondImage.imagePixels[i].red);

        tempPixel.blue = (unsigned char) tempBlue;
        tempPixel.green = (unsigned char) tempGreen;
        tempPixel.red = (unsigned char) tempRed;
        tempImage.imagePixels.push_back(tempPixel);
    }
    tempImage.totalPixels = totalPixels;
    return tempImage;
}

Image ImageProcessor::subtractImages(const Image &topImage, const Image &bottomImage)
{
    int tempBlue = 0;
    int tempGreen = 0;
    int tempRed = 0;
    Pixel tempPixel;
    Image tempImage;

    for (unsigned int i = 0; i < totalPixels; i++)
    {

        tempBlue =  calculateSubtract((int) topImage.imagePixels[i].blue,(int) bottomImage.imagePixels[i].blue);
        tempGreen = calculateSubtract((int) topImage.imagePixels[i].green,(int) bottomImage.imagePixels[i].green);
        tempRed = calculateSubtract((int) topImage.imagePixels[i].red,(int) bottomImage.imagePixels[i].red);

        clampRGB(tempBlue);
        clampRGB(tempGreen);
        clampRGB(tempRed);

        tempPixel.blue = (unsigned char) tempBlue;
        tempPixel.green = (unsigned char) tempGreen;
        tempPixel.red = (unsigned char) tempRed;
        tempImage.imagePixels.push_back(tempPixel);
    }
    tempImage.totalPixels = totalPixels;
    return tempImage;
}

Image ImageProcessor::screenImages(const Image &firstImage, const Image &secondImage)
{
    float tempBlue = 0;
    float tempGreen = 0;
    float tempRed = 0;
    Pixel tempPixel;
    Image tempImage;

    for (unsigned int i = 0; i < totalPixels; i++)
    {
        tempBlue = calculateScreen((float)firstImage.imagePixels[i].blue, (float) secondImage.imagePixels[i].blue);
        tempGreen = calculateScreen((float)firstImage.imagePixels[i].green, (float) secondImage.imagePixels[i].green);
        tempRed = calculateScreen((float)firstImage.imagePixels[i].red, (float) secondImage.imagePixels[i].red);

        tempPixel.blue = (unsigned char) tempBlue;
        tempPixel.green = (unsigned char) tempGreen;
        tempPixel.red = (unsigned char) tempRed;
        tempImage.imagePixels.push_back(tempPixel);
    }
    tempImage.totalPixels = firstImage.totalPixels;
    return tempImage;
}

Image ImageProcessor::overlayImages(const Image &topImage, const Image &bottomImage)
{
    float tempBlue = 0;
    float tempGreen = 0;
    float tempRed = 0;
    Pixel tempPixel;
    Image tempImage;

    for (unsigned int i = 0; i < totalPixels; i++)
    {
        tempBlue = calculateOverlay((float) topImage.imagePixels[i].blue, (float) bottomImage.imagePixels[i].blue);
        tempGreen = calculateOverlay((float) topImage.imagePixels[i].green, (float) bottomImage.imagePixels[i].green);
        tempRed = calculateOverlay((float) topImage.imagePixels[i].red, (float) bottomImage.imagePixels[i].red);

        tempPixel.blue = (unsigned char) tempBlue;
        tempPixel.green = (unsigned char) tempGreen;
        tempPixel.red = (unsigned char) tempRed;
        tempImage.imagePixels.push_back(tempPixel);
    }
    tempImage.totalPixels = bottomImage.totalPixels;
    return tempImage;
}

Image ImageProcessor::addGreenChannel(const Image &myImage)
{
    int tempBlue = 0;
    int tempGreen = 0;
    int tempRed = 0;
    Pixel tempPixel;
    Image tempImage;
    for (unsigned int i = 0; i < totalPixels; i++)
    {
        tempBlue = (int) myImage.imagePixels[i].blue;
        tempGreen = (int) myImage.imagePixels[i].green + 200;
        tempRed = (int) myImage.imagePixels[i].red;
        clampRGB(tempGreen);
        tempPixel.blue = (unsigned char) tempBlue;
        tempPixel.green = (unsigned char) tempGreen;
        tempPixel.red = (unsigned char) tempRed;
        tempImage.imagePixels.push_back(tempPixel);
    }
    tempImage.totalPixels = myImage.totalPixels;
    return tempImage;
}

Image ImageProcessor::scaleRedBlue(const Image &myImage)
{
    int tempBlue = 0;
    int tempGreen = 0;
    int tempRed = 0;
    Pixel tempPixel;
    Image tempImage;
    for (unsigned int i = 0; i < totalPixels; i++)
    {
        tempBlue = (int) myImage.imagePixels[i].blue * 0;
        tempGreen = (int) myImage.imagePixels[i].green;
        tempRed = (int) myImage.imagePixels[i].red * 4;
        clampRGB(tempRed);
        clampRGB(tempBlue);
        tempPixel.blue = (unsigned char) tempBlue;
        tempPixel.green = (unsigned char) tempGreen;
        tempPixel.red = (unsigned char) tempRed;
        tempImage.imagePixels.push_back(tempPixel);
    }
    tempImage.totalPixels = myImage.totalPixels;
    return tempImage;
}
Image ImageProcessor::redChannel(const Image &myImage)
{
    int tempBlue = 0;
    int tempGreen = 0;
    int tempRed = 0;
    Pixel tempPixel;
    Image tempImage;
    for (unsigned int i = 0; i < totalPixels; i++)
    {
        tempBlue = (int) myImage.imagePixels[i].red;
        tempGreen = (int) myImage.imagePixels[i].red;
        tempRed = (int) myImage.imagePixels[i].red;

        tempPixel.blue = (unsigned char) tempBlue;
        tempPixel.green = (unsigned char) tempGreen;
        tempPixel.red = (unsigned char) tempRed;
        tempImage.imagePixels.push_back(tempPixel);
    }
    tempImage.totalPixels = myImage.totalPixels;
    return tempImage;
}

Image ImageProcessor::blueChannel(const Image &myImage)
{
    int tempBlue = 0;
    int tempGreen = 0;
    int tempRed = 0;
    Pixel tempPixel;
    Image tempImage;
    for (unsigned int i = 0; i < totalPixels; i++)
    {
        tempBlue = (int) myImage.imagePixels[i].blue;
        tempGreen = (int) myImage.imagePixels[i].blue;
        tempRed = (int) myImage.imagePixels[i].blue;

        tempPixel.blue = (unsigned char) tempBlue;
        tempPixel.green = (unsigned char) tempGreen;
        tempPixel.red = (unsigned char) tempRed;
        tempImage.imagePixels.push_back(tempPixel);
    }
    tempImage.totalPixels = myImage.totalPixels;
    return tempImage;
}
Image ImageProcessor::greenChannel(const Image &myImage)
{
    int tempBlue = 0;
    int tempGreen = 0;
    int tempRed = 0;
    Pixel tempPixel;
    Image tempImage;
    for (unsigned int i = 0; i < totalPixels; i++)
    {
        tempBlue = (int) myImage.imagePixels[i].green;
        tempGreen = (int) myImage.imagePixels[i].green;
        tempRed = (int) myImage.imagePixels[i].green;

        tempPixel.blue = (unsigned char) tempBlue;
        tempPixel.green = (unsigned char) tempGreen;
        tempPixel.red = (unsigned char) tempRed;
        tempImage.imagePixels.push_back(tempPixel);
    }
    tempImage.totalPixels = myImage.totalPixels;
    return tempImage;
}

Image ImageProcessor::combineThreeLayers(const Image &blueLayer, const Image &greenLayer, const Image &redLayer)
{
    int tempBlue = 0;
    int tempGreen = 0;
    int tempRed = 0;
    Pixel tempPixel;
    Image tempImage;
    for (unsigned int i = 0; i < totalPixels; i++)
    {
        tempBlue = (int) blueLayer.imagePixels[i].blue;
        tempGreen = (int) greenLayer.imagePixels[i].green;
        tempRed = (int) redLayer.imagePixels[i].red;
        tempPixel.blue = (unsigned char) tempBlue;
        tempPixel.green = (unsigned char) tempGreen;
        tempPixel.red = (unsigned char) tempRed;
        tempImage.imagePixels.push_back(tempPixel);
    }
    tempImage.totalPixels = blueLayer.totalPixels;
    return tempImage;
}

Image ImageProcessor::rotateImage(const Image &myImage)
{   int tempBlue = 0;
    int tempGreen = 0;
    int tempRed = 0;
    Pixel tempPixel;
    Image tempImage;

    for (int i = totalPixels-1;  i>=0; i--)
    {
        tempBlue = (int) myImage.imagePixels[i].blue;
        tempGreen = (int) myImage.imagePixels[i].green;
        tempRed = (int) myImage.imagePixels[i].red;
        tempPixel.blue = (unsigned char) tempBlue;
        tempPixel.green = (unsigned char) tempGreen;
        tempPixel.red = (unsigned char) tempRed;
        tempImage.imagePixels.push_back(tempPixel);
    }
    tempImage.totalPixels = myImage.totalPixels;
    return tempImage;
}
//////////////calculations///////////
float ImageProcessor::calculateMultiplication(const float &firstRGB, const float &secondRGB)
{
    float temp = 0;
    temp = (firstRGB * secondRGB/255.0f) + 0.5f;
    return temp;
}
int ImageProcessor::calculateSubtract(const int &topRGB, const int &bottomRGB)
{
    int temp = 0;
    temp = (int) bottomRGB - (int) topRGB;
    return temp;
}
float ImageProcessor::calculateScreen(const float &firstRGB, const float &secondRGB)
{
    return ((1.0f - ((1.0f - (firstRGB/255.0f)) * (1.0f - (secondRGB/255.0f))))*255.0f) + 0.5f;
}
float ImageProcessor::calculateOverlay(const float &topRGB, const float &bottomRGB)
{
    float temp = 0.0f;
    if (bottomRGB/255.0f <= 0.5)
    {
        temp = ((2.0f * bottomRGB * topRGB)/255) + 0.5f;
    }
    else if (bottomRGB/255.0f > 0.5)
    {
        temp = ((1.0f - (2.0f * ((1-(bottomRGB/255.0f))) * ((1- topRGB/255.0f)))) * 255.0f)+0.5f;
    }
    return temp;
}
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::vector;

class ImageProcessor {
public:

    ImageProcessor();
    ImageProcessor (const ImageProcessor &rhs);
    ImageProcessor &operator=(const ImageProcessor &rhs);
    ~ImageProcessor();
    //functions//
    void Display();
    Image setData(const string &filename); //sets the header and the pixel data then pushes header
    void writeData(const string &filename, Image &finalImage);

    // image manipulation//
    Image multiplyImages(const Image &firstImage, const Image &secondImage);
    Image subtractImages(const Image &topImage, const Image &bottomImage);
    Image screenImages(const Image &firstImage, const Image &secondImage);
    Image overlayImages(const Image &topImage, const Image &bottomImage);

    Image addGreenChannel(const Image &myImage);
    Image redChannel(const Image &myImage);
    Image greenChannel(const Image &myImage);
    Image blueChannel(const Image &myImage);
    Image scaleRedBlue (const Image &myImage);
    Image combineThreeLayers(const Image &blueLayer, const Image &greenLayer, const Image &redLayer);
    Image rotateImage (const Image &myImage);

    //pixel manipulation//
    void clampRGB(int &colorValue);

    //accessor//
    Header& getHeader();

    //calculations///
    int calculateSubtract(const int &topRGB, const int &bottomRGB);
    float calculateMultiplication(const float &firstRGB, const float &secondRGB);
    float calculateScreen(const float &firstRGB, const float &secondRGB);
    float calculateOverlay(const float &topRGB, const float &bottomRGB);

private:
    vector<Image> myImages;
    unsigned int numOFImages;
    Header headerData;
    unsigned int totalPixels;

};



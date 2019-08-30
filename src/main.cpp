#include "ImageProcessor.h"

void setHeaderVector(ifstream &file, vector<unsigned int> &headerVector);
bool compareImage(const string &exampleFile, const string &outputFile, const unsigned int &totalPixels, int &totalCompletedTests);

int main()
{
    int totalCompletedTests = 1;
    int testIndex = 1;
    int numOfPasses = 0;

    while (testIndex != 12)
    {
        bool passedTest = false;
        bool passedRed = false; //for if statement at test 8
        bool passedGreen = false; //for if statement at test 8
        Image tempImageOne;
        Image tempImageTwo;
        Image tempImageThree;
        ImageProcessor binaryFile;
        if (testIndex == 1)
        {
            Image layer1 = binaryFile.setData("input/layer1.tga");
            Image pattern1 = binaryFile.setData("input/pattern1.tga");
            tempImageOne = binaryFile.multiplyImages(layer1, pattern1);
            binaryFile.writeData("output/part1.tga", tempImageOne);
            passedTest = compareImage("examples/EXAMPLE_part1.tga", "output/part1.tga",tempImageOne.totalPixels, totalCompletedTests);
        }
        else if (testIndex == 2)
        {
            Image car = binaryFile.setData("input/car.tga"); //car is bottom
            Image layer2 = binaryFile.setData("input/layer2.tga"); //layer 2 is top
            tempImageOne = binaryFile.subtractImages(layer2 , car);
            binaryFile.writeData("output/part2.tga", tempImageOne);
            passedTest = compareImage("examples/EXAMPLE_part2.tga","output/part2.tga" ,tempImageOne.totalPixels, totalCompletedTests);
        }
        else if (testIndex == 3)
        {
            Image layer1 = binaryFile.setData("input/layer1.tga");
            Image pattern2 = binaryFile.setData("input/pattern2.tga");
            tempImageOne = binaryFile.multiplyImages(layer1, pattern2);
            Image text = binaryFile.setData("input/text.tga");
            tempImageTwo = binaryFile.screenImages(tempImageOne, text);
            binaryFile.writeData("output/part3.tga", tempImageTwo);
            passedTest = compareImage("examples/EXAMPLE_part3.tga","output/part3.tga" ,tempImageOne.totalPixels, totalCompletedTests);
        }
        else if (testIndex == 4)
        {
            Image layer2 = binaryFile.setData("input/layer2.tga");
            Image circles = binaryFile.setData("input/circles.tga");
            tempImageOne = binaryFile.multiplyImages(circles, layer2);
            Image pattern2 = binaryFile.setData("input/pattern2.tga"); //top
            tempImageTwo = binaryFile.subtractImages(pattern2, tempImageOne);
            binaryFile.writeData("output/part4.tga", tempImageTwo);
            passedTest = compareImage("examples/EXAMPLE_part4.tga","output/part4.tga" ,tempImageTwo.totalPixels, totalCompletedTests);
        }
        else if (testIndex == 5)
        {
            Image layer1 = binaryFile.setData("input/layer1.tga"); //top layer
            Image pattern1 = binaryFile.setData("input/pattern1.tga"); //bottom layer
            tempImageOne = binaryFile.overlayImages(layer1,pattern1);
            binaryFile.writeData("output/part5.tga", tempImageOne);
            passedTest = compareImage("examples/EXAMPLE_part5.tga","output/part5.tga" ,tempImageOne.totalPixels, totalCompletedTests);
        }
        else if (testIndex == 6)
        {
            Image car = binaryFile.setData("input/car.tga"); //car is bottom
            tempImageOne = binaryFile.addGreenChannel(car);
            binaryFile.writeData("output/part6.tga",tempImageOne);
            passedTest = compareImage("examples/EXAMPLE_part6.tga","output/part6.tga" ,tempImageOne.totalPixels, totalCompletedTests);
        }
        else if (testIndex == 7)
        {
            Image car = binaryFile.setData("input/car.tga");
            tempImageOne = binaryFile.scaleRedBlue(car);
            binaryFile.writeData("output/part7.tga",tempImageOne);
            passedTest = compareImage("examples/EXAMPLE_part7.tga","output/part7.tga" ,tempImageOne.totalPixels, totalCompletedTests);
        }
        else if (testIndex == 8)
        {
            Image car = binaryFile.setData("input/car.tga");
            //red channel//
            tempImageOne = binaryFile.redChannel(car);
            binaryFile.writeData("output/part8_r.tga",tempImageOne);
            passedRed = compareImage("examples/EXAMPLE_part8_r.tga","output/part8_r.tga" ,tempImageOne.totalPixels, totalCompletedTests);
            //green channel//
            tempImageTwo = binaryFile.greenChannel(car);
            binaryFile.writeData("output/part8_g.tga",tempImageTwo);
            passedGreen = compareImage("examples/EXAMPLE_part8_g.tga","output/part8_g.tga" ,tempImageOne.totalPixels, totalCompletedTests);
           //blue channel//
            tempImageThree = binaryFile.blueChannel(car);
            binaryFile.writeData("output/part8_b.tga",tempImageThree);
            passedTest = compareImage("examples/EXAMPLE_part8_b.tga","output/part8_b.tga" ,tempImageThree.totalPixels, totalCompletedTests); //the next if check for passTest
        }
        else if (testIndex == 9)
        {
            Image layer_blue = binaryFile.setData("input/layer_blue.tga");
            Image layer_green = binaryFile.setData("input/layer_green.tga");
            Image layer_red = binaryFile.setData("input/layer_red.tga");
            tempImageOne = binaryFile.combineThreeLayers(layer_blue,layer_green,layer_red);
            binaryFile.writeData("output/part9.tga",tempImageOne);
            passedTest = compareImage("examples/EXAMPLE_part9.tga","output/part9.tga", tempImageOne.totalPixels, totalCompletedTests);
        }
        else if (testIndex == 10)
        {
            Image text2 = binaryFile.setData("input/text2.tga");
            tempImageOne = binaryFile.rotateImage(text2);
            binaryFile.writeData("output/part10.tga",tempImageOne);
            passedTest = compareImage("examples/EXAMPLE_part10.tga","output/part10.tga", tempImageOne.totalPixels, totalCompletedTests);
        }
        else if (testIndex == 11) //extra credit
        {

        }

        if (passedTest)
        {
            if (testIndex == 11)
            {
                cout << "Test extra credit" << "......Passed!" << endl;
            }
            numOfPasses++;
        }
        else
        {
            if (testIndex == 11)
            {
                cout << "Test extra credit" << "......Failed!" << endl;
            }
        }
        if (passedGreen)
        {
            numOfPasses++;
        }
        if (passedRed)
        {
            numOfPasses++;
        }
        binaryFile.Display();
        cout << "" << endl;

        testIndex++;
    }

    cout << "Test results: " << numOfPasses << " / " << "13" << endl;
    if (numOfPasses < 8)
    {
        cout << "Grade: " << numOfPasses * 11 << " / " << "110" <<endl;
    }
    else
    {
        cout << "Grade: " << (numOfPasses-2) * 11 << " / " << "110" <<endl;
    }

}

void setHeaderVector(ifstream &file, vector<unsigned int> &headerVector)
{
    Header exampleTemp;
    file.read(&exampleTemp.idLength, 1);
    file.read(&exampleTemp.colorMapType, 1);
    file.read(&exampleTemp.dataTypeCode, 1);
    //color map specs
    file.read((char*) &exampleTemp.colorMapOrigin, 2);
    file.read((char*) &exampleTemp.colorMapLength, 2);
    file.read(&exampleTemp.colorMapDepth, 1);
    //image specs
    file.read((char*) &exampleTemp.xOrigin, 2);
    file.read((char*) &exampleTemp.yOrigin, 2);
    file.read((char*) &exampleTemp.width, 2);
    file.read((char*) &exampleTemp.height, 2);
    file.read(&exampleTemp.bitsPerPixel, 1);
    file.read(&exampleTemp.imageDescriptor, 1);

    headerVector.push_back((unsigned int) exampleTemp.idLength);
    headerVector.push_back((unsigned int) exampleTemp.colorMapType);
    headerVector.push_back((unsigned int) exampleTemp.dataTypeCode);
    headerVector.push_back((unsigned int) exampleTemp.colorMapOrigin);
    headerVector.push_back((unsigned int) exampleTemp.colorMapLength);
    headerVector.push_back((unsigned int) exampleTemp.colorMapDepth);
    headerVector.push_back((unsigned int) exampleTemp.xOrigin);
    headerVector.push_back((unsigned int) exampleTemp.yOrigin);
    headerVector.push_back((unsigned int) exampleTemp.width);
    headerVector.push_back((unsigned int) exampleTemp.height);
    headerVector.push_back((unsigned int) exampleTemp.bitsPerPixel);
    headerVector.push_back((unsigned int) exampleTemp.imageDescriptor);
}


bool compareImage(const string &exampleFile, const string &outputFile, const unsigned int &totalPixels, int &totalCompletedTests) //reference totalCompletedTests is incremented every time this function is called;
{
    ifstream exFile(exampleFile, ios::binary);
    ifstream outFile(outputFile, ios::binary);
    bool sameFile = true;
    if (exFile.is_open() && outFile.is_open())
    {
        /////header comparison////
        bool sameHeader = true;
        vector<unsigned int> exampleTemp;
        vector<unsigned int> outputTemp;
        setHeaderVector(exFile, exampleTemp);
        setHeaderVector(outFile, outputTemp);
        for (unsigned int i = 0; i < 12; i++)
        {
            if (exampleTemp[i] != outputTemp[i])
            {
                sameHeader = false;
            }
        }

        //////////image comparison///////
        Pixel examplePixel;
        Pixel outputPixel;
        bool sameImage = true;
        for (unsigned int i = 0; i < totalPixels; i++)
        {
            /////storing pixels from example image///
            exFile.read((char*) &examplePixel.blue, 1);
            exFile.read((char*) &examplePixel.green, 1);
            exFile.read((char*) &examplePixel.red, 1);
            ////storing pixels from output file image///
            outFile.read((char*) &outputPixel.blue, 1);
            outFile.read((char*) &outputPixel.green, 1);
            outFile.read((char*) &outputPixel.red, 1);
            if ((unsigned int) examplePixel.blue != (unsigned int) outputPixel.blue || (unsigned int) examplePixel.green != (unsigned int) outputPixel.green || (unsigned int) examplePixel.red != (unsigned int) outputPixel.red)
            {
                cout << "Bad pixel at index: " << i << endl;
                sameImage = false;
            }
        }
        if (!sameImage || !sameHeader)
        {
            sameFile = false;
            cout << "Test #" << totalCompletedTests << "......Failed!" << endl;
        }
        else
        {
            cout << "Test #" << totalCompletedTests << "......Passed!" << endl;
        }


        exFile.close();
        outFile.close();
    }
    totalCompletedTests++;
    return sameFile;
}
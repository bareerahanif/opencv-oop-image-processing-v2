#include <opencv2/opencv.hpp>
#include <iostream>

//COLOURED!!!!!!!!!!!
//raw image 
int main1()  //raw image
{
    // Load the image
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png");

    // Get image dimensions
    int rows = image.rows;
    int cols = image.cols;

    ////////////3D DYNAMIC ARRAY TO HOLD THE IMAGE DATA////////////////
    int*** coloredImageArr = new int** [rows];
    for (int i = 0; i < rows; ++i) {
        coloredImageArr[i] = new int* [cols];
        for (int j = 0; j < cols; ++j) {
            coloredImageArr[i][j] = new int[3]; // Assuming 3 channels (BGR)
        }
    }

    // Copy pixel values from the image to the dynamic array
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cv::Vec3b pixelValues = image.at<cv::Vec3b>(i, j);
            coloredImageArr[i][j][0] = static_cast<int>(pixelValues[0]); // Blue Channel
            coloredImageArr[i][j][1] = static_cast<int>(pixelValues[1]); // Green Channel
            coloredImageArr[i][j][2] = static_cast<int>(pixelValues[2]); // Red Channel
        }
    }

    //Decrease the value of green channel
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (coloredImageArr[i][j][1] > 50)
                coloredImageArr[i][j][1] -= 50;
        }
    }

    // Create a cv::Mat to store the processed image
    cv::Mat processed_image(rows, cols, CV_8UC3);

    // Copy pixel values from the dynamic array to the cv::Mat
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cv::Vec3b& pixelValues = processed_image.at<cv::Vec3b>(i, j);
            pixelValues[0] = static_cast<uchar>(coloredImageArr[i][j][0]); // Blue
            pixelValues[1] = static_cast<uchar>(coloredImageArr[i][j][1]); // Green
            pixelValues[2] = static_cast<uchar>(coloredImageArr[i][j][2]); // Red
        }
    }

    // Don't forget to release the allocated memory
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            delete[] coloredImageArr[i][j];
        }
        delete[] coloredImageArr[i];
    }
    delete[] coloredImageArr;

    cv::imshow("Original Image", image);
    cv::imshow("Processed Image", processed_image);

    cv::waitKey(0);
    return 0;
}
//problem 2 - inc/dec colours
int main2()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png");

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    int rows = image.rows;
    int cols = image.cols;

    int** coloredImageArr = new int* [rows * cols];
    for (int i = 0; i < rows * cols; ++i) 
    {
        coloredImageArr[i] = new int[3];
    }

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            cv::Vec3b pixelValues = image.at<cv::Vec3b>(i, j);
            int index = i * cols + j;
            coloredImageArr[index][0] = static_cast<int>(pixelValues[0]); // Blue 
            coloredImageArr[index][1] = static_cast<int>(pixelValues[1]); // Green 
            coloredImageArr[index][2] = static_cast<int>(pixelValues[2]); // Red 
        }
    }

    int changered, changegreen, changeblue;

    std::cout << "Do you want to increase or decrease the red color? (Enter '1' for increase, '-1' for decrease, '0' for no change): ";
    int choice;
    std::cin >> choice;
    if (choice == 1)
    {
        std::cout << "Enter value to increase red color: ";
        std::cin >> changered;
    }
    else if (choice == -1)
    {
        std::cout << "Enter value to decrease red color: ";
        std::cin >> changered;
        changered = -changered;
    }
    else
    {
        changered = 0;
    }

    std::cout << "Do you want to increase or decrease the green color? (Enter '1' for increase, '-1' for decrease, '0' for no change): ";
    std::cin >> choice;
    if (choice == 1)
    {
        std::cout << "Enter value to increase green color: ";
        std::cin >> changegreen;
    }
    else if (choice == -1)
    {
        std::cout << "Enter value to decrease green color: ";
        std::cin >> changegreen;
        changegreen = -changegreen;
    }
    else {
        changegreen = 0;
    }

    std::cout << "Do you want to increase or decrease the blue color? (Enter '1' for increase, '-1' for decrease, '0' for no change): ";
    std::cin >> choice;
    if (choice == 1)
    {
        std::cout << "Enter value to increase blue color: ";
        std::cin >> changeblue;
    }
    else if (choice == -1)
    {
        std::cout << "Enter value to decrease blue color: ";
        std::cin >> changeblue;
        changeblue = -changeblue;
    }
    else
    {
        changeblue = 0;
    }

    for (int i = 0; i < rows * cols; ++i)
    {
        coloredImageArr[i][0] += changeblue;
        coloredImageArr[i][1] -= changegreen;
        coloredImageArr[i][2] += changered;
    }

    cv::Mat processed_image(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            cv::Vec3b& pixelValues = processed_image.at<cv::Vec3b>(i, j);
            int index = i * cols + j;
            pixelValues[0] = static_cast<uchar>(coloredImageArr[index][0]); // Blue
            pixelValues[1] = static_cast<uchar>(coloredImageArr[index][1]); // Green
            pixelValues[2] = static_cast<uchar>(coloredImageArr[index][2]); // Red
        }
    }

    for (int i = 0; i < rows * cols; ++i) 
    {
        delete[] coloredImageArr[i];
    }
    delete[] coloredImageArr;

    cv::imshow("Original Image", image);
    cv::imshow("Processed Image", processed_image);

    cv::waitKey(0);
    return 0;
}
//problem 3 - cropping
void cropImage(cv::Mat& image, int cropH, int cropW) 
{
    int rows = image.rows;
    int cols = image.cols;

    if (cropH <= 0 || cropW <= 0 || cropH > rows || cropW > cols) 
    {
        std::cerr << "Invalid crop dimensions." << std::endl;
        return;
    }

    int startRow = (rows - cropH) / 2;
    int startCol = (cols - cropW) / 2;

    image = image(cv::Rect(startCol, startRow, cropW, cropH));
}
int main3()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png");

    if (image.empty()) 
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    int cropHeight, cropWidth;
    std::cout << "Enter the height for cropping: ";
    std::cin >> cropHeight;
    std::cout << "Enter the width for cropping: ";
    std::cin >> cropWidth;

    cropImage(image, cropHeight, cropWidth);

    cv::imshow("Cropped Image", image);

    cv::waitKey(0);
    return 0;
}
//problem 4 - rotation
void rotateImage(cv::Mat& image, int dor) 
{
    if (dor != 90 && dor != 180 && dor != 270) 
    {
        std::cerr << "Invalid rotation degree. Valid options are 90, 180, or 270." << std::endl;
        return;
    }

    cv::Mat rotimg;
    int rows = image.rows;
    int cols = image.cols;

    if (dor == 90) 
    {
        rotimg.create(cols, rows, image.type());
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                rotimg.at<cv::Vec3b>(j, rows - 1 - i) = image.at<cv::Vec3b>(i, j);
            }
        }
    }
    else if (dor == 180) 
    {
        rotimg.create(rows, cols, image.type());
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j) 
            {
                rotimg.at<cv::Vec3b>(rows - 1 - i, cols - 1 - j) = image.at<cv::Vec3b>(i, j);
            }
        }
    }
    else if (dor == 270) 
    {
        rotimg.create(cols, rows, image.type());
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j) 
            {
                rotimg.at<cv::Vec3b>(cols - 1 - j, i) = image.at<cv::Vec3b>(i, j);
            }
        }
    }

    image = rotimg;
}
int main4() 
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png");

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    int degreeofrot;
    std::cout << "Enter the degree of rotation (90, 180, or 270): ";
    std::cin >> degreeofrot;

    rotateImage(image, degreeofrot);

    cv::imshow("Rotated Image", image);

    cv::waitKey(0);
    return 0;
}
//problem 5 - channel specific
void quantizeChannels(cv::Mat& image, int blueLevel, int greenLevel, int redLevel)
{
    if (blueLevel <= 0 || greenLevel <= 0 || redLevel <= 0) 
    {
        std::cerr << "Invalid level. Level must be greater than 0." << std::endl;
        return;
    }

    blueLevel = std::min(blueLevel, 128);
    greenLevel = std::min(greenLevel, 128);
    redLevel = std::min(redLevel, 128);

    for (int i = 0; i < image.rows; i++) 
    {
        for (int j = 0; j < image.cols; j++)
        {
            cv::Vec3b& pixelValues = image.at<cv::Vec3b>(i, j);
            pixelValues[0] = static_cast<uchar>(blueLevel);  // Blue
            pixelValues[1] = static_cast<uchar>(greenLevel); // Green
            pixelValues[2] = static_cast<uchar>(redLevel);   // Red
        }
    }
}
int main5() 
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png");

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    int blueLevel, greenLevel, redLevel;
    std::cout << "Enter the level for Blue channel (2/4/8/16/32/64/128): ";
    std::cin >> blueLevel;

    std::cout << "Enter the level for Green channel (2/4/8/16/32/64/128): ";
    std::cin >> greenLevel;

    std::cout << "Enter the level for Red channel (2/4/8/16/32/64/128): ";
    std::cin >> redLevel;

    quantizeChannels(image, blueLevel, greenLevel, redLevel);

    cv::imshow("Quantized Image", image);

    cv::waitKey(0);
    return 0;
}

//GRAYSCALE!!!!!!
//raw grayscale image
int main6()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png", cv::IMREAD_GRAYSCALE);

    int rows = image.rows;
    int cols = image.cols;

    int** imageArr = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        imageArr[i] = new int[cols];
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            imageArr[i][j] = static_cast<int>(image.at<uchar>(i, j));
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (imageArr[i][j] > 50)
                imageArr[i][j] -= 50;
        }
    }

    for (int i = 0; i < rows; ++i) {
        delete[] imageArr[i];
    }
    delete[] imageArr;

    cv::imshow("Grayscale Image", image);

    cv::waitKey(0);
    return 0;
}
//inc dec
void processGrayscaleImage(cv::Mat& image, int intensityChange)
{
    int rows = image.rows;
    int cols = image.cols;

    int** grayarr = new int* [rows * cols];
    for (int i = 0; i < rows * cols; ++i)
    {
        grayarr[i] = new int;
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            uchar pixelValue = image.at<uchar>(i, j);
            int index = i * cols + j;
            grayarr[index][0] = static_cast<int>(pixelValue);
        }
    }

    std::cout << "Do you want to increase or decrease the intensity? (Enter '1' for increase, '-1' for decrease, '0' for no change): ";
    int choice;
    std::cin >> choice;

    if (choice == 1)
    {
        std::cout << "Enter value to increase intensity: ";
    }
    else if (choice == -1)
    {
        std::cout << "Enter value to decrease intensity: ";
    }
    else
    {
        intensityChange = 0; 
    }

    std::cin >> intensityChange;

    for (int i = 0; i < rows * cols; ++i)
    {
        grayarr[i][0] += choice * intensityChange;
        grayarr[i][0] = std::max(0, std::min(255, grayarr[i][0])); 
    }

    cv::Mat processedImage(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            uchar& pixelValue = processedImage.at<uchar>(i, j);
            int index = i * cols + j;
            pixelValue = static_cast<uchar>(grayarr[index][0]);
        }
    }

    for (int i = 0; i < rows * cols; ++i)
    {
        delete[] grayarr[i];
    }
    delete[] grayarr;

    cv::imshow("Original Image", image);
    cv::imshow("Processed Image", processedImage);

    cv::waitKey(0);
}
int main7()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png", cv::IMREAD_GRAYSCALE);

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    int intch = 0; 
    processGrayscaleImage(image, intch);

    return 0;
}
//cropping
void cropImage1(cv::Mat& image, int cropH, int cropW)
{
    int rows = image.rows;
    int cols = image.cols;

    if (cropH <= 0 || cropW <= 0 || cropH > rows || cropW > cols)
    {
        std::cerr << "Invalid crop dimensions." << std::endl;
        return;
    }

    int startRow = (rows - cropH) / 2;
    int startCol = (cols - cropW) / 2;

    image = image(cv::Rect(startCol, startRow, cropW, cropH));
}
int main8()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png", cv::IMREAD_GRAYSCALE);

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    int cropHeight, cropWidth;
    std::cout << "Enter the height for cropping: ";
    std::cin >> cropHeight;
    std::cout << "Enter the width for cropping: ";
    std::cin >> cropWidth;

    cropImage1(image, cropHeight, cropWidth);

    cv::imshow("Cropped Image", image);

    cv::waitKey(0);
    return 0;
}
//rotation
void rotateImage1(cv::Mat& image, int dor)
{
    if (dor != 90 && dor != 180 && dor != 270)
    {
        std::cerr << "Invalid rotation degree. Valid options are 90, 180, or 270." << std::endl;
        return;
    }

    cv::Mat rotimg;
    int rows = image.rows;
    int cols = image.cols;

    if (dor == 90)
    {
        rotimg.create(cols, rows, image.type());
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                rotimg.at<uchar>(j, rows - 1 - i) = image.at<uchar>(i, j);
            }
        }
    }
    else if (dor == 180)
    {
        rotimg.create(rows, cols, image.type());
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                rotimg.at<uchar>(rows - 1 - i, cols - 1 - j) = image.at<uchar>(i, j);
            }
        }
    }
    else if (dor == 270)
    {
        rotimg.create(cols, rows, image.type());
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                rotimg.at<uchar>(cols - 1 - j, i) = image.at<uchar>(i, j);
            }
        }
    }

    image = rotimg;
}
int main9()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png", cv::IMREAD_GRAYSCALE);

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    int degreeofrot;
    std::cout << "Enter the degree of rotation (90, 180, or 270): ";
    std::cin >> degreeofrot;

    rotateImage1(image, degreeofrot);

    cv::imshow("Rotated Image", image);

    cv::waitKey(0);
    return 0;
}
//specified channel
void quantizeChannels1(cv::Mat& image, int level)
{
    if (level <= 0)
    {
        std::cerr << "Invalid level. Level must be greater than 0." << std::endl;
        return;
    }

    level = std::min(level, 128);

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            uchar& pixelValue = image.at<uchar>(i, j);
            pixelValue = static_cast<uchar>(level);
        }
    }
}
int main10()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png", cv::IMREAD_GRAYSCALE);

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    int level;
    std::cout << "Enter the level for quantization (2/4/8/16/32/64/128): ";
    std::cin >> level;

    quantizeChannels1(image, level);

    cv::imshow("Quantized Image", image);

    cv::waitKey(0);
    return 0;
}



void menu()
{
    std::cout << "1. Raw - coloured" << std::endl;
    std::cout << "2. Inc/Dec - coloured" << std::endl;
    std::cout << "3. Cropping - coloured" << std::endl;
    std::cout << "4. Rotation - coloured" << std::endl;
    std::cout << "5. Channel Specific - coloured" << std::endl;
    std::cout << "6. Raw - grayscale" << std::endl;
    std::cout << "7. Inc/Dec - grayscale" << std::endl;
    std::cout << "8. Cropping - grayscale" << std::endl;
    std::cout << "9. Rotation - grayscale" << std::endl;
    std::cout << "10. Channel Specific - grayscale" << std::endl;
    std::cout << "0. Exit" << std::endl;

}
int main()
{
    int choice;
    while (true)
    {
        std::cout << "__________________________\n" << std::endl;
        menu();
        std::cout << "__________________________\n" << std::endl;
        std::cout << "Enter Choice:";
        std::cin >> choice;

        switch (choice)
        {
        case 0:
            return 0;
            break;
        case 1:
            main1();
            break;
        case 2:
            main2();
            break;
        case 3:
            main3();
            break;
        case 4:
            main4();
            break;
        case 5:
            main5();
            break;
        case 6:
            main6();
            break;
        case 7:
            main7();
            break;
        case 8:
            main8();
            break;
        case 9:
            main9();
            break;
        case 10:
            main10();
            break;
        default:
            break;
        }
    }
    return 0;
}

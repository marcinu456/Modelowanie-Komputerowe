#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "complex.h"

using namespace std;

const double PI = 3.14159265359;

// Function Prototype declaration :
double mapToReal(int x, int imageWidth, double minR, double maxR);
double mapToImaginary(int y, int imageHeight, double minI, double maxI);
Complex power(Complex c, int n);          // power of a complex number prototype declaration
Complex sum(Complex, Complex);            // operations defined on two complex numbers (sum and
Complex prod(Complex, Complex);           // product of 2 complex numbers).
int maxNumberOfIterationsMandelbrot(Complex c, int Nmax);

//main
int main()
{
    double cr; // real part of c.
    double ci; // imaginary part of c.
    Complex c; // c, is a complex numbers.
    int n;

    // get the required values from an input file called 'inputMandelbrot.txt'
    ifstream inFile;
    inFile.open("C:\\Users\\Marc\\CloudStation\\AQUATION\\STATISTICS\\C++ Code Blocks\\PROJECTS\\LEARNINGc++\\inputMandelbrot.txt");
    int imageWidth, imageHeight, maxN;
    double minReal, maxReal, minImaginary, maxImaginary;
    if (!inFile)
    {
        cout << "Could not open file. Make sure the file 'inputMandelbrot.txt' does exist." << endl;
        cin.ignore();
        return 0;
    }
    inFile >> imageWidth >> imageHeight >> maxN >> minReal >> maxReal >> minImaginary >> maxImaginary;
    inFile.close(); // close input file when the required values have been read.
    // cout << "The max number of iteration is : " << maxN << endl;

    // open the PPM output file (ppm format means 'portable pixmap format')
    // .ppm format has a header with 3 lines ended by a new line character :
    // P3 endl;
    // 3 2 endl;
    // 255 endl;
    // This header means : P3 means it is a RGB (Red Green Blue) color image in ASCII.
    // 3 2 means width and height of the image in pixels.
    // 255 is the maximum value for each color.
    // After the header, image data are triplets of integer numbers. All triplets are separated by a single space character :
    //   255 0 0 will produce a red pixel.
    //   0 255 0 will produce a green pixel, 255 255 0 is a mix of red and green which is yellow, etc...
    //   0 0 255 will produce a blue pixel.
    //   0 0 0 a black pixel and 255 255 255 a white pixel.
    // To read an image file in .ppm format you will need a special open source software like GIMP (GNU image manipulation program).
    ofstream outFile;
    outFile.open("C:\\Users\\Marc\\CloudStation\\AQUATION\\STATISTICS\\C++ Code Blocks\\PROJECTS\\LEARNINGc++\\output_image.ppm");
    outFile << "P3" << endl; // header of ppm file meaning that the pixel data are triplets of RGB color in ASCII code.
    outFile << imageWidth << " " << imageHeight << endl; // Width and Height of the image in pixels.
    outFile << "256" << endl; // maximum value of the color scale for each of the three colors.

    // For every pixel...
    for (int y = 0; y < imageHeight; y++) // for all rows...
    {
        for (int x = 0; x < imageWidth; x++) // for all pixels in the row...
        {
            // ...Find the real and imaginary values for c, corresponding to that x, y pixel in the image.
            //use mapTo functions for cr and ci and complex c *******************************************************************************
            cr = mapToReal(x, imageWidth, minReal, maxReal);
            ci = mapToImaginary(y, imageHeight, minImaginary, maxImaginary);
            c.setReal(cr);
            c.setImag(ci);

            // ...Find the number of iterations in the Mandelbrot formula using said c :
            n = maxNumberOfIterationsMandelbrot(c, maxN);

            // ...Map the resulting value to an RGB value :
            int r = ((int)(n*sinf(n))%256); //% 255;//(n*3) % 255; // change for more interesting colors...
            int g = (n * 3) % 256;//255 - (n % 255);
            int b = n % 256; //% 255;//255 - (n*2) % 255;

            // ... output it to the ppm file :
            outFile << r << " " << g << " " << b << " ";
        }
        outFile << endl;
    }

    outFile.close(); // close the created image output file
    cout << "Mandelbrot set is completed in the PPM format file.\n";
    cout << "Please open the file 'output_image.ppm' with GIMP tool." << endl;
    return 0;
}

// Function implementations :
// Map the integer pixels to real and imaginary parts of the complex plane:
double mapToReal(int x, int imageWidth, double minR, double maxR)
{
    double range = maxR - minR;
    return x * (range / imageWidth) + minR;
}
double mapToImaginary(int y, int imageHeight, double minI, double maxI)
{
    double range = maxI - minI;
    return y * (range / imageHeight) + minI;
}
// Compute the power of a complex number :
Complex power(Complex c, int n) // returns the n power of complex number c
            {
                double rho, arg, re, im;
                Complex out;
                rho = pow(c.getNorm(), n);
                arg = fmod(n*c.getTheta(), 2*PI);
                re = rho * cos(arg);
                im = rho * sin(arg);
                out.setReal(re);
                out.setImag(im);
                return out;
            }
Complex sum(Complex c1, Complex c2) // returns the sum of two complex numbers
    {
        double re, im;
        Complex out;
        re = c1.getReal() + c2.getReal();
        im = c1.getImag() + c2.getImag();
        out.setReal(re);
        out.setImag(im);
        return out;
    }

Complex prod(Complex c1, Complex c2) // returns the product of two complex numbers
    {
        double re, im;
        Complex out;
        re = c1.getReal() * c2.getReal() - c1.getImag() * c2.getImag();
        im = c1.getReal() * c2.getImag() + c1.getImag() * c2.getReal();
        out.setReal(re);
        out.setImag(im);
        return out;
    }

int maxNumberOfIterationsMandelbrot(Complex c, int Nmax) // returns the number of iterations at which z diverges
// or the max allowed number of iterations
    {
        int iter;
        Complex zNext;
        double module;
        zNext.setReal(0);
        zNext.setImag(0);
        iter = 0;
        do
        {
            zNext = sum(power(zNext, 2), c);
            module = zNext.getNorm();
            iter += 1;
        }
        while (module <= 2.0 && iter <= Nmax);
        return iter;
    }
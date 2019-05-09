#include <iostream>
using namespace std;

// By Jackie Chan
// Written on Jan 27, 2019

// Purpose: This program will approximate the enclosed or total area under 
// a curve modeled by a cubic equation (y = ax^3 + bx^2 + cx + d) using 
// the midpoints of rectangles. In addition to the a, b, c, d coefficients 
// to the cubic equation, the user can provide either the number of 
// rectangles or the known total area and a desired tolerance as input. 
// The approximate enclosed area or the minimum number of rectangles to 
// achieve the solution with the given tolerance will be printed to the 
// console.

const int APPROXIMATE_INTEGRAL_OPTION = 1;
const int EXPERIMENT_WITH_PRECISION_OPTION = 2;
const int QUIT_OPTION = 3;
const int MAX_RECTS_TO_TRY = 100;
const int MIN_RECTS_TO_TRY = 1; // begin estimation with 1 rectangle

// Displays the possible choices the user has in a menu format.
void printMenu();

double toThePower(double val, int power);

// Computes the solution to the cubic equation (ax^3 + bx^2 + cx + d),
// and stores it in resultVal. If resultVal is non-negative, logical
// true is returned while false is returned when it is negative. 
bool evaluateCubicFormula(double aCoeff, double bCoeff, double cCoeff,
                          double dCoeff, double xValue, double &resultVal);

// Computes the estimated area using the midpoints of rectangles for a
// given range (from startX to endX) and number of rectangles.
double approximateAreaWithRect(double aCoeff, double bCoeff, double cCoeff,
                               double dCoeff, double startX, double endX,
                               int numRects);

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main()
{
    int choice;
    double aCoeff;
    double bCoeff;
    double cCoeff;
    double dCoeff;
    double startX;
    double endX;
    int numRects;
    double approxArea;
    double userArea; // user provided answer to the integration
    double tolerance;
    double absoluteDiff; // |approxArea - userArea|
    bool isPrecise; // flag to check if numRects achieves desired precision
    bool isValidInput; // flag to check for bad user input

    do
    {
        printMenu();
        cout << "YOUR CHOICE: ";
        cin >> choice;

        // Checks if user has provided proper input. Reprompts user if not.
        if(choice != APPROXIMATE_INTEGRAL_OPTION &&
           choice != EXPERIMENT_WITH_PRECISION_OPTION &&
           choice != QUIT_OPTION) 
        {
            cout << "Please select a valid option (1, 2, or 3)." << endl;
        }

        // User has provided proper input and has elected not to quit.
        // Prompts user for coefficients and x start and end values.
        if(choice == APPROXIMATE_INTEGRAL_OPTION ||
           choice == EXPERIMENT_WITH_PRECISION_OPTION)
        {
            cout << "Enter (a b c d) for function "
                    "y = a*x^3 + b*x^2 + c*x + d: ";

            cin >> aCoeff >> bCoeff >> cCoeff >> dCoeff;
            cout << "Now enter x start and end values: ";
            cin >> startX >> endX;

            // Now check if endX is greater than startX.
            isValidInput = true;

            if(startX > endX)
            {
                isValidInput = false;
                cout << "The second number must be "
                        "larger than the first." << endl;
            }

            // User has provided valid input so far. In this case, user
            // has elected to go with the first option.
            if(isValidInput && choice == APPROXIMATE_INTEGRAL_OPTION)
            {
                cout << "Enter the number of rectangles to use: ";
                cin >> numRects;

                // Negative rectangles doesn't make sense. Zero
                // rectangles will cause a division by 0 issue in
                // approximateAreaWithRect functions so check that.
                if(numRects <= 0)
                {
                    cout << "Please enter a positive value." << endl;
                }
                else
                {
                    approxArea = approximateAreaWithRect(aCoeff, bCoeff,
                                                         cCoeff, dCoeff,
                                                         startX, endX,
                                                         numRects);

                    cout << "Rectangle result is: " << approxArea << endl;
                }
            }
            // User has elected to go with the second option.
            else if(isValidInput && choice == EXPERIMENT_WITH_PRECISION_OPTION)
            {
                cout << "Enter correct answer: ";
                cin >> userArea;

                // Negative area doesn't make sense. 0 area can
                // be achieved if x start and end are the same.
                if(userArea < 0)
                {
                    isValidInput = false;
                    cout << "Area is always positive." << endl;
                }
                else
                {
                    cout << "Enter precision to reach: ";
                    cin >> tolerance;

                    // Personally, I think tolerance should be positive so this
                    // checks that.
                    if(tolerance < 0)
                    {
                        isValidInput = false;
                        cout << "Precision cannot be negative." << endl;
                    }
                }

                // If both userArea and tolerance inputs are valid, proceed.
                if(isValidInput)
                {
                    numRects = MIN_RECTS_TO_TRY;
                    isPrecise = false; // precision not achieved initially

                    while(!isPrecise && numRects <= MAX_RECTS_TO_TRY)
                    {
                        approxArea = approximateAreaWithRect(aCoeff, bCoeff,
                                                             cCoeff, dCoeff,
                                                             startX, endX,
                                                             numRects);

                        absoluteDiff = approxArea - userArea;

                        // Computes the absolute value.
                        if(absoluteDiff < 0)
                        {
                            absoluteDiff = -absoluteDiff;
                        }
                        if(absoluteDiff <= tolerance)
                        {
                            isPrecise = true;
                            cout << "Rectangles needed to reach precision: "
                                 << numRects << endl;
                        }
                        if(!isPrecise && numRects == MAX_RECTS_TO_TRY)
                        {
                            cout << "Tried 100 rectangles without "
                                    "reaching precision" << endl;
                        }
                        numRects++;
                    }
                }
            }
        }
    }
    while(choice != QUIT_OPTION);
    cout << "Thanks for using this program" << endl;
    return 0;
}

#endif

void printMenu()
{
    cout << "1. Approximate Integral Using Rectangles" << endl;
    cout << "2. Experiment With Rectangle Precision" << endl;
    cout << "3. Quit The Program" << endl;
}

double toThePower(double val, int power)
{
    double result = 1; // basically val to the zero power

    for(int i = 0; i < power; i++)
    {
        result *= val;
    }
    return result;
}

bool evaluateCubicFormula(double aCoeff, double bCoeff, double cCoeff,
                          double dCoeff, double xValue, double &resultVal)
{
    resultVal = aCoeff * toThePower(xValue, 3) +
                bCoeff * toThePower(xValue, 2) +
                cCoeff * xValue +
                dCoeff;

    if(resultVal < 0)
    {
        return false;
    }
    return true;
}

double approximateAreaWithRect(double aCoeff, double bCoeff, double cCoeff,
                               double dCoeff, double startX, double endX,
                               int numRects)
{
    double rectWidth = (endX - startX) / numRects;
    double rectHeight;
    double approxArea = 0.0; // resets approxArea for consecutive function calls
    double xMidpoint;
    bool isPositive; // true if rectangle above x-axis (positive rectHeight)

    for(int i = 0; i < numRects; i++)
    {
        xMidpoint = startX + i * rectWidth + rectWidth / 2;
        isPositive = evaluateCubicFormula(aCoeff, bCoeff, cCoeff, dCoeff,
                                          xMidpoint, rectHeight);

        if(isPositive)
        {
            approxArea += rectWidth * rectHeight;
        }
        else{ // if negative, subtract to make it positive
            approxArea -= rectWidth * rectHeight;
        }
    }
    return approxArea;
}

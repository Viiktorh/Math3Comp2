#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <Eigen/Dense>
#include "LinearLeastSquares.h"
#include "QuadraticLeastSquares.h"


// Function to compute Sum of Squares with any amount of x's or y's
// Takes a vector of points(x, y) and a vector of strings. Only "x" or "y" calculates. 
double Sum_function(const std::vector<Point>& points, const std::vector<std::string> F)
{
	std::map<std::string, int> FMap{}; //Map to store and count our degrees of unknowns
	double sum = 0;
	int xPow = 0;
	int yPow = 0;
	for (int i = 0; i < F.size(); i++)
	{
		if (FMap.contains(F[i]) != true)
		{
			FMap.emplace(F[i], 1); //add the key-string and the value of 1 if it does not exist in the map
		}
		else if (FMap.contains(F[i]) == true)
		{
			FMap.at(F[i]) = FMap.at(F[i]) + 1; //Finds the key-string and adds 1 to the value of it
		}
	}
	xPow = FMap["x"];
	yPow = FMap["y"];

	for (const auto& p : points)
	{
		sum += pow(p.x, xPow) * pow(p.y, yPow);
	}
	return sum;
}


std::vector<Point> ReadPoints(std::string readFile)
{
	std::ifstream file(readFile);  // Open the file
	std::string line;

	// Check if the file opened successfully
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return { {0,0} };
	}

	std::vector<Point> compPoints;
	// Read each line from the file
	while (std::getline(file, line)) {
		std::stringstream ss(line);    // Create a stringstream from the line
		std::string x_str, y_str;

		// Split the line at the comma
		while (std::getline(ss, x_str, ',') && std::getline(ss, y_str, ',')) {
			// Convert strings to float and store them in the Point struct
			Point p;
			p.x = std::stof(x_str);  // Convert x to float
			p.y = std::stof(y_str);  // Convert y to float

			compPoints.push_back(p);      // Add the point to the vector
		}
	}
	return compPoints;
}

void findVariation(const std::vector<Point> points)
{
	std::vector<int> deviationPoint = {};
	std::vector<Point> pointsComp;
	pointsComp = ReadPoints("MixedData.csv");
	double a, b, c;

	double predictedY = 0;
	double averageY = 0;
	double totalY = 0;
	double diff = 0;
	double biggestDiff = 0;
	double SSE = 0;
	double Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;
	int currentStep = 0;
	double previousStepY = 0, currentStepY = 0;
	double currentBeta1, currentBeta0;

	
	for (const auto& p : points)
	{
		Sx += p.x;
		Sy += p.y;
		Sxx += p.x * p.x;
		Sxy += p.x * p.y;
		averageY = Sy / ++currentStep;
		

		currentBeta1 = (currentStep * Sxy - Sx * Sy) / (currentStep * Sxx - Sx * Sx);
		currentBeta0 = (Sy - currentBeta1 * Sx) / currentStep;



		/*
		* TODO: use SSE to determine variance and not a brute forced way of diff and biggestDiff.
		*/
		currentStepY = p.y;
		if (currentStep >= 1)
		{
			diff = currentStepY - previousStepY;

			if (abs(diff) > (3 * biggestDiff) && currentStep > 3)
			{
				deviationPoint.push_back(p.x-1);
				currentStep = 1;
			}
			if(abs(diff) > biggestDiff) 
				biggestDiff = abs(diff);
		}
		if (currentStep >= 0)
		{
			previousStepY = p.y;
		}
		std::cout << "Biggest difference = " << biggestDiff << " Current Difference = " << diff << std::endl;
	}
	deviationPoint.push_back(points.size()); //push back the size of the full array.
	int previousEnd = 0;
	for (int i = 0; i < deviationPoint.size(); i++)
	{
		std::cout << "deviationpoint: " << deviationPoint[i] << ", " << std::endl;

		quadraticLeastSquares(pointsComp, a, b, c, previousEnd, deviationPoint[i]);
		std::cout << "Best quadratic fit curve: y = " << a << "x^2 + " << b << "x + " << c <<
			std::endl;

		linearLeastSquares(pointsComp, a, b, previousEnd, deviationPoint[i]);
		std::cout << "Best linear fit line: y = " << b << "x + " << a << std::endl << std::endl;
		previousEnd = deviationPoint[i];
	}
}

int main()
{
	//std::vector<Point> pointsBB = { {1, 2}, {2, 2.8}, {3, 3.6}, {4, 4.5}, {5, 5.1} };
	//std::vector<Point> pointsTest = { {11,25}, {12,33}, {11,22},{15,41}, {8,18}, {10,28}, {11,32}, {12,24},{17,53}, {11,26} };
	double a, b, c;

	std::vector<Point> pointsComp;
	pointsComp = ReadPoints("MixedData.csv");
	findVariation(pointsComp);

	return 0;
}
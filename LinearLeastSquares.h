#pragma once
#include "Point.h"

// Function to compute linear least squares
void linearLeastSquares(const std::vector<Point>& points, double& Beta0, double& Beta1)
{
	int n = points.size();
	double Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;

	for (const auto& p : points)
	{
		Sx += p.x;
		Sy += p.y;
		Sxx += p.x * p.x;
		Sxy += p.x * p.y;
	}


	Beta1 = (n * Sxy - Sx * Sy) / (n * Sxx - Sx * Sx);
	Beta0 = (Sy - Beta1 * Sx) / n;
};

void linearLeastSquares(const std::vector<Point>& points, double& Beta0, double& Beta1, int startPoint, int endPoint)
{
	int n = endPoint-startPoint;
	double Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;

	for (int i = startPoint; i < endPoint; i++)
	{
		Sx += points.at(i).x;
		Sy += points.at(i).y;
		Sxx += points.at(i).x * points.at(i).x;
		Sxy += points.at(i).x * points.at(i).y;
	}


	Beta1 = (n * Sxy - Sx * Sy) / (n * Sxx - Sx * Sx);
	Beta0 = (Sy - Beta1 * Sx) / n;
};
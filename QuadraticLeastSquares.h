#pragma once
#include "Point.h"

void quadraticLeastSquares(const std::vector<Point>& points, double& a, double& b,
	double& c) {
	int n = points.size();
	double Sx = 0, Sy = 0, Sxx = 0, Sxxx = 0, Sxxxx = 0, Sxy = 0, Sxxy = 0;
	for (const auto& p : points) {
		Sx += p.x;
		Sy += p.y;
		Sxx += p.x * p.x;
		Sxxx += p.x * p.x * p.x;
		Sxxxx += p.x * p.x * p.x * p.x;
		Sxy += p.x * p.y;
		Sxxy += p.x * p.x * p.y;
	}
	// Solve using Eigen for Ax = B (Matrix Form)
	Eigen::Matrix3d A;
	Eigen::Vector3d B, X;
	A << Sxxxx, Sxxx, Sxx,
		Sxxx, Sxx, Sx,
		Sxx, Sx, n;
	B << Sxxy, Sxy, Sy;
	X = A.colPivHouseholderQr().solve(B);
	a = X(0);
	b = X(1);
	c = X(2);
}

void quadraticLeastSquares(const std::vector<Point>& points, double& a, double& b, double& c, int startPoint, int endPoint) {
	int n = endPoint-startPoint;
	double Sx = 0, Sy = 0, Sxx = 0, Sxxx = 0, Sxxxx = 0, Sxy = 0, Sxxy = 0;
	for (int i = startPoint; i < endPoint; i++) {
		Sx += points.at(i).x;
		Sy += points.at(i).y;
		Sxx += points.at(i).x * points.at(i).x;
		Sxxx += points.at(i).x * points.at(i).x * points.at(i).x;
		Sxxxx += points.at(i).x * points.at(i).x * points.at(i).x * points.at(i).x;
		Sxy += points.at(i).x * points.at(i).y;
		Sxxy += points.at(i).x * points.at(i).x * points.at(i).y;
	}
	// Solve using Eigen for Ax = B (Matrix Form)
	Eigen::Matrix3d A;
	Eigen::Vector3d B, X;
	A << Sxxxx, Sxxx, Sxx,
		Sxxx, Sxx, Sx,
		Sxx, Sx, n;
	B << Sxxy, Sxy, Sy;
	X = A.colPivHouseholderQr().solve(B);
	a = X(0);
	b = X(1);
	c = X(2);
}
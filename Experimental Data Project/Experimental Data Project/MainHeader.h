#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Point
{
	double x;
	double y;
};

vector <Point> Points;
double Mx2, Mx, My, Mxy, Mz, Mxz, Mlnx, Mlny, Mlnx2, Mlnxlny;
double aLine = 1, bLine = 0;
double aRegression, mRegression;
double aFracLine, bFracLine;
double errorLine = 0, errorRegression = 0, errorFracLine = 0;

void Input();

void Coefficients(vector<Point> Points);

void Line(double Mx, double My, double Mx2, double Mxy);
void Regression(double Mlnx, double Mlny, double Mlnx2, double Mlnxlny);
void FracLine(double Mx, double Mz, double Mx2, double Mxz);

void Calculate(double Mx, double My, double Mx2, double Mxy, double Mlnx, double Mlny, double Mlnx2, double Mlnxlny, double Mz, double Mxz);

void AccuracyLine(double aLine, double bLine, vector <Point> Points);
void AccuracyRegression(double mRegression, vector <Point> Points);
void AccuracyFracLine(double aFracLine, double bFracLine, vector <Point> Points);

void Accuracy(double aLine, double bLine, double aRegression, double mRegression, double aFracLine, double bFracLine, vector <Point> Points);

void Outpoot(double aLine, double bLine, double aRegression, double mRegression, double aFracLine, double bFracLine, double errorLine, double errorRegression, double errorFracLine);

void Input()
{
	string A;
	ifstream in("A.txt");
	if (in.is_open())
	{
		double X, Y;

		for (int i = 0; !in.eof(); i++)
		{
			in >> X >> Y;
			Points.push_back({ X, Y });
		}
	}
	in.close();
}

void Coefficients(vector <Point> Points)
{
	double sum = 0;

	for (int i = 0; i < Points.size(); i++)
		sum += Points[i].x;
	Mx = sum / Points.size();
	sum = 0;

	for (int i = 0; i < Points.size(); i++)
		sum += Points[i].y;
	My = sum / Points.size();
	sum = 0;

	for (int i = 0; i < Points.size(); i++)
		sum += Points[i].x * Points[i].y;
	Mxy = sum / Points.size();
	sum = 0;

	for (int i = 0; i < Points.size(); i++)
		sum += Points[i].x * Points[i].x;
	Mx2 = sum / Points.size();
	sum = 0;

	int count = 0; //Because in C++ doesn't exist exception like a/0

	for (int i = 0; i < Points.size(); i++)
	{
		if (Points[i].x == 0)
			count++;
		else
			sum += 1 / Points[i].y;
		if (count == Points.size())
			Mz = 0;
		else Mz = sum / (Points.size() - count);
	}
	count = 0;
	sum = 0;

	for (int i = 0; i < Points.size(); i++)
	{
		if (Points[i].x == 0)
			count++;
		else
			sum += 1 / Points[i].y * Points[i].x;
		if (count == Points.size())
			Mxz = 0;
		else Mxz = sum / (Points.size() - count);
	}
	count = 0;
	sum = 0;

	for (int i = 0; i < Points.size(); i++)
	{
		if (Points[i].x != 0)
		{
			if (Points[i].x < 0)
				sum += log(-Points[i].x);
			else
				sum += log(Points[i].x);
		}
		else
			count++;
			if (count == Points.size())
				Mlnx = 0;
			else Mlnx = sum / (Points.size() - count);
		
	}
	count = 0;
	sum = 0;

	for (int i = 0; i < Points.size(); i++)
	{
		if (Points[i].x != 0)
		{
			if (Points[i].x < 0)
				sum += log(-Points[i].x) * log(-Points[i].x);
			else
				sum += log(Points[i].x) * log(Points[i].x);
		}
		else
			count++;
		if (count == Points.size())
			Mlnx2 = 0;
		else Mlnx2 = sum / (Points.size() - count);
	}
	count = 0;
	sum = 0;

	for (int i = 0; i < Points.size(); i++)
	{
		if (Points[i].y != 0)
		{
			if (Points[i].y < 0)
				sum += log(-Points[i].y);
			else
				sum += log(Points[i].y);
		}
		else
			count++;
		if (count == Points.size())
			Mlny = 0;
		else Mlny = sum / (Points.size() - count);
	}
	count = 0;
	sum = 0;

	for (int i = 0; i < Points.size(); i++)
	{
		if (Points[i].x != 0 && Points[i].y != 0)
		{
			if (Points[i].x < 0)
				if (Points[i].y < 0)
					sum += log(-Points[i].x) * log(-Points[i].y);
				else
					sum += log(-Points[i].x) * log(Points[i].y);
			else
				if (Points[i].y < 0)
					sum += log(Points[i].x) * log(-Points[i].y);
				else
					sum += log(Points[i].x) * log(Points[i].y);
		}
		else
			count++;
		if (count == Points.size())
			Mlnxlny = 0;
		else Mlnxlny = sum / (Points.size() - count);
	}
	count = 0;
	sum = 0;
}

void Line(double Mx, double My, double Mx2, double Mxy)
{
	aLine = (Mxy - Mx * My) / (Mx2 - Mx * Mx);
	bLine = My - Mx * aLine;
}

void Regression(double Mlnx, double Mlny, double Mlnx2, double Mlnxlny)
{
	mRegression = (Mlnxlny - Mlnx * Mlny) / (Mlnx2 - Mlnx * Mlnx);
	aRegression = exp(Mlny - Mlnx * mRegression);
}

void FracLine(double Mx, double Mz, double Mx2, double Mxz)
{
	aFracLine = (Mxz - Mx * Mz) / (Mx2 - Mx * Mx);
	bFracLine = Mz - Mx * aFracLine;
}

void Calculate(double Mx, double My, double Mx2, double Mxy, double Mlnx, double Mlny, double Mlnx2, double Mlnxlny, double Mz, double Mxz)
{
	Line(Mx, My, Mx2, Mxy);
	Regression(Mlnx, Mlny, Mlnx2, Mlnxlny);
	FracLine(Mx, Mz, Mx2, Mxz);
}

void AccuracyLine(double aLine, double bLine, vector <Point> Points)
{
	for (int i = 0; i < Points.size(); i++)
		errorLine += (Points[i].y - (aLine * Points[i].x + bLine)) * (Points[i].y - (aLine * Points[i].x + bLine));
}

void AccuracyRegression(double mRegression, vector <Point> Points)
{
	double pErrorRegression = 0, nErrorRegression = 0;
	for (int i = 0; i < Points.size(); i++)
	{
		if (Points[i].x >= 0)
		{
			pErrorRegression += (Points[i].y - aRegression * pow(Points[i].x, mRegression)) * (Points[i].y - aRegression * pow(Points[i].x, mRegression));
			nErrorRegression += (Points[i].y + aRegression * pow(Points[i].x, mRegression)) * (Points[i].y + aRegression * pow(Points[i].x, mRegression));
		}
		else
		{
			if((int)mRegression == mRegression)
			{
			pErrorRegression += (Points[i].y - aRegression * pow(Points[i].x, mRegression)) * (Points[i].y - aRegression * pow(Points[i].x, mRegression));
			nErrorRegression += (Points[i].y + aRegression * pow(Points[i].x, mRegression)) * (Points[i].y + aRegression * pow(Points[i].x, mRegression));
			}

		}
	}
	if (pErrorRegression > nErrorRegression)
	{
		errorRegression = nErrorRegression;
		aRegression *= -1;
	}
	else
		errorRegression = pErrorRegression;
}

void AccuracyFracLine(double aFracLine, double bFracLine, vector <Point> Points)
{
	for (int i = 0; i < Points.size(); i++)
		if (aFracLine * Points[i].x + bFracLine != 0)
			errorFracLine += (Points[i].y - 1 / (aFracLine * Points[i].x + bFracLine)) * (Points[i].y - 1 / (aFracLine * Points[i].x + bFracLine));
}

void Accuracy(double aLine, double bLine, double aRegression, double mRegression, double aFracLine, double bFracLine, vector <Point> Points)
{
	AccuracyLine(aLine, bLine, Points);
	AccuracyRegression(mRegression, Points);
	AccuracyFracLine(aFracLine, bFracLine, Points);
}


void Outpoot(double aLine, double bLine, double aRegression, double mRegression, double aFracLine, double bFracLine, double errorLine, double errorRegression, double errorFracLine)
{
	cout << "Results:";

	cout << endl << "Linear: " << aLine << "x + " << bLine << "		Error: [" << errorLine << "]";

	cout << endl << "Regression: " << aRegression << "x^" << mRegression << "	Error: [" << errorRegression << "]";

	cout << endl << "FracLine: 1/(" << aFracLine << "x + " << bFracLine << ")	Error: [" << errorFracLine << "]";
}


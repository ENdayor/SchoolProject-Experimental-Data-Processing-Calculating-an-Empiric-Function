#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
const double e = 2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427427466391932003059921;
struct Point
{
	double x;
	double y;
};
vector <Point> Points;
double errors[8];
bool MathProblemAx = true, MathProblemAy = true,MathProblemBx = true, MathProblemBy = true;
double Mx4, Mx3, Mx2y, Mx2, Mx, My, Mxy, Mu, Mu2, Muy, Mlnx, Mlny, Mlnx2, Mlnxlny, Mxlny, Mz, Mxz, Mlnxy, Muz;

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
	for (int i = 0; i < Points.size(); i++)
		sum += Points[i].x * Points[i].x * Points[i].y;
	Mx2y = sum / Points.size();
	sum = 0;
	for (int i = 0; i < Points.size(); i++)
		sum += Points[i].x * Points[i].x * Points[i].x;
	Mx3 = sum / Points.size();
	sum = 0;
	for (int i = 0; i < Points.size(); i++)
		sum += Points[i].x * Points[i].x * Points[i].x * Points[i].x;
	Mx4 = sum / Points.size();
	sum = 0;
	for (int i = 0; i < Points.size(); i++)
		if (Points[i].x == 0)
			MathProblemAx = false;
	if (MathProblemAx)
	{
		for (int i = 0; i < Points.size(); i++)
			sum += 1 / Points[i].x;
		Mu = sum / Points.size();
		sum = 0;
		for (int i = 0; i < Points.size(); i++)
			sum += 1 / (Points[i].x * Points[i].x);
		Mu2 = sum / Points.size();
		sum = 0;
		for (int i = 0; i < Points.size(); i++)
			sum += 1 / Points[i].x * Points[i].y;
		Muy = sum / Points.size();
		sum = 0;
	}
	for (int i = 0; i < Points.size(); i++)
		if (Points[i].y == 0)
			MathProblemAy = false;
	if (MathProblemAy)
	{
		for (int i = 0; i < Points.size(); i++)
			sum += 1 / Points[i].y * Points[i].x;
		Mxz = sum / Points.size();
		sum = 0;
		for (int i = 0; i < Points.size(); i++)
			sum += 1 / Points[i].y;
		Mz = sum / Points.size();
		sum = 0;
	}
	if (MathProblemAx && MathProblemAy)
	{
		for (int i = 0; i < Points.size(); i++)
			sum += 1 / Points[i].y * (1 / Points[i].x);
		Muz = sum / Points.size();
		sum = 0;
	}
	for (int i = 0; i < Points.size(); i++)
		if (Points[i].x < 0)
			MathProblemBx = false;
	if (MathProblemBx)
	{
		for (int i = 0; i < Points.size(); i++)
			sum += log(Points[i].x);
		Mlnx = sum / Points.size();
		sum = 0;
		for (int i = 0; i < Points.size(); i++)
			sum += log(Points[i].x) * log(Points[i].x);
		Mlnx2 = sum / Points.size();
		sum = 0;
	}
	for (int i = 0; i < Points.size(); i++)
		if (Points[i].x < 0)
			MathProblemBy = false;
	if (MathProblemBy)
	{
		for (int i = 0; i < Points.size(); i++)
			sum += log(Points[i].y);
		Mlny = sum / Points.size();
		sum = 0;
		for (int i = 0; i < Points.size(); i++)
			sum += log(Points[i].y) * (Points[i].x);
		Mxlny = sum / Points.size();
		sum = 0;

	}
	if (MathProblemBx && MathProblemBy)
	{
		for (int i = 0; i < Points.size(); i++)
			sum += log(Points[i].y) * log(Points[i].x);
		Mlnxlny = sum / Points.size();
		sum = 0;
	}
}

double aLine, bLine;
void Line(double Mx, double My, double Mx2, double Mxy)
{
	aLine = (Mxy - Mx * My) / (Mx2 - Mx * Mx);
	bLine = My - Mx * aLine;
}

double aQuad, bQuad, cQuad;
void Quad(double Mx4, double Mx3, double Mx2y, double Mx2, double Mx, double My, double Mxy)
{
	aQuad = (Mx2y * (Mx2 - Mx * Mx) - Mx3 * (Mxy - Mx * My) - (Mx2 - Mx * Mx) * (Mx2 * My + Mx2 * Mx * (Mxy + Mx * My))) / ((Mx2 - Mx * Mx) * Mx4 + Mx3 * Mx2 * Mx - Mx3 * Mx3 - Mx2 * Mx * Mx + Mx3 * Mx - (Mx2 - Mx * Mx) * (Mx2 * My) + Mx2 * Mx * (Mxy + Mx * My));
	bQuad = (Mx * Mx2 * aQuad - Mx3 * aQuad + Mxy - Mx * My) / (Mx2 - Mx * Mx);
	cQuad = My - Mx * bQuad - Mx2 * aQuad;
}

double aHyperbola, bHyperbola;
void Hyperbola(double Mu, double My, double Mu2, double Muy)
{
	aHyperbola = (Muy - Mu * My) / (Mu2 - Mu * Mu);
	bHyperbola = My - Mu * aHyperbola;
}
double aRegression, mRegression;
void Regression(double Mlnx, double Mlny, double Mlnx2, double Mlnxlny)
{
	mRegression = (Mlnxlny - Mlnx * Mlny) / (Mlnx2 - Mlnx * Mlnx);
	aRegression = pow(e, (Mlny - Mlnx * mRegression));
}
double aExp, mExp;
void Exp(double Mx, double Mlny, double Mx2, double Mxlny)
{
	mExp = (Mxlny - Mx * Mlny) / (Mx2 - Mx * Mx);
	aExp = pow(e, (Mlny - Mx * mExp));
}
double aFracLine, bFracLine;
void FracLine(double Mx, double Mz, double Mx2, double Mxz)
{
	aFracLine = (Mxz - Mx * Mz) / (Mx2 - Mx * Mx);
	bFracLine = Mz - Mx * aFracLine;
}
double aLn, bLn;
void Ln(double Mlnx, double My, double Mlnx2, double Mlnxy)
{
	aLn = (Mlnxy - Mlnx * My) / (Mlnx2 - Mlnx * Mlnx);
	bLn = My - Mlnx * aLn;
}
double aFracRat, bFracRat;
void FracRat(double Mu, double Mz, double Mu2, double Muz)
{
	aFracRat = (Muz - Mu * Mz) / (Mu2 - Mu * Mu);
	bFracRat = Mz - Mu * aFracRat;
}
int main()
{
	string A;
	ifstream in("A.txt");
	getline(in, A);
	if (in.is_open())
	{
		for (int i = 0; !in.eof(); i++)
		{
			double X, Y, Z;
			in >>  X >> Y;
			Points.push_back({ X, Y });
		}
	}
	in.close();
	Coefficients(Points);
	Line(Mx, My, Mx2, Mxy); //0
	Quad(Mx4, Mx3, Mx2y, Mx2, Mx, My, Mxy); //1
	if(MathProblemAx) Hyperbola(Mu, My, Mu2, Muy); //2 This is so broblematic case, you must fix it
	if(MathProblemBx && MathProblemBy) Regression(Mlnx, Mlny, Mlnx2, Mlnxlny); //3
	if(MathProblemBy) Exp(Mx, Mlny, Mx2, Mxlny); //4
	if(MathProblemAy) FracLine(Mx, Mz, Mx2, Mxz); //5
	if(MathProblemBx) Ln(Mlnx, My, Mlnx2, Mlnxy); //6
	if(MathProblemAx && MathProblemAy)FracRat(Mu, Mz, Mu2, Muz); //7
	double error = 0;
	int minErrorINDEX{ 0 };
	for (int i = 0; i < Points.size(); i++)
		error += (Points[i].y - (aLine * Points[i].x + bLine)) * (Points[i].y - (aLine * Points[i].x + bLine));
	errors[0] = error;
	error = 0;
	
	if (MathProblemBx && MathProblemBy)
		for (int i = 0; i < Points.size(); i++)
			error += (Points[i].y - (aRegression * (pow(Points[i].x, mRegression)))) * (Points[i].y - (aRegression * (pow(Points[i].x, mRegression))));
	else
		error = 1.7E+308;
	errors[3] = error;
	if (errors[3] < errors[0])
		minErrorINDEX = 3;
	error = 0;
	
	if (MathProblemAy)
		for (int i = 0; i < Points.size(); i++)
			error += (Points[i].y - (1 / (aFracLine * Points[i].x + bFracLine))) * (Points[i].y - (1 / (aFracLine * Points[i].x + bFracLine)));
	else
		error = 1.7E+308;
	errors[5] = error;
	if (errors[5] < errors[minErrorINDEX])
		minErrorINDEX = 5;
	error = 0;
	
	switch (minErrorINDEX)
	{
	case 0: cout << aLine << "x + " << bLine;
		break;
	case 1: cout << aQuad << "x^2 + " << bQuad << "x +" << cQuad;
		break;
	case 2: cout << aHyperbola << "/x + " << bHyperbola;
		break;
	case 3: cout << aRegression << "*x^" << mRegression;
		break;
	case 4: cout << aExp << "*exp(" << mExp << "*x)";
		break;
	case 5: cout << "1/(" << aFracLine << "*x +" << bFracLine << ")";
		break;
	case 6: cout << aLn << "*lnx +" << bLn;
		break;
	case 7: cout << "x/(" << aFracRat << "*x +" << bFracRat << ")";
		break;
	default: cout << "Error, unsusual case"; break;
	}
	return 0;
}


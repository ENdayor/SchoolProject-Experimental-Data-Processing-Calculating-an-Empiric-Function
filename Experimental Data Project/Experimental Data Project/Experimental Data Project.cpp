#include "MainHeader.h"

int main()
{
	Input();
	Coefficients(Points);
	Calculate(Mx, My, Mx2, Mxy, Mlnx, Mlny, Mlnx2, Mlnxlny, Mz, Mxz);
	Accuracy(aLine, bLine, aRegression, mRegression, aFracLine, bFracLine, Points);
	Outpoot(aLine, bLine, aRegression, mRegression, aFracLine, bFracLine, errorLine, errorRegression,errorFracLine);
	//cin >> Mx;
	return 0;
}

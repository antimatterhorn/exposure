/*
 *  exposure.cpp
 *  
 *
 *  Created by Cody Raskin on 5/30/10.
 *  Copyright 2010 Cody Raskin. All rights reserved.
 *
 */

#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>

using namespace std;

double FRatio,SB,frac,focalLength,diameter,mag,angDiam,iso;
int num,den,neg;

void Brightness(double m, double d)
{
	SB = pow(10,0.4*(9.5-m)) / (d*d);	
}

void FnumberPrime(double fl, double d)
{
	FRatio = fl/d;
}

void Fraction(double d)
{
	num = 0;
	den = 0;
	neg = 1;
	
	if (d<0) neg = -1;	//determines whether to add or subtract
	
	frac = 0;
	
	while (fabs(frac - d) > 0.0001) {
		if (fabs(frac) > fabs(d)) 
		{
			den++;		//if frac is too big, increase denominator
		} else {
			num += neg;	//else increase numerator
		}
			
		frac = (double)num/(double)den;	
	}
}

void ExposureDuration(double f, double is, double b)
{
	double ex = f*f/(is*b);
	if (ex > 59)
	{
		if (ex > 3599)
		{
			printf("%3.2f hours",ex/3600.);
		} else {
			printf("%3.2f minutes",ex/60.);
		}
	} else {
		if (ex < 0.25)
		{
			Fraction(ex);
			printf("%d/%d seconds",num,den);
		} else {
			printf("%3.2f seconds",ex);
		}
	}
}

int main()
{
	cout << "\nTelescope Properties\n";
	cout << "Focal Length (mm): ";
	cin >> focalLength;
	cout << "Diameter (mm): ";
	cin >> diameter;
	FnumberPrime(focalLength,diameter);
	printf("f%3.2f\n",FRatio);
	
	cout << endl << "Object Properties\n";
	cout << "Apparent Mag: ";
	cin >> mag;
	cout << "Angular Diameter (arc-sec): ";
	cin >> angDiam;
	Brightness(mag,angDiam);
	
	
	printf("\nExposure -------\n");
	printf("ISO\tTime\n");
	
	int i;
	
	for (i=0;i<5;i++)
	{
		iso = pow(2.0,(double)i)*100;
		printf("%4.0f\t",iso);
		ExposureDuration(FRatio,iso,SB);
		printf("\n");
	}
	
	return 0;
}
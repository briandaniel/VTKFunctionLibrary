/*
 * vtkColorMapDefinitions.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: brian
 */




#include "vtkColorMaps.hpp"

// Rescales color map values to be between 0 and 1
// which is required by the color mapper
void rescaleColorMapFromBounds( double ** scalar, double cMin, double cMax, int N, int M )
{
	for (int i = 0; i < N; i ++)
	{
		for(int j = 0; j < M; j++ )
		{
			scalar[i][j] =  ( scalar[i][j] - cMin )/(cMax - cMin);

			if(scalar[i][j] > 1 )
				scalar[i][j] = 1;
			if(scalar[i][j] < 0)
				scalar[i][j] = 0;

		}
	}
}


// Rescales color map values to be between 0 and 1
// which is required by the color mapper
void rescaleColorMap( double ** scalar, int N, int M )
{
	double scalarMax = scalar[0][0];
	double scalarMin = scalar[0][0];
	for (int i = 0; i < N; i ++)
	{
		for(int j = 0; j < M; j++ )
		{
			if(scalar[i][j] > scalarMax)
			{
				scalarMax = scalar[i][j];
			}
			if( scalar[i][j] < scalarMin)
			{
				scalarMin = scalar[i][j];
			}
		}
	}

	for (int i = 0; i < N; i ++)
	{
		for(int j = 0; j < M; j++ )
		{
			scalar[i][j] =  ( scalar[i][j] - scalarMin )/(scalarMax - scalarMin);
		}
	}
}


/* setVTKColorMap( vtkSmartPointer<vtkDataSetMapper> localMapper, int Ncolors, double ** colors )
 * 	Sets the color map in localMapper
 *
 * Ncolors defines the number of colors to set in the lookup table
 * colors is a 3 x Ncolors matrix defining the RGB values, which must be in [0,1]
 *
 * Note: Colors are (probably linearly) interpolated in between the set colors
 *    	 this function also has a safety that sets values to 0 or 1 if incorrect values are given
 *
 */
void setVTKColorMap( vtkSmartPointer<vtkDataSetMapper> localMapper, int Ncolors, double ** colors )
{

	  // Create a lookup table to map cell data to colors
	  vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
	  lut->SetNumberOfTableValues(Ncolors);
	  lut->Build();

	  // Fill in a few known colors, the rest will be generated if needed
	  for(int k = 0; k < Ncolors; k++)
	  {

		  double r = colors[0][k];
		  if (r > 1)
		  {
			  r = 1;
		  	  //cout << "Colormap table only accepts values between 0 and 1!!! automatically setting to 0 or 1." << endl;
		  }
		  if(r <0)
		  {
			  r = 0;
			  //cout << "Colormap table only accepts values between 0 and 1!!! automatically setting to 0 or 1." << endl;
		  }

		  double g = colors[1][k];
		  if (g > 1)
		  {
			  g = 1;
			 // cout << "Colormap table only accepts values between 0 and 1!!! automatically setting to 0 or 1." << endl;
		  }
		  if(g<0)
		  {
			 // cout << "Colormap table only accepts values between 0 and 1!!! automatically setting to 0 or 1." << endl;
			  g = 0;
		  }

		  double b = colors[2][k];
		  if (b > 1)
		  {
			  b = 1;
			//  cout << "Colormap table only accepts values between 0 and 1!!! automatically setting to 0 or 1." << endl;
		  }
		  if (b < 0)
		  {
			  b = 0;
			 // cout << "Colormap table only accepts values between 0 and 1!!! automatically setting to 0 or 1." << endl;
		  }

		  //cout << " r = " << r << ", g = " << g << ", b  =" << b << endl;
		  lut->SetTableValue(k, r, g, b, 1);
	  }

	  localMapper->SetLookupTable(lut);
}


void increaseColorMapResolutionRegularSpacing( int NcolorsIn, double ** colorsIn, int NcolorsOut, double ** colorsOut )
{
	double * xSpacingIn = new double [NcolorsIn];
	double * xSpacingOut = new double [NcolorsOut];


	// void linspace( double a, double b, int N, double*x )

	linspace(0,1,NcolorsIn,xSpacingIn);
	linspace(0,1,NcolorsOut,xSpacingOut);


	increaseColorMapResolution( NcolorsIn, colorsIn, xSpacingIn, NcolorsOut, colorsOut, xSpacingOut );


	delete [] xSpacingIn;
	delete [] xSpacingOut;


}


void increaseColorMapResolution( int NcolorsIn, double ** colorsIn, double * xSpacingIn, int NcolorsOut, double ** colorsOut, double * xSpacingOut )
{


	Spline1D colorSplineR;
	Spline1D colorSplineG;
	Spline1D colorSplineB;


	// void Spline1D::computeSplineCoef( int NnodesIn, double * x, double * y, double * dydx )
    colorSplineR.computeNaturalSplineCoef( NcolorsIn, xSpacingIn, colorsIn[0] );
    colorSplineG.computeNaturalSplineCoef( NcolorsIn, xSpacingIn, colorsIn[1] );
    colorSplineB.computeNaturalSplineCoef( NcolorsIn, xSpacingIn, colorsIn[2] );

    for (int k = 0; k < NcolorsOut; k++ )
    {
    	colorsOut[0][k] = colorSplineR.evaluateSpline( xSpacingOut[k] );
    	colorsOut[1][k] = colorSplineG.evaluateSpline( xSpacingOut[k] );
    	colorsOut[2][k] = colorSplineB.evaluateSpline( xSpacingOut[k] );
    }


}


void setVTKColorMapIncreasedResolution( vtkSmartPointer<vtkDataSetMapper> localMapper, int NcolorsFixed , double colorsFixed[][3]  )
{


	int NcolorsResd = 5000;

	double ** colors = new double * [3];
	double ** colorsResd = new double * [3];
	for(int k = 0; k < 3; k++)
	{
		colors[k] = new double [NcolorsFixed];
		colorsResd[k] = new double [NcolorsResd];
	}

	for(int i = 0; i < NcolorsFixed; i++)
	{
		for(int j  = 0; j < 3; j++)
		{

			// !!! Note: order is reversed!!!
			colors[j][i] = colorsFixed[i][j];
		}
	}



	// increase the resolution with regular spacing
	increaseColorMapResolutionRegularSpacing( NcolorsFixed, colors, NcolorsResd, colorsResd );


	// set color map
	setVTKColorMap( localMapper, NcolorsResd, colorsResd );



	// clean up
	for(int k = 0; k < 3; k++)
	{
		delete [] colors[k];
		delete [] colorsResd[k];
	}
	delete [] colors;
	delete [] colorsResd;
}

// Sets the color map to matlab's parula
void setVTKColorMapParula( vtkSmartPointer<vtkDataSetMapper> localMapper)
{

	int NcolorsFixed = 10;
	double parulaFixed [10][3] = {
		{0.2422,    0.1504,    0.6603},
		{0.2803,    0.2782,    0.9221},
		{0.2440,    0.4358,    0.9988},
		{0.1540,    0.5902,    0.9218},
		{0.0297,    0.7082,    0.8163},
		{0.1938,    0.7758,    0.6251},
		{0.5044,    0.7993,    0.3480},
		{0.8634,    0.7406,    0.1596},
		{0.9892,    0.8136,    0.1885},
		{0.9769,    0.9839,    0.0805} };

	 setVTKColorMapIncreasedResolution( localMapper, NcolorsFixed, parulaFixed );

}



// Sets the color map to black to red
void setVTKColorMapBlackToRed( vtkSmartPointer<vtkDataSetMapper> localMapper)
{

	int NcolorsFixed = 3;
	double parulaFixed [10][3] = {
		{0.0,    0.0,    0.0},
		{0.5,    0.0,    0.0},
		{1.0,    0.0,    0.0} };

	 setVTKColorMapIncreasedResolution( localMapper, NcolorsFixed, parulaFixed );

}

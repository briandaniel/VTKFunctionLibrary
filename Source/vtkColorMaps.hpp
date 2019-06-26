/*
 * vtkColorMapDefinitions.hpp
 *
 *  Created on: Sep 19, 2018
 *      Author: brian
 */

#ifndef VTKCOLORMAPS_HPP_
#define VTKCOLORMAPS_HPP_


// Utility function includes
#include "CubicSplines1D/cubicSplinesFunctions1D.hpp"

// VTK includes
#include <vtkDataSetMapper.h>

// VTK lookup table for colormap
#include <vtkLookupTable.h>


//  local functions

// Rescales color map values to be between 0 and 1 based on defined min/max values
void rescaleColorMapFromBounds( double ** scalar, double cMin, double cMax, int N, int M );

// Rescales color map values to be between 0 and 1
void rescaleColorMap( double ** scalar, int N, int M );

/* setVTKColorMap( vtkSmartPointer<vtkDataSetMapper> localMapper, int Ncolors, double ** colors )
 * 	Sets the color map in localMapper
 *
 * Ncolors defines the number of colors to set in the lookup table
 * colors is a NcolorsX3 matrix defining the RGB values, which must be in [0,1]
 *
 * Note: Colors are (probably linearly) interpolated in between the set colors
 *    	 this function also has a safety that sets values to 0 or 1 if incorrect values are given
 *
 */
void setVTKColorMap( vtkSmartPointer<vtkDataSetMapper> localMapper, int Ncolors, double ** colors );

void increaseColorMapResolutionRegularSpacing( int NcolorsIn, double ** colorsIn, int NcolorsOut, double ** colorsOut );

void increaseColorMapResolution( int NcolorsIn, double ** colorsIn, double * xSpacingIn, int NcolorsOut, double ** colorsOut, double * xSpacingOut );

void setVTKColorMapIncreasedResolution( vtkSmartPointer<vtkDataSetMapper> localMapper, int NcolorsFixed , double colorsFixed[][3]  );

// Color maps
void setVTKColorMapParula( vtkSmartPointer<vtkDataSetMapper> localMapper);
void setVTKColorMapBlackToRed( vtkSmartPointer<vtkDataSetMapper> localMapper);


#endif /* VTKCOLORMAPS_HPP_ */

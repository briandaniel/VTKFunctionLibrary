/*
 * linePlot3DFunctions.hpp
 *
 *  Created on: Jan 16, 2019
 *      Author: brian
 */

#ifndef LINEPLOT3DFUNCTIONS_HPP_
#define LINEPLOT3DFUNCTIONS_HPP_

using namespace std;


// standard includes
#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <complex>
#include <cstdio>
#include <ctime>
#include <vector>
#include <mpi.h>
#include <iomanip>
#include <string>

// vtk standard includes
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyLine.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>

// local functions
void createLineInActor( vector<double> & xLine, vector<double> & yLine, vector <double> & zLine,
		vtkSmartPointer<vtkActor> localActor, double opacity, double redIdx, double greenIdx, double blueIdx );


#endif /* LINEPLOT3DFUNCTIONS_HPP_ */

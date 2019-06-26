/*
 * generalVTKFunctions.hpp
 *
 *  Created on: Sep 18, 2018
 *      Author: brian
 */

#ifndef GENERALVTKFUNCTIONS_HPP_
#define GENERALVTKFUNCTIONS_HPP_

// standard includes
#include <iostream>
#include <fstream>
#include <string>
#include <inttypes.h>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <mpi.h>
#include <math.h>
#include <vector>

// local includes

// VTK includes
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>


// VTK figure writer includes
#include <vtkBMPWriter.h>
#include <vtkImageWriter.h>
#include <vtkJPEGWriter.h>
#include <vtkPNGWriter.h>
#include <vtkPNMWriter.h>
#include <vtkPostScriptWriter.h>
#include <vtkTIFFWriter.h>
#include <vtkWindowToImageFilter.h>


using namespace std;

// local functions
void writeVTKpng( string pngFileName, vtkSmartPointer<vtkRenderWindow> renderWindow );




#endif /* GENERALVTKFUNCTIONS_HPP_ */

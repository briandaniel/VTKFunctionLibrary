/*
 * vtkFunctions.hpp
 *
 *  Created on: Feb 14, 2018
 *      Author: brian
 */

#ifndef VTKFUNCTIONS_VTKFUNCTIONS_HPP_
#define VTKFUNCTIONS_VTKFUNCTIONS_HPP_





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
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkTriangleStrip.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyDataNormals.h>

// render window
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

// simple sources
#include <vtkCylinderSource.h>
#include <vtkSphereSource.h>
#include <vtkNamedColors.h>

// export formats
#include "vtkGL2PSExporter.h"
#include <vtkBMPWriter.h>
#include <vtkImageWriter.h>
#include <vtkJPEGWriter.h>
#include <vtkPNGWriter.h>
#include <vtkPNMWriter.h>
#include <vtkPostScriptWriter.h>
#include <vtkTIFFWriter.h>
#include <vtkWindowToImageFilter.h>
#include <vtkExporter.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkVRMLExporter.h>

// other includes
#include "vtkNew.h"
#include "vtkCamera.h"
#include "vtkLight.h"
#include "vtkTestUtilities.h"
#include "vtkRegressionTestImage.h"
#include "vtkTestingInteractor.h"
#include <vtkFloatArray.h>
#include <vtkPointData.h>


// Local includes
void addTriangleStripSurfaceToActor( vtkSmartPointer<vtkActor> surfActor, double ** x, double ** y, double **z, int N, int M );
void addTriangleStripSurfaceToActorConnected( vtkSmartPointer<vtkActor> surfActor, double ** x, double ** y, double **z, int N, int M );
void addTriangleStripSurfaceToActorConnectedColumn( vtkSmartPointer<vtkActor> surfActor, double ** x, double ** y, double **z, int N, int M );
void addTriangleStripSurfaceToActorAndMapperConnectedColumnWithScalar(vtkSmartPointer<vtkActor> surfActor, vtkSmartPointer<vtkDataSetMapper> surfMapper,
		double ** x, double ** y, double **z, double ** scalar, int N, int M );

void addTriangleStripSurfaceToActorWithScalar( vtkSmartPointer<vtkActor> surfActor, double ** x, double ** y, double **z, double ** scalar, int N, int M );
void addTriangleStripSurfaceToMapperWithScalar( vtkSmartPointer<vtkDataSetMapper> mapper, double ** x, double ** y, double **z, double ** scalar, int N, int M );

void addTriangleStripSurfaceToActorAndMapperWithScalar( vtkSmartPointer<vtkActor> surfActor, vtkSmartPointer<vtkDataSetMapper> mapper,
		double ** x, double ** y, double **z, double ** scalar, int N, int M );









#endif /* VTKFUNCTIONS_VTKFUNCTIONS_HPP_ */

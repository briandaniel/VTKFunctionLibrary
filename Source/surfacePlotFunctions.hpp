/*
 * surfacePlotFunctions.hpp
 *
 *  Created on: Sep 18, 2018
 *      Author: brian
 */

#ifndef SURFACEPLOTFUNCTIONS_HPP_
#define SURFACEPLOTFUNCTIONS_HPP_


// local includes
#include "triangleStripFunctions.hpp"
#include "vtkColorMaps.hpp"

// Utility function library includes
#include "DataContainer/dataContainer.hpp"

// standard includes
#include <string>
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


// vtk includes

#include "vtkTestUtilities.h"
#include "vtkRegressionTestImage.h"
#include "vtkGL2PSExporter.h"

#include "vtkActor.h"
#include "vtkNew.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkTestingInteractor.h"
#include "vtkTextActor.h"
#include "vtkTextMapper.h"

#include <vtkVersion.h>
#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkDataSetMapper.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTriangleStrip.h>

#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>


#include <vtkVersion.h>
#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkDataSetMapper.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTriangleStrip.h>
#include "vtkCamera.h"
#include "vtkLight.h"
#include <vtkPolyDataNormals.h>
#include <vtkExporter.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkVRMLExporter.h>

#include <vtkTextActor.h>
#include <vtkTextProperty.h>

#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

/*
 * void createSurfaceInActorAndMapperWithDefinedColors(...)
 *   Generates a surface of size NxM in the actor and mapper with colors defined tas values in c
 *
 *  Note: x, y, z, c have size NxM.
 */
void createSurfaceInActorAndMapperWithDefinedColors( double ** x, double ** y, double ** z, double ** c, int N, int M,
		vtkSmartPointer<vtkActor> localActor, vtkSmartPointer<vtkDataSetMapper> localMapper,
		double opacity, double ambientIdx, double ambientRedIdx, double ambientGreenIdx, double ambientBlueIdx );


/*
 * void createSurfaceInActorWithMap(...)
 *   Generates a surface of size NxM in the actor with map defined through the values in c
 *
 *  Note: x, y, z, c have size NxM.
 */
void createSurfaceInActorWithMap( double ** x, double ** y, double ** z, double ** c, int N, int M, vtkSmartPointer<vtkActor> localActor,
		double opacity, double ambientIdx, double ambientRedIdx, double ambientGreenIdx, double ambientBlueIdx );

/*
 * void createSurfaceInActor(...)
 *   Generates a surface of size NxM in the actor
 *
 *  Note: x, y, z have size NxM.
 */
void createSurfaceInActor( double ** x, double ** y, double ** z, int N, int M, vtkSmartPointer<vtkActor> localActor,
		double opacity, double redIdx, double greenIdx, double blueIdx, double ambientIdx, double ambientRedIdx, double ambientGreenIdx, double ambientBlueIdx );


/*
 * void createSurfaceInActorConnected(...)
 *   Generates a surface of size NxM in the actor
 *   The last elements in the vector are connected to the first element
 *   Using the second index
 *
 *  Note: x, y, z have size NxM.
 */
void createSurfaceInActorConnectedColumn( double ** x, double ** y, double ** z, int N, int M, vtkSmartPointer<vtkActor> localActor,
		double opacity, double redIdx, double greenIdx, double blueIdx, double ambientIdx, double ambientRedIdx, double ambientGreenIdx, double ambientBlueIdx );

void createSurfaceInActorAndMapperConnectedColumnWithScalar( double ** x, double ** y, double ** z, double ** scalar, int N, int M,
		vtkSmartPointer<vtkActor> localActor, vtkSmartPointer<vtkDataSetMapper> localMapper, double opacity, double ambientIdx );

void createSurfaceInActorFromContainer(  vtkSmartPointer<vtkActor> localActor, DataContainer & surfData, string xName, string yName, string zName,
		double opacity, double redIdx, double greenIdx, double blueIdx, double ambientIdx, double ambientRedIdx, double ambientGreenIdx, double ambientBlueIdx );
void loadDataContainerIntoActor( vtkSmartPointer<vtkActor> localActor, DataContainer & surfData, string xName, string yName, string zName );

#endif /* SURFACEPLOTFUNCTIONS_HPP_ */

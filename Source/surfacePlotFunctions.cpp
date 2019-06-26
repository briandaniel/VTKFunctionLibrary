/*
 * surfacePlotFunctions.cpp
 *
 *  Created on: Sep 18, 2018
 *      Author: brian
 */

#include "surfacePlotFunctions.hpp"


/*
 * void createSurfaceInActorAndMapperWithDefinedColors(...)
 *   Generates a surface of size NxM in the actor and mapper with colors defined tas values in c
 *
 *  Note: x, y, z, c have size NxM.
 */
void createSurfaceInActorAndMapperWithDefinedColors( double ** x, double ** y, double ** z, double ** c, int N, int M,
		vtkSmartPointer<vtkActor> localActor, vtkSmartPointer<vtkDataSetMapper> localMapper,
		double opacity, double ambientIdx, double ambientRedIdx, double ambientGreenIdx, double ambientBlueIdx )
{
	rescaleColorMap( c, N, M );

	addTriangleStripSurfaceToActorAndMapperWithScalar( localActor, localMapper, x, y, z, c, N, M );

	localActor->GetProperty()->SetAmbient(ambientIdx);
	localActor->GetProperty()->SetAmbientColor(ambientRedIdx, ambientGreenIdx, ambientBlueIdx);
	localActor->GetProperty()->SetOpacity(opacity);

}


/*
 * void createSurfaceInActorWithMap(...)
 *   Generates a surface of size NxM in the actor with map defined through the values in c
 *
 *  Note: x, y, z, c have size NxM.
 */
void createSurfaceInActorWithMap( double ** x, double ** y, double ** z, double ** c, int N, int M, vtkSmartPointer<vtkActor> localActor,
		double opacity, double ambientIdx, double ambientRedIdx, double ambientGreenIdx, double ambientBlueIdx )
{
	rescaleColorMap( c, N, M );

	addTriangleStripSurfaceToActorWithScalar( localActor, x, y, z, c, N, M );

	localActor->GetProperty()->SetAmbient(ambientIdx);
	localActor->GetProperty()->SetAmbientColor(ambientRedIdx, ambientGreenIdx, ambientBlueIdx);
	localActor->GetProperty()->SetOpacity(opacity);

}



/*
 * void createSurfaceInActor(...)
 *   Generates a surface of size NxM in the actor
 *
 *  Note: x, y, z have size NxM.
 */
void createSurfaceInActor( double ** x, double ** y, double ** z, int N, int M, vtkSmartPointer<vtkActor> localActor,
		double opacity, double redIdx, double greenIdx, double blueIdx, double ambientIdx, double ambientRedIdx, double ambientGreenIdx, double ambientBlueIdx )
{
	addTriangleStripSurfaceToActor( localActor, x, y, z, N, M );

	localActor->GetProperty()->SetColor(redIdx, greenIdx, blueIdx);
	localActor->GetProperty()->SetAmbient(ambientIdx);
	localActor->GetProperty()->SetAmbientColor(ambientRedIdx, ambientGreenIdx, ambientBlueIdx);
	localActor->GetProperty()->SetOpacity(opacity);

}



/*
 * void createSurfaceInActorConnected(...)
 *   Generates a surface of size NxM in the actor
 *   The last elements in the vector are connected to the first element
 *   Using the second index
 *
 *  Note: x, y, z have size NxM.
 */
void createSurfaceInActorConnectedColumn( double ** x, double ** y, double ** z, int N, int M, vtkSmartPointer<vtkActor> localActor,
		double opacity, double redIdx, double greenIdx, double blueIdx, double ambientIdx, double ambientRedIdx, double ambientGreenIdx, double ambientBlueIdx )
{
	addTriangleStripSurfaceToActorConnectedColumn( localActor, x, y, z, N, M );

	localActor->GetProperty()->SetColor(redIdx, greenIdx, blueIdx);
	localActor->GetProperty()->SetAmbient(ambientIdx);
	localActor->GetProperty()->SetAmbientColor(ambientRedIdx, ambientGreenIdx, ambientBlueIdx);
	localActor->GetProperty()->SetOpacity(opacity);

}


/*
 * void createSurfaceInActorConnected(...)
 *   Generates a surface of size NxM in the actor
 *   The last elements in the vector are connected to the first element
 *   Using the second index
 *
 *  Note: x, y, z have size NxM.
 */
void createSurfaceInActorAndMapperConnectedColumnWithScalar( double ** x, double ** y, double ** z, double ** scalar, int N, int M,
		vtkSmartPointer<vtkActor> localActor, vtkSmartPointer<vtkDataSetMapper> localMapper, double opacity, double ambientIdx )
{
	// rescaleColorMap( scalar, N, M );

	addTriangleStripSurfaceToActorAndMapperConnectedColumnWithScalar( localActor, localMapper, x, y, z, scalar, N, M );

	localActor->GetProperty()->SetAmbient(ambientIdx);
	localActor->GetProperty()->SetOpacity(opacity);

}


void createSurfaceInActorFromContainer(  vtkSmartPointer<vtkActor> localActor, DataContainer & surfData, string xName, string yName, string zName,
		double opacity, double redIdx, double greenIdx, double blueIdx, double ambientIdx, double ambientRedIdx, double ambientGreenIdx, double ambientBlueIdx )
{

	loadDataContainerIntoActor( localActor, surfData, xName, yName, zName  );
	localActor->GetProperty()->SetColor(redIdx, greenIdx, blueIdx);
	localActor->GetProperty()->SetAmbient(ambientIdx);
	localActor->GetProperty()->SetAmbientColor(ambientRedIdx, ambientGreenIdx, ambientBlueIdx);
	localActor->GetProperty()->SetOpacity(opacity);

}

void loadDataContainerIntoActor( vtkSmartPointer<vtkActor> localActor, DataContainer & surfData, string xName, string yName, string zName )
{


	vector <int> dataSize;
	int Ndim;
	surfData.getDataSize( xName, Ndim, dataSize );

	// Set data size
	int N = dataSize[0];
	int M = dataSize[1];

	// create data matrices
	double ** x = new double * [N];
	double ** y = new double * [N];
	double ** z = new double * [N];
	for (int i = 0; i < N; i ++)
	{
		x[i] = new double [M];
		y[i] = new double [M];
		z[i] = new double [M];
	}

	// now pull the data and make the endocardial surface
	surfData.readDataSet( xName, x);
	surfData.readDataSet( yName, y);
	surfData.readDataSet( zName, z);

	addTriangleStripSurfaceToActor( localActor, x, y, z, N, M );

	// clean up

	for (int i = 0; i < N; i ++)
	{
		delete [] x[i];
		delete [] y[i];
		delete [] z[i];
	}
	delete [] x;
	delete [] y;
	delete [] z;

}




/*
 * vtkFunctions.cpp
 *
 *  Created on: Feb 14, 2018
 *      Author: brian
 */



#include "triangleStripFunctions.hpp"






void addTriangleStripSurfaceToActor( vtkSmartPointer<vtkActor> surfActor, double ** x, double ** y, double **z, int N, int M )
{

	// 1. Put points into VTK smart pointer <vtkPoints> class
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<M; j++)
		{
			points->InsertNextPoint(x[i][j], y[i][j], z[i][j]);
		}
	}


	// 2. Create triangle strips along surface that will be stored in "cells," a <vtkCellArray> object.
	vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
	for (int i = 0; i < ( N-1 ); i++)
	{
		// Make a triangle strip for each row
		vtkSmartPointer<vtkTriangleStrip> triangleStrip = vtkSmartPointer<vtkTriangleStrip>::New();
		triangleStrip->GetPointIds()->SetNumberOfIds(2*M);
		int c = 0;

		for (int j = 0; j < M; j++)
		{

 			// New top row data point
			triangleStrip->GetPointIds()->SetId( c , j + i*M);
			c++;

			// Connect the bottom row data point
			triangleStrip->GetPointIds()->SetId( c , j + (i+1)*M );
			c++;

		}

		cells->InsertNextCell(triangleStrip);
	}
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);
	polydata->SetStrips(cells);

	// Generate normals -- this is the oh-so-important step to get the clean look which is
	// one of the main reasons to use a program like VTK.

	// Triangle strips automatically calculate normals [or so it appears] but neighboring
	// triangle strips have hard edges unless you run the following couple of lines..

	// Try lowering the resolution (50x50 points or so) then see what happens when you
	// comment out these lines.
	vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
	normalGenerator->SetInputData(polydata);
	normalGenerator->Update();
	polydata = normalGenerator->GetOutput();


	// Create map and add it to the actor
	vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputData(polydata);
	surfActor->SetMapper(mapper);





}







// in this version the surfaces are considered to be connected
// in the standard surface matrices for prolate spheroid coordinates
void addTriangleStripSurfaceToActorConnected( vtkSmartPointer<vtkActor> surfActor, double ** x, double ** y, double **z, int N, int M )
{

	// 1. Put points into VTK smart pointer <vtkPoints> class
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<M; j++)
		{
			points->InsertNextPoint(x[i][j], y[i][j], z[i][j]);
		}
	}


	// 2. Create triangle strips along surface that will be stored in "cells," a <vtkCellArray> object.
	vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
	for (int i = 0; i < N-1 ; i++)
	{
		// Make a triangle strip for each row
		vtkSmartPointer<vtkTriangleStrip> triangleStrip = vtkSmartPointer<vtkTriangleStrip>::New();
		triangleStrip->GetPointIds()->SetNumberOfIds(2*M);
		int c = 0;



		for (int j = 0; j < M; j++)
		{

 			// New top row data point
			if (j > 0)
			{
				triangleStrip->GetPointIds()->SetId( c , j + i*M);
			}
			else
			{
				triangleStrip->GetPointIds()->SetId( c , j + i*M);

				//triangleStrip->GetPointIds()->SetId( c , 0);
			}
			c++;

			// Connect the bottom row data point
			if ( i < N-2)
			{
				triangleStrip->GetPointIds()->SetId( c , j + (i+1)*M );
			}
			else
			{
				triangleStrip->GetPointIds()->SetId( c , j + 0*M );
			}

			c++;

		}

		cells->InsertNextCell(triangleStrip);
	}
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);
	polydata->SetStrips(cells);

	// Generate normals -- this is the oh-so-important step to get the clean look which is
	// one of the main reasons to use a program like VTK.

	// Triangle strips automatically calculate normals [or so it appears] but neighboring
	// triangle strips have hard edges unless you run the following couple of lines..

	// Try lowering the resolution (50x50 points or so) then see what happens when you
	// comment out these lines.
	vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
	normalGenerator->SetInputData(polydata);
	normalGenerator->Update();
	polydata = normalGenerator->GetOutput();


	// Create map and add it to the actor
	vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputData(polydata);
	surfActor->SetMapper(mapper);





}





// in this version the surfaces are considered to be connected
// in the standard surface matrices for prolate spheroid coordinates
void addTriangleStripSurfaceToActorConnectedColumn( vtkSmartPointer<vtkActor> surfActor, double ** x, double ** y, double **z, int N, int M )
{

	// 1. Put points into VTK smart pointer <vtkPoints> class
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<M; j++)
		{
			points->InsertNextPoint(x[i][j], y[i][j], z[i][j]);
		}
	}


	// 2. Create triangle strips along surface that will be stored in "cells," a <vtkCellArray> object.
	vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
	for (int i = 0; i < N-1 ; i++)
	{
		// Make a triangle strip for each row
		vtkSmartPointer<vtkTriangleStrip> triangleStrip = vtkSmartPointer<vtkTriangleStrip>::New();
		triangleStrip->GetPointIds()->SetNumberOfIds(2*M);
		int c = 0;

		int j = 0;
		// connect the first M-1 points
		for (j = 0; j < M-1; j++)
		{

 			// New top row data point
			triangleStrip->GetPointIds()->SetId( c , j + i*M);
			c++;

			// Connect the bottom row data point
			triangleStrip->GetPointIds()->SetId( c , j + (i+1)*M );
			c++;

		}

		// now connect the last column to the first instead of the last
		j = 0;
		// New top row data point
		triangleStrip->GetPointIds()->SetId( c , j + i*M);
		c++;

		// Connect the bottom row data point
		triangleStrip->GetPointIds()->SetId( c , j + (i+1)*M );
		c++;


		cells->InsertNextCell(triangleStrip);
	}
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);
	polydata->SetStrips(cells);

	// Generate normals -- this is the oh-so-important step to get the clean look which is
	// one of the main reasons to use a program like VTK.

	// Triangle strips automatically calculate normals [or so it appears] but neighboring
	// triangle strips have hard edges unless you run the following couple of lines..

	// Try lowering the resolution (50x50 points or so) then see what happens when you
	// comment out these lines.
	vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
	normalGenerator->SetInputData(polydata);
	normalGenerator->Update();
	polydata = normalGenerator->GetOutput();


	// Create map and add it to the actor
	vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputData(polydata);
	surfActor->SetMapper(mapper);





}





// in this version the surfaces are considered to be connected
// in the standard surface matrices for prolate spheroid coordinates
void addTriangleStripSurfaceToActorAndMapperConnectedColumnWithScalar(vtkSmartPointer<vtkActor> surfActor, vtkSmartPointer<vtkDataSetMapper> surfMapper,
		double ** x, double ** y, double **z, double ** scalar, int N, int M )
{

	// 1. Put points into VTK smart pointer <vtkPoints> class
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkFloatArray> pointValues = vtkSmartPointer<vtkFloatArray>::New();

	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<M; j++)
		{
			points->InsertNextPoint(x[i][j], y[i][j], z[i][j]);
			pointValues->InsertNextValue( scalar[i][j] );

		}
	}


	// 2. Create triangle strips along surface that will be stored in "cells," a <vtkCellArray> object.
	vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
	for (int i = 0; i < N-1 ; i++)
	{
		// Make a triangle strip for each row
		vtkSmartPointer<vtkTriangleStrip> triangleStrip = vtkSmartPointer<vtkTriangleStrip>::New();
		triangleStrip->GetPointIds()->SetNumberOfIds(2*M);
		int c = 0;

		int j = 0;
		// connect the first M-1 points
		for (j = 0; j < M-1; j++)
		{

 			// New top row data point
			triangleStrip->GetPointIds()->SetId( c , j + i*M);
			c++;

			// Connect the bottom row data point
			triangleStrip->GetPointIds()->SetId( c , j + (i+1)*M );
			c++;

		}

		// now connect the last column to the first instead of the last
		j = 0;
		// New top row data point
		triangleStrip->GetPointIds()->SetId( c , j + i*M);
		c++;

		// Connect the bottom row data point
		triangleStrip->GetPointIds()->SetId( c , j + (i+1)*M );
		c++;


		cells->InsertNextCell(triangleStrip);
	}
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);
	polydata->SetStrips(cells);

	// Generate normals -- this is the oh-so-important step to get the clean look which is
	// one of the main reasons to use a program like VTK.

	// Triangle strips automatically calculate normals [or so it appears] but neighboring
	// triangle strips have hard edges unless you run the following couple of lines..

	// Try lowering the resolution (50x50 points or so) then see what happens when you
	// comment out these lines.
	vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
	normalGenerator->SetInputData(polydata);
	normalGenerator->Update();
	polydata = normalGenerator->GetOutput();

	// set the scalar values
	polydata->GetPointData()->SetScalars(pointValues);


	// Create map and add it to the actor
	surfMapper->SetInputData(polydata);
	surfActor->SetMapper(surfMapper);





}


void addTriangleStripSurfaceToActorWithScalar( vtkSmartPointer<vtkActor> surfActor, double ** x, double ** y, double **z, double ** scalar, int N, int M )
{

	// 1. Put points into VTK smart pointer <vtkPoints> class
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkFloatArray> pointValues = vtkSmartPointer<vtkFloatArray>::New();
	pointValues->SetNumberOfComponents(1);
	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<M; j++)
		{
			points->InsertNextPoint(x[i][j], y[i][j], z[i][j]);
			pointValues->InsertNextValue( scalar[i][j] );
		}
	}


	// 2. Create triangle strips along surface that will be stored in "cells," a <vtkCellArray> object.
	vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
	for (int i = 0; i < ( N-1 ); i++)
	{
		// Make a triangle strip for each row
		vtkSmartPointer<vtkTriangleStrip> triangleStrip = vtkSmartPointer<vtkTriangleStrip>::New();
		triangleStrip->GetPointIds()->SetNumberOfIds(2*M);
		int c = 0;

		for (int j = 0; j < M; j++)
		{

 			// New top row data point
			triangleStrip->GetPointIds()->SetId( c , j + i*M);
			c++;

			// Connect the bottom row data point
			triangleStrip->GetPointIds()->SetId( c , j + (i+1)*M );
			c++;

		}

		cells->InsertNextCell(triangleStrip);
	}
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);
	polydata->SetStrips(cells);

	// Generate normals -- this is the oh-so-important step to get the clean look which is
	// one of the main reasons to use a program like VTK.

	// Triangle strips automatically calculate normals [or so it appears] but neighboring
	// triangle strips have hard edges unless you run the following couple of lines..

	// Try lowering the resolution (50x50 points or so) then see what happens when you
	// comment out these lines.
	vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
	normalGenerator->SetInputData(polydata);
	normalGenerator->Update();
	polydata = normalGenerator->GetOutput();

	polydata->GetPointData()->SetScalars(pointValues);

	// Create map and add it to the actor
	vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputData(polydata);
	surfActor->SetMapper(mapper);





}





void addTriangleStripSurfaceToMapperWithScalar( vtkSmartPointer<vtkDataSetMapper> mapper, double ** x, double ** y, double **z, double ** scalar, int N, int M )
{

	// 1. Put points into VTK smart pointer <vtkPoints> class
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

	vtkSmartPointer<vtkFloatArray> pointValues = vtkSmartPointer<vtkFloatArray>::New();
	pointValues->SetNumberOfComponents(1);

	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<M; j++)
		{
			points->InsertNextPoint(x[i][j], y[i][j], z[i][j]);

			pointValues->InsertNextValue( scalar[i][j] );

		}
	}


	// 2. Create triangle strips along surface that will be stored in "cells," a <vtkCellArray> object.
	vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
	for (int i = 0; i < ( N-1 ); i++)
	{
		// Make a triangle strip for each row
		vtkSmartPointer<vtkTriangleStrip> triangleStrip = vtkSmartPointer<vtkTriangleStrip>::New();
		triangleStrip->GetPointIds()->SetNumberOfIds(2*M);
		int c = 0;

		for (int j = 0; j < M; j++)
		{

 			// New top row data point
			triangleStrip->GetPointIds()->SetId( c , j + i*M);
			c++;

			// Connect the bottom row data point
			triangleStrip->GetPointIds()->SetId( c , j + (i+1)*M );
			c++;

		}

		cells->InsertNextCell(triangleStrip);
	}
	vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
	polyData->SetPoints(points);
	polyData->SetStrips(cells);

	polyData->GetPointData()->SetScalars(pointValues);

	// Generate normals -- this is the oh-so-important step to get the clean look which is
	// one of the main reasons to use a program like VTK.

	// Triangle strips automatically calculate normals [or so it appears] but neighboring
	// triangle strips have hard edges unless you run the following couple of lines..

	// Try lowering the resolution (50x50 points or so) then see what happens when you
	// comment out these lines.
	vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
	normalGenerator->SetInputData(polyData);
	normalGenerator->Update();
	polyData = normalGenerator->GetOutput();


	// Create map and add it to the actor
	mapper->SetInputData(polyData);


}









void addTriangleStripSurfaceToActorAndMapperWithScalar( vtkSmartPointer<vtkActor> surfActor, vtkSmartPointer<vtkDataSetMapper> localMapper,
		double ** x, double ** y, double **z, double ** scalar, int N, int M )
{

	// 1. Put points into VTK smart pointer <vtkPoints> class
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkFloatArray> pointValues = vtkSmartPointer<vtkFloatArray>::New();
	pointValues->SetNumberOfComponents(1);
	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<M; j++)
		{
			points->InsertNextPoint(x[i][j], y[i][j], z[i][j]);
			pointValues->InsertNextValue( scalar[i][j] );
		}
	}


	// 2. Create triangle strips along surface that will be stored in "cells," a <vtkCellArray> object.
	vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
	for (int i = 0; i < ( N-1 ); i++)
	{
		// Make a triangle strip for each row
		vtkSmartPointer<vtkTriangleStrip> triangleStrip = vtkSmartPointer<vtkTriangleStrip>::New();
		triangleStrip->GetPointIds()->SetNumberOfIds(2*M);
		int c = 0;

		for (int j = 0; j < M; j++)
		{

 			// New top row data point
			triangleStrip->GetPointIds()->SetId( c , j + i*M);
			c++;

			// Connect the bottom row data point
			triangleStrip->GetPointIds()->SetId( c , j + (i+1)*M );
			c++;

		}

		cells->InsertNextCell(triangleStrip);
	}
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);
	polydata->SetStrips(cells);

	// Generate normals -- this is the oh-so-important step to get the clean look which is
	// one of the main reasons to use a program like VTK.

	// Triangle strips automatically calculate normals [or so it appears] but neighboring
	// triangle strips have hard edges unless you run the following couple of lines..

	// Try lowering the resolution (50x50 points or so) then see what happens when you
	// comment out these lines.
	vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
	normalGenerator->SetInputData(polydata);
	normalGenerator->Update();
	polydata = normalGenerator->GetOutput();

	polydata->GetPointData()->SetScalars(pointValues);

	// Create map and add it to the actor
	localMapper->SetInputData(polydata);
	surfActor->SetMapper(localMapper);


}


/*
 * VTKRenderContainer.cpp
 *
 *  Created on: Oct 24, 2018
 *      Author: brian
 */


#include "VTKRenderContainer.hpp"





void RenderContainerVTK::plotPoint(double x, double y, double z, double red, double green, double blue, double size )
{
	  vtkSmartPointer<vtkPoints> points =
	    vtkSmartPointer<vtkPoints>::New();
	  vtkSmartPointer<vtkPolyData> pointsPolydata =
	    vtkSmartPointer<vtkPolyData>::New();


	  points->InsertNextPoint (x, y, z);


	  pointsPolydata->SetPoints(points);

	  vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =
	    vtkSmartPointer<vtkVertexGlyphFilter>::New();

	  vertexFilter->SetInputData(pointsPolydata);

	  vertexFilter->Update();

	  vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	  polydata->ShallowCopy(vertexFilter->GetOutput());


	  unsigned char color[3] = { (unsigned char) round(255*red), (unsigned char) round(255*green), (unsigned char) round(255*blue)};
	  vtkSmartPointer<vtkUnsignedCharArray> colors =  vtkSmartPointer<vtkUnsignedCharArray>::New();
	  colors->SetNumberOfComponents(3);
	  colors->SetName ("Colors");
	  colors->InsertNextTupleValue(color);


	  polydata->GetPointData()->SetScalars(colors);

	  // Visualization
	  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

	  mapper->SetInputData(polydata);

	  vtkSmartPointer<vtkActor> actor =  vtkSmartPointer<vtkActor>::New();
	  actor->SetMapper(mapper);
	  actor->GetProperty()->SetPointSize(size);

	  renderer->AddActor(actor);

}




void plotParabolicSurf( double zscale, RenderContainerVTK & rcVTK )
{


	// parameters


		int N = 100;
		int M = 100;
		double amp = 5.0;
		double sigma_x = 2;
		double sigma_y = 2;

		double xMin = -4;
		double xMax = 4;
		double yMin = -4;
		double yMax = 4;


		// local arrays
		double * xVec = new double [N];
		double * yVec = new double [M];

		double ** x = new double * [N];
		double ** y = new double * [N];
		double ** z = new double * [N];
		double ** c = new double * [N];
		for(int i = 0; i < N; i++)
		{
			x[i] = new double [M];
			y[i] = new double [M];
			z[i] = new double [M];
			c[i] = new double [M];

		}

		// set values
		linspace( xMin, xMax, N, xVec);
		linspace( yMin, yMax, M, yVec);
		double zmax = 0;
		for(int j = 0; j < M; j++)
		{
			for( int i = 0; i<N; i ++)
			{
				// Set x/y
				x[i][j] = xVec[i];
				y[i][j] = yVec[j];

				// compute 2D gaussian as z
				z[i][j] = (pow(x[i][j],2) + pow(y[i][j],2) )*zscale;
				if(z[i][j] > zmax)
				{
					zmax = z[i][j];
				}
			}
		}

		for(int j = 0; j < M; j++)
		{
			for( int i = 0; i<N; i ++)
			{

				c[i][j] = z[i][j];
			}
		}
	// VTK commands
	vtkSmartPointer<vtkActor> surfActor = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkDataSetMapper> surfMapper = vtkSmartPointer<vtkDataSetMapper>::New();

	// create actor
	/* add surface to actor
	 *
	 * 	void createSurfaceInActorAndMapperWithDefinedColors( double ** x, double ** y, double ** z, double ** c, int N, int M,
	 *		vtkSmartPointer<vtkActor> localActor, vtkSmartPointer<vtkDataSetMapper> localMapper,
	 *		double opacity, double ambientIdx, double ambientRedIdx, double ambientGreenIdx, double ambientBlueIdx );
	 */
	createSurfaceInActorAndMapperWithDefinedColors( x, y, z, c, N, M, surfActor, surfMapper, 0.5, 0.0, 1.0, 1.0, 1.0 );

	// set the color map
	setVTKColorMapParula( surfMapper );
	//setVTKColorMapBlackToRed(gaussianMapper);


	// create the camera
	rcVTK.camera->SetPosition(0, 0, 20);
	rcVTK.camera->SetFocalPoint(0, 0, 2);
	rcVTK.camera->SetRoll(-90);

	// Create a renderer, render window, and interactor


	rcVTK.renderer->SetActiveCamera(rcVTK.camera);

	// add actors
	rcVTK.renderer->AddActor(surfActor);



	// clean up
	delete [] xVec;
	delete [] yVec;
	for(int i = 0; i < N; i++)
	{
		delete [] x[i];
		delete [] y[i];
		delete [] z[i];
	}
	delete [] x;
	delete [] y;
	delete [] z;
}


/*
 * examples.cpp
 *
 *  Created on: Sep 18, 2018
 *      Author: brian
 */


#include "vtkFunctionLibrary_examples.hpp"

void plot2DGaussianSurface()
{

	// parameters
	int N = 150;
	int M = 150;

	double amp = 5.0;
	double sigma_x = 2;
	double sigma_y = 2;

	double xMin = -10;
	double xMax = 10;
	double yMin = -10;
	double yMax = 10;


	// local arrays
	double * xVec = new double [N];
	double * yVec = new double [M];

	double ** x = new double * [N];
	double ** y = new double * [N];
	double ** z = new double * [N];
	for(int i = 0; i < N; i++)
	{
		x[i] = new double [M];
		y[i] = new double [M];
		z[i] = new double [M];

	}

	// set values
	linspace( xMin, xMax, N, xVec);
	linspace( yMin, yMax, M, yVec);
	for(int j = 0; j < M; j++)
	{
		for( int i = 0; i<N; i ++)
		{
			// Set x/y
			x[i][j] = xVec[i];
			y[i][j] = yVec[j];

			// compute 2D gaussian as z
			z[i][j] = amp*exp( - ( pow(x[i][j],2)/(2*pow(sigma_x,2)) + pow(y[i][j],2)/(2*pow(sigma_y,2)) ) );
		}
	}


	// VTK commands

	// create actor
	vtkSmartPointer<vtkActor> gaussianActor = vtkSmartPointer<vtkActor>::New();

	// add surface to actor
	// void createSurfaceInActor( double ** x, double ** y, double ** z, int N, int M, vtkSmartPointer<vtkActor> localActor,
	//		double opacity, double redIdx, double greenIdx, double blueIdx, double ambientIdx, double ambientRedIdx, double ambientGreenIdx, double ambientBlueIdx )
	createSurfaceInActor( x, y, z, N, M, gaussianActor,	1, 0.8, 0.2, 0.2, 0.0, 0.0, 0.0, 0.0 );


	// create the camera
	vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
	camera->SetPosition(20, 20,10);
	camera->SetFocalPoint(0, 0, 0);
	camera->SetRoll(-105);


	// Set up the lighting.
	vtkSmartPointer<vtkLight> light1 = vtkSmartPointer<vtkLight>::New();
	light1->SetIntensity(1.2);
	light1->SetFocalPoint(0,0,0);
	light1->SetPosition(-20,20,20);
	light1->SetDiffuseColor(1.0,0.5,0.5);


	// Create a renderer, render window, and interactor
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

	// background color
	renderer->SetBackground(1,1,1); // Background color

	// antialiasing frames
	renderWindow->SetAAFrames(5);

	// set renderer
	renderWindow->AddRenderer(renderer);


	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindow-> SetSize (800, 800) ;
	renderer->AddActor(gaussianActor);
	renderer->SetActiveCamera(camera);
	renderer->AddLight(light1);

	renderWindow->Render();

	// Interactor that pauses the program for interactions with the VTK renderer
	renderWindowInteractor->Start();


	// export a png of the scene
	writeVTKpng( "2DGaussian.png", renderWindow );




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






void plot2DGaussianSurfaceWithColorMap()
{

	// parameters
	int N = 250;
	int M = 250;

	double amp = 5.0;
	double sigma_x = 2;
	double sigma_y = 2;

	double xMin = -10;
	double xMax = 10;
	double yMin = -10;
	double yMax = 10;


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
	for(int j = 0; j < M; j++)
	{
		for( int i = 0; i<N; i ++)
		{
			// Set x/y
			x[i][j] = xVec[i];
			y[i][j] = yVec[j];

			// compute 2D gaussian as z
			z[i][j] = amp*exp( - ( pow(x[i][j],2)/(2*pow(sigma_x,2)) + pow(y[i][j],2)/(2*pow(sigma_y,2)) ) );
			c[i][j] = 1-cos( 0.7*sqrt( pow(x[i][j],2) + pow(y[i][j],2) ) );
		}
	}


	// VTK commands

	// create actor
	vtkSmartPointer<vtkActor> gaussianActor = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkDataSetMapper> gaussianMapper = vtkSmartPointer<vtkDataSetMapper>::New();


	/* add surface to actor
	 *
	 * 	void createSurfaceInActorAndMapperWithDefinedColors( double ** x, double ** y, double ** z, double ** c, int N, int M,
	 *		vtkSmartPointer<vtkActor> localActor, vtkSmartPointer<vtkDataSetMapper> localMapper,
	 *		double opacity, double ambientIdx, double ambientRedIdx, double ambientGreenIdx, double ambientBlueIdx );
	 */
	createSurfaceInActorAndMapperWithDefinedColors( x, y, z, c, N, M, gaussianActor, gaussianMapper, 1, 0.0, 1.0, 1.0, 1.0 );

	// set the color map
	setVTKColorMapParula( gaussianMapper );
	//setVTKColorMapBlackToRed(gaussianMapper);




	// create the camera
	vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
	camera->SetPosition(20, 20,10);
	camera->SetFocalPoint(0, 0, 0);
	camera->SetRoll(-105);


	// Set up the lighting.
	vtkSmartPointer<vtkLight> light1 = vtkSmartPointer<vtkLight>::New();
	light1->SetIntensity(1.5);
	light1->SetFocalPoint(0,0,0);
	light1->SetPosition(-20,20,20);
	light1->SetDiffuseColor(1.0,1.0,1.0);


	// Create a renderer, render window, and interactor
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

	// background color
	renderer->SetBackground(1,1,1); // Background color

	// antialiasing frames
	renderWindow->SetAAFrames(5);

	// set renderer
	renderWindow->AddRenderer(renderer);


	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindow-> SetSize (800, 800) ;
	renderer->AddActor(gaussianActor);
	renderer->SetActiveCamera(camera);
	renderer->AddLight(light1);

	renderWindow->Render();

	// Interactor that pauses the program for interactions with the VTK renderer
	renderWindowInteractor->Start();


	// export a png of the scene
	writeVTKpng( "2DGaussianWithMap.png", renderWindow );




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

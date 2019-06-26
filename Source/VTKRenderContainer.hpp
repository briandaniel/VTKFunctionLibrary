/*
 * VTKRenderContainer.hpp
 *
 *  Created on: Oct 24, 2018
 *      Author: brian
 */

#ifndef VTKRENDERCONTAINER_HPP_
#define VTKRENDERCONTAINER_HPP_

// vtk headers
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkVertexGlyphFilter.h>

// local includes
#include "triangleStripFunctions.hpp"
#include "surfacePlotFunctions.hpp"
#include "generalVTKFunctions.hpp"
#include "vtkColorMaps.hpp"

// Utility function library includes
#include "UtilityFunctions/utilityFunctions.hpp"

class RenderContainerVTK {

  public:
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkRenderWindow> renderWindow;
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
	vtkSmartPointer<vtkCamera> camera;
	vtkSmartPointer<vtkLight> light1;


    void plotPoint(double x, double y, double z, double red, double green, double blue, double size );

	RenderContainerVTK()
	{


		camera = vtkSmartPointer<vtkCamera>::New();
		light1 = vtkSmartPointer<vtkLight>::New();
	    renderer = vtkSmartPointer<vtkRenderer>::New();
		renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
		renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();


		renderer->SetBackground(0.1,0.1,0.3); // Background color
		renderWindow-> SetSize (1200, 1200) ;
		renderWindow->AddRenderer(renderer);		// set renderer



		// Set up the lighting.
		light1->SetIntensity(1.0);
		light1->SetFocalPoint(0,0,0);
		light1->SetPosition(0,0,100);
		light1->SetDiffuseColor(1,1,1);
		renderer->AddLight(light1);


		// antialiasing frames
		// renderWindow->SetAAFrames(5);

		renderWindowInteractor->SetRenderWindow(renderWindow);

	}

};

// local functions
void plotParabolicSurf( double zscale, RenderContainerVTK & rcVTK );


#endif /* VTKRENDERCONTAINER_HPP_ */

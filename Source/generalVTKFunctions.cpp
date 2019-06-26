/*
 * generalVTKFunctions.cpp
 *
 *  Created on: Sep 18, 2018
 *      Author: brian
 */

#include "generalVTKFunctions.hpp"

void writeVTKpng( string pngFileName, vtkSmartPointer<vtkRenderWindow> renderWindow )
{
	//vtkSmartPointer<vtkImageWriter> writer = vtkSmartPointer<vtkImageWriter>::New();
	//	writer = vtkSmartPointer<vtkPNGWriter>::New();

	vtkSmartPointer<vtkImageWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
	vtkSmartPointer<vtkWindowToImageFilter> window_to_image_filter =vtkSmartPointer<vtkWindowToImageFilter>::New();

	window_to_image_filter->SetInput(renderWindow);
	window_to_image_filter->ReadFrontBufferOff();
	window_to_image_filter->Update();

	writer->SetFileName(pngFileName.c_str());
	writer->SetInputConnection(window_to_image_filter->GetOutputPort());
	writer->Write();

}







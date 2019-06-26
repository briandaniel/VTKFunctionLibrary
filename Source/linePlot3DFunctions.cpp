/*
 * linePlot3DFunctions.cpp
 *
 *  Created on: Jan 16, 2019
 *      Author: brian
 */



#include "linePlot3DFunctions.hpp"

void createLineInActor( vector<double> & xLine, vector<double> & yLine, vector <double> & zLine,
		vtkSmartPointer<vtkActor> localActor, double opacity, double redIdx, double greenIdx, double blueIdx )
{

	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

	double xyz[3] = {0,0,0};
	for(int i = 0; i < xLine.size(); i++)
	{
		xyz[0] = xLine[i];
		xyz[1] = yLine[i];
		xyz[2] = zLine[i];

		points->InsertNextPoint(xyz);
	}

	vtkSmartPointer<vtkPolyLine> polyLine =  vtkSmartPointer<vtkPolyLine>::New();
	polyLine->GetPointIds()->SetNumberOfIds(xLine.size());
	for(unsigned int i = 0; i < xLine.size(); i++)
	{
		polyLine->GetPointIds()->SetId(i,i);
	}

	// Create a cell array to store the lines in and add the lines to it
	vtkSmartPointer<vtkCellArray> cells =  vtkSmartPointer<vtkCellArray>::New();
	cells->InsertNextCell(polyLine);

	// Create a polydata to store everything in
	vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();

	// Add the points to the dataset
	polyData->SetPoints(points);

	// Add the lines to the dataset
	polyData->SetLines(cells);

	// Setup actor and mapper
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	#if VTK_MAJOR_VERSION <= 5
		mapper->SetInput(polyData);
	#else
		mapper->SetInputData(polyData);
	#endif

	localActor->SetMapper(mapper);


	localActor->GetProperty()->SetColor(redIdx, greenIdx, blueIdx);
	localActor->GetProperty()->SetOpacity(opacity);

}

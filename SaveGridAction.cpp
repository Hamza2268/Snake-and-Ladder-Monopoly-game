#include "SaveGridAction.h"
#include "Grid.h"
#include <iostream>
#include <fstream>

SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp)
{
}

void SaveGridAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Enter the filename to save the grid: ");
    fileName = pIn->GetSrting(pOut);

    pOut->ClearStatusBar();
}

void SaveGridAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();

    // Read filename
    ReadActionParameters();

    // Open the file for writing
    std::ofstream outfile(fileName);
    if (!outfile.is_open())
    {
        pOut->PrintMessage("Error: Could not open file to save the grid. Click to continue...");
        pOut->ClearStatusBar();
        return;
    }
    std::cout << "Saving ladders..." << std::endl;
    // Save ladders, snakes, and cards
    pGrid->SaveAll(outfile, LaddersType); // Save ladders
    pGrid->SaveAll(outfile, SnakesType);  // Save snakes
    pGrid->SaveAll(outfile, CardsType);   // Save cards

    // Close the file
    outfile.close();

    pOut->PrintMessage("Grid saved successfully to " + fileName + ". Click to continue...");
    pOut->ClearStatusBar();
}

SaveGridAction::~SaveGridAction()
{
}

#include "OpenGridAction.h"
#include "Grid.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include <fstream>

OpenGridAction::OpenGridAction(ApplicationManager* pApp) : Action(pApp)
{
}

void OpenGridAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Enter the filename to load the grid: ");
    fileName = pIn->GetSrting(pOut);

    pOut->ClearStatusBar();
}

void OpenGridAction::Execute()
{
    // Read file name
    ReadActionParameters();
    //Check if filename is empty
    if (fileName.empty())
        return;

    std::ifstream infile(fileName);
    if (!infile.is_open())
    {
        Grid* pGrid = pManager->GetGrid();
        pGrid->PrintErrorMessage("Error: Could not open file. Click to continue...");
        return;
    }

    // Clear the current grid
    Grid* pGrid = pManager->GetGrid();
    pGrid->ClearGrid();

    // Load ladders, snakes, and cards from the file
    pGrid->LoadAll(infile, LaddersType);
    pGrid->LoadAll(infile, SnakesType);
    pGrid->LoadAll(infile, CardsType);

    // Close file and display success message
    infile.close();
    pGrid->PrintErrorMessage("Grid loaded successfully. Click to continue...");
}

OpenGridAction::~OpenGridAction()
{
}


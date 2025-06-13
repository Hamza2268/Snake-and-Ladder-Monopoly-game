#include "AddSnakeAction.h"

#include "Input.h"
#include "Output.h"
#include "Snake.h"

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces and Grid
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();


	while (!startPos.IsValidCell()) //Checks the validaty of startPos
	{
		pOut->PrintMessage("Invalid start cell! Ensure it's valid.Click again.");
		startPos = pIn->GetCellClicked();
	}
	while (startPos.VCell() == 8) //Checks if startPos is in the first row
	{
		pOut->PrintMessage("Invalid start cell! Ensure it's not in the first row. Click again.");
		startPos = pIn->GetCellClicked();
	}
	while (!pGrid->IsCellValidForStart(startPos)) //Checks if StartPos contain another object
	{
		pOut->PrintMessage("Invalid start cell! Ensure it doesn't contain another object. Click again.");
		startPos = pIn->GetCellClicked();
	}
	

	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

	while (!endPos.IsValidCell()) //Checks the validaty of endPos
	{
		pOut->PrintMessage("Invalid end cell! Ensure it's valid. Click again.");
		endPos = pIn->GetCellClicked();
	}
	while (endPos.HCell() != startPos.HCell()) //Checks if start and end in the same column
	{
		pOut->PrintMessage("Invalid end cell! Ensure it's in the same column. Click again.");
		endPos = pIn->GetCellClicked();
	}
	while (startPos.VCell() >= endPos.VCell()) //Checks if start is above end
	{
		pOut->PrintMessage("Invalid end cell! Ensure it's under the start cell. Click again.");
		endPos = pIn->GetCellClicked();
	}
	while (pGrid->IsEndCellStartOfAnotherObject(endPos)) 
	{
		pOut->PrintMessage("End cell can not be the start of another ladder or snake. Click again.");
		endPos = pIn->GetCellClicked();
	}
	///TODO: Make the needed validations on the read parameters (DONE)

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddSnakeAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	Snake* pTempSnake = new Snake(startPos, endPos);
	
	if (pGrid->IsOverlapping(pTempSnake))
	{
		pGrid->PrintErrorMessage("Error: Overlapping with an existing ladder or snake!...");
		delete pTempSnake;
		return;
	}
	// Create a Snake object with the parameters read from the user
	Snake* pSnake = new Snake(startPos, endPos);

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pSnake);
	// if the GameObject cannot be added
	
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the Snake is created and added to the GameObject of its Cell, so we finished executing the AddSnakeAction
}


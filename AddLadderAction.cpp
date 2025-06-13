#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces and Grid
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	
	//Check if it is invalid
	while(!startPos.IsValidCell())
	{
		pOut->PrintMessage("Invalid start cell! Ensure it's valid.Click again.");
		startPos = pIn->GetCellClicked();
	}
	 while(startPos.VCell() == 0) //Check if StartPos in the last row
	{
		pOut->PrintMessage("Invalid start cell! Ensure it's not in the last row. Click again.");
		startPos = pIn->GetCellClicked();
	}
	 while (!pGrid->IsCellValidForStart(startPos))
	{
		pOut->PrintMessage("Invalid start cell! Ensure it doesn't contain another object. Click again.");
		startPos = pIn->GetCellClicked();
	}
	 while (startPos.VCell() == 8 && startPos.HCell() == 0) //Checks that the start of the ladder not in the start of the game
	 {
		 pOut->PrintMessage("Invalid start cell! Click again.");
		 startPos = pIn->GetCellClicked();
	 }

	 // Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

	//Check if it is invalid
	while (!endPos.IsValidCell())
	{
		pOut->PrintMessage("Invalid end cell! Ensure it's valid. Click again.");
		endPos = pIn->GetCellClicked();
	}
	 while (endPos.HCell() != startPos.HCell()) //Checks is start and end not in the same column
	{
		pOut->PrintMessage("Invalid end cell! Ensure it's in the same column. Click again.");
		endPos = pIn->GetCellClicked();
	}
     while (startPos.VCell() <= endPos.VCell()) //Checks if endPos is above the startPos
	{
		pOut->PrintMessage("Invalid end cell! Ensure it's above the start cell. Click again.");
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
void AddLadderAction::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	Ladder* pTempLadder = new Ladder(startPos, endPos);

	if (pGrid->IsOverlapping(pTempLadder))
	{
		pGrid->PrintErrorMessage("Error: Overlapping with an existing ladder or snake!...");
		delete pTempLadder;
		return;
	}
	// Create a Ladder object with the parameters read from the user
	Ladder * pLadder = new Ladder(startPos, endPos);
	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pLadder);
	
	// if the GameObject cannot be added
	if (! added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}

#include "InputDiceValueAction.h"

#include "Grid.h"
#include "Player.h"

InputDiceValueAction::InputDiceValueAction(ApplicationManager* pApp) :Action(pApp)
{
}

void InputDiceValueAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pInp = pGrid->GetInput();
	Output* pOutp = pGrid->GetOutput();


	pOutp->PrintMessage("Enter Dice Number: ");
	InputDiceValue = pInp->GetInteger(pOutp);
	while (InputDiceValue > 6 || InputDiceValue < 1)  // Checking the input is Ranging From 1 to 6
	{
		pOutp->PrintMessage("Invalid ,Please Enter a Number Ranging between 1 to 6 !");
		InputDiceValue = pInp->GetInteger(pOutp);
	}


}

void InputDiceValueAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOutp = pGrid->GetOutput();
	if (!(pGrid->GetEndGame()))		// Check the Game is not Over
	{
		ReadActionParameters();     // Read the input dice value from te user
		Player* currentPlayer = pGrid->GetCurrentPlayer();   //Get a Pointer on the current player to move
		pOutp->PrintMessage("Your Input :"+to_string(InputDiceValue));
		currentPlayer->Move(pGrid, InputDiceValue);
		pGrid->AdvanceCurrentPlayer();
	}
	else
	{
		Input* pInp = pGrid->GetInput();	// In case the Game Ended
		
		pOutp->PrintMessage("Oops ,Game Over !");
		pInp->GetCellClicked();
	}
}

InputDiceValueAction::~InputDiceValueAction()
{
}


#include "RollDiceAction.h"

#include "Grid.h"
#include "Player.h"

#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager* pApp) : Action(pApp)
{
}

void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}

void RollDiceAction::Execute()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Player* currentPlayer = pGrid->GetCurrentPlayer();
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action

	if (!(pGrid->GetEndGame()))   // Check Game did not End
		// -- If not ended, do the following --:
	{

		// 2- Generate a random number from 1 to 6 --> This step is done for you
		srand((int)time(NULL)); // time is for different seed each run
		int diceNumber = 1 + rand() % 6; // from 1 to 6 --> should change seed

		if (!currentPlayer->GetPoison())  // To Valide Special Attack "Poison"
		{

			pOut->PrintMessage("Your Dice Value is " + to_string(diceNumber));
		}
		else
		{
			// Applying Poison By Reducing Roll Value by 1
			pOut->PrintMessage("Your Dice Value is " + to_string(diceNumber) + " ,Applying Poison to be " + to_string(diceNumber - 1));
			diceNumber--;
		}
		// 3- Get the "current" player from pGrid
		currentPlayer->Move(pGrid, diceNumber);
		// 4- Move the currentPlayer using function Move of class player

		// 5- Advance the current player number of pGrid
		pGrid->AdvanceCurrentPlayer();
	}
	else
	{
		pGrid->PrintErrorMessage("GameOver !");  //In case the Game Ended
	}
	// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).

}

RollDiceAction::~RollDiceAction()
{
}

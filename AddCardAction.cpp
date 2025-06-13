#include "AddCardAction.h"

#include "Input.h"
#include "Output.h"
#include"Card.h"
#include "CardOne.h"
#include"CardTwo.h"
#include"CardThree.h"
#include"CardFour.h"
#include"CardFive.h"
#include"CardSix.h"
#include"Card7.h"
#include"CardEight.h"
#include"Card9.h"
#include"CardTen.h"
#include"Card11.h"
#include"Card12.h"
#include"Card13.h"


AddCardAction::AddCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters() //Reads card number and gets valid position from user
{

	

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();



	// 2- Read the "cardNumber" parameter and set its position
	pOut->PrintMessage("Type card number: ");
	cardNumber = pIn->GetInteger(pOut);

	if (cardNumber < 1 || cardNumber>14)
	{
		pGrid->PrintErrorMessage("Invalid Card Number,Click to continue");
		return;

	}
	else {
		pOut->PrintMessage("Click on the cell you desire : ");
		cardPosition = pIn->GetCellClicked();

		while (!cardPosition.IsValidCell() || cardPosition.GetCellNumFromPosition(cardPosition) == 1)
		{
			pGrid->PrintErrorMessage("Invalid cell Position,Please choose valid cell");
			cardPosition = pIn->GetCellClicked();
		}
	}
	pOut->ClearStatusBar();
	
}

void AddCardAction::Execute()// calls ReadParameters function to get card number and creats new card based on card number
{

	Grid* pGrid = pManager->GetGrid();
	
	ReadActionParameters();

	Card* pCard = NULL; // will point to the card object type
	switch (cardNumber)
	{
	case 1:
		pCard = new CardOne(cardPosition);
		break;
	case 2:
		pCard = new CardTwo(cardPosition);
		break;
	case 3:
		pCard = new CardThree(cardPosition);
		break;
	case 4:
		pCard = new CardFour(cardPosition);
		break;
	case 5:
		pCard = new CardFive(cardPosition);
		break;
	case 6:
		pCard = new CardSix(cardPosition);
		break;
	case 7:
		pCard = new Card7(cardPosition);
		break;
	case 8:
		pCard = new CardEight(cardPosition);
		break;
	case 9:
		pCard = new Card9(cardPosition);
		break;
	case 10:
		pCard = new CardTen(cardPosition);
		break;
	case 11:
		pCard = new Card11(cardPosition);
		break;
	case 12:
		pCard = new Card12(cardPosition);
		break;
	case 13:
		pCard = new Card13(cardPosition);
		break;




		// A- Add the remaining cases

	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)

	if (pCard)
	{
		pCard->ReadCardParameters(pGrid);

		if (!pGrid->AddObjectToCell(pCard) && cardPosition.IsValidCell())//checks that cell is available to place card
		{
			pGrid->PrintErrorMessage("The cell already has another gameobject");
		}
		
	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}
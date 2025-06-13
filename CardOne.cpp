#include "CardOne.h"

CardOne::CardOne(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
}

CardOne::~CardOne(void)
{
}

void CardOne::ReadCardParameters(Grid * pGrid)//reads wallrt amount
{
	
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Input* piN = pGrid->GetInput();
	Output* pouT = pGrid->GetOutput();
	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."
	pouT->PrintMessage("New CardOne, Enter its wallet amount: ");
		
	this->walletAmount =piN->GetInteger(pouT);
	

	// [ Note ]:
	// In CardOne, the only parameter of CardOne is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar
	pouT->ClearStatusBar();
}

void CardOne::Apply(Grid* pGrid, Player* pPlayer)//applies on player
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid,pPlayer);
	// 2- Decrement the wallet of pPlayer by the walletAmount data member of CardOne
	int currentWallet = pPlayer->GetWallet();
	pPlayer->SetWallet(currentWallet- walletAmount);
}
void CardOne::Save(std::ofstream& outfile, ObjectType type)// saves wallet amount
{
	if (type == CardsType)  // Save only if the object is of type CARD
	{
		outfile << cardNumber << " " << position.GetCellNum() << " " << walletAmount << endl;
	}

}
void CardOne::Load(ifstream& Infile)//loads
{
	// Load only if the object is of type CARD
	{
		Card::Load(Infile);
		int w;
		Infile >> w;
		walletAmount = w;
	}
}

bool CardOne::IsOverlapping(GameObject* newObj) const
{
	return false;
}
void CardOne::EditParameters(Grid* pGrid)
{
	// Get pointers to Input and Output interfaces
	Input* pInput = pGrid->GetInput();
	Output* pOutput = pGrid->GetOutput();

	// Print a message to inform the user about the edit action
	pOutput->PrintMessage("Editing CardOne: Enter new wallet amount to deduct...");

	// Read the new wallet amount from the user
	int newWalletAmount = pInput->GetInteger(pOutput);
	while (newWalletAmount < 0) // Ensure the wallet amount is non-negative
	{
		pOutput->PrintMessage("Invalid amount. Please enter a valid value:");
		newWalletAmount = pInput->GetInteger(pOutput);
	}

	walletAmount = newWalletAmount;

	// Clear the status bar
	pOutput->ClearStatusBar();
}
void CardOne::SetWalletAmount(int w)
{
	walletAmount = w;
}
int CardOne::GetWalletAmount()
{
	return walletAmount;
}

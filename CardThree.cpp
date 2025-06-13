#include "CardThree.h"
#include"Ladder.h"


CardThree::CardThree(const CellPosition& pos) : Card(pos) {
	
		cardNumber = 3;
}
CardThree::~CardThree(void)
{
}

void CardThree::Apply(Grid* pGrid, Player* pPlayer) //checks next ladder then applies moving player if found
{

	Card::Apply(pGrid, pPlayer); //to print msg

	Ladder* NextLadder=pGrid->GetNextLadder(this->GetPosition());

	if (NextLadder) {
		
		pGrid->UpdatePlayerCell(pPlayer, NextLadder->GetPosition());
		NextLadder->Apply(pGrid, pPlayer);
		pGrid->PrintErrorMessage("Card3: You've been moved to the start of the next ladder!");
	}
	else
	{
		pGrid->PrintErrorMessage("Card3: No Ladders found ahead!");
	}
}
void CardThree::Save(std::ofstream& outfile, ObjectType type)
{
	Card::Save(outfile, type);
	outfile << endl;
}

void CardThree::Load(ifstream& Infile) 
{

		Card::Load(Infile);
}
bool CardThree::IsOverlapping(GameObject* newObj) const
{
	return false;
}
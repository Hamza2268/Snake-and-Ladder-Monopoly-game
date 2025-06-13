#include "CardFour.h"
#include"Snake.h"


CardFour::CardFour(const CellPosition& pos) : Card(pos) {

	cardNumber = 4;
}
CardFour::~CardFour(void)
{
}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)//checks next snake  then applies moving player if found
{

	Card::Apply(pGrid, pPlayer); //to print msg 

	Snake* NextSnake = pGrid->GetNextSnake(this->GetPosition());

	if (NextSnake) {

		pGrid->UpdatePlayerCell(pPlayer, NextSnake->GetPosition());
		NextSnake->Apply(pGrid, pPlayer);
		pGrid->PrintErrorMessage("Card3: You've been moved to the start of the next snake!");
	}
	else
	{
		pGrid->PrintErrorMessage("Card3: No Snakes found ahead!");
	}
}
void CardFour::Save(std::ofstream& outfile, ObjectType type)
{
	Card::Save(outfile, type);
	outfile << endl;
}
void CardFour::Load(ifstream& Infile) {

		Card::Load(Infile);
}
bool CardFour::IsOverlapping(GameObject* newObj) const
{
	return false;
}

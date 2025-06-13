#include "CardSix.h"

CardSix::CardSix(const CellPosition& pos) :Card(pos)  // set the cell position of the card
{
	cardNumber = 6;  // set the inherited cardNumber data member with the card number (6 here)
}

void CardSix::ReadCardParameters(Grid* pGrid)   //No parameters are Needed
{
}

void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);

	pPlayer->Move(pGrid, -(pPlayer->GetjustRolledDiceNum()));
	pPlayer->SetTurnCount(pPlayer->GetTurnCount() - 1);
}

CardSix::~CardSix()
{
}

void CardSix::Draw(Output* pOut) const
{
	pOut->DrawCell(position, cardNumber);
}


bool CardSix::IsOverlapping(GameObject* newObj) const
{
	return false;
}
void CardSix::Save(std::ofstream& outfile, ObjectType type)
{
	Card::Save(outfile, type);
	outfile<< endl;
}

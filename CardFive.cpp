#include "CardFive.h"

CardFive::CardFive(const CellPosition& pos) :Card(pos)  // set the cell position of the card
{
	cardNumber = 5;  // set the inherited cardNumber data member with the card number (5 here)
}

void CardFive::ReadCardParameters(Grid* pGrid)  //No parameters are Needed
{
}

void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);

	pPlayer->Move(pGrid, pPlayer->GetjustRolledDiceNum());
	pPlayer->SetTurnCount(pPlayer->GetTurnCount() - 1);
}

CardFive::~CardFive()
{
}

void CardFive::Draw(Output* pOut) const
{
	pOut->DrawCell(position, cardNumber);
}

bool CardFive::IsOverlapping(GameObject* newObj) const
{
	return false;
}

void CardFive::Save(std::ofstream& outfile, ObjectType type)
{
	Card::Save(outfile, type);
	outfile << endl;
}

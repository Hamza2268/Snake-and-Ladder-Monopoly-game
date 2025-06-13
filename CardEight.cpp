#include "CardEight.h"

CardEight::CardEight(const CellPosition& pos) : Card(pos)
{
	cardNumber = 8;   // set the inherited cardNumber data member with the card number (8 here)
}

void CardEight::ReadCardParameters(Grid* pGrid)   //No parameters are Needed
{
}

void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	if (pPlayer->GetjustRolledDiceNum())
	{
		pPlayer->SetjustRolledDiceNum(0);
	}
	 pPlayer->SetjustRolledDiceNum(0); 
}

CardEight::~CardEight()
{
}

void CardEight::Draw(Output* pOut) const
{
	pOut->DrawCell(position, cardNumber);
}

void CardEight::Save(std::ofstream& outfile, ObjectType type)
{
	Card::Save(outfile, type);
	outfile << endl;
}

bool CardEight::IsOverlapping(GameObject* newObj) const
{
	return false;
}
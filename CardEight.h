#pragma once

#include "Card.h"


class CardEight : public Card
{
public:
	CardEight(const CellPosition& pos);  // A Constructor takes card position
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);  // Applies the effect of CardFive on the passed Player 
													   // By Preventing the player from rolling the next turn
	virtual ~CardEight();  // A Virtual Destructor
	void Draw(Output* pOut) const;  // To Draw the Card
	virtual void Save(std::ofstream& outfile, ObjectType type);  // Saves card data
	virtual bool IsOverlapping(GameObject* newObj) const;
};


#pragma once

#include "Card.h"


class CardFive : public Card
{
	// No data members are Needed
public:
	CardFive(const CellPosition& pos);  // A Constructor takes card position
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardFive on the passed Player 
													  // By Moving Player forward by the same number of steps that just rolled 
	virtual ~CardFive();  // A Virtual Destructor
	void Draw(Output* pOut) const;  // To Draw the Card
	virtual bool IsOverlapping(GameObject* newObj) const;   
	virtual void Save(std::ofstream& outfile, ObjectType type);  // Saves card data
};

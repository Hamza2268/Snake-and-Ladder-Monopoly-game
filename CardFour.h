#pragma once
#include"Card.h"


class CardFour:public Card
{
public:
	CardFour(const CellPosition& pos);
	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void Save(std::ofstream& outfile, ObjectType type); // Saves card data
	virtual void Load(ifstream& Infile);

	virtual ~CardFour();
	virtual bool IsOverlapping(GameObject* newObj) const;
};


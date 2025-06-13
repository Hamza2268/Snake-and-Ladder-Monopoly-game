#pragma once
#include"Card.h"

class CardThree:public Card
{
public:
	CardThree(const CellPosition& pos);
	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual void Save(std::ofstream& outfile, ObjectType type); // Saves card data
	virtual void Load(ifstream& Infile);
	virtual bool IsOverlapping(GameObject* newObj) const;
	virtual ~CardThree();
};


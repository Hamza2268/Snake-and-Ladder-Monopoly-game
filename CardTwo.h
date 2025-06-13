#pragma once

#include "Card.h"
class CardTwo:public Card
{	// CardTwo Parameters:
	int walletAmount; // the wallet value to increase to the player

public:
	CardTwo(const CellPosition& pos); // A Constructor takes card position
	void EditParameters(Grid* pGrid);
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount
	void SetWalletAmount(int w);
	int GetWalletAmount();
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
	// by decrementing the player's wallet by the walletAmount data member
	virtual void Save(std::ofstream& outfile, ObjectType type); // Saves card data
	virtual void Load(ifstream& Infile);
 	// Loads and Reads the GameObject parameters from the file
	virtual ~CardTwo(); // A Virtual Destructor
	virtual bool IsOverlapping(GameObject* newObj) const;
};


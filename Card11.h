#pragma once
#include "Card.h"
class Card11 :
    public Card
{

	static int Price;
	static int Fees;
	static bool Initialized;
	static Player* Owner;
	static bool SavedOnce;
	static bool OpenOnce;
public:
	Card11(const CellPosition& pos);

	void setPrice(int x);

	void setFees(int y);
	int GetPrice();
	int GetFees();
	virtual void ReadCardParameters(Grid* pGrid); // Reads card parameters once

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies card effect
	virtual void Save(std::ofstream& outfile, ObjectType type); // Saves card data
	virtual void Load(ifstream& InFile); // Loads card data

	virtual bool IsOverlapping(GameObject* newObj) const;

	void EditParameters(Grid* pGrid);

	virtual ~Card11(); // Destructor
	void Reset();

	static void setSavedOnce(bool s);
	static void setOpenOnce(bool s);

};


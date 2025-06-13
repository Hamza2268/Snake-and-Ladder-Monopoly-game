#pragma once
#include"Card.h"

class CardTen:public Card
{
	static int Price;
	static int Fees;
	static bool Initialized;
	static Player* Owner;
	static bool SavedOnce;
	static bool OpenOnce;

public:	
	CardTen(const CellPosition& pos);

	void setPrice(int x);

	void setFees(int y);
	int GetPrice();
	int GetFees();

	virtual bool IsOverlapping(GameObject* newObj) const;

	virtual void ReadCardParameters(Grid* pGrid) ; // Reads card parameters once

	virtual void Apply(Grid* pGrid, Player* pPlayer) ; // Applies card effect

	virtual void Save(std::ofstream& outfile, ObjectType type); // Saves card data
	virtual void Load(ifstream& InFile) ; // Loads card data

	void EditParameters(Grid* pGrid);
	virtual ~CardTen(); // Destructor

	void Reset();

	static void setSavedOnce(bool s);
	static void setOpenOnce(bool s);

};


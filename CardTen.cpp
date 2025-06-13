#include "CardTen.h"


int CardTen::Price = 0;
int CardTen::Fees = 0;
bool CardTen::Initialized = false;
Player* CardTen::Owner = nullptr;
bool CardTen::SavedOnce = false;
bool CardTen::OpenOnce = false;

CardTen::CardTen(const CellPosition& pos) : Card(pos) {

	cardNumber = 10;
    SavedOnce = 0;
}

CardTen::~CardTen()
{
   
}

int CardTen::GetPrice()
{
    return Price;
}

int CardTen::GetFees()
{
    return Fees;
}
void CardTen::setPrice(int x) {
	if (x >= 0) Price = x;
}

void CardTen::setFees(int x) {
	if (x >= 0) Fees= x;
}

void CardTen::ReadCardParameters(Grid* pGrid)// Reads from user Valid price and fees for card
{
	if (!Initialized) {
		Input* piN = pGrid->GetInput();
		Output* pouT = pGrid->GetOutput();


		pouT->PrintMessage("New CardTen, Enter the station price: ");
		int cprice = piN->GetInteger(pouT);
		

        while (cprice <= 0)
        {
            pouT->PrintMessage("Invalid :New CardTen, Enter the station price: ");
             cprice = piN->GetInteger(pouT);
        }
        setPrice(cprice);

		pouT->PrintMessage("New CardTen, Enter the station fees: ");
		int cfees = piN->GetInteger(pouT);
		

        while (cfees <= 0)
        {
            pouT->PrintMessage("Invalid :New CardTen, Enter the station fees: ");
             cfees = piN->GetInteger(pouT);
        }
        setFees(cfees);

		Initialized = true;

		pouT->ClearStatusBar();
	}

}

void CardTen::Apply(Grid* pGrid, Player* pPlayer)//Applys during the game to give option to buy card if not owned 
//and deducts fees if owned and adds it to the owner
{

	Card::Apply(pGrid, pPlayer);

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

    if (Owner == nullptr)
    {
        pOut->PrintMessage("Do you want to buy Card10? (Price: "+to_string(Price)+") (Y/N)");
        string choice = pIn->GetSrting(pOut);

        while (!(choice == "Y" || choice == "y" || choice == "N" || choice == "n")) {

            pOut->PrintMessage("Please enter valid Answer ,Do you want to buy Card10? (Price: " + to_string(Price) + ") (Y/N)");
            choice = pIn->GetSrting(pOut);
        }

        if (choice == "Y" || choice == "y")
        {
            if (pPlayer->GetWallet() >= Price)
            {
                pPlayer->SetWallet(pPlayer->GetWallet() - Price);
                Owner = pPlayer;
                pOut->PrintMessage("You bought all Card10 stations!");
            }
            else
            {
                pOut->PrintMessage("Insufficient wallet amount to buy the station.");
            }
        }
        else if (choice == "N" || choice == "n")
        {
            pOut->PrintMessage("Didn't buy station");
           
        }

    }
    else if (Owner != pPlayer) 
    {
        pOut->PrintMessage("This station is owned. You must pay fees!");
        if (pPlayer->GetWallet() - Fees > 0)
            Owner->SetWallet(Owner->GetWallet() + Fees);
        else
            Owner->SetWallet(Owner->GetWallet() + pPlayer->GetWallet());
        pPlayer->SetWallet(pPlayer->GetWallet() - Fees);
    }
    else
    {
        pOut->PrintMessage("You already own this station.");
    }
}


void CardTen::Save(std::ofstream& outfile, ObjectType type)//saves special parameters
{
    if (!SavedOnce)
    {
        Card::Save(outfile, type); outfile << " " << Price << " " << Fees << endl;
        SavedOnce = true;
    }
    else
    {
        Card::Save(outfile, type);
        outfile << endl;
    }

}

void CardTen::Load(ifstream& InFile)// loads special parameters
{
    Card::Load(InFile);
    if (!OpenOnce)
    {
        int p, f;
        InFile >> p >> f;
        setPrice(p);
        setFees(f);
        OpenOnce = true;
    }
}
bool CardTen::IsOverlapping(GameObject* newObj) const
{
    return false;
}
void CardTen::EditParameters(Grid* pGrid)//rereads valid parameters for editimg card
{
    // Get pointers to Input and Output interfaces
    Input* pInput = pGrid->GetInput();
    Output* pOutput = pGrid->GetOutput();

    // Print a message to inform the user about the edit action
    pOutput->PrintMessage("Editing CardTen: Enter new card price...");

    // Read the new price from the user
    int newPrice = pInput->GetInteger(pOutput);
    while (newPrice < 0) // Ensure the price is positive
    {
        pOutput->PrintMessage("Invalid price. Please enter a positive value:");
        newPrice = pInput->GetInteger(pOutput);
    }

    // Print a message to enter the new fees
    pOutput->PrintMessage("Enter new fees for CardTen...");
    int newFees = pInput->GetInteger(pOutput);
    while (newFees < 0) // Ensure the fees are positive
    {
        pOutput->PrintMessage("Invalid fees. Please enter a positive value:");
        newFees = pInput->GetInteger(pOutput);
    }

    // Update the card's data members
    setPrice(newPrice);
    setFees(newFees);

    // Clear the status bar
    pOutput->ClearStatusBar();
}
void CardTen::Reset()// resets owner to none for new game
{
   
    Owner = nullptr;
    Initialized = false;
}

void CardTen::setSavedOnce(bool s)//so it doesn't save price amd fees for all cards
{
    SavedOnce = s;
}

void CardTen::setOpenOnce(bool s)//so it doesn't load price and fees more than once
{
    OpenOnce = s;
}

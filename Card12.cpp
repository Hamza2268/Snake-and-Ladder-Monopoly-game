#include "Card12.h"


int Card12::Price = 0;
int Card12::Fees = 0;
bool Card12::Initialized = false;
Player* Card12::Owner = nullptr;
bool Card12::SavedOnce = false;
bool Card12::OpenOnce=false;

Card12::Card12(const CellPosition& pos) : Card(pos) {

    cardNumber = 12;
}
Card12::~Card12()
{

}
int Card12::GetPrice()
{
    return Price;
}

int Card12::GetFees()
{
    return Fees;
}
void Card12::setPrice(int x) {
    if (x >= 0) Price = x;
}

void Card12::setFees(int x) {
    if (x >= 0) Fees = x;
}
//all functions same as cards 10 &11
void Card12::ReadCardParameters(Grid* pGrid)// Reads from user Valid price and fees for card
{
    if (!Initialized) {
        Input* piN = pGrid->GetInput();
        Output* pouT = pGrid->GetOutput();


        pouT->PrintMessage("New Card12, Enter the station price: ");
        int cprice = piN->GetInteger(pouT);

        while (cprice <= 0)
        {
            pouT->PrintMessage("Invalid :New Card12, Enter the station price: ");
             cprice = piN->GetInteger(pouT);
        }
        setPrice(cprice);

        pouT->PrintMessage("New Card12, Enter the station fees: ");
        int cfees = piN->GetInteger(pouT);

        while (cfees <= 0)
        {
            pouT->PrintMessage("Invalid :New Card12, Enter the station fees: ");
             cfees = piN->GetInteger(pouT);
        }
        setFees(cfees);

        Initialized = true;
        pouT->ClearStatusBar();
    }

}

void Card12::Apply(Grid* pGrid, Player* pPlayer)//Applys during the game to give option to buy card if not owned 
//and deducts fees if owned and adds it to the owner
{

    Card::Apply(pGrid, pPlayer);

    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    if (Owner == nullptr)
    {
        pOut->PrintMessage("Do you want to buy Card12? (Price: " + to_string(Price) + ") (Y/N)");
        string choice = pIn->GetSrting(pOut);

        while (!(choice == "Y" || choice == "y" || choice == "N" || choice == "n")) {

            pOut->PrintMessage("Please enter valid Answer ,Do you want to buy Card12? (Price: " + to_string(Price) + ") (Y/N)");
            choice = pIn->GetSrting(pOut);
        }

        if (choice == "Y" || choice == "y")
        {
            if (pPlayer->GetWallet() >= Price)
            {
                pPlayer->SetWallet(pPlayer->GetWallet() - Price);
                Owner = pPlayer;
                pOut->PrintMessage("You bought all Card12 stations!");
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


void Card12::Save(std::ofstream& outfile, ObjectType type)//saves special parameters as price and fees if not saved before
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

void Card12::Load(ifstream& InFile)//loads special parameters as price and fees if not loaded before
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
bool Card12::IsOverlapping(GameObject* newObj) const
{
    return false;
}
void Card12::EditParameters(Grid* pGrid)// rereads from user Valid price and fees for card and edits them
{
    // Get pointers to Input and Output interfaces
    Input* pInput = pGrid->GetInput();
    Output* pOutput = pGrid->GetOutput();

    // Print a message to inform the user about the edit action
    pOutput->PrintMessage("Editing Card12: Enter new card price...");

    // Read the new price from the user
    int newPrice = pInput->GetInteger(pOutput);
    while (newPrice < 0) // Ensure the price is positive
    {
        pOutput->PrintMessage("Invalid price. Please enter a positive value:");
        newPrice = pInput->GetInteger(pOutput);
    }

    // Print a message to enter the new fees
    pOutput->PrintMessage("Enter new fees for Card12...");
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

void Card12::Reset()//resets owner to none for a new game
{
    
    Owner = nullptr;
    Initialized = false;
}

void Card12::setSavedOnce(bool s)//so it doesn't save price amd fees for all cards
{
    SavedOnce = s;
}

void Card12::setOpenOnce(bool s)//so it doesn't load price and fees more than once
{
    OpenOnce = s;
}

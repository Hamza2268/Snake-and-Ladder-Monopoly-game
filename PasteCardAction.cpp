#include "PasteCardAction.h"
#include "Grid.h"
#include "Card.h"
#include "Input.h"
#include "Output.h"
#include"Ladder.h"
#include"Snake.h"

#include"CardOne.h"
#include"CardTwo.h"
#include"CardThree.h"
#include"CardFour.h"
#include"CardFive.h"
#include"CardSix.h"
#include"Card7.h"
#include"CardEight.h"
#include"Card9.h"
#include"CardTen.h"
#include"Card11.h"
#include"Card12.h"
#include"Card13.h"

PasteCardAction::PasteCardAction(ApplicationManager* pApp) : Action(pApp)
{
}

void PasteCardAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Paste Card: Click on the destination cell ...");

    destinationCell = pIn->GetCellClicked();

    if (!destinationCell.IsValidCell())
    {
        pOut->PrintMessage("Invalid cell! Operation cancelled.");
        destinationCell.SetVCell(-1);
    }
    else
    {
        pOut->ClearStatusBar();
    }
}

void PasteCardAction::Execute()
{
    ReadActionParameters();

    if (!destinationCell.IsValidCell())
        return;

    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();

    // Check if the destination cell already contains a GameObject
    GameObject* pGameObject = pGrid->GetGameObjectFromCell(destinationCell);
    if (pGameObject)
    {
        if (dynamic_cast<Card*>(pGameObject) || dynamic_cast<Ladder*>(pGameObject) || dynamic_cast<Snake*>(pGameObject))
        {
            pOut->PrintMessage("The destination cell already contains a card, ladder, or snake. Operation cancelled.");
            return;
        }
    }

    // Retrieve the card to paste from the clipboard
    Card* pCardToPaste = pGrid->GetClipboard();
    if (!pCardToPaste)
    {
        pOut->PrintMessage("Clipboard is empty. No card to paste.");
        return;
    }

    // Create a new card based on the type of the card to paste
    Card* pNewCard = nullptr;
    int cardNumber = pCardToPaste->GetCardNumber();

    if (dynamic_cast<CardOne*>(pCardToPaste))
    {
        CardOne* pOriginalCardOne = dynamic_cast<CardOne*>(pCardToPaste);
        pNewCard = new CardOne(destinationCell);
        dynamic_cast<CardOne*>(pNewCard)->SetWalletAmount(pOriginalCardOne->GetWalletAmount());
    }
    else if (dynamic_cast<CardTwo*>(pCardToPaste))
    {
        CardTwo* pOriginalCardTwo = dynamic_cast<CardTwo*>(pCardToPaste);
        pNewCard = new CardTwo(destinationCell);
        dynamic_cast<CardTwo*>(pNewCard)->SetWalletAmount(pOriginalCardTwo->GetWalletAmount());
    }
    else if (dynamic_cast<CardThree*>(pCardToPaste))
    {
        CardThree* pOriginalCardThree = dynamic_cast<CardThree*>(pCardToPaste);
        pNewCard = new CardThree(destinationCell);

    }
    else if (dynamic_cast<CardFour*>(pCardToPaste))
    {
        CardFour* pOriginalCard = dynamic_cast<CardFour*>(pCardToPaste);
        pNewCard = new CardFour(destinationCell);

    }
    else if (dynamic_cast<CardFive*>(pCardToPaste))
    {
        CardFive* pOriginalCardFive = dynamic_cast<CardFive*>(pCardToPaste);
        pNewCard = new CardFive(destinationCell);

    }
    else if (dynamic_cast<CardSix*>(pCardToPaste))
    {
        CardSix* pOriginalCard = dynamic_cast<CardSix*>(pCardToPaste);
        pNewCard = new CardSix(destinationCell);

    }
    else if (dynamic_cast<Card7*>(pCardToPaste))
    {
        Card7* pOriginalCard = dynamic_cast<Card7*>(pCardToPaste);
        pNewCard = new Card7(destinationCell);

    }
    else if (dynamic_cast<CardEight*>(pCardToPaste))
    {
        CardEight* pOriginalCard = dynamic_cast<CardEight*>(pCardToPaste);
        pNewCard = new CardEight(destinationCell);

    }
    else if (dynamic_cast<Card9*>(pCardToPaste))
    {
        Card9* pOriginalCard = dynamic_cast<Card9*>(pCardToPaste);
        pNewCard = new Card9(destinationCell);
        dynamic_cast<Card9*>(pNewCard)->SetCell(pOriginalCard->GetCell());

    }
    else if (dynamic_cast<CardTen*>(pCardToPaste))
    {
        CardTen* pOriginalCardTen = dynamic_cast<CardTen*>(pCardToPaste);
        pNewCard = new CardTen(destinationCell);
        dynamic_cast<CardTen*>(pNewCard)->setPrice(pOriginalCardTen->GetPrice());
        dynamic_cast<CardTen*>(pNewCard)->setFees(pOriginalCardTen->GetFees());
    }
    else if (dynamic_cast<Card11*>(pCardToPaste))
    {
        Card11* pOriginalCard11 = dynamic_cast<Card11*>(pCardToPaste);
        pNewCard = new Card11(destinationCell);
        dynamic_cast<Card11*>(pNewCard)->setPrice(pOriginalCard11->GetPrice());
        dynamic_cast<Card11*>(pNewCard)->setFees(pOriginalCard11->GetFees());
    }
    else if (dynamic_cast<Card12*>(pCardToPaste))
    {
        Card12* pOriginalCard12 = dynamic_cast<Card12*>(pCardToPaste);
        pNewCard = new Card12(destinationCell);
        dynamic_cast<Card12*>(pNewCard)->setPrice(pOriginalCard12->GetPrice());
        dynamic_cast<Card12*>(pNewCard)->setFees(pOriginalCard12->GetFees());
    }
    else if (dynamic_cast<Card13*>(pCardToPaste))
    {
        Card13* pOriginalCard13 = dynamic_cast<Card13*>(pCardToPaste);
        pNewCard = new Card13(destinationCell);
        dynamic_cast<Card13*>(pNewCard)->setPrice(pOriginalCard13->GetPrice());
        dynamic_cast<Card13*>(pNewCard)->setFees(pOriginalCard13->GetFees());
    }

    else
    {
        pNewCard = new Card(destinationCell);
    }

    if (!pNewCard)
    {
        pOut->PrintMessage("Failed to create a new card. Operation cancelled.");
        return;
    }

    // Add the new card to the grid
    if (!pGrid->AddObjectToCell(pNewCard))
    {
        pOut->PrintMessage("Failed to add the card to the destination cell. Operation cancelled.");
        delete pNewCard; // Clean up memory if adding fails
        return;
    }

    pOut->PrintMessage("Card pasted successfully.");
    pGrid->UpdateInterface();
    pOut->ClearStatusBar();
}

PasteCardAction::~PasteCardAction()
{
}

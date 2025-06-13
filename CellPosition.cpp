#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
	// from the passed (cellNum)
	// (*this) = ... --> this will copy the returned (vCell and hCell)
	//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	if (v >= 0 && v <= 8)
	{
		vCell = v;
		return true;
	}
	else
		return false; // this line sould be changed with your implementation
}

bool CellPosition::SetHCell(int h)
{
	if (h >= 0 && h <= 10)
	{
		hCell = h;
		return true;
	}
	else
		return false; // this line sould be changed with your implementation
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	if (hCell >= 0 && hCell <= 10 && vCell >= 0 && vCell <= 8)
		return true;
	else
		return false; // this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
	// which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{

	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it
	if (cellPosition.IsValidCell())
	{
		int Num = (8 - cellPosition.vCell) * 11 + cellPosition.hCell + 1;
		return Num;
	}
	else
		return -1;
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;
	if (cellNum <= 0 || cellNum >= 100)
	{
		position.SetVCell(-1);
		position.SetHCell(-1);
		return position;
	}
	else
	{
		int v = 8;
		while (cellNum > 11)
		{
			cellNum -= 11;
			v--;
		}
		position.SetVCell(v);
		position.SetHCell(cellNum - 1);



		// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
		//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


		return position;
	}
}

void CellPosition::AddCellNum(int addedNum)
{
	int Num = GetCellNumFromPosition(*this);
	if (Num + addedNum <= 99 && Num + addedNum >= 1)
	{
		Num += addedNum;

		CellPosition NewpPosition = GetCellPositionFromNum(Num);
		*this = NewpPosition;
	}
	else
	{
		CellPosition NewpPosition = GetCellPositionFromNum(100); //there is no 100 to verify a win
		*this = NewpPosition;
	}
	// Note: this function updates the data members (vCell and hCell) of the calling object

}
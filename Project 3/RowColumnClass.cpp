#include "RowColumnClass.h"
#include "constants.h"


//////// RowColumnClass Constructors and Member Functions ////////
RowColumnClass::RowColumnClass()
{
    row = MIN_ROW_COL_VAL;
    col = MIN_ROW_COL_VAL;
}

void RowColumnClass::setRowCol(int inRow, int inCol)
{
    setRow(inRow);
    setCol(inCol);
}

void RowColumnClass::setRow(int inRow)
{
    row = inRow;
}

void RowColumnClass::setCol(int inCol)
{
    col = inCol;
}

int RowColumnClass::getRow()
{
    return row;
}

int RowColumnClass::getCol()
{
    return col;
}

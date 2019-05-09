#ifndef _ROWCOLUMNCLASS_H_
#define _ROWCOLUMNCLASS_H_

// The RowColumnClass helps to uniquely identify a specific pixel within an
// image with a row and column value.
class RowColumnClass
{
    private:
        int row;
        int col;

    public:
        RowColumnClass();

        // Setter functions that directly set the appropriate attribute(s)
        // to the value(s) provided.
        void setRowCol(int inRow, int inCol);
        void setRow(int inRow);
        void setCol(int inCol);

        // Getter functions that simply return the appropriate attribute
        // values.
        int getRow();
        int getCol();
};


#endif
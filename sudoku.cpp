//
// Coded by Gabriel Prostitis, date: 1/4/2022
//

#include <bits\stdc++.h>
using namespace std;

//
// Prints all table
//
void PrintTable(const short Table[9][9])
{
    for(short i = 0; i < 9; ++i){
        for(short j = 0; j < 9; ++j){
            if(j == 8) cout << Table[i][j] << '\n';
            else if((j+1) % 3 == 0) cout << Table[i][j] << "    ";
            else cout << Table[i][j] << " ";
        }
        if((i+1) % 3 == 0) cout << '\n';
    }
    cout << '\n';
}

//
// Auxiliary function
//
void FindBox(short res[4], short row, short col)
{
    /*
    short res[4] = {
        -1, -1 // start and end of iteration on rows
        -1, -1 // start and end of iteration on coloumns
    };
    */

    //
    // For rows. (WARNING: in the iteration use i < n not i <= n)
    //
    if(row <= 2) { res[0] = 0; res[1] = 3; }
    else if(row <= 5) { res[0] = 3; res[1] = 6; }
    else { res[0] = 6; res[1] = 9; }

    //
    //  For columns.
    // 
    if(col <= 2) { res[2] = 0; res[3] = 3; }
    else if(col <= 5) { res[2] = 3; res[3] = 6; }
    else { res[2] = 6; res[3] = 9; }
}

//
// Checks if the value in the small box is valid
//
bool IsValid(const short Table[9][9], short row, short col)
{
    if(Table[row][col] == 0) return true;
    
    //
    // Checks vertically and horizontally 
    //
    for(short i = 0; i < 9; ++i)
    {
        if(Table[row][i] == Table[row][col] && i != col) return false;
        if(Table[i][col] == Table[row][col] && i != row) return false;
    }

    short itPos[4];
    FindBox(itPos, row, col);
    
    //
    // Checks if value is valid inside of box
    //
    for(short i = itPos[0]; i < itPos[1]; ++i)
    {
        for(short j = itPos[2]; j < itPos[3]; ++j)
        {
            if(Table[i][j] == Table[row][col] && i != row && j != col) return false;
        }
    }
    
    return true;
}  

//
// Calls 81 times IsValid
//
bool CheckAllTable(const short Table[9][9])
{
    for(short i = 0; i < 9; ++i)
    {
        for(short j = 0; j < 9; ++j)
        {
            if(IsValid(Table, i, j) == false) return false;
        }
    }
    return true;
}


void SudokuSolve(const short Table[9][9], short Temp[9][9], short row, short col)
{
    static bool found = false; // For breaking all stacked function calls

    if(col == 9) {col = 0; ++row; } // Self explanatory
    
    //
    // Last Case
    // 
    if(row == 9) {
        PrintTable(Temp);
        found = true;
        return;
    }
    
    //
    // For all boxes
    //
    if(Table[row][col] != 0) // If the small box was given by user
    {
        SudokuSolve(Table, Temp, row, col+1);
    } else { // if the small box wasn't given by user
        for(short i = 1; i <= 9; ++i){
            Temp[row][col] = i;
            if(IsValid(Temp, row, col)) { SudokuSolve(Table, Temp, row, col+1); if(found) break; } // Recursion
        }
    }

    if(Table[row][col] == 0) Temp[row][col] = 0; // Resets the value to 0 if the value wasn't given by user
    return; // Goes back to previous small box
}

int main(){
    
    /*
        0, 0, 0,    0, 0, 0,    0, 0, 0,
        0, 0, 0,    0, 0, 0,    0, 0, 0,
        0, 0, 0,    0, 0, 0,    0, 0, 0,

        0, 0, 0,    0, 0, 0,    0, 0, 0,
        0, 0, 0,    0, 0, 0,    0, 0, 0,
        0, 0, 0,    0, 0, 0,    0, 0, 0,
        
        0, 0, 0,    0, 0, 0,    0, 0, 0,
        0, 0, 0,    0, 0, 0,    0, 0, 0,
        0, 0, 0,    0, 0, 0,    0, 0, 0,
    */

     short Table[9][9] = {
        3, 0, 0,    0, 0, 0,    0, 0, 5,
        0, 2, 5,    0, 0, 8,    0, 1, 0,
        6, 0, 0,    0, 2, 0,    0, 0, 0,

        0, 0, 0,    0, 0, 1,    4, 0, 0,
        2, 0, 0,    0, 0, 0,    0, 0, 0,
        0, 7, 9,    0, 8, 0,    0, 0, 6,
        
        0, 0, 0,    9, 0, 0,    0, 6, 0,
        0, 0, 3,    0, 0, 0,    0, 0, 0,
        0, 5, 8,    0, 7, 0,    0, 0, 9

    };

    short TableTemp[9][9];
    memcpy(TableTemp, Table, 9*9*sizeof(short));

    SudokuSolve(Table, TableTemp, 0, 0);

    return 0;
}

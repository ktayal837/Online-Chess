#include <iostream>
#include <stdlib.h>

class ChessGamePiece
{
public:
    ChessGamePiece(char PieceColor) : mPieceColor(PieceColor) {}
    ~ChessGamePiece() {}
    virtual char GetPiece() = 0;
    char GetColor() {
        return mPieceColor;
    }
    bool IsLegalMove(int iR, int iC, int jR, int jC, ChessGamePiece* iGameBoard[8][8]) {
        ChessGamePiece* qpDest = iGameBoard[jR][jC];
        if ((qpDest == 0) || (mPieceColor != qpDest->GetColor())) {
            return LegalSq(iR, iC, jR, jC, iGameBoard);
        }
        return false;
    }
private:
    virtual bool LegalSq(int iR, int iC, int jR, int jC, ChessGamePiece* iGameBoard[8][8]) = 0;
    char mPieceColor;
};

//movement of PawnPiece
class Pawn : public ChessGamePiece
{
public:
    Pawn(char PieceColor) : ChessGamePiece(PieceColor) {}
    ~Pawn() {}
private:
    virtual char GetPiece() {
        return 'P';
    }
    bool LegalSq(int iR, int iC, int jR, int jC, ChessGamePiece* iGameBoard[8][8]) {
        ChessGamePiece* qpDest = iGameBoard[jR][jC];
        if (qpDest == 0) {
            
            if (iC == jC) {
                if (GetColor() == 'W') {
                    if (jR == iR + 1) {
                        return true;
                    }
                } else {
                    if (jR == iR - 1) {
                        return true;
                    }
                }
            }
        } else {
            
            if ((iC == jC + 1) || (iC == jC - 1)) {
                if (GetColor() == 'W') {
                    if (jR == iR + 1) {
                        return true;
                    }
                } else {
                    if (jR == iR - 1) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

//movement of RookPiece

class Rook : public ChessGamePiece
{
public:
    Rook(char PieceColor) : ChessGamePiece(PieceColor) {}
    ~Rook() {}
private:
    virtual char GetPiece() {
        return 'R';
    }
    bool LegalSq(int iR, int iC, int jR, int jC, ChessGamePiece* iGameBoard[8][8]) {
        if (iR == jR) {

            // Make sure that all intercede squares are empty
            int ColumnOffset = (jC - iC > 0) ? 1 : -1;
            for (int CheckCol = iC + ColumnOffset; CheckCol !=  jC; CheckCol = CheckCol + ColumnOffset) {
                if (iGameBoard[iR][CheckCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if (jC == iC) {
            
            int RowOffset = (jR - iR > 0) ? 1 : -1;
            for (int CheckRow = iR + RowOffset; CheckRow !=  jR; CheckRow = CheckRow + RowOffset) {
                if (iGameBoard[CheckRow][iC] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

//movement of BishopPiece

class Bishop : public ChessGamePiece
{
public:
    Bishop(char PieceColor) : ChessGamePiece(PieceColor) {}
    ~Bishop() {}
private:
    virtual char GetPiece() {
        return 'B';
    }
    bool LegalSq(int iR, int iC, int jR, int jC, ChessGamePiece* iGameBoard[8][8]) {
        if ((jC - iC == jR - iR) || (jC - iC == iR - jR)) {
            // Make sure that all invervening squares are empty
            int RowOffset = (jR - iR > 0) ? 1 : -1;
            int ColumnOffset = (jC - iC > 0) ? 1 : -1;
            int CheckRow;
            int CheckCol;
            for (CheckRow = iR + RowOffset, CheckCol = iC + ColumnOffset;
                CheckRow !=  jR;
                CheckRow = CheckRow + RowOffset, CheckCol = CheckCol + ColumnOffset)
            {
                if (iGameBoard[CheckRow][CheckCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

//movement of KnightPiece

class Knight : public ChessGamePiece
{
public:
    Knight(char PieceColor) : ChessGamePiece(PieceColor) {}
    ~Knight() {}
private:
    virtual char GetPiece() {
        return 'N';
    }
    bool LegalSq(int iR, int iC, int jR, int jC, ChessGamePiece* iGameBoard[8][8]) {
        // Destination square is unoccupied or occupied by opposite color
        if ((iC == jC + 1) || (iC == jC - 1)) {
            if ((iR == jR + 2) || (iR == jR - 2)) {
                return true;
            }
        }
        if ((iC == jC + 2) || (iC == jC - 2)) {
            if ((iR == jR + 1) || (iR == jR - 1)) {
                return true;
            }
        }
        return false;
    }
};


//movement of KingPiece
class King : public ChessGamePiece
{
public:
    King(char PieceColor) : ChessGamePiece(PieceColor) {}
    ~King() {}
private:
    virtual char GetPiece() {
        return 'K';
    }
    bool LegalSq(int iR, int iC, int jR, int jC, ChessGamePiece* iGameBoard[8][8]) {
        int iRowDel = jR - iR;
        int iColDel = jC - iC;
        if (((iRowDel >= -1) && (iRowDel <= 1)) &&
            ((iColDel >= -1) && (iColDel <= 1)))
        {
            return true;
        }
        return false;
    }
};

//movement of QueenPiece
class Queen : public ChessGamePiece
{
public:
    Queen(char PieceColor) : ChessGamePiece(PieceColor) {}
    ~Queen() {}
private:
    virtual char GetPiece() {
        return 'Q';
    }
    bool LegalSq(int iR, int iC, int jR, int jC, ChessGamePiece* iGameBoard[8][8]) {
        if (iR == jR) {
            // Make sure that all invervening squares are empty
            int ColumnOffset = (jC - iC > 0) ? 1 : -1;
            for (int CheckCol = iC + ColumnOffset; CheckCol !=  jC; CheckCol = CheckCol + ColumnOffset) {
                if (iGameBoard[iR][CheckCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if (jC == iC) {
            // Make sure that all invervening squares are empty
            int RowOffset = (jR - iR > 0) ? 1 : -1;
            for (int CheckRow = iR + RowOffset; CheckRow !=  jR; CheckRow = CheckRow + RowOffset) {
                if (iGameBoard[CheckRow][iC] != 0) {
                    return false;
                }
            }
            return true;
        } else if ((jC - iC == jR - iR) || (jC - iC == iR - jR)) {
            // Make sure that all invervening squares are empty
            int RowOffset = (jR - iR > 0) ? 1 : -1;
            int ColumnOffset = (jC - iC > 0) ? 1 : -1;
            int CheckRow;
            int CheckCol;
            for (CheckRow = iR + RowOffset, CheckCol = iC + ColumnOffset;
                CheckRow !=  jR;
                CheckRow = CheckRow + RowOffset, CheckCol = CheckCol + ColumnOffset)
            {
                if (iGameBoard[CheckRow][CheckCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};


class CBoard
{
public:
    CBoard() {
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                DrawGameBoard[iRow][iCol] = 0;
            }
        }
        // Allocate and place black pieces
        for (int iCol = 0; iCol < 8; ++iCol) {
            DrawGameBoard[6][iCol] = new Pawn('B');
        }
        DrawGameBoard[7][0] = new Rook('B');
        DrawGameBoard[7][1] = new Knight('B');
        DrawGameBoard[7][2] = new Bishop('B');
        DrawGameBoard[7][3] = new King('B');
        DrawGameBoard[7][4] = new Queen('B');
        DrawGameBoard[7][5] = new Bishop('B');
        DrawGameBoard[7][6] = new Knight('B');
        DrawGameBoard[7][7] = new Rook('B');
        // Allocate and place white pieces
        for (int iCol = 0; iCol < 8; ++iCol) {
            DrawGameBoard[1][iCol] = new Pawn('W');
        }
        DrawGameBoard[0][0] = new Rook('W');
        DrawGameBoard[0][1] = new Knight('W');
        DrawGameBoard[0][2] = new Bishop('W');
        DrawGameBoard[0][3] = new King('W');
        DrawGameBoard[0][4] = new Queen('W');
        DrawGameBoard[0][5] = new Bishop('W');
        DrawGameBoard[0][6] = new Knight('W');
        DrawGameBoard[0][7] = new Rook('W');
    }
    ~CBoard() {
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                delete DrawGameBoard[iRow][iCol];
                DrawGameBoard[iRow][iCol] = 0;
            }
        }
    }

    void Print() {
        using namespace std;
        const int kiSqWidth = 4;
        const int kiSqHeight = 3;
        for (int iRow = 0; iRow < 8*kiSqHeight; ++iRow) {
            int SqRow = iRow/kiSqHeight;
            // Print side border with numbering
            if (iRow % 3 == 1) {
                cout << '-' << (char)('1' + 7 - SqRow) << '-';
            } else {
                cout << "--";
            }
            // Print the chess board
            for (int iCol = 0; iCol < 8*kiSqWidth; ++iCol) {
                int SqCol = iCol/kiSqWidth;
                if (((iRow % 3) == 1) && ((iCol % 4) == 1 || (iCol % 4) == 2) && DrawGameBoard[7-SqRow][SqCol] != 0) {
                    if ((iCol % 4) == 1) {
                        cout << DrawGameBoard[7-SqRow][SqCol]->GetColor();
                    } else {
                        cout << DrawGameBoard[7-SqRow][SqCol]->GetPiece();
                    }
                } else {
                    if ((SqRow + SqCol) % 2 == 1) {
                        cout << '#';
                    } else {
                        cout <<' ';
                    }
                }
            }
            cout << endl;
        }
        // Print the bottom border with numbers
        for (int iRow = 0; iRow < kiSqHeight; ++iRow) {
            if (iRow % 3 == 1) {
                cout << "--";
                for (int iCol = 0; iCol < 8*kiSqWidth; ++iCol) {
                    int SqCol = iCol/kiSqWidth;
                    if ((iCol % 4) == 1) {
                        cout << (SqCol + 1);
                    } else {
                        cout << '-';
                    }
                }
                cout << endl;
            } else {
                for (int iCol = 1; iCol < 9*kiSqWidth; ++iCol) {
                    cout << '-';
                }
                cout << endl;
            }
        }
    }

    bool IsInCheck(char PieceColor) {
        // Find the king
        int KingRow;
        int KingCol;
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (DrawGameBoard[iRow][iCol] != 0) {
                    if (DrawGameBoard[iRow][iCol]->GetColor() == PieceColor) {
                        if (DrawGameBoard[iRow][iCol]->GetPiece() == 'K') {
                            KingRow = iRow;
                            KingCol = iCol;
                        }
                    }
                }
            }
        }
        // Run through the opponent's pieces and see if any can take the king
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (DrawGameBoard[iRow][iCol] != 0) {
                    if (DrawGameBoard[iRow][iCol]->GetColor() != PieceColor) {
                        if (DrawGameBoard[iRow][iCol]->IsLegalMove(iRow, iCol, KingRow, KingCol, DrawGameBoard)) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    bool CanMove(char PieceColor) {
        // Run through all pieces
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (DrawGameBoard[iRow][iCol] != 0) {
                    // If it is a piece of the current player, see if it has a legal move
                    if (DrawGameBoard[iRow][iCol]->GetColor() == PieceColor) {
                        for (int MoveRow = 0; MoveRow < 8; ++MoveRow) {
                            for (int MoveCol = 0; MoveCol < 8; ++MoveCol) {
                                if (DrawGameBoard[iRow][iCol]->IsLegalMove(iRow, iCol, MoveRow, MoveCol, DrawGameBoard)) {
                                    // Make move and check whether king is in check
                                    ChessGamePiece* qpTemp                   = DrawGameBoard[MoveRow][MoveCol];
                                    DrawGameBoard[MoveRow][MoveCol]   = DrawGameBoard[iRow][iCol];
                                    DrawGameBoard[iRow][iCol]           = 0;
                                    bool bCanMove = !IsInCheck(PieceColor);
                                    // Undo the move
                                    DrawGameBoard[iRow][iCol]           = DrawGameBoard[MoveRow][MoveCol];
                                    DrawGameBoard[MoveRow][MoveCol]   = qpTemp;
                                    if (bCanMove) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    ChessGamePiece* DrawGameBoard[8][8];
};

//Draw chess board

class ChessBoard
{
public:
    ChessBoard() : mcPlayerTurn('W') {}
    ~ChessBoard() {}

    void Start() {
        do {
            GetNextMove(mqGameBoard.DrawGameBoard);
            AlternateTurn();
        } while (!IsGameOver());
        mqGameBoard.Print();
    }

    void GetNextMove(ChessGamePiece* iGameBoard[8][8]) {
        using namespace std;
        bool bValidMove     = false;
        do {
            system ("clear");
            cout<<endl<<endl<<" Welcome to Online Chess Game "<<endl<<endl<<endl;
            cout<<"  Notations of sysmbols used "<<endl<<endl<<endl;
            cout<<" # = White Sq"<<endl;
            cout<<" Blank space = Black Sq"<<endl;
            cout<<" WP = White pawn"<<endl;
            cout<<"BP = Black pawn"<<endl;
            cout<<" WN = White Knight"<<endl;
            cout<<"BN = Black Knight"<<endl;
            cout<<" WB = White Bishop"<<endl;
            cout<<"BB = Black Bishop"<<endl;
            cout<<" WR = White Rook"<<endl;
            cout<<" BR = Black Rook"<<endl;
            cout<<" WQ = White Queen"<<endl;
            cout<<" BQ = Black Queen"<<endl;
            cout<<" WK = White King"<<endl;
            cout<<" BK =Black King"<<endl;
            cout<<"Rules to move pieces :"<<endl;
            cout<<"Move the pieces by selecting first row & then column to a valid location to avoid illegal move"<<endl<<endl<<endl;
            mqGameBoard.Print();

            // Get input and convert to coordinates
            cout << mcPlayerTurn << "'s Move: ";
            int StartMove;
            cin >> StartMove;
            int StartRow = (StartMove / 10) - 1;
            int StartCol = (StartMove % 10) - 1;

            cout << "To: ";
            int EndMove;
            cin >> EndMove;
            int EndRow = (EndMove / 10) - 1;
            int EndCol = (EndMove % 10) - 1;

            // Check that the indices are in range
            // and that the source and destination are different
            if ((StartRow >= 0 && StartRow <= 7) &&
                (StartCol >= 0 && StartCol <= 7) &&
                (EndRow >= 0 && EndRow <= 7) &&
                (EndCol >= 0 && EndCol <= 7)) {
                // Additional checks in here
                ChessGamePiece* qpCurrPiece = iGameBoard[StartRow][StartCol];
                // Check that the piece is the correct color
                if ((qpCurrPiece != 0) && (qpCurrPiece->GetColor() == mcPlayerTurn)) {
                    // Check that the destination is a valid destination
                    if (qpCurrPiece->IsLegalMove(StartRow, StartCol, EndRow, EndCol, iGameBoard)) {
                        // Make the move
                        ChessGamePiece* qpTemp                   = iGameBoard[EndRow][EndCol];
                        iGameBoard[EndRow][EndCol]     = iGameBoard[StartRow][StartCol];
                        iGameBoard[StartRow][StartCol] = 0;
                        // Make sure that the current player is not in check
                        if (!mqGameBoard.IsInCheck(mcPlayerTurn)) {
                            delete qpTemp;
                            bValidMove = true;
                        } else { // Undo the last move
                            iGameBoard[StartRow][StartCol] = iGameBoard[EndRow][EndCol];
                            iGameBoard[EndRow][EndCol]     = qpTemp;
                        }
                    }
                }
            }
            if (!bValidMove) {
                cout << "Illegal Move!" << endl;
            }
        } while (!bValidMove);
    }

    void AlternateTurn() {
        mcPlayerTurn = (mcPlayerTurn == 'W') ? 'B' : 'W';
    }

//GAMR OVER!!!

    bool IsGameOver() {
        // Check that the current player can move
        // If not, we have a stalemate or checkmate
        bool bCanMove(false);
        bCanMove = mqGameBoard.CanMove(mcPlayerTurn);
        if (!bCanMove) {
            if (mqGameBoard.IsInCheck(mcPlayerTurn)) {
                AlternateTurn();
                std::cout << "Checkmate, " << mcPlayerTurn << " Wins!" << std::endl;
            } else {
                std::cout << "Draw/Stalemate!" << std::endl;
            }
        }
        return !bCanMove;
    }
private:
    CBoard mqGameBoard;
    char mcPlayerTurn;
};

int main() {
    ChessBoard qGame;
    qGame.Start();
    return 0;
}


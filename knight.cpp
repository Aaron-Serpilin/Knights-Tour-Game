#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <string>
#include <stdlib.h>
#include <stdio.h>

std::vector<int> coordinateTransformer (char* argv[]) {

    std::vector<std::string> startAndEndSquare;
    std::vector<int> vectorCoordinates;
    startAndEndSquare.push_back(argv[2]);
    startAndEndSquare.push_back(argv[3]);

    int xStartingCoordinate = startAndEndSquare.at(0).at(0) - 'a';
    int yStartingCoordinate;
    int xEndingCoordinate = startAndEndSquare.at(1).at(0) - 'a';
    int yEndingCoordinate = startAndEndSquare.at(1).at(1) - '1';

    if (startAndEndSquare.at(0).length() == 3) { //Checks if the y starting coordinate is greater than 9, causing it to have two indexes

        int firstDigit = startAndEndSquare.at(0).at(1);
        int secondDigit = startAndEndSquare.at(0).at(2);
        std::string completeDigit;
        completeDigit = firstDigit;
        completeDigit += secondDigit;
        yStartingCoordinate = std::stoi(completeDigit) - 1;
        
    } else {
        yStartingCoordinate = startAndEndSquare.at(0).at(1) - '1';
    }

    vectorCoordinates.push_back(xStartingCoordinate);
    vectorCoordinates.push_back(yStartingCoordinate);
    vectorCoordinates.push_back(xEndingCoordinate);
    vectorCoordinates.push_back(yEndingCoordinate);

    //std::cout << "Starting: (" << xStartingCoordinate << ", " << yStartingCoordinate << ")" << std::endl;
    //std::cout << "Starting: (" << xEndingCoordinate << ", " << yEndingCoordinate << ")" << std::endl;
    //std::cout << "Complete digit is: " << completeDigit << std::endl;

    return vectorCoordinates;

}

std::vector<std::vector<int> > chessBoardGenerator (int& boardSize) {

    std::vector<std::vector<int> > chessBoard;
    
    for (int i = 0 ; i < boardSize; i++) {

        chessBoard.push_back(std::vector<int>());

        for (int j = 0 ; j < boardSize; j++) {

            chessBoard.at(i).push_back(0);

        }

    }

    return chessBoard;

}

bool isMoveOnBoard (int currentX, int currentY, int boardSize, std::vector< std::vector<int> >& chessBoard) {
    return currentX >= 0 && currentY >= 0 && currentX < boardSize && currentY < boardSize && chessBoard.at(currentX).at(currentY) == 0;
}

void possibleMoves (int potentialMoveLocation, int& xPotentialCoordinate, int& yPotentialCoordinate) {

    switch (potentialMoveLocation) {

        case 1: xPotentialCoordinate += 1, yPotentialCoordinate += 2; break;
        case 2: xPotentialCoordinate += 2, yPotentialCoordinate += 1; break;
        case 3: xPotentialCoordinate -= 1, yPotentialCoordinate += 2; break;
        case 4: xPotentialCoordinate += 2, yPotentialCoordinate -= 1; break;
        case 5: xPotentialCoordinate += 1, yPotentialCoordinate -= 2; break;
        case 6: xPotentialCoordinate -= 2, yPotentialCoordinate += 1; break;
        case 7: xPotentialCoordinate -= 2, yPotentialCoordinate -= 1; break;
        case 8: xPotentialCoordinate -= 1, yPotentialCoordinate -= 2; break;
    
    }

    //std::cout << "next x is " << xPotentialCoordinate << " next y is " << yPotentialCoordinate << std::endl;

}

bool findKnightsTour (int& boardSize, int xCoordinate, int yCoordinate, int& xEndingCoordinate, int& yEndingCoordinate, std::vector<std::vector<int> >& chessBoard, int& visitOrder) {
    
    chessBoard.at(xCoordinate).at(yCoordinate) = visitOrder; //Marks visited squares and assigns them with the order in which they were visited

    if (xCoordinate == xEndingCoordinate && yCoordinate == yEndingCoordinate) {

        return true;

    } else {
        
        int xPotentialCoordinate;
        int yPotentialCoordinate;

       for (int potentialMoveLocation = 1; potentialMoveLocation < 9; potentialMoveLocation++) {

            xPotentialCoordinate = xCoordinate;
            yPotentialCoordinate = yCoordinate;

            possibleMoves(potentialMoveLocation, xPotentialCoordinate, yPotentialCoordinate); //Generates and assigns the possible move coordinates

            if (isMoveOnBoard(xPotentialCoordinate, yPotentialCoordinate, boardSize, chessBoard)) {
            
                //std::cout << visitOrder << " " << xPotentialCoordinate << " " << yPotentialCoordinate << std::endl;
                visitOrder++;
                bool success = findKnightsTour(boardSize, xPotentialCoordinate, yPotentialCoordinate, xEndingCoordinate, yEndingCoordinate, chessBoard, visitOrder);

                // for (int i = 0; i < chessBoard.size(); i++) {

                //     for (int j = 0; j < chessBoard.size(); j++) {

                //         std::cout << chessBoard.at(i).at(j);
                //     }
                //     std::cout << std::endl;
                // }

                if (success) {
                    return true;
                }

                chessBoard.at(xPotentialCoordinate).at(yPotentialCoordinate) = 0; //Removes the visited marks
                visitOrder--; //Decreases the order in which the squares were visited to initiate backtracking

            }

       }
        
    }

    return false;

}

std::string squareStepPrinter (std::vector<std::vector <int> >& chessBoard, int& visitOrder) {

    char xOutputCoordinate;
    int yOutputCoordinate;
    std::string outputSquare;

    for (int i = 1; i <= visitOrder; i++) {

        for (int j = 0; j < chessBoard.size(); j++) {

            for (int k = 0; k < chessBoard.at(j).size(); k++) {

                if (chessBoard.at(j).at(k) == i) {

                    xOutputCoordinate = 'a' + j;
                    yOutputCoordinate = k + 1;
                    outputSquare += xOutputCoordinate;
                    outputSquare += std::to_string(yOutputCoordinate);
                    outputSquare += " ";
                    //std::cout << "x is " << xOutputCoordinate << " y is " << yOutputCoordinate << " i is " << i << std::endl;

                }

            }

        }

    }

    return outputSquare;

}

void inputProcessor (int argc, char* argv[], std::string& startSquare, std::string& endSquare, int& boardSize) {

    char startSquareLetter = startSquare[0];
    int startSquareNumber = startSquare[1] - '0';
    char endSquareLetter = endSquare[0];
    int endSquareNumber = endSquare[1] - '0';

    if (boardSize < 1 || boardSize > 26 || startSquareLetter < 'a' || startSquareLetter > ('a' + boardSize - 1) || startSquareNumber < 1 || startSquareNumber > boardSize 
    || endSquareLetter < 'a' || endSquareLetter > ('a' + boardSize -1) || endSquareNumber < 1 || endSquareNumber > boardSize) {

        throw std::runtime_error("invalid parameter list");

    }

}

bool isBoardSizeNumber (char* argv[]) {

    std::string boardSizeVal = argv[1];
    //std::cout << "the size is " << boardSizeVal.length() << std::endl;

    if (boardSizeVal.length() > 2) {
        return false;
    }

    return true;
}

int main (int argc, char* argv[]) {
    
    try {

        if (argc != 4 || !(isBoardSizeNumber(argv))) {
        
            throw std::runtime_error("invalid parameter list");

        }

        int boardSize = std::stoi(argv[1]);
        std::string startSquare = argv[2];
        std::string endSquare = argv[3];
        std::vector< std::vector <int> > chessBoard;
        int visitOrder = 1;
        
        inputProcessor(argc, argv, startSquare, endSquare, boardSize);
        chessBoard = chessBoardGenerator(boardSize);

        if (findKnightsTour(boardSize, coordinateTransformer(argv).at(0), coordinateTransformer(argv).at(1), coordinateTransformer(argv).at(2), coordinateTransformer(argv).at(3), chessBoard, visitOrder)) {
            std::cout << squareStepPrinter(chessBoard, visitOrder) << std::endl;
        } else {
            std::cout << "could not find a knight's tour" << std::endl;
        }
        
    
    } catch (std::runtime_error &excpt) {

        std::cout << excpt.what();

    }

    return 0;

}
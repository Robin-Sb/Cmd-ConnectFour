// ConnectFour.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "Game.h"

void startGameLoop() {
    bool isRedTurn{ true };
    bool gameIsFinished = false;
    Game game = Game();
    while (!gameIsFinished) {
        std::cout << game.printBoard() << std::endl;
        std::cout << "It's " << (isRedTurn ? "reds" : "yellows") << " turn \n";
        std::cout << "Please type in a number corresponding to the column you want to insert your stone in. \n";
        std::string column_str{ };
        std::cin >> column_str;
        int column{};
        try {
            column = std::stoi(column_str);
        } catch (const std::invalid_argument& e) {
            std::cout << "Wrong input. Please type in a number. \n";
            continue;
        }
        if (column < 1 || column > 7) {
            std::cout << "Wrong input. Please type in a number between 1 and 7. \n";
            continue;
        }
        GameState gs = game.insertStone(isRedTurn, column - 1);
        if (gs.playerWon) {
            std::cout << "Game has ended!" << std::endl;
            std::cout << (isRedTurn ? "red" : "yellow") << " has won." << std::endl;
            break;
        }
        if (game.checkIfFilled()) {
            std::cout << "The board is filled. Neither player has won." << std::endl;
            break;
        }
        if (!gs.columnFilled) {
            isRedTurn = !isRedTurn;
        }
        else {
            std::cout << "This column is already filled. Choose another one." << std::endl;
        }
    }
    std::cout << game.printBoard() << std::endl;
}


int main()
{
    startGameLoop();
}
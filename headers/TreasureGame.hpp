#pragma once
#include <iostream>

class Game {
private:
    char grid[10][10];
    int positionX, positionY;

public:
    Game() {
        positionX = 1;
        positionY = 1;
        initializeGrid();
    }

    void initializeGrid() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == 0 || i == 9 || j == 0 || j == 9)
                    grid[i][j] = 'e';
                else
                    grid[i][j] = ' ';
            }
        }
        grid[8][8] = 'x';
        grid[1][1] = 'c';
    }

    void displayGrid() {
        system("cls");
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                printf("%c ", grid[i][j]);
            }
            printf("\n");
        }
    }

    void play() {
        displayGrid();
        while (true) {
            char move;
            printf("Enter move (w = up, s = down, a = left, d = right): ");
            std::cin >> move;

            if (move != 'w' && move != 'a' && move != 's' && move != 'd') {
                printf("Wrong input, please enter w, a, s, or d.\n");
                continue;
            }

            bool validMove = false;
            int newPositionX = positionX;
            int newPositionY = positionY;

            if (move == 'w' && positionX > 1) {
                newPositionX--;
                validMove = true;
            }
            else if (move == 's' && positionX < 8) {
                newPositionX++;
                validMove = true;
            }
            else if (move == 'a' && positionY > 1) {
                newPositionY--;
                validMove = true;
            }
            else if (move == 'd' && positionY < 8) {
                newPositionY++;
                validMove = true;
            }
            else {
                printf("You hit the wall\n");
            }

            if (validMove) {
                grid[positionX][positionY] = ' ';
                positionX = newPositionX;
                positionY = newPositionY;
                grid[positionX][positionY] = 'c';

                displayGrid();
            }

            if (positionX == 8 && positionY == 8) {
                printf("You found the treasure\n");
                break;
            }
        }
    }
};

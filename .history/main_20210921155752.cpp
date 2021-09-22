#include<iostream>#include <conio.h>//
#include"Maze.h"
//#include "Player.h"


int main(){
    //Board chess_board(4,4);
    //Maze my_maze = new Maze(4,4);
    //chess_board.displayUpdated();
    Maze *my_maze = new Maze(4,4, "me");
    while(!my_maze->IsGameOver()){
        std::cout << *my_maze << std::endl;
        char ch = std::cin.get();
        //ch = getch();
        switch (ch)
        {
        case 'w': //up
        case 'W':
            Position(my_maze->)
            break;
        case 'D': //down
        case 'd':

            break;
        case 's': //left
        case 'S':
            break;
        case 'A': //right
        case 'a':
            break;
        default:
            break;
        }

    }
    
    //my_maze.getMaze()->displayUpdated();
    //delete my_maze;
    return 0;
}
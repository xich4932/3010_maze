#include<iostream>
#include"Maze.h"
//#include "Player.h"


int main(){
    //Board chess_board(4,4);
    //Maze my_maze = new Maze(4,4);
    //chess_board.displayUpdated();
    Maze *my_maze = new Maze(4,4, "me");
    while(!my_maze->IsGameOver()){
        std::cout << *my_maze << std::endl;
        int ch = getch();
        ch = getch();
        
    }
    
    //my_maze.getMaze()->displayUpdated();
    //delete my_maze;
    return 0;
}
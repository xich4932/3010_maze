#include<iostream>
#include"Maze.h"
#include "Player.h"


int main(){
    //Board chess_board(4,4);
    //Maze my_maze = new Maze(4,4);
    //chess_board.displayUpdated();
    Maze *my_maze = new Maze(4,4, "me");
    while(my_maze->IsGameOver()){
        
    }

    delete my_maze;
    return 0;
}
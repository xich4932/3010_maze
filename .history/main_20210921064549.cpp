#include<iostream>
//m#include"Maze.h"
//#include "Player.h"


int main(){
    //Board chess_board(4,4);
    //Maze my_maze = new Maze(4,4);
    //chess_board.displayUpdated();
    Maze *my_maze = new Maze(4,4, "me");
    std::cout << my_maze->getMaze() << std::endl;

    delete my_maze;
    return 0;
}
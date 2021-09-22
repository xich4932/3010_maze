#include<iostream>#include <conio.h>//
#include"Maze.h"
//#include "Player.h"


int main(){
    //Board chess_board(4,4);
    //Maze my_maze = new Maze(4,4);
    //chess_board.displayUpdated();
    Maze *my_maze = new Maze(4,4, "me");
    Player * user = my_maze->getPlayer(0);
    Board * myboard = my_maze->getMaze();
    //std::cout << *my_maze << std::endl;
    //std::cout << *my_maze << std::endl;
    
    std::cout << my_maze->IsGameOver() << std::endl;
    std::cout << *my_maze << std::endl;
    while(!my_maze->IsGameOver()){
        //std::cout << myboard << std::endl;
         char ch = std::cin.get();
        std::cout << *my_maze << std::endl;
        Position step = Position(user->get_position());
        //ch = getch();
        switch (ch)
        {
        case 'w': //up
        case 'W':
            step.col --;
            break;
        case 'D': //down
        case 'd':
            step.row ++;
            break;
        case 's': //left
        case 'S':
            step.col ++;
            break;
        case 'A': //right
        case 'a':
            step.row --;
            break;
        default:
            std::cout <<"wrong input"<<std::endl;
            break;
        }
        std::vector<Position> move = myboard->GetMoves();
        
        
    }
    
    //my_maze.getMaze()->displayUpdated();
    //delete my_maze;
    return 0;
}
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
    char ch[2];
    std::cout << my_maze->IsGameOver() << std::endl;
    std::cout << *my_maze << std::endl;
    while(!my_maze->IsGameOver()){
        std::vector<std::string> temp_move = myboard->GetMoves(user);
        my_maze->GenerateReport(temp_move);
        //std::cout << myboard << std::endl;
         //char ch = std::cin.get();
         //std::string ch;
         //char ch;
         std::cin.getline(ch, 1);
         //std::cin.ignore(999, '\n');
        std::cout << *my_maze << std::endl;
        Position step = Position(user->get_position());
        //ch = getch();
        switch (ch[0])
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
        myboard->MovePlayer(user,step);
        
    }
    
    //my_maze.getMaze()->displayUpdated();
    //delete my_maze;
    return 0;
}
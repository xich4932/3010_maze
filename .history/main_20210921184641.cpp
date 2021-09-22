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
    char ch;
    //std::cout << *my_maze << std::endl;
    while(!my_maze->IsGameOver()){
        std::cout << *my_maze << std::endl;
        std::vector<std::string> temp_move = myboard->GetMoves(user);
        my_maze->GenerateReport(temp_move);
        
        std::cin >> ch;
        std::cin.clear();
        std::cin.sync();
         
        Position step = Position(user->get_position());
        //ch = getch();
        if(ch == 'w' || ch == 'W'){
            step.col --;
        }else if(ch == 'D' || ch == 'd'){
            step.row ++;
        }else if(ch == 's' || ch == 'S'){
            step.col ++;
        }else if(ch == 'a' || ch == 'A'){
            step.row --;
        }else{
            std::cout <<"invalid input" << std::endl;
        }
        if(!myboard->MovePlayer(user,step)){
            std::cout <<"oohs, you are caught by enemy!" <<std::endl;
            my_maze->IsGameOver();

        } 
    }
    std::cout <<"you earn " << user->get_points() << " points." << std::endl; 
    std::cout << "game end!" << std::endl;
    
    return 0;
}
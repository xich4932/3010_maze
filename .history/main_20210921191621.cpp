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
    Player *turn_enemy;
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
        if(temp_move.size() > 2){
            turn_enemy = my_maze->getPlayer(rand()%3+1);
            std::string attack_direction = turn_enemy->ToRelativePosition(user->get_position());
            for(int y = 0; y < attack_direction.length(); y++){
                if(y == )
            }
            
            turn_enemy->enemyStrategy(user, )
        }else{
            std::cout<<"Enemy is observing you"<<std::endl;
        }
        

    }
    std::cout <<"you earn " << user->get_points() << " points." << std::endl; 
    std::cout << "game end!" << std::endl;
    
    return 0;
}
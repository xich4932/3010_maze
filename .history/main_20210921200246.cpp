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
    std::vector<std::string> temp_move;
    //std::cout << *my_maze << std::endl;
    while(!my_maze->IsGameOver()){
        std::cout << *my_maze << std::endl;
        temp_move = myboard->GetMoves(user);
        my_maze->GenerateReport(temp_move, user);
        
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
        std::cout << *my_maze << std::endl;
        temp_move = myboard->GetMoves(user);
        if(temp_move.size() >= 2){
            turn_enemy = my_maze->getPlayer(rand()%3+1);
            std::vector<std::string> attack_direction = turn_enemy->ToRelativePosition(user->get_position());
            //std::cout << "attack_diretion " << attack_direction << std::endl;
            std::vector<SquareType> attack_choice;
            std::vector<Position> attack_point;
            Position po;
            for(std::vector<std::string> y = attack_direction.begin(); y != attack_direction.end(); y++){
                if(*y == "RIGHT"){
                    po = turn_enemy->get_position();
                    po.row ++;
                    attack_choice.push_back(myboard->get_square_value(po));
                    attack_point.push_back(po);
                }else if(y == "L"){
                    po = turn_enemy->get_position();
                    po.row --;
                    attack_choice.push_back(myboard->get_square_value(po));
                    attack_point.push_back(po);
                }else if(y == 'U'){
                    po = turn_enemy->get_position();
                    po.col ++;
                    attack_choice.push_back(myboard->get_square_value(po));
                    attack_point.push_back(po);
                }else if(y == 'D'){
                    po = turn_enemy->get_position();
                    po.col --;
                    attack_choice.push_back(myboard->get_square_value(po));
                    attack_point.push_back(po);
                }
            }

            for(int e =0; e < attack_point.size(); e++){
                std::cout << "point: "<< attack_point[e].col << " " << attack_point[e].row << std::endl;
            }

            po = turn_enemy->enemyStrategy(attack_choice, attack_point);
            myboard->MovePlayer(turn_enemy,po);
            std::cout << *my_maze << std::endl;
        }else{
            std::cout<<"Enemy is observing you"<<std::endl;
        }
        

    }
    std::cout <<"you earn " << user->get_points() << " points." << std::endl; 
    std::cout << "game end!" << std::endl;
    
    return 0;
}
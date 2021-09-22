#include<iostream>
#include"Maze.h"

//#include "Player.h"


int main(){
    std::cout <<"-------------------------------------------------------" <<std::endl;
    std::cout <<"the maze is generate with soluable path" << std::endl;
    std::cout <<"enemy is designed to catch up player" << std::endl;
    std::cout <<"sometimes the map can be really hard for player to win" << std::endl;
    std::cout <<"please try serveral times" << std::endl;
    std::cout <<"hint: if two direction of player is blocked," << std::endl;
    std::cout <<"       enemy won't attack user" << std::endl;
    std::cout <<"-------------------------------------------------------" <<std::endl;
    
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
    std::cout << *my_maze << std::endl;
    //std::cout << *my_maze << std::endl;
    while(!my_maze->IsGameOver()){
        //std::cout << *my_maze << std::endl;
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
        
        if(!myboard->MovePlayer(user,step, 0)){
            std::cout <<"oohs, you are caught by enemy!" <<std::endl;
            my_maze->IsGameOver();
        }
        std::cout << *my_maze << std::endl;
        temp_move = myboard->GetMoves(user);
        if(temp_move.size() >= 2){
            std::cout << "enemy is moving"<<std::endl;
            turn_enemy = my_maze->getPlayer((rand()%2)+1);
            std::cout << "current : " << turn_enemy->get_name() << " " << turn_enemy->get_position().col << " " << turn_enemy->get_position().row << std::endl;
            std::vector<std::string> attack_direction = turn_enemy->ToRelativePosition(user->get_position());
            //std::cout << "attack_diretion " << attack_direction << std::endl;
            std::vector<SquareType> attack_choice;
            std::vector<Position> attack_point;
            Position po;
            for(std::vector<std::string>::iterator y = attack_direction.begin(); y != attack_direction.end(); y++){
                if(*y == "RIGHT"){
                    po = turn_enemy->get_position();
                    po.row ++;
                    attack_choice.push_back(myboard->get_square_value(po));
                    attack_point.push_back(po);
                }else if(*y == "LEFT"){
                    po = turn_enemy->get_position();
                    po.row --;
                    attack_choice.push_back(myboard->get_square_value(po));
                    attack_point.push_back(po);
                }else if(*y == "UP"){
                    po = turn_enemy->get_position();
                    po.col ++;
                    attack_choice.push_back(myboard->get_square_value(po));
                    attack_point.push_back(po);
                }else if(*y == "DOWN"){
                    po = turn_enemy->get_position();
                    po.col --;
                    attack_choice.push_back(myboard->get_square_value(po));
                    attack_point.push_back(po);
                }
            }

            po = my_maze->enemyStrategy(attack_choice, attack_point);
            myboard->MovePlayer(turn_enemy,po , 1);
        
            std::cout << *my_maze << std::endl;

        }else{
            std::cout<<"Enemy is observing you"<<std::endl;
        }
        
    }
    std::cout << user->get_name() <<" earn " << user->get_points() << " points." << std::endl;
    std::cout << my_maze->getPlayer(1)->get_name() <<" earn " << my_maze->getPlayer(1)->get_points() << " points." << std::endl;
    std::cout << my_maze->getPlayer(2)->get_name() <<" earn " << my_maze->getPlayer(2)->get_points() << " points." << std::endl;

    std::cout << "game end!" << std::endl;
    
    return 0;
}
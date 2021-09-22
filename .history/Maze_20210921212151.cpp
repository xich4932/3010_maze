#include<iostream>
#include<vector>
#include<cstdlib>
#include<array>
#include"Maze.h"
#include"algorithm"
#include<time.h>
#include<cstring>
//using namespace std;

//return true when the path is in the vector
//used in many function, not for specific purpose
bool checkInPath(const int num, const std::vector<int> &vec){
    for(unsigned int d =0; d < vec.size(); d++){
        if(vec[d] == num) return true;
    }
    return false;
}


inline std::string SquareTypeStringify(SquareType sq){
	switch (sq)
	{
	case SquareType::Wall :
		/* code */
		return "Wall";
	case SquareType::Exit :
		/* code */
		return "Exit";
	case SquareType::Empty :
		/* code */
		return "Empty";
	case SquareType::Human :
		return "Human";
	case SquareType::Enemy :
		/* code */
		return "Enemy";
	default:
		return "Treasure";
	}
}

Board::Board(){
	rows_ = 4;
    cols_ = 4;
    generate();
}

Board::Board(int c, int r){
    rows_ = r;
    cols_ = c;
    int flag = generate();
    //keey generate until get a soluable maze
     while(!flag){
        path.clear();
        flag = generate();
    } 
    
}

/* void Board::displayUpdated(){
    for(int i = 0; i < rows_; i++){
        for(int d = 0; d < cols_; d++){
            if(checkInPath(4*i +d, path)){
                std::cout<< "*";
            }else{
                std::cout << "+" ;
            }
            
        }
        std::cout << std::endl;
	}
} */

Maze::Maze(int c, int r, std::string name){
    //generate (board_);
    board_ = new Board(c,r);
    /* while(board_->generate()){
        std::cout << "creating path"<<std::endl;
    } */
    players_.push_back(new Player(name ,1));            //0
    players_.push_back(new Player("clown_face1" ,0));   //1      
    players_.push_back(new Player("clown_face2" ,0));   //2        
    players_.push_back(new Player("pear_1" ,0));        //3    
    players_.push_back(new Player("pear_2" ,0));        //4    
    players_.push_back(new Player("wall_1",0));         //5
    players_.push_back(new Player("wall_2" ,0));        //6    
    players_.push_back(new Player("wall_3" ,0));        //7    
    players_.push_back(new Player("exit" ,0));          //8
    std::vector<int> temp_path = board_->getPath();
    //initialize the board with empty
    for(int e =0; e < board_->get_cols(); e++){
        for(int p = 0; p < board_->get_rows(); p++){
            board_->SetSquareValue(Position(e, p), SquareType::Empty);
        }
    }
   //std::cout << "emtpy set "<< std::endl;
    //put wall on the board
    std::vector<int> path = board_->getPath();

    /* for(int i = 0; i < path.size(); i++){
        std::cout << path[i]<< " ";
    } */
    std::cout << std::endl;
    std::vector<int> wall_only;
    std::vector<int> all_else;
    all_else.push_back(0); 
    all_else.push_back(15);
    std::vector<int> no_ptr_path = path; //store the solution path
    /* no_ptr_path.push_back(1); first 2 direction will be free
    no_ptr_path.push_back(board_->get_rows()); */
    srand((unsigned int)(time(NULL)));
    //generate the wall position
    for(int d = 5; d < 8; d++){
        int temp_r = 0, temp_c=0;
        while(checkInPath(4*temp_c + temp_r, no_ptr_path)){ // no wall overlap eachother
            int s = rand() % (r * c);
            temp_r = s % r;
            temp_c = s / r;
        }
        //no_ptr_path.push_back(board_->get_rows() * temp_c + temp_r);
        wall_only.push_back(board_->get_rows() * temp_c + temp_r);
        all_else.push_back(board_->get_rows() * temp_c + temp_r);
        players_[d]->SetPosition(Position(temp_c, temp_r));
        //std::cout <<"wall : " << temp_c << " " << temp_r <<std::endl;
        board_->SetSquareValue(Position(temp_c, temp_r), SquareType::Wall);
    }
    //std::cout << "emtpy wall "<< std::endl;
    //set treasure
    //generate treasure position
    srand((unsigned int)(time(NULL)));
    for(int d = 3; d < 5; d++){
        int temp_r = 0, temp_c=0;
        while(checkInPath(board_->get_rows() * temp_c + temp_r, wall_only) || checkInPath(board_->get_rows() * temp_c + temp_r, all_else)){ //treasure will not on the wall or other objects
            int s = rand() % (r * c);
            temp_r = s % r;
            temp_c = s / r;
        }
        all_else.push_back(board_->get_rows() * temp_c + temp_r);
        players_[d]->SetPosition(Position(temp_c, temp_r));
        board_->SetSquareValue(Position(temp_c, temp_r), SquareType::Treasure);
    }
    //std::cout << "emtpy treasure "<< std::endl;
    //set enemy
    srand((unsigned int)(time(NULL)));
    //generate enemy position
    for(int d = 1; d < 3; d++){
        int temp_r = 0, temp_c=0;
        while(checkInPath(board_->get_rows() * temp_c + temp_r, wall_only) || checkInPath(board_->get_rows() * temp_c + temp_r, all_else)){ //enemy will not on the wall or other objects
            int s = rand() % (r * c);
            temp_r = s % r;
            temp_c = s / r;
        }
        no_ptr_path.push_back(4*temp_c + temp_r);
        wall_only.push_back(4*temp_c + temp_r);
        all_else.push_back(4*temp_c + temp_r);
        players_[d]->SetPosition(Position(temp_c, temp_r));
        board_->SetSquareValue(Position(temp_c, temp_r), SquareType::Enemy);
    }
    
    board_->SetSquareValue(Position(0,0), SquareType::Human);
    board_->SetSquareValue(Position(board_->get_cols()-1,board_->get_rows()-1), SquareType::Exit);

    //set exit
    players_[8]->SetPosition(Position(c-1, r-1));
    
}


/* 
Maze::~Maze(){
    delete board_;
} */
//for debug
void printer(std::vector<int> pri){
    for(unsigned int i  =0 ; i< pri.size(); i++){
        std::cout << pri[i] <<" ";
    }
    std::cout << std::endl;
}


//looking for availble direction based on current position
//it only take care of bounrdry of board
std::vector<int> getDirection(int point, int max_c, int max_r, std::vector<int> vec){
                        //{col,row} up left down right
    std::vector< int > ret;
    ret.push_back(point - max_r); //up
    ret.push_back(point + 1); //right
    ret.push_back(point + max_r); //down
    ret.push_back(point - 1); //left
    int r = point % max_r;
    int c = point / max_r;
    if(r == 0){
        ret.erase(ret.begin()+3);
    }else if(r == max_r - 1){
        ret.erase(ret.begin()+1);
    }
    if(c == 0){
        ret.erase(ret.begin());
    }else if(c == max_c - 1){
        ret.erase(ret.begin()+2);
    }
    
    std::vector<int> tmp;
    for(unsigned int i = 0; i < ret.size(); i++){
        if(!checkInPath(ret[i], vec)){
            tmp.push_back(ret[i]);
        }
    }
   
    return tmp;
}



//if enemy or player in the same position
//or if player at the exit, games end
bool Maze::IsGameOver(){
    if(players_[0]->get_position() == players_[8]->get_position()){
        players_[0]->ChangePoints(1);
        return true;
    }else if(players_[0]->get_position() == players_[1]->get_position() ||
    players_[0]->get_position() == players_[2]->get_position()){
        return true;
    }
    return false;
}
//not used
/* bool vec_push_back(int num, std::vector<int>& vec){
    if( vec[vec.size()-1] != num){
        vec.push_back(num);
        return true;
    }
    return false;
} */

//generate a soluable path of maze, return false it failed
bool Board::generate(){ 
    int max_step = 1; //max step to reach exit is 8
    int visited[cols_][rows_];;
    
    memset(visited, 0, sizeof(visited));
    
    path.push_back(0);
    srand((unsigned ) time(NULL));
    //int max = rows_ * cols_;
    visited[0][0] = 1;
    //len[0] = 1;
    //int start_r = 0;
    //int start_c = 0;
    //int end_c = cols_ - 1;
    //int end_r = rows_ - 1;
    //int time = 16;
        //the maximum step of soluable path is 12
        //because we need to leave space for enemy, player, treasure, and exit
     while( path[path.size()-1] != rows_ * cols_ - 1 && path.size() < 12 && max_step < 16){
        std::vector<int> direction = getDirection(path[path.size()-1], cols_, rows_, path);
        
        if(!direction.size()) return false;
        int curr = rand()%direction.size();
        if(!direction.size() ) return false;
        
        int temp_r = direction[curr] % rows_;
        int temp_c = direction[curr] / rows_;
        
        if(visited[temp_c][temp_r]) continue;
        visited[temp_c][temp_r] = 1;
        path.push_back(rows_ * temp_c + temp_r);
        
        max_step ++;
    } 
    
    if(path[path.size()-1] == rows_*cols_-1) return true;
    return false;
}

//get the value of sqauretype based on position
SquareType Board::get_square_value(Position pos) const {
    return arr_[pos.col][pos.row];
}; 
// TODO: you MUST implement the following functions

// set the value of a square to the given SquareType
void Board::SetSquareValue(Position pos, SquareType value){
    arr_[pos.col][pos.row] = value;
}

// get the possible Positions that a Player could move to
// (not off the board or into a wall)
std::vector<std::string> Board::GetMoves(Player *p){
    std::vector<std::string> str;
    Position temp_pos = p->get_position();
    //consider player is in the edge of baord
    //or player in the middle of board
    if(temp_pos.col == 0){
        if(SquareTypeStringify(arr_[temp_pos.col + 1][temp_pos.row]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col + 1][temp_pos.row]) != "Enemy")       
        str.push_back("DOWN");
    }else if(temp_pos.col == cols_ - 1){
        if(SquareTypeStringify(arr_[temp_pos.col - 1][temp_pos.row]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col - 1][temp_pos.row]) != "Enemy")       
        str.push_back("UP");
    }else{
        if(SquareTypeStringify(arr_[temp_pos.col + 1][temp_pos.row]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col + 1][temp_pos.row]) != "Enemy")
            str.push_back("DOWN");
        if(SquareTypeStringify(arr_[temp_pos.col - 1][temp_pos.row]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col - 1][temp_pos.row]) != "Enemy")
        str.push_back("UP");
    }
    //consider player is in the edge of baord
    //or player in the middle of board
    if(temp_pos.row == 0){
        if(SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row + 1]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row + 1]) != "Enemy")
        str.push_back("RIGHT");
    }else if(temp_pos.row == rows_ - 1){
        if(SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row - 1]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row - 1]) != "Enemy")
        str.push_back("LEFT");
    }else{
        if(SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row + 1]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row + 1]) != "Enemy")
        str.push_back("RIGHT");
        if(SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row - 1]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row - 1]) != "Enemy")
        str.push_back("LEFT");
        
    }
    return str;
}

// Move a player to a new position on the board. Return
// true if they moved successfully, false otherwise.
bool Board::MovePlayer(Player *p, Position pos, bool is_enemy){
    if(SquareTypeStringify(arr_[pos.col][pos.row]) != "Wall"){
       //p->set_position(pos.row, pos.col);
        if(SquareTypeStringify(arr_[pos.col][pos.row]) == "Treasure"){//anyone who touch treasure can increase points, the arr get updated
            
            //p->SetPosition(pos);
            SetSquareValue(pos, SquareType::Empty);
            p->ChangePoints(100);
        }
        if(SquareTypeStringify(arr_[pos.col][pos.row]) == "Enemy" && !is_enemy){ // if player touch enemy, player get kileld
            SetSquareValue(p->get_position(), SquareType::Empty);
            p->SetPosition(pos);
            return false;
        }
        if(SquareTypeStringify(arr_[pos.col][pos.row]) == "Human" && is_enemy){ // if enemy touch player, player get killed also
            SetSquareValue(pos, SquareType::Enemy);
            SetSquareValue(p->get_position(), SquareType::Empty);
            //arr_[pos.col][pos.row] = SquareType::Enemy;
            //arr_[p->get_position().col][p->get_position().row] = SquareType::Empty;
            std::cout << p->get_name()<<" catch you!" <<std::endl;
            p->SetPosition(pos);
            return false;
        }
        if(SquareTypeStringify(arr_[pos.col][pos.row]) == "Exit" && !is_enemy){ // when player touch exit, quit game
            SetSquareValue(p->get_position(), SquareType::Empty);
            return true;
        }else if(SquareTypeStringify(arr_[pos.col][pos.row]) == "Exit" && is_enemy){ //when enemy touch exit, do nothing
            return false;
        }
                                                                                //otherwise, swap two squaretype
        SquareType temp = arr_[p->get_position().col][p->get_position().row];
        arr_[p->get_position().col][p->get_position().row] = arr_[pos.col][pos.row];
        arr_[pos.col][pos.row] = temp;
        p->SetPosition(Position(pos.col, pos.row));
        return true;
    }
    return true;
}

void Maze::GenerateReport(std::vector<std::string> str, Player* curr_player){
    std::cout << curr_player->get_name() << " can go ";
    for(int y = 0; y < str.size(); y++){
        std::cout << str[y] << ", ";
    }
    std::cout << std::endl;
    std::cout <<"Please enter your choice" << std::endl;
}

// Get the square type of the exit square∏
SquareType Board::GetExitOccupant(){
    return SquareType::Exit;
}

// You probably want to implement this
std::ostream& operator<<(std::ostream& os, const Board &b){
    //Board *b = m.board_;
    for(int i = 0; i < b.cols_; i++){
        for(int e = 0; e < b.rows_; e++){
            //Position p =Position(i,e);
            std::string temp_str = SquareTypeStringify(b.arr_[i][e]);
            if(temp_str == "Wall"){
                std::cout << "❌";
            }else if(temp_str == "Exit"){
                std::cout << "✅";
            }else if(temp_str == "Empty"){
                std::cout << "⬜️";
            }else if(temp_str == "Human"){
                std::cout << "🦉";
            }else if(temp_str == "Enemy"){
                std::cout << "🤡";
            }else{
                std::cout << "🍐";
            }
        }
        std::cout << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Maze &m){
    std::cout << *m.board_ << std::endl;
    return os;
}
 
Player * Maze::getPlayer(int num){
    if(num < players_.size()){
        return players_[num];
    }else{
        return NULL;
    }
}

/* 
if player can only move with less than 2 direction, enemy won't attack player
in case player are blocked and no way to escape
otherwise enemy will calculate the direction of player and chase behind
 */

Position Maze::enemyStrategy(std::vector<SquareType> choice, std::vector<Position> po){
    //std::string str = ToRelativePosition(pos);
    
    //Position enemy_now = pos_;
    //std::cout << po.size() << std::endl;
         int i = rand()%choice.size();
    while(SquareTypeStringify(choice[i]) == "Wall" || SquareTypeStringify(choice[i]) == "Treasure" ){
        i = rand()%choice.size();
    }
    return po[i];
}
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
bool checkInPath(const int num, const std::vector<int> &vec){
    for(int d =0; d < vec.size(); d++){
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
    std::cout << "emtpy set "<< std::endl;
    //put wall on the board
    std::vector<int> path = board_->getPath();

    for(int i = 0; i < path.size(); i++){
        std::cout << path[i]<< " ";
    }
    std::cout << std::endl;
    std::vector<int> wall_only;
    std::vector<int> all_else;
    all_else.push_back(0);
    all_else.push_back(15);
    std::vector<int> no_ptr_path = path;
    srand((unsigned int)(time(NULL)));
    for(int d = 5; d < 8; d++){
        int temp_r = 0, temp_c=0;
        while(checkInPath(4*temp_c + temp_r, no_ptr_path)){
            int s = rand() % (r * c);
            temp_r = s % r;
            temp_c = s / r;
        }
        //no_ptr_path.push_back(board_->get_rows() * temp_c + temp_r);
        wall_only.push_back(board_->get_rows() * temp_c + temp_r);
        all_else.push_back(board_->get_rows() * temp_c + temp_r);
        players_[d]->SetPosition(Position(temp_c, temp_r));
        std::cout <<"wall : " << temp_c << " " << temp_r <<std::endl;
        board_->SetSquareValue(Position(temp_c, temp_r), SquareType::Wall);
    }
    std::cout << "emtpy wall "<< std::endl;
    //set treasure
    srand((unsigned int)(time(NULL)));
    for(int d = 3; d < 5; d++){
        int temp_r = 0, temp_c=0;
        while(checkInPath(board_->get_rows() * temp_c + temp_r, wall_only) || checkInPath(board_->get_rows() * temp_c + temp_r, all_else)){
            int s = rand() % (r * c);
            temp_r = s % r;
            temp_c = s / r;
        }
        //no_ptr_path.push_back(board_->get_rows() * temp_c + temp_r);
        all_else.push_back(board_->get_rows() * temp_c + temp_r);
        players_[d]->SetPosition(Position(temp_c, temp_r));
        std::cout <<"tresure : " << temp_c << " " << temp_r <<std::endl;
        board_->SetSquareValue(Position(temp_c, temp_r), SquareType::Treasure);
    }
    std::cout << "emtpy treasure "<< std::endl;
    //set enemy
    srand((unsigned int)(time(NULL)));
    for(int d = 1; d < 3; d++){
        int temp_r = 0, temp_c=0;
        while(checkInPath(board_->get_rows() * temp_c + temp_r, wall_only) || checkInPath(board_->get_rows() * temp_c + temp_r, all_else)){
            int s = rand() % (r * c);
            temp_r = s % r;
            temp_c = s / r;
        }
        no_ptr_path.push_back(4*temp_c + temp_r);
        all_else.push_back(4*temp_c + temp_r);
        players_[d]->SetPosition(Position(temp_c, temp_r));
        std::cout <<"enemy : " << temp_c << " " << temp_r <<std::endl;
        board_->SetSquareValue(Position(temp_c, temp_r), SquareType::Enemy);
    }
    std::cout << "emtpy enemy "<< std::endl;
    board_->SetSquareValue(Position(0,0), SquareType::Human);
    board_->SetSquareValue(Position(board_->get_cols()-1,board_->get_rows()-1), SquareType::Exit);
    std::cout << "everything set "<< std::endl;
}

/* 
Maze::~Maze(){
    delete board_;
} */

void printer(std::vector<int> pri){
    for(int i  =0 ; i< pri.size(); i++){
        std::cout << pri[i] <<" ";
    }
    std::cout << std::endl;
}

std::vector<int> getDirection(int point, int max_c, int max_r, std::vector<int> vec){
                        //{col,row} up left down right
    //int direction[4][2] ={{1,0},{0,1},{-1,0},{0,-1}};
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
    /* std::cout << "ret: " << point << std::endl;
    for(int i = 0; i < ret.size() ; i++)
        std::cout << ret[i] << " ";
    std::cout << std::endl;  */
   // printer(ret);
    std::vector<int> tmp;
    for(int i = 0; i < ret.size(); i++){
        if(!checkInPath(ret[i], vec)){
            tmp.push_back(ret[i]);
        }
    }
   // std::cout << "tmp: ";
   // printer(tmp);
    return tmp;
}



void printer1(std::vector<std::array<int, 2>> pri){
    for(int d =0; d < pri.size(); d++){
        std::cout<<pri[d][0] <<" " << pri[d][1] <<std::endl;
    }
        
}

bool Maze::IsGameOver(){
    if(players_[0]->get_position() == players_[8]->get_position()){
        return true;
    }else if(players_[0]->get_position() == players_[1]->get_position() ||
    players_[0]->get_position() == players_[2]->get_position()){
        return true;
    }
    return false;
}

bool vec_push_back(int num, std::vector<int>& vec){
    if( vec[vec.size()-1] != num){
        vec.push_back(num);
        return true;
    }
    return false;
}




bool Board::generate(){ 
    int max_step = 1; //max step to reach exit is 8
    int visited[cols_][rows_];;
    //int len[cols_*rows_]= {0};
    //memset( visited, 0, sizeof(visited) );
    //visited[0][0] = 0;
    memset(visited, 0, sizeof(visited));
     /* for(int d =0 ;d < cols_; d++){
        for(int f = 0; f < rows_; f++){
            std::cout << visited[d][f] << " ";
        }
        std::cout << std::endl;
    }  */
    //vector<int> path;
    path.push_back(0);
    srand((unsigned ) time(NULL));
    //int max = rows_ * cols_;
    visited[0][0] = 1;
    //len[0] = 1;
    int start_r = 0;
    int start_c = 0;
    int end_c = cols_ - 1;
    int end_r = rows_ - 1;
    int time = 16;
    //std::cout <<"befpre" << std::endl;
     while( path[path.size()-1] != 15 && path.size() < 13 && max_step < 16){
        std::vector<int> direction = getDirection(path[path.size()-1], cols_, rows_, path);
        //std::cout << "direction : ";
        //printer(direction);
        if(!direction.size()) return false;
        int curr = rand()%direction.size();
        if(!direction.size() ) return false;
        printer(path);
        int temp_r = direction[curr] % rows_;
        int temp_c = direction[curr] / rows_;
        //max_step ++;
        if(visited[temp_c][temp_r]) continue;
        visited[temp_c][temp_r] = 1;
        path.push_back(rows_ * temp_c + temp_r);
        //len[rows_ * temp_c + temp_r] = 1;
        max_step ++;
    } 
    //std::cout << "print path "<<std::endl;
    //printer(path);
    if(path[path.size()-1] == rows_*cols_-1) return true;
    return false;
}

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
std::vector<Position> Board::GetMoves(Player *p){
    std::vector<Position> ret;
    Position temp_pos = p->get_position();
    if(temp_pos.col == 0){
        if(SquareTypeStringify(arr_[temp_pos.col + 1][temp_pos.row]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col + 1][temp_pos.row]) != "Enemy")
        ret.push_back(Position(temp_pos.col + 1, temp_pos.row));
    }else if(temp_pos.col == cols_ - 1){
        if(SquareTypeStringify(arr_[temp_pos.col - 1][temp_pos.row]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col - 1][temp_pos.row]) != "Enemy")
        ret.push_back(Position(temp_pos.col - 1, temp_pos.row));
    }else{
        if(SquareTypeStringify(arr_[temp_pos.col + 1][temp_pos.row]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col + 1][temp_pos.row]) != "Enemy")
        ret.push_back(Position(temp_pos.col + 1, temp_pos.row));
        if(SquareTypeStringify(arr_[temp_pos.col - 1][temp_pos.row]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col - 1][temp_pos.row]) != "Enemy")
        ret.push_back(Position(temp_pos.col - 1, temp_pos.row));
    }

    if(temp_pos.row == 0){
        if(SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row + 1]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row + 1]) != "Enemy")
        ret.push_back(Position(temp_pos.col , temp_pos.row + 1));
    }else if(temp_pos.row == rows_ - 1){
        if(SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row - 1]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row - 1]) != "Enemy")
        ret.push_back(Position(temp_pos.col , temp_pos.row - 1));
    }else{
        if(SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row + 1]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row + 1]) != "Enemy")
        ret.push_back(Position(temp_pos.col , temp_pos.row + 1));
        if(SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row - 1]) != "Wall" &&
            SquareTypeStringify(arr_[temp_pos.col ][temp_pos.row - 1]) != "Enemy")
        ret.push_back(Position(temp_pos.col , temp_pos.row - 1));
    }
    return ret;
}

// Move a player to a new position on the board. Return
// true if they moved successfully, false otherwise.
bool Board::MovePlayer(Player *p, Position pos){
    if(SquareTypeStringify(arr_[pos.col][pos.row]) != "Wall"){
       //p->set_position(pos.row, pos.col);
        p->SetPosition(Position(pos.col, pos.row));
        SquareType temp = arr_[p->get_position().col][p->get_position().row];
        arr_[p->get_position().col][p->get_position().row] = arr_[pos.col][pos.row];
        arr_[pos.col][pos.row] = temp;
        return true;
    }
    return false;
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
 

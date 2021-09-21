#include<iostream>
#include<vector>
#include<cstdlib>
#include<array>
#include"Maze.h"
#include<time.h>
#include<cstring>
//using namespace std;
//return true when the path is not in the vector
bool checkInPath(const int num, const std::vector<int> &vec){
    for(int d =0; d < vec.size(); d++){
        if(vec[d] == num) return true;
    }
    return false;
}


Board::Board(){
	rows_ = 4;
    cols_ = 4;
    generate();
}

Board::Board(int r, int c){
    rows_ = r;
    cols_ = c;
    generate();
}

void Board::displayUpdated(){
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
}

Maze::Maze(int r, int c, std::string name){
    //generate (board_);
    board_ = new Board(r, c);
    players_.push_back(new Player(name ,1));
    players_.push_back(new Player( ,0));
    players_.push_back(new Player(name ,0));
    players_.push_back(new Player(name ,0));
    players_.push_back(new Player(name ,0));
    players_.push_back(new Player(name ,0));
    players_.push_back(new Player(name ,0));
    players_.push_back(new Player(name ,0));
    

}

Maze::~Maze(){
    delete board_;
}

std::vector<int> getDirection(int point, int max_r, int max_c){
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
    std::cout << "ret: " << point << std::endl;
    for(int i = 0; i < ret.size() ; i++)
        std::cout << ret[i] << " ";
    std::cout << std::endl; 
    return ret;
}

void printer(std::vector<int> pri){
    for(int i  =0 ; i< pri.size(); i++){
        std::cout << pri[i] <<" ";
    }
    std::cout << std::endl;
}

void printer1(std::vector<std::array<int, 2>> pri){
    for(int d =0; d < pri.size(); d++){
        std::cout<<pri[d][0] <<" " << pri[d][1] <<std::endl;
    }
        
}

bool Maze::IsGameOver(){
    
}


bool Board::generate(){ 
    int max_step = 1; //max step to reach exit is 8
    int visited[cols_][rows_] ;
    //visited[0][0] = 0;
    memset(visited, 0, sizeof(visited));
    for(int d =0 ;d < cols_; d++){
        for(int f = 0; f < rows_; f++){
            std::cout << visited[d][f] << " ";
        }
        std::cout << std::endl;
    }
    //vector<int> path;
    path.push_back(0);
    srand((unsigned ) time(NULL));
    int max = rows_ * cols_;
    visited[0][0] = 1;
    int start_r = 0;
    int start_c = 0;
    int end_c = cols_ - 1;
    int end_r = rows_ - 1;
     while( path[path.size()-1] != 15 && path.size() < 13 && max_step < 16){
        std::vector<int> direction = getDirection(path[path.size()-1], rows_, cols_);
        //printer1(direction);
        int curr = rand()%direction.size();
        int temp_r = direction[curr] % rows_;
        int temp_c = direction[curr] / rows_;
        

        //std::cout << direction[curr][0] << " " << direction[curr][1] << std::endl;
        if(visited[temp_c][temp_r]) continue;
        std::cout << "tmp_point " << temp_r << " " << temp_c <<  std::endl;
        //std::cout << "tmp_c " << temp_c << std::endl;
        std::cout <<"-------------"<<std::endl;
         for(int t =0; t < cols_; t++){
            for(int y =0; y < rows_; y++){
                if(t == temp_c && y == temp_r){
                    std::cout << 2 << " ";
                }else{
                    std::cout << visited[t][y] << " ";
                } 
                //std::cout << visited[t][y] << " ";
                
            }
            std::cout << std::endl;
        }
        std::cout <<"-------------"<<std::endl;
        path.push_back(direction[curr]);
        max_step ++;
        
        //start_c += direction[curr][0];
        //start_r += direction[curr][1];
        visited[temp_c][temp_r] = 1;
        direction.clear();
        //displayUpdated();
    } 
    printer(path);
    if(start_r == end_r && start_c == end_c) return true;
    return false;
}


 using namespace std;
int PGMimageProcessor::NumIslands(Pixel ** &grid){
         if(grid==nullptr){
            return 0;
        }
        int id=1;
        int numComps = 0;
        int H = imageRows;
        int W = imageCols;
      
        auto inside =[&](int row,int col){
            return 0<=row &&row < H && 0 <=col && col < W;
        };
        std::vector<std::pair<int,int>> directions{{1,0},{0,1},{-1,0},{0,-1}};
        std::vector<std::vector<bool>> vis(H,std::vector<bool>(W));
    
        for(int row =0;row<H;row++){
            for(int col=0;col<W;col++){
                if(!vis[row][col]&& int(grid[row][col].pixel)==0){
                 
                  ConnectedComponent component;
                  std::queue<std::pair<int , int>> q;
                  q.push({row,col});
                  vis[row][col]=true;
                  while(q.empty()){
                      std::pair<int, int> p=q.front();
                      q.pop();
                      for(std::pair<int,int> dir:directions){
                          int new_row=p.first;
                          int new_col=p.second;
                          if(inside(new_row,new_col) && !vis[new_row][new_col] && int(grid[new_row][new_col].pixel)==0){
                               numComps++;
                              q.push({new_row,new_col});
                              vis[new_row][new_col]=true;

                          }
                      }
                  }


                }
               



            }
        }
        return numComps;
    }
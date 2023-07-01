#include <iostream>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h>


using namespace std;

char board[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
int end_game_cnt=9;

//Function to make a mark on board.
void insert_char(int i,int j,char c)
{
    board[i][j]=c;
    end_game_cnt--;
}

//Function to print board.
void print_board()
{
    cout<<"\n";
    cout << "1      |2       |3\n";
    cout <<"   "<<board[0][0] << "   |   "<<board[0][1] << "    |   "<<board[0][2]<<"\n";
    cout << "_______|________|_______\n";
    cout << "4      |5       |6\n";
    cout <<"   "<<board[1][0] << "   |   "<<board[1][1] << "    |   "<<board[1][2]<<"\n";
    cout << "_______|________|_______\n";
    cout << "7      |8       |9\n";
    cout <<"   "<<board[2][0] << "   |   "<<board[2][1] << "    |   "<<board[2][2]<<"\n";
    cout << "       |        |\n\n";
}

//Function which gives score of winning if we mark c(either system's or players) at i,j.
int get_score(int i,int j,char c)
{   int ans=0;
    int cnt=0;
    int temp=board[i][j];
    board[i][j]=c;
    for(int i=0;i<3;i++)
    {
      vector<char> vec;
      int temp_cnt=0;
      int temp_ans=0;
      for(int j=0;j<3;j++)
      {
          if(board[i][j]=='O' || board[i][j]=='X') {
                vec.push_back(board[i][j]);
                if(board[i][j]==c) temp_cnt++;}
      }
      if(temp_cnt!=vec.size()) continue;
      if(temp_cnt==2) temp_ans=1e3;
      else if(temp_cnt==3) temp_ans=1e5;
      if(temp_ans>ans)
      {
          ans=temp_ans;
          cnt=1;
      }
      else if(temp_ans==ans) cnt++;
    }

    for(int j=0;j<3;j++)
    {
      vector<char> vec;
      int temp_cnt=0;
      int temp_ans=0;
      for(int i=0;i<3;i++)
      {
          if(board[i][j]=='O' || board[i][j]=='X') {
                vec.push_back(board[i][j]);
                if(board[i][j]==c) temp_cnt++;}
      }
      if(temp_cnt!=vec.size()) continue;
      if(temp_cnt==2) temp_ans=1e3;
      else if(temp_cnt==3) temp_ans=1e5;
      if(temp_ans>ans)
      {
          ans=temp_ans;
          cnt=1;
      }
      else if(temp_ans==ans) cnt++;
    }

      vector<char> vec;
      int temp_cnt=0;
      int temp_ans=0;

      for(int i=0;i<3;i++){
          if(board[i][i]=='O' || board[i][i]=='X') {
                vec.push_back(board[i][i]);
                if(board[i][i]==c) temp_cnt++;}
      }


      if(temp_cnt==vec.size()){
      if(temp_cnt==2) temp_ans=1e3;
      else if(temp_cnt==3) temp_ans=1e5;
      if(temp_ans>ans)
      {
          ans=temp_ans;
          cnt=1;
      }
      else if(temp_ans==ans) cnt++;

      }
       vec.clear();
       temp_cnt=0;
       temp_ans=0;

      for(int i=0;i<3;i++){
          if(board[i][2-i]=='O' || board[i][2-i]=='X') {
                vec.push_back(board[i][i]);
                if(board[i][2-i]==c) temp_cnt++;}
      }

      if(temp_cnt==vec.size()){
      if(temp_cnt==2) temp_ans=1e3;
      else if(temp_cnt==3) temp_ans=1e5;
      if(temp_ans>ans)
      {
          ans=temp_ans;
          cnt=1;
      }
      else if(temp_ans==ans) cnt++;
      }
      board[i][j]=temp;
    return cnt*ans;

}

//Function which checks if player won.
int check_for_player_win(int i,int j)
{   int c=0;
    for(int k=0;k<3;k++)
        if(board[i][k]=='X') c++;
        else break;
    if(c==3) return 1;
    c=0;
     for(int k=0;k<3;k++)
        if(board[k][j]=='X') c++;
        else break;
    if(c==3) return 1;
    if(i==j)
    {
        c=0;
    for(int k=0;k<3;k++)
        if(board[k][k]=='X') c++;
        else break;
    if(c==3) return 1;
    }
    if(i==2-j)
    {
        c=0;
    for(int k=0;k<3;k++)
        if(board[k][2-k]=='X') c++;
        else break;
    if(c==3) return 1;
    }
    return 0;

}

//Function to make a move of player.
int player_turn()
{
    int num;
    cout << "Enter your turn: ";
    cin >> num;
    int i=(num-1)/3;
    int j=(num-1)%3;
    if(board[i][j]=='X' || board[i][j]=='O') return -1;
    insert_char(i,j,'X');
    if(check_for_player_win(i,j)==1) return 1;
    return 0;
}

//Function for the computer to make it's move.
int computer_turn()
{  srand(time(0));
    vector<vector<int>> vec1(3,vector<int>(3));
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]!='O' && board[i][j]!='X')
            {
               vec1[i][j]=get_score(i,j,'O');
               if(vec1[i][j]>=1e5) {
                     insert_char(i,j,'O');
                    return 1e5;}
            }
            else vec1[i][j]=-1;
        }
    }
    int ans=0;
    vector<pair<int,int>> vec2;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]!='O' && board[i][j]!='X')
            {
               int temp_score=get_score(i,j,'X');
               if(temp_score>ans)
               {   ans=temp_score;
                   vec2.clear();
                   vec2.push_back({i,j});
               }
               else if(temp_score==ans)
               {
                  vec2.push_back({i,j});
               }
            }

        }
    }
    vector<pair<int,int>> vec3;
    ans=0;
    for(auto x:vec2)
    {
        int i=x.first;
        int j=x.second;
        if(vec1[i][j]>ans)
        {
            vec3.clear();
            vec3.push_back({i,j});
            ans=vec1[i][j];
        }
        else if(vec1[i][j]==ans)
            {
            vec3.push_back({i,j});
        }
    }

     int k=rand()%vec3.size();
    int i=vec3[k].first;
    int j=vec3[k].second;
    cout << "system chose : "<<i*3+j+1 << "\n";
     insert_char(i,j,'O');
     return 0;
}

int main()
{
    cout << "System symbol : O\nPlayer symbol : X\n";

    print_board();

    cout << "Who will start first?\nEnter 1 for the system to start\nEnter 0 if u want to start\n";
     int turn;
        cin >> turn;
        cout << "\n";
    while(end_game_cnt)
    {

        if(turn==1) {
                int temp=computer_turn();print_board();
        if(temp>=1e5){
            cout<<"System won.\n\n";
            return 0;
        }
        }
        else if(turn==0) {
        int temp=player_turn();
        if(temp==-1){
            cout<<"invalid input";
            return 0;
        }

        print_board();
        if(temp==1){
            cout<<"You won!.\n\n";
            return 0;
        }}
        turn=1-turn;

    }
    cout << "Oops! It's a tie.\n\n" ;
    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
using namespace std;
int INF=1000000000;
struct member{
    string name;
    vector<pair<string,int>> ex_date;
    int work_count=0;
};
class timetable{
private:
    vector<vector<string>> table;
    vector<string> days;
    vector<member> members;
    int times;
public:
    timetable(){
        set_val();
    }
    void set_val(){
        std::cout << "[안내] (테이블을 만들 모든 날짜)를 한줄에 입력해주세요(예- 6/19 6/20 6/21 6/25 6/26 6/27 7/1 )\n";
        string str;
        getline(cin,str);
        for(int i=0;i<str.size();i++){
            if(str[i]=='/')
                days.push_back(str.substr(i-1,4));
        }
        std::cout << "[안내] (필요한 타임 수)를 입력해주세요 (예- 10~11,11~12,1~2,2~3,3~4,4~5 시간에 인원이 필요하면 6입력)\n";
        std::cin >> times;
        
        table.resize(days.size(),vector<string>(times));
        std::cout << "[안내] (인원이름 안되는날짜-타임)을 입력해주세요 (예- 손태균 6/19-2 6/20-1 6/20-5) 마지막인원인 경우 0을 입력해주세요\n";
        cin.ignore();
        while(1){
            getline(cin,str);
            if(str[0] == '0')
                break ;
            bool flag=false;
            member tmp_mem;
            for(int i=0;i<str.size();i++){
                if(str[i]==' '){
                    if(!flag){
                        tmp_mem.name=str.substr(0,i);
                        flag=true;
                    }
                    else if(str[i-1]!=' '){
                        tmp_mem.ex_date.push_back({str.substr(i-6,4),stoi(str.substr(i-1,1))});
                    }

                }
            }
            if(str.back()!=' ')
                tmp_mem.ex_date.push_back({str.substr(str.size()-6,4),stoi(str.substr(str.size()-1,1))});
            members.push_back(tmp_mem);
        }
    }   
    
    void recursive(int x,int y){
        if(y>=times){
            recursive(x+1,0);
            return ;
        }
        else if(x>=days.size())
            return ;
        int min_val=INF,min_idx=-1;
        std::random_device rd;
        std::mt19937 g(rd());
        shuffle(members.begin(),members.end(),g);
        for(int i=0;i<members.size();i++){
            bool flag = false;
            for(pair<string,int> ed : members[i].ex_date){
                if(days[x]==ed.first && y+1==ed.second)
                    flag=true;
            }
            if(flag)
                continue ;
            if(min_val>members[i].work_count){
                min_val = min(members[i].work_count,min_val);
                min_idx = i;
            }
        }
        if(min_idx!=-1){
            table[x][y]=members[min_idx].name;
            members[min_idx].work_count++;
        }
        recursive(x,y+1);
    }

    void find_table(){
        recursive(0,0);
        std::cout << "------테이블-------------------------------\n";
        for(int i=0;i<days.size();i++){
            std::cout << days[i] << "   ";
        }
        std::cout << '\n';
        for(int j=0;j<times;j++){
            for(int i=0;i<days.size();i++)
                std::cout << table[i][j]<<" ";
            std::cout << '\n';
        }
        std::cout << "-----------------------------------------\n";
        
        for(member mb : members){
            std::cout << mb.name <<" : "<< mb.work_count <<"회\n";
        }

    }


};
int main(){
    timetable tt; 
    tt.find_table();
    return 0;
}
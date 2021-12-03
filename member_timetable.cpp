#include <iostream>
#include <vector>
#include <string>
using namespace std;
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
        std::cout << "테이블을 만들 모든 날짜를 한줄에 입력해주세요(예- 6/19 6/20 6/21 6/25 6/26 6/27 7/1 )\n";
        string str;
        getline(cin,str);
        for(int i=0;i<str.size();i++){
            if(str[i]=='/')
                days.push_back(str.substr(i-1,i+3));
        }
        std::cout << "하루에 필요한 시간단위 수를 입력해주세요 (예- 10~11,11~12,1~2,2~3,3~4,4~5 시간에 인원이 필요하면 6입력)\n";
        std::cin >> times;
        
        table.resize(days.size(),vector<string>(times));
        std::cout << "(인원 이름) (안되는 시간)을 입력해주세요 (예- 손태균 6/19-2 6/20-1 6/20-5) 마지막인원인 경우 0을 입력해주세요\n";
        while(1){
            getline(cin,str);
            if(str[0] == '0')
                break ;
            bool flag=false;
            member tmp_mem;
            for(int i=0;i<str.size();i++){
                if(str[i]==' ' ){
                    if(flag==false){
                        tmp_mem.name=str.substr(0,i);
                        flag=true;
                    }
                    else if(str[i-1]!=' '){
                        tmp_mem.ex_date.push_back({str.substr(i-6,i-2),stoi(str.substr(i-1,i))});
                    }

                }
            }
            members.push_back(tmp_mem);
        }
        for(member mb : members){
            std::cout << mb.name<<'\n';
            for(pair<string,int> st : mb.ex_date)
                std::cout << st.first << ' ';
            std::cout << '\n';
        }

    }   



};
int main(){
    timetable tt; 

    return 0;
}
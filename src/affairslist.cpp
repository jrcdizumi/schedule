#include "affairslist.h"
affairs::affairs()
{
    kind=-1;
    name="";
    for(int i=1;i<17;i++)week[i]=false;
    day=-1;
    start_time=-1;
    end_time=-1;
    location="";
    exam_time="";
    exam_location="";
}
affairs::affairs(int kind, std::string name, int day,int start_time, int end_time, std::string location, std::string exam_time, std::string exam_location)
{
    this->kind=kind;
    this->name=name;
    for(int i=0;i<17;i++)week[i]=false;
    this->day=day;
    this->start_time=start_time;
    this->end_time=end_time;
    this->location=location;
    this->exam_time=exam_time;
    this->exam_location=exam_location;
}
affairslist::affairslist()
{
    Json::Reader reader;
    Json::Value root;
    string loc=".\\data\\affairslist.json";
    ifstream in(loc,ios::binary);
    if(!in.is_open()){
        cout<<"error opening file\n";
    }
    if(reader.parse(in,root)){
        for(int i=0;i<root.size();i++){
            affairs thisaffair(root[i]["kind"].asInt(),
                    root[i]["name"].asString(),
                    root[i]["day"].asInt(),
                    root[i]["start_time"].asInt(),
                    root[i]["end_time"].asInt(),
                    root[i]["location"].asString(),
                    root[i]["exam_time"].asString(),
                    root[i]["exam_location"].asString()
                );
                Json::Value jsweek=root[i]["week"];
                for(int j=0;j<jsweek.size();j++){
                    thisaffair.week[j]=jsweek[j].asBool();
                }
                Json::Value jsstudent=root[i]["student"];
                for(int j=0;j<jsstudent.size();j++){
                    thisaffair.student.push_back(jsstudent[j].asInt());
                }
            list.push_back(thisaffair);
            serach_trie.insert(thisaffair.name,i);
        }
    }
};
affairslist::~affairslist()
{
    Json::Value root;
    for(int i=0;i<list.getSize();i++){
        Json::Value thisaffair;
        thisaffair["kind"]=list[i].kind;
        thisaffair["name"]=list[i].name;
        thisaffair["day"]=list[i].day;
        thisaffair["start_time"]=list[i].start_time;
        thisaffair["end_time"]=list[i].end_time;
        thisaffair["location"]=list[i].location;
        thisaffair["exam_time"]=list[i].exam_time;
        thisaffair["exam_location"]=list[i].exam_location;
        Json::Value jsstudent;
        for(int j=0;j<list[i].student.getSize();j++){
            jsstudent.append(list[i].student[j]);
        }
        thisaffair["student"]=jsstudent;
        Json::Value jsweek;
        for(int j=0;j<17;j++){
            jsweek.append(list[i].week[j]);
        }
        thisaffair["week"]=jsweek;
        root.append(thisaffair);
    }
    Json::StyledWriter writer;
    string loc=".\\data\\affairslist.json";
    ofstream out(loc,ios::binary);
    out<<writer.write(root);
    out.close();
};
Vector<affairs> affairslist::search_affairs(std::string name,int student_id)
{
    Vector<affairs> result;
    Vector<int> ans=serach_trie.search(name);
    for(int i=0;i<ans.getSize();i++){
        for(int i=0;i<list[ans[i]].student.getSize();i++){
            if(list[ans[i]].student[i]==student_id){
                result.push_back(list[ans[i]]);
                break;
            }
        }
    }
    return result;
}
void affairslist::add_affairs(int kind, std::string name, int day,int start_time, int end_time, std::string location, std::string exam_time, std::string exam_location, int week[17], Vector<int> student)
{
    affairs thisaffair(kind,name,day,start_time,end_time,location,exam_time,exam_location);
    for(int i=0;i<17;i++)thisaffair.week[i]=week[i];
    thisaffair.student=student;
    list.push_back(thisaffair);
    serach_trie.insert(name,list.getSize()-1);
}
bool affairslist::update_affairs(int a,int nowweek){
    affairs tmpaffairs=list[a];
    for(int i=nowweek+1;i<=16;i++){
        if(tmpaffairs.week[i]){
            return 0;
        }
    }
    list[a].kind=3;
    return 1;
}
affairslist Affairslist;

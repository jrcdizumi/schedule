#include "affairslist.h"

affairs::affairs()
{
    kind=-1;
    name="";
    for(int i=0;i<17;i++)week[i]=false;
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
                    thisaffair.student.push_back(jsstudent[j].asString());
                }
            list.push_back(thisaffair);
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
Vector<affairs> affairslist::search_affairs(int kind,std::string name,std::string student_id)
{
    Vector<affairs> result;
    int left = 0, right = list.getSize() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (list[mid].kind == kind && list[mid].name == name) {
            int l1=mid-1,r1=mid+1;
            while(l1>=0&&list[l1].kind==kind&&list[l1].name==name)l1--;
            while(r1<list.getSize()&&list[r1].kind==kind&&list[r1].name==name)r1++;
            for(int i=l1+1;i<r1;i++){
                int l2=0,r2=list[i].student.getSize()-1;
                while(l2<=r2){
                    int mid2=(l2+r2)/2;
                    if(list[i].student[mid2]==student_id){
                        result.push_back(list[i]);
                        break;
                    }
                    else if(list[i].student[mid2]<student_id){
                        l2=mid2+1;
                    }
                    else{
                        r2=mid2-1;
                    }
                }
           }
            break;
        }
        else if (list[mid].kind < kind || (list[mid].kind == kind && list[mid].name < name)) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return result;
}
void affairslist::add_affairs(int kind, std::string name, int day,int start_time, int end_time, std::string location, std::string exam_time, std::string exam_location, int week[17], Vector<string> student)
{
    affairs thisaffair(kind,name,day,start_time,end_time,location,exam_time,exam_location);
    for(int i=0;i<17;i++)thisaffair.week[i]=week[i];
    for(int i=0;i<student.getSize();i++)thisaffair.student.push_back(student[i]);
    list.push_back(thisaffair);
    for(int i=list.getSize()-1;i>0;i--){
        if(list[i].kind<list[i-1].kind||(list[i].kind==list[i-1].kind&&list[i].name<list[i-1].name)){
            affairs temp=list[i];
            list[i]=list[i-1];
            list[i-1]=temp;
        }
        else break;
    }
}

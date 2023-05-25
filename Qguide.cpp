#include "qguide.h"

Qguide::Qguide(QWidget *parent ) :
    QWidget(parent),
    ui(new Ui::Qguide)
{
    //this->setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
    ui->draw->installEventFilter(this);
    ui->SetofEnd->setReadOnly(true);
    ui->start_edit->setClearButtonEnabled(true);
    ui->end_edit->setClearButtonEnabled(true);
    img.load(":/data/map.jpg");
    QFile idFile(":/data/id.in");
    QFile PointFile(":/data/map.in");
    QFile EdgeFile(":/data/edge.in");
    idFile.open(QIODevice::ReadOnly);
    PointFile.open(QIODevice::ReadOnly);
    EdgeFile.open(QIODevice::ReadOnly);
    QTextStream input(&PointFile);
    QString tmp;
    int a,b,c;
    while(!input.atEnd()){
        input>>a>>b>>c;
        ps.push_back(node(QPointF(b,c),a,1));
//        qDebug()<<ps.back().point<<Qt::endl;
    }
    QTextStream input1(&idFile);
    IdtoName.resize(ps.size());
    while(!input1.atEnd()){
        input1>>a>>tmp>>c;
        qDebug()<<a<<" "<<tmp<<" "<<c<<Qt::endl;
        ps[a].f=ps[a].f&c;
        if(ps[a].f==0)
            location.append(tmp);
        idcheck.insert(tmp.toStdString(),a);
        IdtoName[a]=tmp.toStdString();
    }
    QTextStream input2(&EdgeFile);
    mymap::map_init(schoolmap,ps.size());
    while(!input2.atEnd()){
        input2>>a>>b>>c;
        mymap::add_edge(schoolmap,a,b,c,1);
        mymap::add_edge(schoolmap,b,a,c,1);
    }
    filter = new MyCompleter(location,this);
//    ui->draw->setAutoFillBackground(true);
    ui->draw->setAttribute(Qt::WA_TranslucentBackground);
//    pal = ui->draw->palette();
//    pal.setColor(QPalette::Window,QColor(0,0,0,100));
//    ui->draw->setPalette(pal);
    /*
    connect(filter, QOverload<const QString&>::of(&QCompleter::activated), this, [=](const QString& text) {
        // 在此处清空文本框中的文本
        ui->end_edit->clear();
    });
    connect(filter,SIGNAL(activated(QString)),this,SLOT(getactivited()));
    */

    ui->start_edit->setCompleter(filter);
    ui->end_edit->setCompleter(filter);

    ui->picture->setPixmap(QPixmap::fromImage(img));


    pixma = ui->picture->pixmap();
    QPainter painter(&pixma);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::red);

    for(int i=0;i<ps.size();i++){
        //qDebug()<<"wtf"<<Qt::endl;
        if(ps[i].f==0){
            //qDebug()<<ps[i].point<<Qt::endl;
            painter.drawEllipse(ps[i].point,R,R);
            ui->picture->setPixmap(pixma);
        }
    }

    init();
    return ;
}
void Qguide::getactivited(){
    qDebug()<<ui->end_edit->displayText()<<Qt::endl;
    ui->end_edit->clear();
    qDebug()<<ui->end_edit->displayText()<<Qt::endl;
    return;
}
Qguide::~Qguide()
{
    delete ui;
    delete filter;
    //delete tt;
}
bool Qguide::eventFilter(QObject *obj,QEvent *event){
    if(obj==ui->draw){
        if(event->type() == QEvent::MouseButtonPress){
            //qDebug()<<"???\n";
            QMouseEvent *mouse = static_cast<QMouseEvent*>(event);
            if(mouse->button()==Qt::LeftButton){

                //qDebug()<<mouse->pos()<<Qt::endl;
                QPointF poi = mouse->pos();
                QLineF line;
                bool flag=0;
                qDebug()<<" point :: "<<poi<<Qt::endl;
                for(int i=0;i<ps.count();i++){
                    qDebug()<<"match::"<<ps[i].f<<" id :: "<<ps[i].id<<Qt::endl;
                    if(ps[i].f==0){
                        line.setPoints(poi,ps[i].point);

                        if(line.length()<=R+2){
                            qDebug()<<ps[i].id<<Qt::endl;
                            flag=1;
                            if(choice==false){
                                changestartpoint(ps[i].id);

                            }
                            else{
                                add_endpoint(ps[i].id);

                            }
                            break;
                        }
                    }
                }
                if(flag==0){
                    QMessageBox::warning(this,tr("非地图选点"),tr("重新选择"),QMessageBox::Ok);
                }
                return true;
            }
        }
    }
    return false;
}


void Qguide::drawpath(edge &a){
    QLineF line(ps[a.from].point,ps[a.to].point);
    QPainter painter(&pixma);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::red);
    painter.drawLine(line);
    ui->draw->setPixmap(pixma);
    return ;
}

void Qguide::clear(){
    pixma.fill(Qt::transparent);
    //ui->draw->setStyleSheet("QLabel {background-color: transparent;}");
    ui->draw->setPixmap(pixma);


    //    QGraphicsOpacityEffect tt(ui->draw);
    //    tt.setOpacity(1);
    //    ui->draw->setGraphicsEffect(&tt);   
}
void Qguide::init(){
    clear();
    start=-1;

    choice=false;
    ui->startbutton->setChecked(1);
    mindis=true;
    ui->accuary->setChecked(1);
    pathid=-1;
    ui->start_edit->clear();
    clear_endpoint();
    ui->dis->clear();
    return ;
}


void Qguide::on_start_edit_textEdited(const QString &arg1)
{
    return;
}


void Qguide::on_start_edit_editingFinished()
{
    if(ui->start_edit->displayText()=="")
        return;
    if(idcheck.inhash(ui->start_edit->displayText().toStdString())==false){
        QMessageBox::warning(this,tr("地点错误"),tr("重新输入"),QMessageBox::Ok);
        return;
    }
    start=idcheck.get(ui->start_edit->displayText().toStdString());
    qDebug()<<start<<" "<<ui->start_edit->displayText()<<Qt::endl;
    return ;
}


void Qguide::on_startbutton_toggled(bool checked)
{
    if(checked){
        choice= false; //start
        qDebug()<<"start"<<Qt::endl;
    }
}


void Qguide::on_endbutton_toggled(bool checked)
{
    if(checked){
        choice= true; //end;
        qDebug()<<"end"<<Qt::endl;
    }
}


void Qguide::on_accuary_toggled(bool checked)
{
    if(checked){
        mindis=true;
        qDebug()<<"accuary"<<Qt::endl;
    }
}


void Qguide::on_SA_toggled(bool checked)
{
    if(checked){
        mindis=false;
        qDebug()<<"SA"<<Qt::endl;
    }
}
QPointF Qguide::mapTo(const QPixmap &pixmap,const QPoint &pos)const{
    qreal ratio = static_cast<qreal>(pixmap.width()) / width();
    return QPointF(pos.x() * ratio, pos.y() * ratio);
}


void Qguide::on_nextButton_clicked()
{
    if(pathid==-1){
        QMessageBox::warning(this,tr("未进行导航"),tr("点击开始导航"),QMessageBox::Ok);
    }
    else if(pathid==path.getSize()){
        QMessageBox::warning(this,tr("到达终点"),tr("到达终点了！"),QMessageBox::Ok);
    }
    else{
        drawpath(path[pathid]);
        pathid++;
    }
    return;
}


void Qguide::on_callButton_clicked()
{
    if(start ==-1 || endpoint.getSize() == 0){
        QMessageBox::warning(this,tr("数据错误"),tr("填写起始点"),QMessageBox::Ok);
        return ;
    }
    int ans=-1;
    if(mindis==0){
        ans=mymap::sa_mutidis(start,endpoint,schoolmap,path);
    }
    else{
        ans=mymap::accuratr_mutidis(start,endpoint,schoolmap,path);
    }
    pathid=0;
    ui->dis->setNum(ans);
    return ;
}


void Qguide::on_clearButton_clicked()
{
    init();
    return;
}


void Qguide::on_end_edit_editingFinished()
{
    if(ui->end_edit->completer()->popup()->isVisible()){
        return;
    }
    if(ui->end_edit->displayText()=="")
        return;
    //qDebug()<<ui->end_edit->displayText()<<Qt::endl;
    if(idcheck.inhash(ui->end_edit->displayText().toStdString())==false){
        QMessageBox::warning(this,tr("地点错误"),tr("重新输入"),QMessageBox::Ok);
        ui->end_edit->clear();
        return;
    }
    int i=idcheck.get(ui->end_edit->displayText().toStdString());
    add_endpoint(i);
    ui->end_edit->clear();
    return;
}


void Qguide::on_SetofEnd_textChanged(){
    return;
}


void Qguide::on_end_edit_textChanged(const QString &arg1)
{
    qDebug()<<ui->end_edit->displayText()<<Qt::endl;
    return;
}


void Qguide::on_end_edit_returnPressed()
{
    return;
}
void Qguide::add_endediter(){
    ui->SetofEnd->append(QString::number(endpoint.getSize())+" : "+QString::fromStdString(IdtoName[endpoint.back()]));
    ui->SetofEnd->moveCursor(QTextCursor::End);
    drawendpoint(ps[endpoint.back()].point);
    return;
}
bool Qguide::add_endpoint(int &tid){
    if(tid>=ps.size()){
        return 0;
    }
    endpoint.push_back(tid);
    add_endediter();
    return 1;
}
void Qguide::clear_endpoint(){
    endpoint.clear();
    ui->SetofEnd->clear();
    ui->end_edit->clear();
    return;
}
bool Qguide::add_endpoint(Vector<int> &tid){
    for(int i=0;i<tid.getSize();i++){
        if(tid[i]>=ps.size()){
            return 0;
        }
    }
    for(int i=0;i<tid.getSize();i++){
        add_endpoint(tid[i]);
    }
    return 1;
}
void Qguide::drawstartpoint(QPointF &p){
    QPainter painter;
    painter.setRenderHint(QPainter::Antialiasing,true);
    if(start!=-1){
        clear();
    }
    painter.begin(&pixma);
    if(start!=-1){
        for(int j=0;j<endpoint.getSize();j++){
            painter.setBrush(Qt::yellow);
            painter.drawEllipse(ps[endpoint[j]].point,R,R);
            ui->draw->setPixmap(pixma);
        }
    }

    painter.setBrush(Qt::green);
    painter.drawEllipse(p,R,R);
    ui->draw->setPixmap(pixma);
    painter.end();
        //                                    QRect rang (ps[start].point.rx()-R,ps[start].point.ry()-R,2*R,2*R);
        //                                    painter.setCompositionMode(QPainter::CompositionMode_Clear);
        //                                    painter.save();
        //                                    painter.setBrush(Qt::transparent);
        //                                    painter.fillRect(rang,Qt::transparent);
        //                                    painter.drawEllipse(ps[start].point,R,R);
        //                                    painter.eraseRect(ps[start].point.rx()-R,ps[start].point.ry()-R,2*R,2*R);
        //                                    painter.restore();
        //                                    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    return ;
}
void Qguide::drawendpoint(QPointF &p){
    QPainter painter;
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.begin(&pixma);
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(p,R,R);
    ui->draw->setPixmap(pixma);
    painter.end();
    return;
}
bool Qguide::changestartpoint(int &tmp){
    if(tmp>=ps.size()){
        return 0;
    }
    drawstartpoint(ps[tmp].point);
    if(ui->start_edit->displayText()!=QString::fromStdString(IdtoName[ps[tmp].id]))
        ui->start_edit->setText(QString::fromStdString(IdtoName[ps[tmp].id]));
    start=tmp;
    return 1;
}


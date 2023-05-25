#include "searchwindow2.h"
#include "qcombobox.h"
#include "ui_searchwindow2.h"
#include <QStandardItemModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "src/affairslist.h"
extern affairslist Affairslist;
extern Schedule schedule;
extern int now_user;
SearchWindow2::SearchWindow2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWindow2)
{
    ui->setupUi(this);
    // 初始化数组
   comboBox->addItem("课程");
   comboBox->addItem("活动");
   comboBox->addItem("临时事务");
   this->ui->horizontalLayout->insertWidget(8,comboBox);
    m_fruits << "Apple" << "Banana" << "Cherry" << "Durian" << "Elderberry" << "Fig" << "Grape"<<"ddd"<<"dadd"<<"a"<<"aahkjds"<<"dasnjdk";
    m_model = new QStandardItemModel(0,0,this);
    ui->tableView->setModel(m_model);
    connect(ui->tableView, &QTableView::clicked, this, [this](const QModelIndex &index)
            {
                int row = index.row(); // 获取被点击的单元格的行号
                int column = index.column(); // 获取被点击的单元格的列号
                qDebug()<<row<<" "<<column;
                course_info A;
                A.set_affair(a[row]);
                A.exec();
            });
    connect(m_model, &QStandardItemModel::dataChanged, this, [this](const QModelIndex &topLeft, const QModelIndex &bottomRight)
            {
                for (int row = topLeft.row(); row <= bottomRight.row(); ++row) {
                    for (int column = topLeft.column(); column <= bottomRight.column(); ++column) {
                        QModelIndex index = m_model->index(row, column);
                        QVariant before = index.data(Qt::UserRole); // 获取修改前的数据
                        QVariant after = m_model->data(index, Qt::DisplayRole); // 获取修改后的数据
                        change(before.toString(),after.toString());
                        qDebug() << "Before:" << before.toString() << ", After:" << after.toString();

                    }
                }
            });
    connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index){
        qDebug() << "当前选定的索引为：" << index;
    });
}

SearchWindow2::~SearchWindow2()
{
    delete ui;
}
void SearchWindow2::change(QString s,QString t)
{
    int len=this->m_fruits.size();
    for(int i=0;i<len;i++)
    {
        if(m_fruits.at(i)==s)
        {
            m_fruits.replace(i,t);
        }
    }
}
void SearchWindow2::on_searchButton_clicked()
{
    int skind=this->comboBox->currentIndex();
    qDebug()<<skind;
    int num=0,week=0,day=0,start_time=0,end_time=0;
    week=ui->spinBox->value();
    day=ui->spinBox_4->value();
    start_time=ui->spinBox_3->value();
    end_time=ui->spinBox_2->value();
    a=schedule.all_list[now_user].search_affairs(week,day,start_time,end_time,skind);
    for(int i=0;i<a.getSize();i++)
    {
        QString qstr = QString::fromStdString(Affairslist.list[a[i]].name);
        QStandardItem *item = new QStandardItem(qstr);
        item->setData(qstr, Qt::UserRole); // 保存原始数据
        m_model->setItem(num,0,item);
         Qt::Alignment alignment = Qt::AlignHCenter | Qt::AlignVCenter;
        m_model->setData(m_model->index(num, 0), QVariant::fromValue(alignment), Qt::TextAlignmentRole);//水平居中
        qDebug()<<QString::fromStdString(Affairslist.list[a[i]].name)<<" "<<QString::number(Affairslist.list[a[i]].day);
        num++;
    }
    if(num!=0)
    m_model->setColumnCount(1);
    else
     m_model->setColumnCount(0);
    m_model->setRowCount(num);
    // 根据模型中的行数，设置表格的行数
    ui->tableView->setModel(m_model);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->verticalHeader()->setDefaultSectionSize(this->ui->tableView->height()/5);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui-> tableView->horizontalHeader()->setDefaultSectionSize(this->ui->tableView->width());
    m_model->setHeaderData(0, Qt::Horizontal, "搜索结果");
    ui->tableView->setModel(m_model);

}
void SearchWindow2::closeEvent(QCloseEvent *event)
{
    event->accept();
}



void SearchWindow2::on_spinBox_3_valueChanged(int arg1)
{
    if(ui->spinBox_2->value()<=arg1)ui->spinBox_2->setValue(arg1+1);
}

void SearchWindow2::on_spinBox_2_valueChanged(int arg1)
{
    if(ui->spinBox_3->value()>=arg1)ui->spinBox_3->setValue(arg1-1);
}


#include "searchwindow.h"
#include "qcombobox.h"
#include "ui_searchwindow.h"
#include <QStandardItemModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "src/affairslist.h"
extern affairslist Affairslist;
Vector<affairs> a;
SearchWindow::SearchWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    // 初始化数组
    comboBox->addItem("课程");
   comboBox->addItem("活动");
    comboBox->addItem("临时事务");
   this->ui->horizontalLayout->insertWidget(1,comboBox);
     m_fruits << "Apple" << "Banana" << "Cherry" << "Durian" << "Elderberry" << "Fig" << "Grape"<<"ddd"<<"dadd"<<"a"<<"aahkjds"<<"dasnjdk";
    m_model = new QStandardItemModel(0,0,this);
    ui->tableView->setModel(m_model);
    connect(ui->tableView, &QTableView::clicked, this, [this](const QModelIndex &index)
            {
                int row = index.row(); // 获取被点击的单元格的行号
                int column = index.column(); // 获取被点击的单元格的列号
                qDebug()<<row<<" "<<column;
                course_info A;
                affairs b=a[row];
                //qDebug()<<QString::fromStdString(b.name)<<" "<<QString::number(b.day);
                A.setName(index.data().toString());
                A.setTeacher("李老师");
                A.setClassTime("周"+QString::number(b.day)+"第"+QString::number(b.start_time)+"节到"+QString::number(b.end_time)+"节");
                A.setExamTime(QString::fromStdString(b.exam_time));
                A.setLocation(QString::fromStdString(b.exam_location));
                A.setExamLocation(QString::fromStdString(b.exam_location));
                if(b.kind==1)
                    {
                    A.getButton()->setCheckable(true);
                    A.getButton()->setChecked(true);
                    A.getButton()->setEnabled(false);

                }

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
        if(this->ui->lineEdit->text()!="")
            this->on_searchButton_clicked();
    });
}

SearchWindow::~SearchWindow()
{
    delete ui;
}
void SearchWindow::change(QString s,QString t)
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
void SearchWindow::on_searchButton_clicked()
{
    int skind=this->comboBox->currentIndex();
    qDebug()<<skind;
    QString keyword = ui->lineEdit->text();
    int num=0;
    a=Affairslist.search_affairs(keyword.toStdString(),1,skind);
    for(int i=0;i<a.getSize();i++)
    {
        QString qstr = QString::fromStdString(a[i].name);
        QStandardItem *item = new QStandardItem(qstr);
        item->setData(qstr, Qt::UserRole); // 保存原始数据
        m_model->setItem(num,0,item);
         Qt::Alignment alignment = Qt::AlignHCenter | Qt::AlignVCenter;
        m_model->setData(m_model->index(num, 0), QVariant::fromValue(alignment), Qt::TextAlignmentRole);//水平居中
        qDebug()<<QString::fromStdString(a[i].name)<<" "<<QString::number(a[i].day);
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

void SearchWindow::on_lineEdit_returnPressed()
{
    SearchWindow::on_searchButton_clicked();
}
void SearchWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}



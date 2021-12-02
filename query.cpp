#include "query.h"
#include "ui_query.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>
#include <QDate>

Query::Query(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Query)
{
    ui->setupUi(this);

    QStringList labels;
    labels << "姓名" << "姓别" << "学号" << "书名" << "书ID" << "价格" << "借阅日期" << "归还日期" << "欠费情况";
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

Query::~Query()
{
    delete ui;
}

// 获取当前的日期或者时间
QString Query::getDateTime(Query::DateTimeType type)
{
    QDateTime datetime = QDateTime::currentDateTime();
    QString date = datetime.toString("yyyy-MM-dd");
    QString time = datetime.toString("hh:mm:ss");
    QString dateAndTime = datetime.toString("yyyy-MM-dd dddd hh:mm");
    if(type == Date)
        return date;
    else if(type == Time)
        return time;
    else
        return dateAndTime;
}

void Query::on_btn_query_clicked()
{
    QString person_id;
    person_id = ui->ldt_person_id->text();

    // "姓名" << "姓别" << "学号" << "书名" << "书ID" << "价格" << "借阅日期" << "归还日期" << "欠费情况";
    QSqlQuery query;
    query.exec(QString("select A.name, A.sex, A.num, B.name, B.book_id, B.price, B.date_borrow, B.date_return \
                       from persons A right join books B on A.id=B.person_id where A.id=%1").arg(person_id));
    if (query.lastError().isValid())      // 执行SQL语句有问题时，将错误输出 (调试用)
            qDebug() << query.lastError();

    int row = 0;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    while(query.next()){
        ui->tableWidget->insertRow(row);

        QTableWidgetItem *newItem0 = new QTableWidgetItem(query.value(0).toString());
        ui->tableWidget->setItem(row, 0, newItem0);

        QTableWidgetItem *newItem1 = new QTableWidgetItem(query.value(1).toString());
        ui->tableWidget->setItem(row, 1, newItem1);

        QTableWidgetItem *newItem2 = new QTableWidgetItem(query.value(2).toString());
        ui->tableWidget->setItem(row, 2, newItem2);

        QTableWidgetItem *newItem3 = new QTableWidgetItem(query.value(3).toString());
        ui->tableWidget->setItem(row, 3, newItem3);

        QTableWidgetItem *newItem4 = new QTableWidgetItem(query.value(4).toString());
        ui->tableWidget->setItem(row, 4, newItem4);

        QTableWidgetItem *newItem5 = new QTableWidgetItem(query.value(5).toString());
        ui->tableWidget->setItem(row, 5, newItem5);

        QTableWidgetItem *newItem6 = new QTableWidgetItem(query.value(6).toString());
        ui->tableWidget->setItem(row, 6, newItem6);

        QTableWidgetItem *newItem7 = new QTableWidgetItem(query.value(7).toString());
        ui->tableWidget->setItem(row, 7, newItem7);

        // 获取借阅日期和归还日期
        QDate date_borrow, date_return;

        date_borrow = query.value(6).toDate();
        if(query.value(7).isNull()) {
            // 如果书还没还，把当前日期当作归还日期进行计算
            date_return = QDate::fromString(getDateTime(Date), "yyyy-MM-dd");
        }
        else {
            date_return = query.value(7).toDate();
        }

        // 计算书借出去后，超出免费借阅天数(30天）多少天
        qint64 days;
        if(date_borrow.daysTo(date_return) > 30) {
            days = date_borrow.daysTo(date_return) - 30;
        }
        else {
            days = 0;
        }

        QTableWidgetItem *newItem8 = new QTableWidgetItem(QString("%1").arg(days));
        ui->tableWidget->setItem(row, 8, newItem8);

        row++;
    }
}

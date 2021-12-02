#include "returnbook.h"
#include "ui_returnbook.h"
#include <QDateTime>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDate>
#include <QDebug>

ReturnBook::ReturnBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReturnBook)
{
    ui->setupUi(this);

    ui->ldt_time_return->setText(getDateTime(Date));
}

ReturnBook::~ReturnBook()
{
    delete ui;
}

// 获取当前的日期或者时间
QString ReturnBook::getDateTime(ReturnBook::DateTimeType type)
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

void ReturnBook::on_btn_return_clicked()
{
    QString book_id, date; // person_id,

    // 获取输入框内的信息
//    person_id = ui->ldt_person_id->text();
    book_id = ui->ldt_book_id->text();
    date = ui->ldt_time_return->text();

//    // 判断输入信息有误（人的ID和书的ID是否存在于数据库中？)
    QSqlQuery query;
//    query.exec(QString("select * from persons where id=%1").arg(person_id));
//    if(query.size() < 1) {
//        QMessageBox::critical(this, "Error", "数据库中不存该借阅人信息", QMessageBox::Ok);
//        return;
//    }

//    query.clear();
    query.exec(QString("select * from books where book_id=%1").arg(book_id));
    if(query.size() < 1) {
        QMessageBox::critical(this, "Error", "数据库中不存在该书信息", QMessageBox::Ok);
        return;
    }

    // 判断该书是否已经被借出(判断字段借阅人ID：person_id是否为空，不为空说明被借）
    query.next();       // QSqlQuery返回的数据集，record是停在第一条记录之前的。所以，你获得数据集后，必须执行next()或first()到第一条记录，这时候record才是有效的。
    if(query.value(3).toInt() == 0){
        QMessageBox::critical(this, "Error", "该书还未被借", QMessageBox::Ok);
        return;
    }

    // 获取借书时间和还书时间
    QDate date_borrow, date_return;
    date_borrow = query.value(4).toDate();
    date_return = QDate::fromString(date, "yyyy-MM-dd");

    // 计算书借出去后，超出免费借阅天数(30天）多少天
    qDebug() << date_borrow << "  " << date << " " << date_return << " " << date_borrow.daysTo(date_return);
    if(date_borrow.daysTo(date_return) > 30) {
        // 有超期情况下
        query.exec(QString("update books set books.date_return='%1' where book_id=%2").arg(date).arg(book_id));
        QMessageBox::about(this, "提示", "该书超期归还，产生欠费");
    }
    else {
        // 无超期情况下，清空借阅人ID, 借阅日期
        query.exec(QString("update books set books.person_id=default, books.date_borrow=default where book_id=%1").arg(book_id));
        QMessageBox::about(this, "提示", "该书按期归还，多谢合作");
    }

}

void ReturnBook::on_btn_quit_clicked()
{
    this->accept();
}

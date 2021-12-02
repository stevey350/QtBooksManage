#include "borrowbook.h"
#include "ui_borrowbook.h"
#include <QDateTime>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtGui>

BorrowBook::BorrowBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BorrowBook)
{
    ui->setupUi(this);

    ui->ldt_time_borrow->setText(getDateTime(Date));        // 在界面中的借阅日期显示为当前日期
}

BorrowBook::~BorrowBook()
{
    delete ui;
}

// 获取当前的日期或者时间
QString BorrowBook::getDateTime(BorrowBook::DateTimeType type)
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

void BorrowBook::on_btn_borrow_clicked()
{
    QString person_id, book_id, date;

    // 获取输入框内的信息
    person_id = ui->ldt_person_id->text();
    book_id = ui->ldt_book_id->text();
    date = ui->ldt_time_borrow->text();

    // 判断输入信息有误（人的ID和书的ID是否存在于数据库中？)
    QSqlQuery query;
    query.exec(QString("select * from persons where id=%1").arg(person_id));
    if(query.size() < 1) {
        QMessageBox::critical(this, "Error", "数据库中不存该借阅人信息", QMessageBox::Ok);
        return;
    }

    query.clear();
    query.exec(QString("select * from books where book_id=%1").arg(book_id));
    if(query.size() < 1) {
        QMessageBox::critical(this, "Error", "数据库中不存在该书信息", QMessageBox::Ok);
        return;
    }

    // 判断该书是否已经被借出(判断字段借阅人ID：person_id是否为空，不为空说明被借）
    query.next();       // QSqlQuery返回的数据集，record是停在第一条记录之前的。所以，你获得数据集后，必须执行next()或first()到第一条记录，这时候record才是有效的。
    if(query.value(3).toInt() != 0){
        QMessageBox::critical(this, "Error", "该书已经被借", QMessageBox::Ok);
        return;
    }

    // 将书借出，更新书的信息
    query.exec(QString("update books set books.person_id=%1, books.date_borrow='%2' where book_id=%3").arg(person_id).arg(date).arg(book_id));

    QMessageBox::about(this, "提示", "该书成功被借出");
}

void BorrowBook::on_btn_quit_clicked()
{
    this->accept();
}

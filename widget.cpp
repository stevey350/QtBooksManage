#include "widget.h"
#include "ui_widget.h"
#include "manage.h"
#include "borrowbook.h"
#include "returnbook.h"
#include "query.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_manage_clicked()
{
    this->hide();           // 隐藏主窗口

    Manage w(this);
    w.setModal(true);       // 设置成模态方式（阻塞住，直到窗口关闭）
    w.exec();

    this->show();           // 显示主窗口
}

void Widget::on_btn_borrow_clicked()
{
    this->hide();           // 隐藏主窗口

    BorrowBook w(this);
    w.setModal(true);       // 设置成模态方式（阻塞住，直到窗口关闭）
    w.exec();

    this->show();           // 显示主窗口
}

void Widget::on_btn_query_clicked()
{
    this->hide();           // 隐藏主窗口

    Query w(this);
    w.setModal(true);       // 设置成模态方式（阻塞住，直到窗口关闭）
    w.exec();

    this->show();           // 显示主窗口
}

void Widget::on_btn_return_clicked()
{
    this->hide();           // 隐藏主窗口

    ReturnBook w(this);
    w.setModal(true);       // 设置成模态方式（阻塞住，直到窗口关闭）
    w.exec();

    this->show();           // 显示主窗口
}

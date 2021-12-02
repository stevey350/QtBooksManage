#include "manage.h"
#include "ui_manage.h"
#include <QtGui>
#include <QMessageBox>
#include <QSqlError>

Manage::Manage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manage)
{
    ui->setupUi(this);
    ui->ldt_book_id->setFocusPolicy(Qt::ClickFocus);

    // 借阅人管理 数据模型和显示窗口初始化
    query_model_person = new QSqlQueryModel(this);
    query_model_person->setQuery("select * from persons");
    query_model_person->setHeaderData(0, Qt::Horizontal, tr("借阅人ID"));
    query_model_person->setHeaderData(1, Qt::Horizontal, tr("姓名"));
    query_model_person->setHeaderData(2, Qt::Horizontal, tr("学号"));
    query_model_person->setHeaderData(3, Qt::Horizontal, tr("性别"));

    ui->tableView_person->setModel(query_model_person);
    ui->tableView_person->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 所有列都扩展自适应宽度，填充充满整个屏幕宽度

    // 图书管理
    query_model_book = new QSqlQueryModel(this);
    // query_model_book->setQuery("select A.book_id, A.name, A.price from books as A");
    query_model_book->setQuery("select * from books");
    query_model_book->setHeaderData(0, Qt::Horizontal, tr("书ID"));
    query_model_book->setHeaderData(1, Qt::Horizontal, tr("书名"));
    query_model_book->setHeaderData(2, Qt::Horizontal, tr("价格"));
    query_model_book->setHeaderData(3, Qt::Horizontal, tr("借阅人ID"));
    query_model_book->setHeaderData(4, Qt::Horizontal, tr("借书时间"));
    query_model_book->setHeaderData(5, Qt::Horizontal, tr("归还时间"));

    ui->tableView_book->setModel(query_model_book);
    ui->tableView_book->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

Manage::~Manage()
{
    delete ui;
}

//--------------------------------借阅人管理-------------------------------
void Manage::on_btn_person_add_clicked()
{
    QString id, name, num, sex;

    id = ui->ldt_person_id->text();
    name = ui->ldt_person_name->text();
    num = ui->ldt_person_num->text();
    if(ui->cmb_sex->currentIndex() == 0) {
        sex = "male";
    }
    else {
        sex = "female";
    }

    query_model_person->setQuery(QString("insert into persons values(%1, '%2', '%3', '%4')").arg(id).arg(name).arg(sex).arg(num));
    if (query_model_person->lastError().isValid())
        // 执行SQL语句有问题时，将错误输出 (调试用) 因为数据库中主键要求唯一且不为空，当存在重复主键时，插入会出现借误，通过显示一个对话窗口进行提示
        QMessageBox::critical(this, "database query error", query_model_person->lastError().databaseText(), QMessageBox::Ok);

    query_model_person->setQuery("select * from persons");
}

void Manage::on_btn_person_delete_clicked()
{
    QString id;

    id = ui->ldt_person_id->text();
    if(id.isNull()) {
        QMessageBox::critical(this, tr("错误"), tr("请输入待删除记录对应的ID"), QMessageBox::Ok);
    }

    query_model_person->setQuery(QString("delete from persons where id = %1").arg(id));
    query_model_person->setQuery("select * from persons");
}

//--------------------------------图书管理-------------------------------

void Manage::on_btn_book_add_clicked()
{
    QString id, name, price;

    id = ui->ldt_book_id->text();
    name = ui->ldt_book_name->text();
    price = ui->ldt_book_price->text();

    query_model_book->setQuery(QString("insert into books values(%1, '%2', %3, default, default, default)").arg(id).arg(name).arg(price));
    if (query_model_person->lastError().isValid())      // 执行SQL语句有问题时，将错误输出 (调试用)
        QMessageBox::critical(this, "database query error", query_model_person->lastError().databaseText(), QMessageBox::Ok);
    //query_model_book->setQuery("select A.book_id, A.name, A.price from books as A");
    query_model_book->setQuery("select * from books");
}

void Manage::on_btn_book_delete_clicked()
{
    QString id;

    id = ui->ldt_book_id->text();
    if(id.isNull()) {
        QMessageBox::critical(this, tr("错误"), tr("请输入待删除记录对应的ID"), QMessageBox::Ok);
    }

    query_model_book->setQuery(QString("delete from books where book_id = %1").arg(id));
    //query_model_book->setQuery("select A.book_id, A.name, A.price from books as A");
    query_model_book->setQuery("select * from books");
}

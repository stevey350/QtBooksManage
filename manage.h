#ifndef MANAGE_H
#define MANAGE_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class Manage;
}

class Manage : public QDialog
{
    Q_OBJECT

public:
    explicit Manage(QWidget *parent = nullptr);
    ~Manage();

private slots:
    void on_btn_person_add_clicked();

    void on_btn_person_delete_clicked();

    void on_btn_book_add_clicked();

    void on_btn_book_delete_clicked();

private:
    Ui::Manage *ui;

    QSqlQueryModel *query_model_person;
    QSqlQueryModel *query_model_book;
};

#endif // MANAGE_H

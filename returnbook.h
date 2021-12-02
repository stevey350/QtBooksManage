#ifndef RETURNBOOK_H
#define RETURNBOOK_H

#include <QDialog>

namespace Ui {
class ReturnBook;
}

class ReturnBook : public QDialog
{
    Q_OBJECT

public:
    explicit ReturnBook(QWidget *parent = nullptr);
    ~ReturnBook();

    enum DateTimeType{Time, Date, DateTime};
    QString getDateTime(ReturnBook::DateTimeType type);

private slots:
    void on_btn_return_clicked();

    void on_btn_quit_clicked();

private:
    Ui::ReturnBook *ui;
};

#endif // RETURNBOOK_H

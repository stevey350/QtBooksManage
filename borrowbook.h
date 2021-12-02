#ifndef BORROWBOOK_H
#define BORROWBOOK_H

#include <QDialog>

namespace Ui {
class BorrowBook;
}

class BorrowBook : public QDialog
{
    Q_OBJECT

public:
    explicit BorrowBook(QWidget *parent = nullptr);
    ~BorrowBook();

    enum DateTimeType{Time, Date, DateTime};
    QString getDateTime(BorrowBook::DateTimeType type);

private slots:
    void on_btn_borrow_clicked();

    void on_btn_quit_clicked();

private:
    Ui::BorrowBook *ui;
};

#endif // BORROWBOOK_H

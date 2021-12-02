#ifndef QUERY_H
#define QUERY_H

#include <QDialog>

namespace Ui {
class Query;
}

class Query : public QDialog
{
    Q_OBJECT

public:
    explicit Query(QWidget *parent = nullptr);
    ~Query();

    enum DateTimeType{Time, Date, DateTime};
    QString getDateTime(Query::DateTimeType type);

private slots:
    void on_btn_query_clicked();

private:
    Ui::Query *ui;
};

#endif // QUERY_H

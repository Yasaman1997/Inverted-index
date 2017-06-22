#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "stack.h"


namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

    void on_radioButton_clicked();

    void on_lineEdit_returnPressed();

    void on_pushButton_2_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    QString command;
    Stack cmd;
    int Type;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

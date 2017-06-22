#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include "Driver.cpp"
#include <iostream>
#include <time.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    Type = 1;
    ui->lineEdit->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter( QObject* obj, QEvent *event )
{
    if( obj == ui->lineEdit )
    {
        if( event->type() == QEvent::KeyPress )
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if( keyEvent->key() == Qt::Key_Up )
            {
                string str = cmd.top();
                cmd.pop();
                ui->lineEdit->setText( QString::fromStdString( str ) );
                return true;
            }
        }
        return false;
    }
    return QMainWindow::eventFilter( obj, event );
}

void MainWindow::on_pushButton_5_clicked()
{

    /*QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All files (*.*);;Text File(*.txt)"

                );*/
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);



   ui->lineEdit_2->setText(dir);


  //QMessageBox::information(this,tr("File Name"),ui->lineEdit->text(););
}
void MainWindow::on_pushButton_clicked()
{
//    on_lineEdit_returnPressed("build");
    command =QString::fromStdString("build");
    cmd.push( command.toStdString() );
//    clock_t Begin = clock();
    clock();
    string path = ui->lineEdit_2->text().toStdString();
    string str = Driver(Type, path, command.toStdString());
    const double end=clock();
    cout<<"build time"<<end<<endl;
    ui->lineEdit->setText("");
    ui->textEdit->append( QString::fromStdString(str) );
}

void MainWindow::on_lineEdit_editingFinished()
{
   command=ui->lineEdit->text();
//   on_lineEdit_returnPressed();
}
void MainWindow::on_lineEdit_returnPressed()
{

    command = ui->lineEdit->text();
    cmd.push( command.toStdString() );
//    clock_t Begin = clock();
    string path = ui->lineEdit_2->text().toStdString();

    clock();
    string str = Driver(Type, path, command.toStdString());
    const double end=clock();
    cout<<"command time"<<end<<endl;
    ui->lineEdit->setText("");
    ui->textEdit->append( ">>"+command+"\n"+QString::fromStdString(str) );
//    clock_t End = clock();
    // str -> ui::textBox
    // ( End - Begin ) / CLOCKS_PER_SEC -> ui::textBox
//    double duration=End-Begin;

}

void MainWindow::on_pushButton_2_clicked()
{

}
void MainWindow::on_radioButton_clicked()
{
    Type = 1;
}
void MainWindow::on_radioButton_2_clicked()
{
    Type = 2;
}
void MainWindow::on_radioButton_3_clicked()
{
    Type = 3;
}
void MainWindow::on_radioButton_4_clicked()
{
    Type = 4;
}

void MainWindow::on_pushButton_4_clicked()
{
    close();
}

void MainWindow::on_pushButton_3_clicked()
{
    string help = "Available Commands:\n";
    help = help + "add <document>\n";
    help = help + "del <document>\n";
    help = help + "update <document>\n";
    help = help + "list -w\n";
    help = help + "list -l\n";
    help = help + "list -f\n";
    help = help + "search -s <list of word>\n";
    help = help + "search -w <word>\n";
    ui->textEdit->append( QString::fromStdString(help) );
}

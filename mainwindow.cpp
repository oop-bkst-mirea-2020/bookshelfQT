#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Начальное состояние
    bookID=0;
    bShelfID=0;
    shelfID=0;
    ui->groupBox_Books->setEnabled(false);
    ui->groupBox_Shelf->setEnabled(false);
    ui->pushButton_delBShelf->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_addBShelf_clicked()
{
    //Создать шкаф
    BookShelf bs;
    //Добавить шкаф в список
    bookShelfs.push_back(bs);
    ui->listWidget_BShelfs->
            addItem(QString::number(bookShelfs.size()));
}

void MainWindow::on_listWidget_BShelfs_itemClicked(QListWidgetItem *item)
{
    //Получить ID шкафа
    bShelfID = item->text().toInt();
    //активировать элементы интерфейса
    ui->pushButton_delBShelf->setEnabled(true);
    ui->groupBox_Shelf->setEnabled(true);
    ui->pushButton_delShelf->setEnabled(false);
    //получить кол-во полок
    int shelfN = bookShelfs[bShelfID-1].getShelfsNumber();
    //Очистить список
    ui->listWidget_Shelfs->clear();
    ui->listWidget_Books->clear();
    //Наполнить список полок
    if(shelfN>0){
        for(int i=1;i<=shelfN;i++){
            ui->listWidget_Shelfs->
                    addItem(QString::number(i));
        }
    }
}

void MainWindow::on_pushButton_addSelf_clicked()
{
    //Создать полку добавить полку в шкаф
    bookShelfs[bShelfID-1].addShelf();
    //Обновить список
    int shelfN = bookShelfs[bShelfID-1].getShelfsNumber();
    ui->listWidget_Shelfs->addItem(QString::number(shelfN));
}

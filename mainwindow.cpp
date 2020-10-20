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

void MainWindow::on_listWidget_Shelfs_itemClicked(QListWidgetItem *item)
{
    //Активация списка книг
    ui->groupBox_Books->setEnabled(true);
    //Номер полки
    shelfID = item->text().toInt();
    //Активация кнопки удаления полки
    ui->pushButton_delShelf->setEnabled(true);
    //Обновление списка книг
    updateBookList();
}
//Обновление списка книг
void MainWindow::updateBookList(){
    //Очистка списка полок
    ui->listWidget_Books->clear();
    //Получение содержимого полки
    Shelf shelf = bookShelfs[bShelfID-1].getShelf(shelfID-1);
    //Получить количество книг
    int bookN = shelf.getBookN();
    if(bookN>0){
        //Отображение списка книг
        for (int i=1;i<=bookN;i++) {
            ui->listWidget_Books->addItem(QString::number(i));
        }
    }
}

void MainWindow::on_pushButton_addBook_clicked()
{
    //Получение параметров книги
    QString name = ui->lineEdit_name->text();
    QString author = ui->lineEdit_author->text();
    int pages = ui->spinBox_pages->value();
    //Создание объекта книги
    PrintBook pb;
    pb.setName(name.toStdString());
    pb.setPages(pages);
    //Добавить книгу в шкаф
    bookShelfs[bShelfID-1].addBook(pb,shelfID-1);
    //Обновить список книг
    updateBookList();
}

void MainWindow::on_listWidget_Books_itemClicked(QListWidgetItem *item)
{
    //Получаем ID книги
    bookID = item->text().toInt();
    //Получение книги
    PrintBook pb =
            bookShelfs[bShelfID-1].getBook(shelfID-1,bookID-1);
    //Обновление полей интерфейса
    ui->lineEdit_name->
            setText(QString::fromStdString(pb.getName()));
    ui->spinBox_pages->setValue(pb.getPages());
}

void MainWindow::on_pushButton_delBShelf_clicked()
{
    //Удалить шкаф
    bookShelfs.erase(bookShelfs.begin()+bShelfID-1);
    //Обновить список
    ui->listWidget_BShelfs->clear();//очистка
    int N = bookShelfs.size();//кол-во шкафов
    for (int i=1;i<=N;i++) {//добавление элементов
        ui->listWidget_BShelfs->addItem(QString::number(i));
    }
    //"Скрыть" списки книг и полок
    ui->groupBox_Books->setEnabled(false);
    ui->groupBox_Shelf->setEnabled(false);
}

void MainWindow::on_pushButton_delShelf_clicked()
{
    //Удаление полки
    bookShelfs[bShelfID-1].delShelf(shelfID-1);
    //Обновление списка
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
    //"Скрыть" список книг
    ui->groupBox_Books->setEnabled(false);
}

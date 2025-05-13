#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QStandardItemModel>
#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QIntValidator>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QKeyEvent>
#include <QTextStream>
#include <QTextCodec>
#include <QWidget>
#include <QLabel>
#include <QFont>
#include "textscroll.h"
#include "SQL.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    textScroll* m_textScroll3;
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_slider_valueChanged(int value);
    void on_slider2_valueChanged();
    void onBtnPage21();
    void onBtnPage22();
    void onBtnPage2();
    void onBtnPage3();
    void onBtnPage4();
    void onBtnPage5();
    void showText();
    void validateInput(const QString &text);
    void InitTableViewFunc();
    void picturebing();
    void calculateTotal();
    void picturepay();
    void setItemWithIcon(QStandardItemModel *model, const QString &imagePath, int row, int col);
    void picturecola();
    void on_up_clicked();
    void on_down_clicked();
    void on_up_clicked1();
    void on_down_clicked1();
    void onTableClicked(const QModelIndex &index);
    int getdigital();
    void managerchange();
   // void on_art_clicked();
    void picturenodus();
    void pictureweilong();void picturehotleg();void picturetomato();
    QString  readJsonFile(const QString &filePath);
    bool changeProductQuantity(const QString &filePath, const QString &product, int digital);
    void backjson();
    int readJsonFile2(const QString &filePath, const QString &product);
    //QString readPenultimateLine(const QString& filePath);
   // QString searchProductQuantity(const QString& filePath, const QString& product);
    //void on_lineEdit_returnPressed();2
private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QString test1;  // 声明 test1 变量
    QString test2;
    QString test3; // 声明 test2 变量
    QString test4;
    QString test5;
    QString test6;
    int warm=25;  // 声明 test1 变量
    int dht=30;  // 声明 test2 变量
    int clickCount = 0;
    void writeToCSV(const QString& data);
};
#endif // MAINWINDOW_H

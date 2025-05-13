#ifndef SQL_H
#define SQL_H
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


// 连接数据库
QSqlDatabase connectToDatabase();


// 创建 products 表
void createProductsTable(QSqlDatabase db);

// 插入数据
bool insertProduct(QSqlDatabase db, const QString& productName, int quantity);

// 删除数据
bool deleteProduct(QSqlDatabase db, const QString& productName);

// 更新数据
bool updateProduct(QSqlDatabase db, const QString& productName, int newQuantity);
//查找数据
QString queryProducts(QSqlDatabase db);
// 查询特定商品的数量
int queryProductQuantity(QSqlDatabase db, const QString& productName);
#endif // SQL_H

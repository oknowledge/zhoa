#include "SQL.h"
// 连接数据库
QSqlDatabase connectToDatabase() {
    QSqlDatabase db;
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("test.db");
    }

    if (!db.open()) {
        qDebug() << "database open error：" << db.lastError();
    } else {
        qDebug() << "database ok!";
    }
    return db;
}

// 创建 products 表
void createProductsTable(QSqlDatabase db) {
    QSqlQuery query(db);
    if (db.tables().contains("products")) {
        qDebug() << "table products already exists!";
    } else {
        QString cmd = "CREATE TABLE products (product_name VARCHAR(50) PRIMARY KEY, quantity INT);";
        if (!query.exec(cmd)) {
            qDebug() << "create products table error!";
        } else {
            qDebug() << "products table created successfully!";
        }
    }
    insertProduct(db, "冰红茶", 50);
    insertProduct(db, "可乐", 50);
    insertProduct(db, "方便面", 50);
    insertProduct(db, "辣条", 50);
    insertProduct(db, "火腿肠", 50);
    insertProduct(db, "薯片", 50);

}

// 插入数据
bool insertProduct(QSqlDatabase db, const QString& productName, int quantity) {
    QSqlQuery query(db);
    QString insertCmd = QString("INSERT INTO products (product_name, quantity) VALUES ('%1', %2);").arg(productName).arg(quantity);
    if (!query.exec(insertCmd)) {
        qDebug() << "Insert data error!" << query.lastError();
        return false;
    }
    qDebug() << "Data inserted successfully!";
    return true;
}

// 删除数据
bool deleteProduct(QSqlDatabase db, const QString& productName) {
    QSqlQuery query(db);
    QString deleteCmd = QString("DELETE FROM products WHERE product_name = '%1';").arg(productName);
    if (!query.exec(deleteCmd)) {
        qDebug() << "Delete data error!" << query.lastError();
        return false;
    }
    qDebug() << "Data deleted successfully!";
    return true;
}

// 更新数据
bool updateProduct(QSqlDatabase db, const QString& productName, int newQuantity) {
    QSqlQuery query(db);
    QString updateCmd = QString("UPDATE products SET quantity = %1 WHERE product_name = '%2';").arg(newQuantity).arg(productName);
    if (!query.exec(updateCmd)) {
        qDebug() << "Update data error!" << query.lastError();
        return false;
    }
    qDebug() << "Data updated successfully!";
    return true;
}

// 查询数据并返回结果字符串
QString queryProducts(QSqlDatabase db) {
    QSqlQuery query(db);
    QString result;
    QString selectCmd = "SELECT * FROM products;";
    if (query.exec(selectCmd)) {
        while (query.next()) {
            QString productName = query.value(0).toString();
            int quantity = query.value(1).toInt();
            result += QString("Product: %1, Quantity: %2\n").arg(productName).arg(quantity);
        }
    } else {
        qDebug() << "Query data error!" << query.lastError();
        result = "Query error!";
    }
    return result;
}
// 查询特定商品的数量
int queryProductQuantity(QSqlDatabase db, const QString& productName) {
    QSqlQuery query(db);
    QString selectCmd = QString("SELECT quantity FROM products WHERE product_name = '%1';").arg(productName);
    if (query.exec(selectCmd) && query.next()) {
        return query.value(0).toInt();
    }
    qDebug() << "Query product quantity error!" << query.lastError();
    return -1; // 返回 -1 表示查询出错或未找到该商品
}

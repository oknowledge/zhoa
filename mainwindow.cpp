#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{   ui->setupUi(this);
    this->setWindowTitle("智能售货柜");
    // 连接数据库
    QSqlDatabase db = connectToDatabase();
    // 创建 products 表
    createProductsTable(db);

    // 连接滑块的 valueChanged 信号到槽函数
    connect(ui->slider, &QSlider::valueChanged, this, &MainWindow::on_slider_valueChanged);//调节亮暗的
    connect(ui->slider2, &QSlider::valueChanged, this, &MainWindow::on_slider2_valueChanged);//调节声音的
    // 初始化 label2 的文本
    ui->label2->setText("亮暗程度: 100%");
    // 直接使用已有的 mainb1 按键并连接信号槽
    connect(ui->mainb1, &QPushButton::clicked, this, &MainWindow::onBtnPage2);//跳转到设置界面
    // 直接使用已有的 page0bb 按键并连接信号槽
    connect(ui->page0bb, &QPushButton::clicked, this, &MainWindow::onBtnPage21);//由设置界面跳转回主界面
    connect(ui->page0bb2, &QPushButton::clicked, this, &MainWindow::onBtnPage22);
    connect(ui->page_3b, &QPushButton::clicked, this, &MainWindow::onBtnPage21);
    connect(ui->buy, &QPushButton::clicked, this, &MainWindow::onBtnPage4);
    connect(ui->page51, &QPushButton::clicked, this, &MainWindow::onBtnPage3);
    connect(ui->last, &QPushButton::clicked, this, &MainWindow::onBtnPage5);
    connect(ui->over, &QPushButton::clicked, this, &MainWindow::onBtnPage21);
    connect(ui->backbuy, &QPushButton::clicked, this, &MainWindow::onBtnPage3);
    connect(ui->cont2, &QPushButton::clicked, this, &MainWindow::onBtnPage4);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::onBtnPage4);
    ui->scroll3->setText("本界面由物联网2202班赵荣胜小组共同开发，小组成员：谢智鑫，赵才旦，易承瑛，陈禹立。版权所有，翻录必究",qRgb(71,71,71));
    // 显示温度以及湿度
    ui->lcdNumber->display(25);
    ui->lcdNumber_2->display(35);
    // 为第二个 QLineEdit 设置整数验证器
    QIntValidator *validator = new QIntValidator(this);
    ui->lineEdit_2->setValidator(validator);
    // 连接 textChanged 信号到验证槽函数
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &MainWindow::validateInput);
    // 假设这里使用 ui 中的 change 按钮和两个 QLineEdit
    if (ui->change && ui->lineEdit && ui->lineEdit_2) {
        connect(ui->change, &QPushButton::clicked, this, &MainWindow::showText);
    }
    InitTableViewFunc();
    picturebing();
    picturepay();
    picturecola();
    picturenodus();
    pictureweilong();picturehotleg();picturetomato();
    //on_lineEdit_returnPressed();
    managerchange();
    readJsonFile("products.json");
    // 连接表格点击信号到槽函数
    connect(ui->tableView, &QTableView::clicked, this, &MainWindow::onTableClicked);

    // 手动连接信号与槽
    connect(ui->art, &QPushButton::clicked, this, &MainWindow::backjson);

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::backjson()
{
    // 连接数据库
    QSqlDatabase db = connectToDatabase();
    // 查询数据并获取结果字符串
    QString queryResult = queryProducts(db);
    // 创建一个新的字体对象
    QFont newFont("宋体", 12, QFont::Bold); // 字体为宋体，字号为 12，加粗
    // 设置标签的字体
    ui->label_21->setFont(newFont);
    // 将查询结果设置到标签上
    ui->label_21->setText(queryResult);
}
void MainWindow::managerchange()
{
    ui->lcdNumber_3->display(warm);
    ui->lcdNumber_4->display(dht);
    connect(ui->up, &QPushButton::clicked, this, &MainWindow::on_up_clicked);
    connect(ui->down, &QPushButton::clicked, this, &MainWindow::on_down_clicked);
    connect(ui->up1, &QPushButton::clicked, this, &MainWindow::on_up_clicked1);
    connect(ui->down1, &QPushButton::clicked, this, &MainWindow::on_down_clicked1);
}
void MainWindow::on_up_clicked()
{
    warm++;
    ui->lcdNumber_3->display(warm);
}
void MainWindow::on_down_clicked()
{
    warm--;
    ui->lcdNumber_3->display(warm);
}
void MainWindow::on_up_clicked1()
{
    dht++;
    ui->lcdNumber_4->display(dht);
}
void MainWindow::on_down_clicked1()
{
    dht--;
    ui->lcdNumber_4->display(dht);
}
void MainWindow::onTableClicked(const QModelIndex &index)
{
    // 检查索引是否有效且点击的是否是第四列（索引为 3）
    if (index.isValid() && index.column() == 3) {
        int value = getdigital();
        QString strValue = QString::number(value);  // 将 int 转换为 QString
        model->setItem(index.row(), index.column(), new QStandardItem(strValue));
    }
}
int MainWindow::getdigital()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->lineEdit_3->setText("0"); // 确保初始值为 0
    // 断开之前按钮的所有信号连接
    QString buttonNames[] = {"p0", "p1", "p2", "p3", "p4", "p5", "p6", "p7", "p8", "p9"};
    for (const QString& buttonName : buttonNames) {
        QPushButton* button = this->findChild<QPushButton*>(buttonName);
        if (button) {
            button->disconnect();
        }
    }
    // 重新连接按钮的点击信号
    for (const QString& buttonName : buttonNames) {
        QPushButton* button = this->findChild<QPushButton*>(buttonName);
        if (button) {
            connect(button, &QPushButton::clicked, [this, button]() {
                QString currentText = ui->lineEdit_3->text();
                int currentValue = currentText.toInt();
                int buttonValue = button->text().right(1).toInt();
                int newValue = currentValue * 10 + buttonValue;
                ui->lineEdit_3->setText(QString::number(newValue));
            });
        }
    }
    QPushButton* backbuyButton = this->findChild<QPushButton*>("backbuy");
    if (backbuyButton) {
        // 断开之前可能存在的 backbuy 按钮的其他信号连接
        backbuyButton->disconnect();
        QEventLoop loop;
        connect(backbuyButton, &QPushButton::clicked, &loop, &QEventLoop::quit);
        loop.exec();

        bool ok;
        int value = ui->lineEdit_3->text().toInt(&ok);
        if (ok) {
            onBtnPage3();
            return value;
        }
    }
    return 0;
}
// 定义设置带图标项的函数
void MainWindow::setItemWithIcon(QStandardItemModel *model, const QString &imagePath, int row, int col) {
    // 加载图片
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        // 创建 QIcon 对象
        QIcon icon(pixmap);
        // 创建 QStandardItem 并设置图标
        QStandardItem *item = new QStandardItem();
        item->setIcon(icon);
        // 将带有图标的项设置到模型中
        model->setItem(row, col, item);
    } else {
        // 图片加载失败，设置默认文本
        model->setItem(row, col, new QStandardItem("图片加载失败"));
    }
}

void MainWindow::picturebing()
{
    QPixmap pixmap(":/new/prefix1/R-C.jpg");
    if (!pixmap.isNull()) {
        ui->label_9->setPixmap(pixmap);
        ui->label_9->setScaledContents(true); // 让图片适应标签大小
    } else {
        // 处理图片加载失败的情况
        ui->label_9->setText("图片加载失败");
    }
}

void MainWindow::picturepay()
{
    QPixmap pixmap(":/new/prefix1/pay.jpg");
    if (!pixmap.isNull()) {
        ui->label_14->setPixmap(pixmap);
        ui->label_14->setScaledContents(true); // 让图片适应标签大小
    } else {
        // 处理图片加载失败的情况
        ui->label_14->setText("图片加载失败");
    }
}
void MainWindow::picturecola()
{
    QPixmap pixmap(":/new/prefix1/cola.jpg");
    if (!pixmap.isNull()) {
        ui->label_15->setPixmap(pixmap);
        ui->label_15->setScaledContents(true); // 让图片适应标签大小
    } else {
        // 处理图片加载失败的情况
        ui->label_15->setText("图片加载失败");
    }
}
void MainWindow::picturetomato()
{
    QPixmap pixmap(":/new/prefix1/tamato.jpg");
    if (!pixmap.isNull()) {
        ui->label_31->setPixmap(pixmap);
        ui->label_31->setScaledContents(true); // 让图片适应标签大小
    } else {
        // 处理图片加载失败的情况
        ui->label_31->setText("图片加载失败");
    }
}
void MainWindow::picturenodus()
{
    QPixmap pixmap(":/new/prefix1/nodus.jpg");
    if (!pixmap.isNull()) {
        ui->label_22->setPixmap(pixmap);
        ui->label_22->setScaledContents(true); // 让图片适应标签大小
    } else {
        // 处理图片加载失败的情况
        ui->label_22->setText("图片加载失败");
    }
}
void MainWindow::pictureweilong()
{
    QPixmap pixmap(":/new/prefix1/weilong.jpg");
    if (!pixmap.isNull()) {
        ui->label_25->setPixmap(pixmap);
        ui->label_25->setScaledContents(true); // 让图片适应标签大小
    } else {
        // 处理图片加载失败的情况
        ui->label_25->setText("图片加载失败");
    }
}
void MainWindow::picturehotleg()
{
    QPixmap pixmap(":/new/prefix1/hotleg.jpg");
    if (!pixmap.isNull()) {
        ui->label_28->setPixmap(pixmap);
        ui->label_28->setScaledContents(true); // 让图片适应标签大小
    } else {
        // 处理图片加载失败的情况
        ui->label_28->setText("图片加载失败");
    }
}
void MainWindow::onBtnPage2()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::onBtnPage5()
{
    calculateTotal(); // 先计算总价
    ui->stackedWidget->setCurrentIndex(5);
}
void MainWindow::onBtnPage3()
{
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow::onBtnPage4()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::onBtnPage21()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::onBtnPage22()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_slider_valueChanged(int value)
{
    // 根据滑块的值计算透明度（0到1之间）
    double alpha = static_cast<double>(value) / 100.0;
    setWindowOpacity(alpha);

    // 更新 label2 显示
    ui->label2->setText(QString("透明度: %1%").arg(value));
}

void MainWindow::on_slider2_valueChanged()
{
    // 这里可以添加 slider2 的逻辑
}

void MainWindow::validateInput(const QString &text)
{
    int pos = 0;
    QString nonConstText = text; // 复制一份非 const 的字符串
    if (ui->lineEdit_2->validator()->validate(nonConstText, pos) != QValidator::Acceptable) {
        QMessageBox::warning(this, "输入错误", "请输入数字");
        ui->lineEdit_2->clear();
    }
}

void MainWindow::showText()
{
    QString text1 = ui->lineEdit->text();
    QString text2 = ui->lineEdit_2->text();
    if (text1 == "binghongcha")
    {
        text1="冰红茶";
        ui->label_11->setText(text2);
        test1=text2;
        model->setItem(0, 2, new QStandardItem(test1));

    }
    if (text1 == "kele")
    {
        text1="可乐";
        ui->label_17->setText(text2);
        test2=text2;
        model->setItem(1, 2, new QStandardItem(test2));

    }
    if (text1 == "fangbianmian")
    {
        text1="方便面";
        ui->label_24->setText(text2);
        test3=text2;
        model->setItem(2, 2, new QStandardItem(test3));

    }
    if (text1 == "latiao")
    {
        text1="辣条";
        ui->label_27->setText(text2);
        test4=text2;
        model->setItem(3, 2, new QStandardItem(test4));

    }
    if (text1 == "huotuichang")
    {

        text1="火腿肠";ui->label_30->setText(text2);
        test5=text2;
        model->setItem(4, 2, new QStandardItem(test5));

    }
    if (text1 == "shupian")
    {
        text1="薯片";
        ui->label_33->setText(text2);
        test6=text2;
        model->setItem(5, 2, new QStandardItem(test6));

    }
    // 这里可以使用 test1 和 test2 变量   // test1 = text1;
    QString combinedText = text1 + "的价格已被修改为" + text2 + "元";
    QString newText = combinedText;
    ui->label_8->setText(newText);

}
void MainWindow::InitTableViewFunc()
{
    // 1:添加表头，准备数据模型
    model = new QStandardItemModel(); // 使用类成员变量 model
    model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("商品")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("图片")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("价格")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("数量")));
    // 通过API函数将数据模型绑定到QTableView
    ui->tableView->setModel(model);
    // 设置表格列的宽度
    ui->tableView->setColumnWidth(0, 120);
    // 2:添加数据信息
    model->setItem(0, 0, new QStandardItem("冰红茶"));
    setItemWithIcon(model, ":/new/prefix1/R-C.jpg", 0, 1);
    model->setItem(0, 2, new QStandardItem("3"));
    model->setItem(0, 3, new QStandardItem("0"));

    model->setItem(1, 0, new QStandardItem("可乐"));
    setItemWithIcon(model, ":/new/prefix1/cola.jpg", 1, 1);
    model->setItem(1, 2, new QStandardItem("3"));
    model->setItem(1, 3, new QStandardItem("0"));

    model->setItem(2, 0, new QStandardItem("方便面"));
    setItemWithIcon(model, ":/new/prefix1/nodus.jpg", 2, 1);
    model->setItem(2, 2, new QStandardItem("3"));
    model->setItem(2, 3, new QStandardItem("0"));


    model->setItem(3, 0, new QStandardItem("辣条"));
    setItemWithIcon(model, ":/new/prefix1/weilong.jpg", 3, 1);
    model->setItem(3, 2, new QStandardItem("5"));
    model->setItem(3, 3, new QStandardItem("0"));


    model->setItem(4, 0, new QStandardItem("火腿肠"));
    setItemWithIcon(model, ":/new/prefix1/hotleg.jpg", 4, 1);
    model->setItem(4, 2, new QStandardItem("2"));
    model->setItem(4, 3, new QStandardItem("0"));

    model->setItem(5, 0, new QStandardItem("薯片"));
    setItemWithIcon(model, ":/new/prefix1/tamato.jpg", 5, 1);
    model->setItem(5, 2, new QStandardItem("8"));
    model->setItem(5, 3, new QStandardItem("0"));
    model->sort(6, Qt::DescendingOrder); // 设置降序排列
}
void MainWindow::calculateTotal()
{
    // 连接数据库
    QSqlDatabase db = connectToDatabase();
    if (model) { // 检查 model 是否为 nullptr
        double total = 0;
        int a;
        int rowCount = model->rowCount();
        for (int i = 0; i < rowCount; ++i) {
            QStandardItem *priceItem = model->item(i, 2);
            QStandardItem *quantityItem = model->item(i, 3);
            if (priceItem && quantityItem) {
                double price = priceItem->text().toDouble();
                int quantity = quantityItem->text().toInt();
                total += price * quantity;
                switch (i) {
                    case 0:
                    a=queryProductQuantity(db, "冰红茶");
                    changeProductQuantity("products.json", "冰红茶", a-quantity);
                    // 更新数据
                    updateProduct(db, "冰红茶",a-quantity);
                    break;
                    case 1:
                    a=queryProductQuantity(db, "可乐");
                    changeProductQuantity("products.json", "可乐", a-quantity);
                    updateProduct(db, "可乐",a-quantity);
                    break;
                    case 2:
                    a=queryProductQuantity(db, "方便面");
                    changeProductQuantity("products.json", "方便面", a-quantity);
                    updateProduct(db, "方便面",a-quantity);
                    break;
                    case 3:
                    a=queryProductQuantity(db, "辣条");
                     changeProductQuantity("products.json", "辣条", a-quantity);
                     updateProduct(db, "辣条",a-quantity);
                    break;
                    case 4:
                    a=queryProductQuantity(db, "火腿肠");
                    changeProductQuantity("products.json", "火腿肠", a-quantity);
                    updateProduct(db, "火腿肠",a-quantity);
                    break;
                    case 5:
                    a=queryProductQuantity(db, "薯片");
                    changeProductQuantity("products.json", "薯片", a-quantity);
                    updateProduct(db, "薯片",a-quantity);
                        break;

                    default:
                         break;
                }
                //changeProductQuantity(const QString &filePath, const QString &product, int digital);
                //int readJsonFile2(const QString &filePath, const QString &product)
            }
        }
        // 将结果输出到 label13
        ui->label_13->setText(QString("您需要支付: %1元").arg(total));
    }
}
QString MainWindow::readJsonFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件";
        return "无法打开文件";
    }

    QByteArray jsonData = file.readAll();

    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON 解析错误:" << parseError.errorString();
        return "JSON 解析错误: " + parseError.errorString();
    }

    if (jsonDoc.isObject()) {
        QJsonObject outerObj = jsonDoc.object();
        QString result;
        QTextStream stream(&result);
        for (const auto& key : outerObj.keys()) {
            QJsonValue value = outerObj[key];
            if (value.isObject()) {
                QJsonObject productObj = value.toObject();
                QString name = productObj["name"].toString();
                int digital = productObj["digital"].toInt();
                stream << "产品名称: " << name << "，数量: " << digital << "\n";
            }
        }
        return result;
    }

    return "JSON 数据不是对象类型";
}

bool MainWindow::changeProductQuantity(const QString &filePath, const QString &product, int digital)//对商品数量的一个改变
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件";
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON 解析错误:" << parseError.errorString();
        return false;
    }

    if (jsonDoc.isObject()) {
        QJsonObject outerObj = jsonDoc.object();
        for (const auto& key : outerObj.keys()) {
            QJsonValue value = outerObj[key];
            if (value.isObject()) {
                QJsonObject productObj = value.toObject();
                if (productObj.contains("name") && productObj["name"].toString() == product) {
                    productObj["digital"] = digital;
                    outerObj[key] = productObj;
                    jsonDoc.setObject(outerObj);

                    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
                        file.write(jsonDoc.toJson());
                        file.close();
                        return true;
                    } else {
                        qDebug() << "无法写入文件";
                        return false;
                    }
                }
            }
        }
    }
    return false;
}
int MainWindow::readJsonFile2(const QString &filePath, const QString &product)//读取指定商品的数量
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件";
        return -1;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON 解析错误:" << parseError.errorString();
        return -1;
    }

    if (jsonDoc.isObject()) {
        QJsonObject outerObj = jsonDoc.object();
        for (const auto& key : outerObj.keys()) {
            QJsonValue value = outerObj[key];
            if (value.isObject()) {
                QJsonObject productObj = value.toObject();
                if (productObj.contains("name") && productObj["name"].isString()) {
                    QString name = productObj["name"].toString();
                    if (name == product && productObj.contains("digital") && productObj["digital"].isDouble()) {
                        return productObj["digital"].toInt();
                    }
                }
            }
        }
    }
    return -1; // 未找到冰红茶信息
}



QT版本5.14.1
能够成功移植到stm32mp157正点原子板子上
VM虚拟机用的ubuntu16.04，虚拟机QT版本5.12
移植单片机请查阅相关手册
本人使用的是网络传输
scp -r build-first-atk（tab补全）root@（单片机网络ip）：~
单片机linuxfb启动：
systemctl stop atk-qtapp-start.service
chmod 777 first
./first -platform linuxfb
该项目连接数据库是那个 .db文件，使用时要把这个文件复制到build文件下面，建议在windows下使用Navicat Premium 16连接数据库
这样能更直观观察商品的变化


注：本人只是普通二本学生，技术有限，还望多多提出建议
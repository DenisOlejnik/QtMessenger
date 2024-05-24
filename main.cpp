#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


// !TODO: Отображение сообщений на сервере с никами ((username) joined, вместо ~new client conn~)
// !TODO: Отображение действий пользователей: connected, disconnected, (typing?)
// !TODO: Отображение пользователей в списке справа
// !TODO: Проверка занятости порта
// !TODO: Проверка занятости никнейма



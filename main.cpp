#include "View/MainWindow.h"

#include <QApplication>
#include <QFile>

void applyStyleSheet(QApplication& app, const QString& themeName) {
    QFile file(":/styles/" + themeName + ".qss"); // или без ":/" если из папки рядом
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString style = stream.readAll();
        app.setStyleSheet(style);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    MainWindow w;
    //applyStyleSheet(a, "dark");
    
    w.show();
    
    return a.exec();
}

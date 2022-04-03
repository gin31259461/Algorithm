#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#include <QMainWindow>
#include <QPainter>
#include <QTextBlock>

#include <string>
#include <vector>

#include "collection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public:
    //widget control
    void initWidget();

    //methods
    std::vector<QString> get_plainTextEdit_input();
    std::vector<int> QString2int(QString qstr, QString del = " "); //delimiter
    std::vector<std::string> QString2string(QString qstr, QString del = " ");

    //members
    QPainter *m_painter;
    std::vector<QString> buffer;
    bool collectionFlag = false;

public slots: //handlers
    void pushButton_start_handler();

public:
    void label_message_handler(QString msg);
    void paintEvent(QPaintEvent *event) override;
    void collection_handler();
};
#endif // MAINWINDOW_H

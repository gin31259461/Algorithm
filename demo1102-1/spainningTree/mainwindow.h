#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#include <QMainWindow>
#include <QPainter>
#include <QTextBlock>
#include <QLabel>

#include <string>
#include <vector>
#include <math.h>
#include <algorithm>

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
    QLabel *label_main;

    //methods
    std::vector<QString> get_plainTextEdit_input();
    std::vector<int> QString2int(QString qstr, QString del = " "); //delimiter
    std::vector<std::string> QString2string(QString qstr, QString del = " ");

    void spainningTreeWrap();

    //members
    QPainter *m_painter;
    std::vector<QString> buffer;
    bool treeFlag = false;

public slots: //handlers
    void pushButton_start_handler();
    void scaleIn_handler();
    void scaleOut_handler();

public:
    void label_message_handler(QString msg);
    void paintEvent(QPaintEvent *event) override;

private:
    qreal zoomVal = 2.0;
};
#endif // MAINWINDOW_H

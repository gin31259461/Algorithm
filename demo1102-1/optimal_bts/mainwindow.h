#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBlock>
#include <QPainter>
#include <QFont>
#include <QPen>

#include <vector>
#include "node.h"

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

private slots:
    void pushButton_start_handler();

public:

    //handlers
    void plainTextEdit_inputNum_handler();
    void label_message_handler(QString msg, QColor windowColor = Qt::white, QColor textColor = Qt::black);

    //functions
    QString vectorNum_toQString(std::vector<int> num);
    void drawTree(Node* root, int x, int y, int dx);
    void initWidget();


    //parameters
    Node* m_tree;
    bool m_treeFlag = false;
    int m_circleRadius = 25;
    int m_circleDistance;

    QPainter* painter;
    QPoint curPoint;

    //Vectors
    std::vector<std::vector<int>> storeNum;
    std::vector<int> levelList, stationNames;

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // MAINWINDOW_H

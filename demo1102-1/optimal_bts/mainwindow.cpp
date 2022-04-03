#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "node.h"

#define WIN_WIDTH 1600
#define WIN_HEIDHT 900

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(WIN_WIDTH, WIN_HEIDHT);
    connect(ui->pushButton_start, SIGNAL(clicked(bool)), this, SLOT(pushButton_start_handler()));

    initWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushButton_start_handler()
{
    QString msg;

    plainTextEdit_inputNum_handler();

    if(storeNum.empty())
    {
        msg = "Invalid input!";
        label_message_handler(msg, Qt::white, Qt::red);
        return;
    }

    std::vector<int> index;
    this->stationNames.clear();
    for(int i = 0, a = 65; i < int(storeNum[0].size()); i++, a++)
    {
        stationNames.push_back(a);
        index.push_back(i);
    }

    Node* tree = buildTree_wrap(index, storeNum[0]);

    std::vector<int> inorderList;
    this->levelList.clear();
    tree->inorder(tree, inorderList, levelList, 1);

    msg = vectorNum_toQString(levelList);
    label_message_handler(msg);


    m_tree = tree;
    m_treeFlag = true;
    this->repaint();
}

void MainWindow::plainTextEdit_inputNum_handler()
{
    QTextDocument* doc = ui->plainTextEdit_input->document();
    QString str;

    std::vector<int> initNum;
    this->storeNum.clear();

    int cnt = doc->blockCount();
    for(int i = 0; i < cnt; i++)
    {
        initNum.clear();

        QTextBlock readLine = doc->findBlockByLineNumber(i);
        str = readLine.text();


        QStringList list = str.split(" ");

        if(list[0] == "")
            return;

        for(int i = 0; i < list.size(); i++)
            initNum.push_back(list[i].toInt());

        this->storeNum.push_back(initNum);
    }
}

QString MainWindow::vectorNum_toQString(std::vector<int> num)
{
    if(num.empty())
        return "";

    QString str = "";

    for(int i : num)
    {
        if(i == 1)
            str += "一";
        else if(i == 2)
            str += "二";
        else if(i == 3)
            str += "三";
        else
            str += "簡";

        str += " ";
    }

    return str;
}

void MainWindow::label_message_handler(QString msg, QColor windowColor, QColor textColor)
{
    QPalette pal;
    pal.setColor(QPalette::Window, windowColor);
    pal.setColor(QPalette::WindowText, textColor);

    ui->label_message->setPalette(pal);
    ui->label_message->setText(msg);
}

//draw operation only in paintEvent!! or window will crash.
void MainWindow::paintEvent(QPaintEvent* /*event*/)
{
    QPixmap pix(ui->label_paintArea->width(), ui->label_paintArea->height());
    pix.fill(Qt::white);
    QPainter painter(&pix);
    this->painter = &painter;

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);


    QFont font;
    font.setPointSize(10);
    painter.setFont(font);
    painter.setRenderHint(QPainter::Antialiasing);

    if(m_treeFlag == true)
    {
        //color bar
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        painter.setPen(Qt::NoPen);

        int initPosX = 10, initPosY = 10;

        brush.setColor(Qt::red);
        painter.setBrush(brush);
        painter.drawRect(initPosX, initPosY, 10, 20);
        painter.setPen(Qt::black);
        painter.drawText(initPosX + 20, initPosY, 40, 20, Qt::AlignLeft, "一等站");
        painter.setPen(Qt::NoPen);


        brush.setColor(Qt::yellow);
        painter.setBrush(brush);
        painter.drawRect(initPosX, initPosY + (20 + 10), 10, 20);
        painter.setPen(Qt::black);
        painter.drawText(initPosX + 20, initPosY + (20 + 10), 40, 20, Qt::AlignLeft, "二等站");
        painter.setPen(Qt::NoPen);

        brush.setColor(Qt::green);
        painter.setBrush(brush);
        painter.drawRect(initPosX, initPosY + 2 * (20 + 10), 10, 20);
        painter.setPen(Qt::black);
        painter.drawText(initPosX + 20, initPosY + 2 * (20 + 10), 40, 20, Qt::AlignLeft, "三等站");
        painter.setPen(Qt::NoPen);

        brush.setColor(Qt::blue);
        painter.setBrush(brush);
        painter.drawRect(initPosX, initPosY + 3 * (20 + 10), 10, 20);
        painter.setPen(Qt::black);
        painter.drawText(initPosX + 20, initPosY + 3 * (20 + 10), 40, 20, Qt::AlignLeft, "簡易站");

        //graph
        painter.setPen(pen);
        font.setPointSize(20);
        painter.setFont(font);

        int h = treeHeight(m_tree);
        m_circleDistance = 100;
        drawTree(m_tree, ui->label_paintArea->width()/2, 100, 70 * h);
        ui->label_paintArea->setPixmap(pix);
        m_treeFlag = false;
    }
}

void MainWindow::drawTree(Node* root, int x, int y, int dx)
{
    if(!root)
        return;

    if(root->left != NULL)
        painter->drawLine(x, y, x - dx, y + m_circleDistance);

    if(root->right != NULL)
        painter->drawLine(x, y, x + dx, y + m_circleDistance);

    drawTree(root->left, x - dx, y + m_circleDistance, dx/2);
    drawTree(root->right, x + dx, y + m_circleDistance, dx/2);

    QRectF node(
        x - m_circleRadius, y - m_circleRadius,
        2 * m_circleRadius + 15 * std::to_string(storeNum[0][root->val]).length(), 2 * m_circleRadius
        );

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    int l = levelList[root->val];

    if(l == 1)
        brush.setColor(Qt::red);
    else if(l == 2)
        brush.setColor(Qt::yellow);
    else if(l == 3)
        brush.setColor(Qt::green);
    else
        brush.setColor(Qt::blue);

    painter->setBrush(brush);
    painter->drawRoundedRect(node, 20, 15);
    painter->setBrush(Qt::NoBrush);

    std::string str = "";
    str = char(stationNames[root->val]);

    QString qstr = " ";
    qstr += QString::fromStdString(str) + ":" + QString::number(storeNum[0][root->val]);
    painter->drawText(node, Qt::AlignCenter, qstr);
}

void MainWindow::initWidget()
{
    QFont font;
    font.setPixelSize(20);

    QPalette pal;
    ui->label_message->setAutoFillBackground(true);
    pal.setColor(QPalette::Window, Qt::white);

    ui->label_paintArea->setStyleSheet("border: 3px outset green; background-color: white;");
    ui->label_paintArea->setAutoFillBackground(true);
    ui->label_paintArea->setPalette(pal);

    pal.setColor(QPalette::WindowText, Qt::black);

    ui->label_message->setStyleSheet("border: 3px outset red; background-color: white;");
    ui->label_message->setPalette(pal);
    ui->label_message->setFont(font);

    ui->label_preorder->setStyleSheet("border: 2px outset orange; background-color: white;");
    ui->label_preorder->setAutoFillBackground(true);
    pal.setColor(QPalette::Window, Qt::white);
    pal.setColor(QPalette::WindowText, Qt::black);

    ui->label_preorder->setPalette(pal);
    ui->label_preorder->setFont(font);

    pal.setColor(QPalette::Window, Qt::lightGray);
    this->setPalette(pal);
}

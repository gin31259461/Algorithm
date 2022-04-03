#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    ui->setupUi(this);

    initWidget();

    //connect widget
    connect(ui->pushButton_start, SIGNAL(clicked(bool)), this, SLOT(pushButton_start_handler()));
    connect(ui->scaleIn, SIGNAL(clicked(bool)), this, SLOT(scaleIn_handler()));
    connect(ui->scaleOut, SIGNAL(clicked(bool)), this, SLOT(scaleOut_handler()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidget()
{
    QPalette pal;
    pal.setColor(QPalette::Window, Qt::white);
    pal.setColor(QPalette::WindowText, Qt::black);

    label_main = new QLabel();
    label_main->resize(ui->scrollArea->width(), ui->scrollArea->height());
    label_main->setStyleSheet("background-color: white;");
    label_main->setAutoFillBackground(true);
    label_main->setPalette(pal);

    ui->scrollArea->setWidget(label_main);

    ui->label_message->setStyleSheet("background-color: white; border: 3px outset red;");
    ui->label_message->setPalette(pal);
    ui->label_message->setAutoFillBackground(true);
    ui->label_message->setWordWrap(true);

    pal.setColor(QPalette::Window, Qt::lightGray);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    ui->scrollArea->setWidget(label_main);
}

//////////////////////////////////////////////////////////////////////////

void MainWindow::pushButton_start_handler()
{
    buffer = get_plainTextEdit_input();

    if(!buffer.empty() && buffer.size() >= 1)
    {
        treeFlag = true;
        repaint();
    }
}

void MainWindow::label_message_handler(QString msg)
{
    ui->label_message->setText(msg);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPixmap pix(2100, 2100);
    pix.fill(Qt::white);

    QPainter painter(&pix);
    m_painter = &painter;
    m_painter->setRenderHint(QPainter::Antialiasing);

    int w = pix.width();
    int h = pix.height();
    painter.setWindow(-w/2, h/2, w, -h);

    if(treeFlag)
    {
        treeFlag = false;
        painter.scale(zoomVal, zoomVal);
        spainningTreeWrap();
        label_main->setPixmap(pix);
    }
}

void MainWindow::scaleIn_handler()
{
    zoomVal += 1;
    treeFlag = true;
}

void MainWindow::scaleOut_handler()
{
    zoomVal -= 1;
    if(zoomVal < 1)
        zoomVal = 1;
    treeFlag = true;
}

struct edge
{
    int a, b;
    float w;
};

int findEdge(int a, int p[]) {return a == p[a]? a:p[a] = findEdge(p[a], p);}
void merge(int a, int b, int *p) {p[findEdge(a, p)] = findEdge(b, p);}

void MainWindow::spainningTreeWrap()
{
    int N = buffer[0].toInt();
    std::vector<std::string> stationInfo = QString2string(buffer[1], " ");

    int size = stationInfo.size() / 3;

    std::vector<QPoint> stationPoint;
    std::vector<char> stationShape;
    std::vector<edge> E[size];

    int scale = 10;

    for(int i = 0; i + 2 < int(stationInfo.size()); i += 3)
    {
        stationPoint.push_back(QPoint(scale * std::stoi(stationInfo[i+1]), scale * std::stoi(stationInfo[i+2])));
        stationShape.push_back(stationInfo[i][0]);
    }

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
        {
            if(i == j)
                continue;
            else
            {
                float w = sqrt(
                    pow(stationPoint[i].x() - stationPoint[j].x(), 2) +
                    pow(stationPoint[i].y() - stationPoint[j].y(), 2));

                E->push_back({i, j, w});

            }
        }

    int p[size];
    //initial p with V - 1 edge
    for(int i = 0; i < size; i++)
        p[i] = i;

    std::sort(E->begin(), E->end(), [](edge a, edge b){return a.w < b.w;});

    //exhaustive all edge until limit V - 1
    std::vector<edge>::iterator it = E->begin();

    for(int i = 0; i < size - 1 && it != E->end(); i++, it++)
    {
        while(findEdge(it->a, p) == findEdge(it->b, p)) it++;
        merge(it->a, it->b, p);
    }

    //draw minimum spanning tree
    int radius = 3;
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::yellow);

    for(int i = 0; i < size; i++)
    {
        m_painter->setPen(pen);
        m_painter->drawLine(stationPoint[i], stationPoint[p[i]]);
    }

    m_painter->setBrush(brush);
    m_painter->setPen(Qt::black);

    for(int i = 0; i < size; i++)
    {
        //shape rect start at left-down end at right up
        //initial state is start at left-up end at right-down
        //because the coordinate system has been transform

        if(stationShape[i] == 'c')
            m_painter->drawEllipse(stationPoint[i].x() - radius, stationPoint[i].y() - radius, radius*2, radius*2);
        else if(stationShape[i] == 's')
            m_painter->drawRect(stationPoint[i].x() - radius, stationPoint[i].y() - radius, radius*2, radius*2);
        else if(stationShape[i] == 't')
        {
            QPointF points[]=
            {
                QPointF(stationPoint[i].x(), stationPoint[i].y() + radius),
                QPointF(stationPoint[i].x() - radius, stationPoint[i].y() - radius),
                QPointF(stationPoint[i].x() + radius, stationPoint[i].y() - radius)
            };
            m_painter->drawPolygon(points, 3);
        }
    }
    m_painter->setBrush(Qt::NoBrush);

    //information
    QFont font;
    font.setPointSize(15);

    QString msg;
    msg = "Size : " + QString::number(N) + "\n" + "Points : ";
    for(int i = 0; i < size; i++)
        msg += QString::fromStdString(stationInfo[i]) + ((i != int(stationInfo.size())-1)? " ":"");
    ui->label_message->setFont(font);
    label_message_handler(msg);
}

std::vector<QString> MainWindow::get_plainTextEdit_input()
{
    std::vector<QString> buffer;
    QTextDocument *doc = ui->plainTextEdit_input->document();
    int cnt = doc->blockCount();

    for(int i = 0; i < cnt; i++)
    {
        QTextBlock readLine = doc->findBlockByNumber(i);
        buffer.push_back(readLine.text());
    }
    return buffer;
}

std::vector<int> MainWindow::QString2int(QString qstr, QString del)
{
    std::vector<int> buffer;
    QStringList list = qstr.split(del);
    for(int i = 0; i < list.size(); i++)
        buffer.push_back(list[i].toInt());
    return buffer;
}

std::vector<std::string> MainWindow::QString2string(QString qstr, QString del)
{
    std::vector<std::string> buffer;
    QStringList list = qstr.split(del);
    for(int i = 0; i < list.size(); i++)
        buffer.push_back(list[i].toStdString());
    return buffer;
}

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

    ui->label_main->setStyleSheet("background-color: white; border: 5px outset green;");
    ui->label_main->setAutoFillBackground(true);
    ui->label_main->setPalette(pal);
    ui->label_main->setWordWrap(true);

    ui->label_message->setStyleSheet("background-color: white; border: 3px outset red;");
    ui->label_message->setPalette(pal);
    ui->label_message->setAutoFillBackground(true);
    ui->label_message->setWordWrap(true);

    pal.setColor(QPalette::Window, Qt::lightGray);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

//////////////////////////////////////////////////////////////////////////

void MainWindow::pushButton_start_handler()
{
    buffer = get_plainTextEdit_input();

    if(!buffer.empty() && buffer.size() >= 3)
    {
        collectionFlag = true;
        repaint();
    }
}

void MainWindow::label_message_handler(QString msg)
{
    ui->label_message->setText(msg);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPixmap pix(ui->label_main->width(), ui->label_main->height());
    pix.fill(Qt::white);

    QPainter painter(&pix);
    m_painter = &painter;
    m_painter->setRenderHint(QPainter::Antialiasing);

    if(collectionFlag)
    {
        collectionFlag = false;

        collection_handler();
        ui->label_main->setPixmap(pix);
    }
}

void MainWindow::collection_handler()
{
    std::vector<int> index, index_buffer;
    std::vector<std::string> num_buffer = QString2string(buffer[0], " ");
    std::vector<int> time_buffer = QString2int(buffer[1]);
    std::vector<std::string> type_buffer = QString2string(buffer[2]);

    collection col;

    for(std::string &i : num_buffer)
        index_buffer.push_back(col.name2index[i]);

    QFont font;
    m_painter->setPen(Qt::black);

    int initX = 50, initY = 50;
    QString title;

    for(int i = 0; i < int(index_buffer.size()); i++)
    {
        index.push_back(index_buffer[i]);
        std::vector<int> newIndex;
        col.findBestCombination(index, time_buffer[0], type_buffer[0], newIndex);

        QString msg = "";
        int total_fuel = 0, total_ammo = 0, total_fe = 0, total_al = 0;

        for(int i = 0; i < int(newIndex.size()); i++)
        {
            int j = newIndex[i];
            total_fuel += col.fuel[j];
            total_ammo += col.ammo[j];
            total_fe += col.fe[j];
            total_al += col.al[j];
        }

        msg += "  使用 ";
        msg += QString::number(time_buffer[0]);
        msg += " 分鐘，可得 ";

        msg += QString::number(total_fuel);
        msg += " 燃料";

        msg += " 、";
        msg += QString::number(total_ammo);
        msg += " 彈藥";

        msg += " 、";
        msg += QString::number(total_fe);
        msg += " 鋼鐵";

        msg += " 、";
        msg += QString::number(total_al);
        msg += " 鋁土";

        font.setPointSize(15);
        ui->label_message->setFont(font);
        ui->label_message->setText(msg);

        font.setPointSize(20);
        m_painter->setFont(font);

        title = QString::number(i+1) + " " + QString::fromStdString(col.names[index[i]])+ " : ";
        m_painter->drawText(initX, initY + 80 * i, title);

        //draw rectangle
        int size = newIndex.size();
        int fixedSize = 1450 / size;
        for(int s = 0, c = 20 - 0.5 * size; s < size; s++)
        {
            font.setPointSize(size >= 15 && col.names[newIndex[s]].size() >= 5? c-3:c);
            m_painter->setFont(font);
            msg = QString::fromStdString(col.names[newIndex[s]]);
            QRectF drawArea(initX + 250 + fixedSize * s, initY - 35 + 80 * i, fixedSize, 50);
            m_painter->drawRect(drawArea);
            m_painter->drawText(drawArea, Qt::AlignCenter, msg);
        }
    }
}

//////////////////////////////////////////////////////////////////////////

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

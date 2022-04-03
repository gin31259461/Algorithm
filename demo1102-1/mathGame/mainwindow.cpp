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

    if(!buffer.empty() && buffer.size() >= 1)
    {
        mathGameFlag = true;
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

    if(mathGameFlag)
    {
        mathGameFlag = false;

        mathGame_handler(QString2int(buffer[0]));
        ui->label_main->setPixmap(pix);
    }
}

void backTracking
(
    std::vector<std::vector<int>> dpScore,
    std::vector<std::vector<int>> best,
    std::vector<int> &index,
    std::vector<int> &score,
    int start, int end
)
{
    if(end - start < 2 || index.size() == best.size() - 2)
        return;

    int k = best[start][end];
    index.push_back(k);
    score.push_back(dpScore[start][end]);

    if(k - start > end - k)
    {
        backTracking(dpScore, best, index, score, start, k);
        backTracking(dpScore, best, index, score, k, end);
    }
    else
    {
        backTracking(dpScore, best, index, score, k, end);
        backTracking(dpScore, best, index, score, start, k);
    }
}

void MainWindow::mathGame_handler(std::vector<int> cards)
{
    int size = cards.size();

    //dp
    std::vector<std::vector<int>>
            dp(size, std::vector<int>(size)),
            best(size, std::vector<int>(size)),
            dpScore(size, std::vector<int>(size));

    for(int l = 2; l < size; l++)
        for(int i = 0; i + l < size; i++)
        {
            int j = i + l;

            for(int k = i + 1; k < j; k++)
            {
                int tmp = dp[i][k] + dp[k][j] + (cards[i] + cards[j]) * cards[k];
                if(tmp > dp[i][j])
                {
                    dp[i][j] = tmp;
                    best[i][j] = k;
                    dpScore[i][j] = (cards[i] + cards[j]) * cards[k];
                }
            }
        }

    std::vector<int> index, score;
    std::vector<int> tmpCards = cards;
    backTracking(dpScore, best, index, score, 0, size-1);

    QString msg;
    QFont font;
    font.setPointSize(15);

    for(int i = int(index.size()) - 1; i >= 0; i--)
    {
        tmpCards[index[i]] = -1;
        msg = "移除 ";
        msg += QString::number(cards[index[i]]);
        msg += "，得分  ";
        msg += QString::number(score[i]);
        msg += " 剩餘：";
        for(int n : tmpCards)
        {
            if(n != -1)
                msg += QString::number(n) + " ";
        }

        m_painter->setFont(font);
        m_painter->drawText(50, 10 + 50 * (int(index.size()) - i), msg);
    }

    msg = "總分 ";
    msg += QString::number(dp[0][size-1]);
    msg += " 分";
    m_painter->drawText(50, 10 + 50 * (int(index.size()) + 1), msg);

    ////////////////////////////////////////////////////
    font.setPointSize(15);

    //display input information
    msg = "  Cards :";
    for(int i = 0; i < size; i++)
        msg += " " + QString::number(cards[i]);

    ui->label_message->setFont(font);
    ui->label_message->setText(msg);
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

#include "mainviewcontroller.h"
#include "ui_mainviewcontroller.h"

MainViewController::MainViewController(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainViewController) {
    ui->setupUi(this);

    game = Game::instance();
    game->delegate = this;

    clickCount = 0;

    QPalette p;
    p.setColor(QPalette::Highlight, QColor(52, 52, 52, 128));

    ui->tableView->verticalHeader()->setDefaultSectionSize(64);
    ui->tableView->horizontalHeader()->setDefaultSectionSize(64);
    ui->tableView->setIconSize(QSize(60, 60));
    ui->tableView->setModel(getModel());
    ui->tableView->setPalette(p);
}

QStandardItemModel * MainViewController::getModel() {
    Board * board = game->getBoard();

    QStandardItemModel * model = new QStandardItemModel(ROWS, COLS);

    for (int i = 0; i < model->rowCount(); ++i) {
        for (int j = 0; j < model->columnCount(); ++j) {
            switch (board->getDataAt(i, j)) {
            case BLACK:
                model->setItem(i, j, new QStandardItem(QIcon(":/images/board/resources/black.png"), ""));
                printf(" BALK ");
                break;
            case WHITE:
                model->setItem(i, j, new QStandardItem(QIcon(":/images/board/resources/white.png"), ""));
                printf(" WHTE ");
                break;
            case BLACK_KING:
                model->setItem(i, j, new QStandardItem(QIcon(":/images/board/resources/black_k.png"), ""));
                printf(" BLKK ");
                break;
            case WHITE_KING:
                model->setItem(i, j, new QStandardItem(QIcon(":/images/board/resources/white_k.png"), ""));
                printf(" WHTK ");
                break;
            default:
                printf(" NULL ");
                break;
            }

            if ((i % 2 == 0 && j % 2 > 0) || (i % 2 > 0 && j % 2 == 0)) {
                model->setData(model->index(i, j), QBrush(QColor(142,61,0)), Qt::BackgroundColorRole);
            } else {
                model->setData(model->index(i, j), QBrush(QColor(255,206,103)), Qt::BackgroundColorRole);
            }
        }

        printf("\n");
    }

    printf("\n==============================================\n");

    return model;
}

QStandardItemModel * MainViewController::getModel(std::vector<CGCoordinate2D> r) {
    QStandardItemModel * model = getModel();

    for (unsigned int i = 0; i < r.size(); ++i) {
       model->setData(model->index(r[i].x, r[i].y), QBrush(QColor(94, 149, 208, 25)));
       model->setData(model->index(r[i].x, r[i].y), QBrush(QColor(60, 118, 231)), Qt::BackgroundColorRole);
    }

    return model;
}

MainViewController::~MainViewController() {
    delete ui;
}

void MainViewController::on_tableView_clicked(const QModelIndex &index) {
    if ((clickCount % 2) == 0) {
        from.x = index.row();
        from.y = index.column();

        std::vector<CGCoordinate2D> ret = game->getPossibleMoves(from);

        qDebug("CLICK\n%lu\n", ret.size());

        ui->tableView->setModel(getModel(ret));

    } else {
        to.x = index.row();
        to.y = index.column();

        if (!game->play(from, to)) {
            QMessageBox::about(this, "Error", "Movimiento invalido!");
        }

        ui->tableView->setModel(getModel());

        std::vector<history_t> history = game->getHistory();

        QStandardItemModel * model = new QStandardItemModel(history.size(), 2);

        int i = 0;
        for (history_t item : history) {
            model->setData(model->index(i, 0), QString(QString::fromStdString(item.move)));
            model->setData(model->index(i, 1), QString(QString::fromStdString(item.player)));

            ++i;
        }

        ui->history->setModel(model);
        ui->history->scrollToBottom();
    }



    ++clickCount;
}

#pragma mark - Se implementa el delegado de Game

void MainViewController::didWonGame(Game * game, player_t player) {
    if (player == PLAYER1) {
        QMessageBox::about(this, "Juego finalizado...", "El juego termino y el ganador es JUGADOR 1");
    } else {
         QMessageBox::about(this, "Juego finalizado...", "El juego termino y el ganador es CPU");
    }

    game->init();

    std::vector<history_t> history = game->getHistory();

    QStandardItemModel * model = new QStandardItemModel(history.size(), 2);

    int i = 0;
    for (history_t item : history) {
        model->setData(model->index(i, 0), QString(QString::fromStdString(item.move)));
        model->setData(model->index(i, 1), QString(QString::fromStdString(item.player)));

        ++i;
    }

    ui->history->setModel(model);
    ui->history->scrollToBottom();

    ui->score_black->setText(QString::number(12));
    ui->score_white->setText(QString::number(12));
}

void MainViewController::didChangeScore(Game * game, uint8_t white, uint8_t black) {
    ui->score_black->setText(QString::number(black));
    ui->score_white->setText(QString::number(white));
}

void MainViewController::on_actionNew_triggered()
{
    game->init();

    ui->tableView->setModel(getModel());

    std::vector<history_t> history = game->getHistory();

    QStandardItemModel * model = new QStandardItemModel(history.size(), 2);

    int i = 0;
    for (history_t item : history) {
        model->setData(model->index(i, 0), QString(QString::fromStdString(item.move)));
        model->setData(model->index(i, 1), QString(QString::fromStdString(item.player)));

        ++i;
    }

    ui->history->setModel(model);
    ui->history->scrollToBottom();

    ui->score_black->setText(QString::number(12));
    ui->score_white->setText(QString::number(12));
}

void MainViewController::on_actionSalir_triggered()
{
    exit(0);
}

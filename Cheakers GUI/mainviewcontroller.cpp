#include "mainviewcontroller.h"
#include "ui_mainviewcontroller.h"

MainViewController::MainViewController(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainViewController)
{
    ui->setupUi(this);

    clickCount = 0;

    QPalette p;
    p.setColor(QPalette::Highlight, QColor(52, 52, 52, 128));

    ui->tableView->verticalHeader()->setDefaultSectionSize(64);
    ui->tableView->horizontalHeader()->setDefaultSectionSize(64);
    ui->tableView->setIconSize(QSize(60, 60));
    ui->tableView->setModel(getModel());
    ui->tableView->setPalette(p);
}

QStandardItemModel * MainViewController::getModel() const {
    Board * board = game.getBoard();

    QStandardItemModel * model = new QStandardItemModel(ROWS, COLS);

    for (int i = 0; i < model->rowCount(); ++i) {
        for (int j = 0; j < model->columnCount(); ++j) {
            switch (board->getDataAt(i, j)) {
            case BLACK:
                model->setItem(i, j, new QStandardItem(QIcon(":/images/board/resources/black.png"), ""));
                break;
            case WHITE:
                model->setItem(i, j, new QStandardItem(QIcon(":/images/board/resources/white.png"), ""));
                break;
            case BLACK_KING:
                model->setItem(i, j, new QStandardItem(QIcon(":/images/board/resources/black_k.png"), ""));
                break;
            case WHITE_KING:
                model->setItem(i, j, new QStandardItem(QIcon(":/images/board/resources/white_k.png"), ""));
                break;
            default:
                break;
            }

            if ((i % 2 == 0 && j % 2 > 0) || (i % 2 > 0 && j % 2 == 0)) {
                model->setData(model->index(i, j), QBrush(QColor(142,61,0)), Qt::BackgroundColorRole);
            } else {
                model->setData(model->index(i, j), QBrush(QColor(255,206,103)), Qt::BackgroundColorRole);
            }
        }
    }

    return model;
}

MainViewController::~MainViewController()
{
    delete ui;
}

void MainViewController::on_tableView_clicked(const QModelIndex &index)
{
    if ((clickCount % 2) == 0) {
        from.x = index.row();
        from.y = index.column();
    } else {
        to.x = index.row();
        to.y = index.column();

        if (game.play(from, to)) {
            ui->tableView->setModel(getModel());
        } else {
            QMessageBox::about(this, "Error", "Movimiento invalido!");

        }
    }

    ++clickCount;
}

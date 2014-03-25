#ifndef MAINVIEWCONTROLLER_H
#define MAINVIEWCONTROLLER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include "../game.h"

namespace Ui {
class MainViewController;
}

class MainViewController : public QMainWindow, public GameDelegate
{
    Q_OBJECT

public:
    explicit MainViewController(QWidget *parent = 0);
    ~MainViewController();

private slots:
    void on_tableView_clicked(const QModelIndex &index);
    
    void on_actionNew_triggered();

    void on_actionSalir_triggered();

private:
    Game * game;
    uint8_t clickCount;
    CGCoordinate2D from, to;

    Ui::MainViewController *ui;
    QStandardItemModel * getModel();
    QStandardItemModel * getModel(std::vector<CGCoordinate2D>);

    // Delegado Game
    void didWonGame(Game *, player_t);
    void didChangeScore(Game *, uint8_t, uint8_t);
};

#endif // MAINVIEWCONTROLLER_H

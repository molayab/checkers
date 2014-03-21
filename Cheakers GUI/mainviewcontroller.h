#ifndef MAINVIEWCONTROLLER_H
#define MAINVIEWCONTROLLER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include "../game.h"

namespace Ui {
class MainViewController;
}

class MainViewController : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainViewController(QWidget *parent = 0);
    ~MainViewController();

private slots:
    void on_tableView_clicked(const QModelIndex &index);
    
private:
    Game game;
    uint8_t clickCount;
    CGCoordinate2D from, to;

    Ui::MainViewController *ui;
    QStandardItemModel * getModel() const;
};

#endif // MAINVIEWCONTROLLER_H

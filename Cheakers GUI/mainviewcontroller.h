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

private:
    Game game;
    Ui::MainViewController *ui;
    QStandardItemModel * getModel() const;
};

#endif // MAINVIEWCONTROLLER_H

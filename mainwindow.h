#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "unit.h"
#include "unitdatamanager.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_Left_Name_comboBox_currentTextChanged(const QString &arg1);

    void on_Right_Name_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

private:
    UnitDataManager UnitDataManager;
    QVector<Unit> Units;
};
#endif // MAINWINDOW_H

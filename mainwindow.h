#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sec_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listWidget_currentRowChanged(int currentRow);

    void on_line_search_textChanged(const QString &arg1);

    void on_pushButton_modifica_clicked();

    void on_actionNuovo_contatto_triggered();

    void on_pushButton_elimina_clicked();

private:
    Ui::MainWindow *ui;
    sec_dialog *sec_dialogg;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include <QTimer>
#include <stdint.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void when_timer_rtt_timeout();
    void on_pushButton_send_clicked();
    void on_pushButton_link_clicked();
    void on_pushButton_unlink_clicked();
    void on_pushButton_clearShow_clicked();
    void on_action_help_triggered();
    void on_comboBox_RamBaseAddr_currentIndexChanged(const QString &arg1);
    void on_comboBox_RamSize_currentIndexChanged(const QString &arg1);

    void on_pushButton_clearInput_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer_rtt;
    void save_or_restore_configure_file(bool isSave);
    void op_show(QString tipInfo);
};

#endif // MAINWINDOW_H

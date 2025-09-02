#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDir>
#include <QDateTime>
#include <QTableWidgetItem>
#include <QMap>

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
    void checkDirectory();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QString monitoredDir;
    QMap<QString, QDateTime> fileStatus;

    void add(const QString &fileName, const QString &event, const QDateTime &time);
    void saveToFile();
    void loadFromFile();
};

#endif // MAINWINDOW_H


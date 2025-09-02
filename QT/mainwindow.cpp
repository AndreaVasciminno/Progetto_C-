#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString directory = QFileDialog::getExistingDirectory(this,
                                                          "Seleziona una cartella da monitorare",
                                                          QDir::homePath(),
                                                          QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (directory.isEmpty()) {
        QMessageBox::warning(this, "Errore", "Nessuna cartella selezionata. Il programma verrà chiuso.");
        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
    }

    monitoredDir = directory;
    setWindowTitle("Monitoring: " + monitoredDir);

    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->tableWidget->setSortingEnabled(true);

    ui->saveLogButton->setText("Save log");

    ui->tableWidget->setColumnCount(4);

    QStringList intestazioni;
    intestazioni << "Color" << "Filename" << "Event" << "Time";
    ui->tableWidget->setHorizontalHeaderLabels(intestazioni);

    ui->tableWidget->setColumnWidth(0, 30);
    ui->tableWidget->setColumnWidth(0, 200);
    ui->tableWidget->setColumnWidth(1, 100);
    ui->tableWidget->setColumnWidth(2, 150);

    loadFromFile();

    connect(qApp, &QApplication::aboutToQuit, this, &MainWindow::saveToFile);
    connect(ui->saveLogButton, &QPushButton::clicked, this, &MainWindow::saveToFile);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkDirectory);
    timer->start(3000);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::checkDirectory()
{
    QDir dir(monitoredDir);

    QFile logFile(monitoredDir + "/log.txt");
    QSet<QString> loggedFiles;
    if (logFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&logFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(";");
            if (parts.size() == 4) {
                loggedFiles.insert(parts[1]);
            }
        }
        logFile.close();
    }

    QFileInfoList files = dir.entryInfoList(QDir::Files);
    for (const QFileInfo &fileInfo : files) {
        QString fileName = fileInfo.fileName();

        if (fileName == "log.txt" || loggedFiles.contains(fileName)) {
            continue;
        }

        QDateTime lastModified = fileInfo.lastModified();

        if (!fileStatus.contains(fileName)) {
            // Nuovo file
            add(fileName, "Created", lastModified);
        } else if (fileStatus[fileName] < lastModified) {
            // File modificato
            add(fileName, "Modified", lastModified);
        }
        fileStatus[fileName] = lastModified;
    }

    auto it = fileStatus.begin();
    while (it != fileStatus.end()) {
        if (!dir.exists(it.key())) {
            add(it.key(), "Deleted", QDateTime::currentDateTime());
            it = fileStatus.erase(it);
        } else {
            ++it;
        }
    }
}



void MainWindow::add(const QString &fileName, const QString &event, const QDateTime &time)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    QTableWidgetItem *colorItem = new QTableWidgetItem();
    if (event == "Created") {
        colorItem->setBackground(Qt::green);
    } else if (event == "Modified") {
        colorItem->setBackground(Qt::blue);
    } else if (event == "Deleted") {
        colorItem->setBackground(Qt::red);
    }
    colorItem->setFlags(Qt::NoItemFlags);
    ui->tableWidget->setItem(row, 0, colorItem);

    QTableWidgetItem *fileItem = new QTableWidgetItem(fileName);
    fileItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tableWidget->setItem(row, 1, fileItem);

    QTableWidgetItem *eventItem = new QTableWidgetItem(event);
    eventItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tableWidget->setItem(row, 2, eventItem);

    QTableWidgetItem *timeItem = new QTableWidgetItem(time.toString());
    timeItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tableWidget->setItem(row, 3, timeItem);
}

void MainWindow::saveToFile()
{
    QFile file(monitoredDir + "/log.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            QString color = ui->tableWidget->item(row, 0)->background().color().name();
            QString filename = ui->tableWidget->item(row, 1)->text();
            QString event = ui->tableWidget->item(row, 2)->text();
            QString time = ui->tableWidget->item(row, 3)->text();
            out << color << ";" << filename << ";" << event << ";" << time << "\n";
        }
        file.close();
    }
}

void MainWindow::loadFromFile()
{
    QFile file(monitoredDir + "/log.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(";");
            if (parts.size() == 4) {
                QString fileName = parts[1];
                if (fileName == "log.txt") {
                    continue;
                }
                QTableWidgetItem *colorItem = new QTableWidgetItem();
                colorItem->setBackground(QColor(parts[0]));
                QTableWidgetItem *fileItem = new QTableWidgetItem(parts[1]);
                QTableWidgetItem *eventItem = new QTableWidgetItem(parts[2]);
                QTableWidgetItem *timeItem = new QTableWidgetItem(parts[3]);

                int row = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(row);
                ui->tableWidget->setItem(row, 0, colorItem);
                ui->tableWidget->setItem(row, 1, fileItem);
                ui->tableWidget->setItem(row, 2, eventItem);
                ui->tableWidget->setItem(row, 3, timeItem);
            }
        }
        file.close();
    }
}






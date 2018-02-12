#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Demografia");
    this->statusBar()->setSizeGripEnabled(false);
    this->setFixedSize(QSize(534, 735));

    estrazione_dati();
    regioni();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::estrazione_dati() {

    std::ifstream is;

    is.open("data.txt");

    std::string regione = "";
    std::string range = "";
    int n_m;
    int n_f;
    std::string end = "<END>";

    if(is.is_open()) {
        do {
            // qDebug() << QString::fromStdString(regione);
            is >> regione;
            is >> range;
            is >> n_m;
            is >> n_f;
            if(regione!=end) {
                dato v(regione, range, n_m, n_f);
                this->dati.push_back(v);
            }
        } while(regione!=end);

        // IMPO
        // qDebug() << QString::fromStdString(dati[8].regione);
        // qDebug() << QString::fromStdString(dati[dati.size()-1].range);
    }
}

void MainWindow::regioni() {
    ui->comboBox->addItem("Select Region");
    std::string n_same = "";
    for(unsigned int i=0; i<dati.size()-1; i++) {
        std::string tmp = dati[i].regione;
        if(n_same != tmp) {
            n_same = tmp;
            ui->comboBox->addItem(QString::fromStdString(dati[i].regione));
        }
    }
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);

    if(arg1=="Select Region"){ return; }

    ui->tableWidget->setColumnCount(5);

    // Titolo righe
    QStringList titolo;
    titolo << "Età" << "Maschi" << "% Maschi" << "Femmine" << "% Femmine";
    ui->tableWidget->setHorizontalHeaderLabels(titolo);
    ui->tableWidget->verticalHeader()->setVisible(false);

    for(unsigned int i=0; i<dati.size(); i++) {
        if(QString::fromStdString(dati[i].regione) == arg1) {
            // per inserire una nuova riga, questo qui sotto
            int riga = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());

            ui->tableWidget->setItem(riga, RANGE, new QTableWidgetItem(
                                           QString::fromStdString(dati[i].range)));
            ui->tableWidget->setItem(riga, N_UOMINI, new QTableWidgetItem(
                                           QString::number(dati[i].numero_uomini)));
            ui->tableWidget->setItem(riga, P_UOMINI, new QTableWidgetItem(
                                           QString::number(dati[i].perc_uomini)));
            ui->tableWidget->setItem(riga, N_DONNE, new QTableWidgetItem(
                                           QString::number(dati[i].numero_donne)));
            ui->tableWidget->setItem(riga, P_DONNE, new QTableWidgetItem(
                                           QString::number(dati[i].perc_donne)));

        }
    }
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

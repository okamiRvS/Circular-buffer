#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

struct dato {
    std::string regione;
    std::string range;
    float numero_uomini;
    float perc_uomini;
    float numero_donne;
    float perc_donne;

    dato() {}
    dato(const std::string &reg, const std::string &ran,
         float n_d, float n_u)
        : regione(reg), range(ran), numero_uomini(n_u), perc_uomini(0),
          numero_donne(n_d), perc_donne(0)  {
        float tot = n_u + n_d;
        perc_uomini = (n_u * 100) / tot;
        perc_donne = (n_d * 100) / tot;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void estrazione_dati();
    void regioni();
    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    std::vector<dato> dati;

    enum Colonna {
        RANGE, N_UOMINI, P_UOMINI, N_DONNE, P_DONNE
    };

};

#endif // MAINWINDOW_H

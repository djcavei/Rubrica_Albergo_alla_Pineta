#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <QMessageBox>

//ogni nome fai getline con \n


using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::getline;

bool saved = true;
int edit = 0;
int display_offset = 0;

enum{COGNOME, NOME, DOCUMENTO, RESIDENZA, LUOGO, DATA, NOTE};

int total = 0;

vector<vector<string>> rubrica{};

void sort(vector<vector<string>>& vec) {
    //implementare algoritmo che scambia a due a due
    vector<vector<string>> aux(1);
    int index;
    for(int i = 0; i < vec.size() - 1; ++i) {
        aux[0] = vec[i];
        index = i;
        for(int j = i + 1; j < vec.size(); ++j) {
            if(vec[j][0] <= aux[0][0]) {
                aux[0] = vec[j];
                index = j;
            }
        }
        vec[index] = vec[i];
        vec[i] = aux[0];
    }
}

//se non trova cognomi cerca nomi
void search_by_name(){};

void search(vector<vector<string>>& vec, const QString& arg1, vector<int>& to_display) {
    //ottimizzazione, tenere traccia degli indici e ogni digit o backspace tu fai qualcosa
    string s = arg1.toStdString();
    for(char& elem : s)
        if(elem >= 'A' && elem <= 'Z') elem += 32; //+ fa rimpicciolire
    s[0] -= 32;
    for(int i = 0; i < vec.size() && vec[i][0][0] <= s[0]; ++i) {
        if(s[0] == vec[i][0][0]) {
            int j = 1;
            bool gg = true;
            while(gg && j < vec[i][0].size() && j < s.size()) {
                s[j] != vec[i][0][j] ? gg = false : 0;
                ++j;
            }
            if(gg) {
               if(to_display.empty()) {
                   to_display.push_back(i);
                   to_display.push_back(i);
               } else to_display[1] = i;
            }
            else search_by_name();
        }
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ifstream input("rubrica.txt");
    //if(!input) std::cout<<"Non esiste";
    //else std::cout<<"Si esiste";
    input>>total;
    string s;
    getline(input, s);
    while(total) {
        vector<string> vec{};
        for(int i = 0; i < 6; ++i) {
            string s;
            getline(input, s, '\n');
            vec.push_back(s);
        }
        //trattare diversamente le note
        string s;
        getline(input, s);
        vec.push_back(s);
        rubrica.push_back(vec);
        total--;
    }
    input.close();
    sort(rubrica);
    ofstream output("detti.txt");
    for(auto& elem : rubrica)
        for(auto& elem2 : elem)
            output<<elem2<<std::endl;
    output.close();
    ui->setupUi(this);
    QListWidget list(this);
    for(vector<string> elem : rubrica) {
        //prima metti nella ui e poi nella lista altrimenti non si vede
        QString qstr = QString::fromStdString(elem[COGNOME] + " " + elem[NOME]);
        QListWidgetItem *item = new QListWidgetItem(qstr);
        ui->listWidget->addItem(item);
        list.addItem(item);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void update_label(Ui::MainWindow *&ui, int currentRow) {
    std::cout<<currentRow<<" in updatelabel"<<std::endl;
    if(currentRow >= 0 and currentRow <= rubrica.size()) {
        ui->lineEdit_cognome->setText(QString::fromStdString(rubrica[currentRow][COGNOME]));
        ui->lineEdit_nome->setText(QString::fromStdString(rubrica[currentRow][NOME]));
        ui->lineEdit_data->setText(QString::fromStdString(rubrica[currentRow][DATA]));
        ui->lineEdit_documento->setText(QString::fromStdString(rubrica[currentRow][DOCUMENTO]));
        ui->lineEdit_luogo->setText(QString::fromStdString(rubrica[currentRow][LUOGO]));
        ui->lineEdit_residenza->setText(QString::fromStdString(rubrica[currentRow][RESIDENZA]));
        ui->textEdit_note->setText(QString::fromStdString(rubrica[currentRow][NOTE]));
    }
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    if(!edit) {
        ui->pushButton_modifica->setEnabled(true);
        ui->pushButton_elimina->setEnabled(true);
        edit = 1;
    }
    currentRow += display_offset;
    update_label(ui, currentRow);
}


void MainWindow::on_line_search_textChanged(const QString &arg1)
{
    ui->pushButton_modifica->setDisabled(true);
    ui->pushButton_elimina->setDisabled(true);
    edit = 0;
    //incolonnare cognomi|||||nomi
    ui->listWidget->clear();
    vector<int> to_display{};
    //std::cout<<ui->line_search->text().toStdString()<<std::endl;
    if(arg1.size())
        search(rubrica, arg1, to_display);
    else {
        std::cout<<"vuota"<<std::endl;
        to_display.push_back(0);
        to_display.push_back(rubrica.size()-1);
    }
    QListWidget list;
    if(to_display.size()) {
        display_offset = to_display[0];
        for(int i = to_display[0]; i <= to_display[1]; ++i) {
            QString qstr = QString::fromStdString(rubrica[i][COGNOME] + " " + rubrica[i][NOME]);
            QListWidgetItem *item = new QListWidgetItem(qstr);
            ui->listWidget->addItem(item);
            list.addItem(item);
        }
    }
}


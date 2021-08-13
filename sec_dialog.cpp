#include "sec_dialog.h"
#include "ui_sec_dialog.h"
#include <vector>
#include <string>

sec_dialog::sec_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sec_dialog)
{
    ui->setupUi(this);
}

sec_dialog::~sec_dialog()
{
    delete ui;
}

void sec_dialog::on_pushButton_salva_clicked()
{
    enum{COGNOME, NOME, DOCUMENTO, RESIDENZA, LUOGO, DATA, NOTE};
    if(ui->lineEdit_cognome->text().size() || ui->lineEdit_nome->text().size()) {
        vector<string> vec;
        vec.push_back(ui->lineEdit_cognome->text().toStdString());
        vec.push_back(ui->lineEdit_nome->text().toStdString());
        vec.push_back(ui->lineEdit_documento->text().toStdString());
        vec.push_back(ui->lineEdit_residenza->text().toStdString());
        vec.push_back(ui->lineEdit_luogo->text().toStdString());
        vec.push_back(ui->lineEdit_data->text().toStdString());
        vec.push_back(ui->textEdit_note->toPlainText().toStdString());
        int i = 0;
        for(i = 0; i < v->size(); ++i) {
            if(v->at(i).at(0) >= vec[0]){
                if((v->at(i).at(0) == vec[0] and v->at(i).at(1) > vec[1]) || v->at(i).at(0) > vec[0]) {
                    break;
                }
            }
        }
        //controllare se inserisci per ultimo
        v->insert(v[0].begin()+i, vec);
        close();
    }
}


void sec_dialog::on_lineEdit_cognome_textChanged(const QString &arg1)
{
    if(arg1.size() || ui->lineEdit_nome->text().size())
        ui->pushButton_salva->setEnabled(true);
    else ui->pushButton_salva->setDisabled(true);
}


void sec_dialog::on_lineEdit_nome_textChanged(const QString &arg1)
{
    if(arg1.size() || ui->lineEdit_cognome->text().size())
        ui->pushButton_salva->setEnabled(true);
    else ui->pushButton_salva->setDisabled(true);
}


void sec_dialog::on_pushButton_annulla_clicked()
{
    close();
}


#ifndef SEC_DIALOG_H
#define SEC_DIALOG_H

#include <QDialog>
using std::vector;
using std::string;

namespace Ui {
class sec_dialog;
}

class sec_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit sec_dialog(QWidget *parent = nullptr);
    vector<vector<string>> *v;
    ~sec_dialog();

private slots:
    void on_pushButton_salva_clicked();

    void on_lineEdit_cognome_textChanged(const QString &arg1);

    void on_lineEdit_nome_textChanged(const QString &arg1);

    void on_pushButton_annulla_clicked();

private:
    Ui::sec_dialog *ui;
};

#endif // SEC_DIALOG_H

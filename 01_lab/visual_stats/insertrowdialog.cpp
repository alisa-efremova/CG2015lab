#include "insertrowdialog.h"
#include "ui_insertrowdialog.h"
#include "qpushbutton.h"

InsertRowDialog::InsertRowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertRowDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(onAccepted()));

    connect(ui->editName, SIGNAL(textChanged(const QString)), this, SLOT(onEditName(const QString)));
    connect(ui->editValue, SIGNAL(valueChanged(int)), this, SLOT(onEditValue(int)));
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(this->areInputFieldsValid());
}

InsertRowDialog::~InsertRowDialog()
{
    delete ui;
}

bool InsertRowDialog::areInputFieldsValid()
{
    QString name = ui->editName->text();
    int val = ui->editValue->value();
    return (name != "" && val > 0);
}

void InsertRowDialog::onAccepted()
{
    emit rowReady(ui->editName->text(), ui->editValue->value());
}

void InsertRowDialog::onEditValue(int val)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(this->areInputFieldsValid());
}

void InsertRowDialog::onEditName(const QString &name)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(this->areInputFieldsValid());
}

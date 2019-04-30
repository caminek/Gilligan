#include "gilligan.hpp"
#include "ui_gilligan.h"
#include "generate.hpp"
#include "validate.hpp"

Gilligan::Gilligan(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gilligan)
{
    ui->setupUi(this);

    //Prevent Resize
    this->setFixedWidth(324);
    this->setFixedHeight(324);

    //Generate Tab
    ui->lineEdit_score->setValidator(new QIntValidator(0, 999990, this));
    ui->lineEdit_score->setMaxLength(8);
    ui->lineEdit_score->setText(QString("0"));
    ui->spinbox_level->setMinimum(2);
    ui->spinbox_level->setMaximum(4);
    ui->spinbox_level->setValue(2);
    ui->button_generate->setEnabled(true);  //score of 0 is valid

    //Validate Tab
    ui->lineEdit_password->setValidator(new QRegExpValidator(QRegExp("[a-pA-P]{,8}"), this));
    ui->button_verify->setEnabled(false);

    //Connect
    connect(ui->lineEdit_password, SIGNAL(textEdited(QString)), this, SLOT(password_changed()));
    connect(ui->lineEdit_score, SIGNAL(textEdited(QString)), this, SLOT(score_valid()));
    connect(ui->button_generate, SIGNAL (released()),this, SLOT (generate_password()));
    connect(ui->button_verify, SIGNAL (released()),this, SLOT (verify_password()));
}


Gilligan::~Gilligan()
{
    delete ui;
}


void Gilligan::password_changed()
{
    if (ui->lineEdit_password->text().length() == 8)
    {
        ui->button_verify->setEnabled(true);
    }
    else
    {
        ui->button_verify->setEnabled(false);
        ui->label_verify->clear();
    }
}


void Gilligan::score_valid()
{
    if (ui->lineEdit_score->text().isEmpty())
        ui->button_generate->setEnabled(false);
    else
        ui->button_generate->setEnabled(true);
}


void Gilligan::generate_password()
{
    generate gen;
    uint8_t level = static_cast<uint8_t>(ui->spinbox_level->value());
    std::string score = ui->lineEdit_score->text().toStdString();
    QString password = QString::fromStdString(gen.generator(level, score));
    ui->le_gen_password->setText(password);
}

void Gilligan::verify_password()
{
    validate val;
    Results results;
    QString score;
    QString level;

    std::string pwd = ui->lineEdit_password->text().toStdString();

    results = val.validator(pwd);

    if (!results.is_valid)
    {
        ui->label_verify->setText("Invalid Password");
    }
    else
    {
        score = QString::fromStdString(results.score).remove( QRegExp("^[0]*")) ;

        if (score .length() < 1)  //response for a score of zero
            score = "000000";

        level = QString::number(results.level);
        ui->label_score->setText(score);
        ui->label_level->setText(level);
    }
}



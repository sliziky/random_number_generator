#include "generator.h"
#include "ui_generator.h"
#include <random>
#include <iostream>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
Generator::Generator(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::Generator)
{
    ui->setupUi(this);
    connect(ui->generateButton, &QPushButton::clicked, this, &Generator::generateNumber);
    connect(ui->clearButton,    &QPushButton::clicked, this, &Generator::clear);
    connect(ui->saveButton,     &QPushButton::clicked, this, &Generator::saveToFile);
    connect(ui->exitButton,     &QPushButton::clicked, this, &QApplication::exit);
}

void Generator::generateNumber() {
    clear();
    // if the upper bound is not higher or # of numbers is < 0
    if (!_correctInputParameters ()) {
        QMessageBox::warning ( this, tr("Wrong input"), tr( "Upper bound is not higher or # of nums is < 0") );
        return;
    }


    int numbersCount = ui->numbers->value ();
    QString separator = ui->separator->currentText ();
    _nums = "";
    // random numbers
    if (ui->random->isChecked ()) {
        _generateNumbers (0, numbersCount, true);
    }
    // sequential numbers
    else {
        int lower = ui->minimumSpinBox->value ();
        int upper = ui->maximumSpinBox->value ();
        _generateNumbers (lower, upper + 1, false);
    }
    ui->textEdit->setText (_nums);
}

void Generator::_generateNumbers( int low, int high, bool random ) {
    QString separator = _getSeparator();

    for ( qint32 i = low; i < high; ++i ) {
        if ( random ) {
            _nums += QString::number (_generateNumber ());
        }
        else { // sequential
            _nums += QString::number( i );
        }
        _nums += separator;
        // output into multiple lines
        if (!_oneLineOutput ()) {
            _nums += "\n";
        }
    }
    // get rid of the last separator char
    if ( _oneLineOutput () && separator != "" ) { _removeLastChar(_nums);}
}

void Generator::saveToFile () {
    QString filename = QFileDialog::getSaveFileName (this, tr("Save numbers"), "", tr("Text file (*.txt);;All Files(*)"));
    if ( filename.isEmpty () ) { return; }
    else {
        QFile output(filename);
        if ( !output.open(QIODevice::WriteOnly | QIODevice::Text) ) {
            QMessageBox::information( this,
                                      tr("Unable to open file"),
                                      output.errorString() );
            return;
        }
        QTextStream ts(&output);
        ts << _nums.toUtf8 ();
        output.close();
    }
}

bool Generator::_correctInputParameters() {
    return ui->minimumSpinBox->value () <= ui->maximumSpinBox->value ()
        && ui->numbers->value () >= 0;
}

void Generator::clear (){
    ui->textEdit->clear ();
}

qint32 Generator::_generateNumber() {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution< qint32 > distr( ui->minimumSpinBox->value (),
                                                ui->maximumSpinBox->value () );
    return distr(eng);
}

Generator::~Generator()
{
    delete ui;
}
bool Generator::_oneLineOutput() {
    return ui->oneLine->isChecked ();
}
void Generator::_removeLastChar( QString &string ) {
    string.remove ( string.size () - 1, 1 );
}
QString Generator::_getSeparator() {
    auto separator = ui->separator->currentText();
    if ( separator == "(space)") return " ";
    if ( separator == "(nothing)") return "";
    return separator;
}

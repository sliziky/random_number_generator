#include "generator.h"
#include "ui_generator.h"
#include <random>
#include <iostream>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
namespace Ui {
	class Generator;
}
Generator::Generator(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::Generator)
{
    ui->setupUi(this);

    connect(ui->saveButton,     &QPushButton::clicked,     this, &Generator::saveToFile);
    connect(ui->exitButton,     &QPushButton::clicked,     this, &QApplication::exit);
    connect(ui->minimumSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &Generator::setMinValue);
    connect(ui->maximumSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &Generator::setMaxValue);
}

Generator::~Generator() {
    delete ui;
}

void Generator::on_generateButton_clicked (){
    clear();
    int low = ui->minimumSpinBox->value ();
    int high = ui->maximumSpinBox->value ();
    int numberCount = ui->numbers->value ();
    // random numbers
    if (ui->random->isChecked ()) {
        _generateNumbers (low, high, mode::random);
    }
    if (ui->sequential->isChecked ()) {
        _generateNumbers (low, high + 1, mode::sequential);
    }
    if (ui->sequentialn->isChecked ()) {
        _generateNumbers (low, low + numberCount, mode::sequentialn);
    }

    ui->textEdit->setText (_nums);
}

void Generator::on_sequential_clicked() {
    ui->numbers->setEnabled (false);
    ui->maximumSpinBox->setEnabled (true);
}
void Generator::on_random_clicked() {
    ui->numbers->setEnabled (true);
    ui->maximumSpinBox->setEnabled (true);
}
void Generator::on_sequentialn_clicked() {
    ui->maximumSpinBox->setEnabled (false);
    ui->numbers->setEnabled (true);
}
void Generator::_generateNumbers( int low, int high, const mode& mode ) {
    QString separator = _getSeparator();
    bool isOneLine = _isOneLineOutput ();
    if ( mode == mode::random ) {
        int numbersCount = ui->numbers->value ();
        for ( qint32 i = 0; i < numbersCount; ++i ) {
            _nums += QString::number ( _generateRandomNumber (low, high));
            _appendSeparator ( separator, isOneLine );
        }
    }
    if ( mode == mode::sequential || mode == mode::sequentialn ) {
        for ( int i = low; i < high; ++i ) {
            _nums += QString::number( i );
            _appendSeparator ( separator, isOneLine );
        }
    }


    // get rid of the last separator char
    if ( _isOneLineOutput () && separator != "" ) { _removeLastChar(_nums);}
}

void Generator::saveToFile () {
    QString filename = QFileDialog::getSaveFileName (this,
                                                    tr("Save numbers"), "",
                                                    tr("Text file (*.txt);;All Files(*)"));
    if ( filename.isEmpty () ) { return; }
    QFile output( filename );

    if ( !output.open(QIODevice::WriteOnly | QIODevice::Text) ) {
        QMessageBox::information( this,
                                 tr("Unable to open file"),
                                 output.errorString() );
        return;
    }

    QTextStream ts( &output );
    ts << _nums.toUtf8 ();
    output.close();
}

qint32 Generator::_generateRandomNumber(int low, int high) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution< qint32 > distr( low, high );
    return distr(eng);
}

QString Generator::_getSeparator() {
    auto separator = ui->separator->currentText();
    if ( separator == "(space)" )   return " ";
    if ( separator == "(nothing)" ) return "";
    return separator;
}
void Generator::setMinValue( int newValue ) {
    auto maxValue = ui->maximumSpinBox->value ();
    if ( newValue > maxValue ) { ui->minimumSpinBox->setValue ( maxValue ); }
}

void Generator::setMaxValue ( int newValue ) {
    auto minValue = ui->minimumSpinBox->value ();
    if ( newValue < minValue ) { ui->maximumSpinBox->setValue (minValue); }
}

void Generator::clear (){
    _nums = "";
    ui->textEdit->clear ();
}

void Generator::_removeLastChar( QString &string ) {
    string.remove ( string.size () - 1, 1 );
}

void Generator::on_clearButton_clicked () {
    ui->textEdit->clear ();
}

bool Generator::_hasCorrectInputParameters() {
    return ui->minimumSpinBox->value () <= ui->maximumSpinBox->value ();
}

bool Generator::_isOneLineOutput() {
    return ui->oneLine->isChecked ();
}

void Generator::_appendSeparator( const QString& separator, bool oneLine) {
    _nums += separator;
    if ( !oneLine ) {
        _nums += "\n";
    }
}


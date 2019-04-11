#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QTime>
#include <QVBoxLayout>

#include <random>
#include <qglobal.h>

#include "config.h"
#include "generator.h"


Generator::Generator( QWidget* parent )
    : QWidget( parent )
{
    _init();
    _createDisplay ();
    _createButton ();
    _createSpinBoxes ();
    connect ( _button, SIGNAL(clicked()), this, SLOT(showNumber()) );
}
void Generator::_init() {
    QTime time = QTime::currentTime ();
    qsrand( static_cast< uint >( time.msec ()) );
    setFixedSize( Config::Window::width, Config::Window::height );
    setWindowTitle( "Random Number Generator" );
}
void Generator::_createButton() {
    _button = new QPushButton( Config::Button::title, this );
    _button->setGeometry ( Config::Button::pos_x,
                           Config::Button::pos_y,
                           Config::Button::width,
                           Config::Button::height );
}
void Generator::_createDisplay() {
     _display = new QLabel( this );
     _display->setFont      ( Config::Fonts::sansFont );
     _display->setAlignment ( Qt::AlignCenter);
     _display->setGeometry  ( Config::Display::pos_x,
                              Config::Display::pos_y,
                              Config::Display::width,
                              Config::Display::height );

     _display->setNum ( Config::Display::default_value );
}
void Generator::_createSpinBoxes() {
    _createMinSpinBox();
    _createMaxSpinBox();
    _createSpinBoxLayout();
}
void Generator::_createSpinBoxLayout(){
    _groupBox        = new QGroupBox( this );
    _layout          = new QVBoxLayout;
    QLabel* labelMin = new QLabel( tr("Minimum: ") );
    QLabel* labelMax = new QLabel( tr("Maximum: ") );

    _layout->addWidget   ( labelMin );
    _layout->addWidget   ( _minSpinBox );
    _layout->addWidget   ( labelMax );
    _layout->addWidget   ( _maxSpinBox );
    _groupBox->setLayout ( _layout );
}
void Generator::_createMaxSpinBox() {
    _maxSpinBox = new QSpinBox ( this );
    _maxSpinBox->setMinimum    ( Config::SpinBox::minimum );
    _maxSpinBox->setMaximum    ( Config::SpinBox::maximum );
    _maxSpinBox->setSingleStep ( Config::SpinBox::single_step );
    _maxSpinBox->setValue      ( Config::SpinBox::default_value );
}
void Generator::_createMinSpinBox() {
    _minSpinBox = new QSpinBox ( this );
    _minSpinBox->setMinimum    ( Config::SpinBox::minimum );
    _minSpinBox->setMaximum    ( Config::SpinBox::maximum );
    _minSpinBox->setSingleStep ( Config::SpinBox::single_step );
    _minSpinBox->setValue      ( Config::SpinBox::default_value );
}
int Generator::_generateNumber( int low, int high ) {

    if ( low > high ) {
        throw BadParameters( "Upper bound is NOT higher \n" );
    }
    return qrand() % (( high + 1) - low) + low;
}
void Generator::showNumber() {
    _display->setNum( _generateNumber( _minSpinBox->value(),
                                       _maxSpinBox->value () ));
}

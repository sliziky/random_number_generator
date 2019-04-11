#ifndef GENERATOR_H
#define GENERATOR_H

#include <QWidget>
#include <exception>
class QPushButton;
class QLabel;
class QSpinBox;
class QGroupBox;
class QVBoxLayout;

struct BadParameters : std::logic_error
{
    using std::logic_error::logic_error;
};

class Generator : public QWidget
{
    Q_OBJECT
public:
    explicit Generator( QWidget* parent = nullptr );
public slots:
    void showNumber();
signals:

private:
    QPushButton* _button;
    QLabel*      _display;
    QSpinBox*    _minSpinBox;
    QSpinBox*    _maxSpinBox;
    QGroupBox*   _groupBox;
    QVBoxLayout* _layout;
    int          _generateNumber( int low, int high );
    void         _createSpinBoxes();
    void         _createMinSpinBox();
    void         _createMaxSpinBox();
    void         _createSpinBoxLayout();
    void         _createButton();
    void         _createDisplay();
    void         _init();
};

#endif // GENERATOR_H

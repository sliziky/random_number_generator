#ifndef GENERATOR_H
#define GENERATOR_H

#include <QMainWindow>
class QSpinBox;
namespace Ui {
    class Generator;
}

class Generator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Generator(QWidget *parent = nullptr);
    ~Generator();

public slots:
    void generateNumber();
    void clear();
    void saveToFile();

private:
    Ui::Generator *ui;
    qint32        _generateNumber();
    QString       _nums;
    bool          _correctInputParameters();
    bool          _oneLineOutput();
    void          _generateNumbers( int from, int to, bool random );
    void          _removeLastChar( QString& string );
    QString       _getSeparator();
};

#endif // GENERATOR_H

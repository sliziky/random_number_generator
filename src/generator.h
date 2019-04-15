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
    void clear();
    void saveToFile();
    void setMinValue(int);
    void setMaxValue(int);
private slots:
    void on_clearButton_clicked();

    void on_generateButton_clicked();

    void on_sequential_clicked();

    void on_random_clicked();

    void on_sequentialn_clicked();

private:
    Ui::Generator *ui;
    qint32        _generateRandomNumber(int low, int high);
    QString       _getSeparator();
    QString       _nums;
    bool          _hasCorrectInputParameters();
    bool          _isOneLineOutput();
    void          _generateNumbers( int low, int high, const QString& );
    void          _removeLastChar( QString& );
    void          _appendSeparator( const QString&, bool );
};

#endif // GENERATOR_H

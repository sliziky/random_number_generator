#include <QApplication>
#include <QPushButton>
#include <iostream>
#include "generator.h"
int main(int argc, char **argv)
{
    QApplication qapp( argc, argv );
    Generator generator{};
    generator.show ();
    try {
        qapp.exec();
    }
    catch(const std::exception& e) {
        std::cerr << e.what () << std::endl;
    }
    return 0;

}

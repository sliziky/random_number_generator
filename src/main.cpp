#include <QApplication>
#include <QPushButton>
#include "generator.h"
int main(int argc, char* argv[]) {
    QApplication app(argc ,argv);
    QPushButton button {};
    Generator gen{};
    gen.show ();

    app.exec ();
    return 0;

}

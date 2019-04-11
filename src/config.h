#ifndef CONFIG_H
#define CONFIG_H
#include <QFont>
#include <QString>
namespace Config
{

namespace Window
{
    constexpr static int height = 150;
    constexpr static int width  = 300;
} // Window

namespace Button
{
    const static QString title  = "Generate";
    constexpr static int height = 30;
    constexpr static int width  = 80;
    constexpr static int pos_x  = Window::width  / 2 - width  / 2;
    constexpr static int pos_y  = Window::height - height - 10;
} // Button

namespace Display
{
    constexpr static int height        = 45;
    constexpr static int width         = 90;
    constexpr static int pos_x         = Window::width / 2 - width / 2;
    constexpr static int pos_y         = 20;
    constexpr static int default_value = 0;
} // Display

namespace Fonts
{
    const static QFont serifFont( "Times", 10, QFont::Bold );
    const static QFont sansFont( "Helvetica [Cronyx]", 12 );
} // Fonts

namespace SpinBox
{
    constexpr static int minimum       = -30000;
    constexpr static int maximum       = 30000;
    constexpr static int single_step   = 1;
    constexpr static int default_value = 0;
} // SpinBox

} // Config



#endif // CONFIG_H

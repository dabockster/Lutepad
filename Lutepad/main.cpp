/* Steven Bock
   January 27th, 2014
   SOURCES: Stack Overflow, Cplusplus.com, Qt Docs

   Bitcoin/Dogecoin GitHub Repos used as reference for
   Object-Oriented approach
 */

#include "lutepadmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LutepadMainWindow w;
    w.show();
    
    return a.exec();
}

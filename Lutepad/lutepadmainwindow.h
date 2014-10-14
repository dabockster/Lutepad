/* Steven Bock
   January 27th, 2014
   SOURCES: Stack Overflow, Cplusplus.com, Qt Docs

   Bitcoin/Dogecoin GitHub Repos used as reference for
   Object-Oriented approach
 */


#ifndef LUTEPADMAINWINDOW_H
#define LUTEPADMAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QMenu>
#include <QPlainTextEdit>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QDateTime>
#include <QLineEdit>
#include <QPushButton>
#include <QSignalMapper>
#include <QTextBlock>

//About Lutepad - built at compile time from aboutlutepad.ui
#include "aboutlutepad.h"
#include "ui_aboutlutepad.h" //check this to see the code

class aboutlutepad;
class find_replace;

namespace Ui {
class LutepadMainWindow;
}

class LutepadMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit LutepadMainWindow(QWidget *parent = 0);
    ~LutepadMainWindow();

protected slots:
    void find();
    void find_next(QString );
    
private:
    Ui::LutepadMainWindow *ui;

    //Actual text editor
    QPlainTextEdit * editor;

    //Instantiate the status bar
    QStatusBar * status_bar;

    //Instantiate the menu bar
    QMenuBar * menu_bar;

    //File menu
    QMenu * file_menu;
    QAction * new_item;
    QAction * open_item;
    QAction * save_item;
    QAction * print_item;
    QAction * exit_item;

    //Edit menu
    QMenu * edit_menu;
    QAction * undo_item;
    QAction * cut_item;
    QAction * copy_item;
    QAction * paste_item;
    QAction * delete_item;
    QAction * find_item;
    QAction * select_all_item;
    QAction * time_date_item;

    //Help menu
    QMenu * help_menu;
    QAction * about_lutepad_item;
    QAction * about_qt_item;

    //create QActions
    void assemble_actions();

    //create menus
    void assemble_menus();

    //set window title
    void set_title(QString);

    //see if the user wants the document saved
    int user_save();

private slots: //One slot for each menu action

    //File
    void new_file();
    void open_file();
    void save_file();
    void print();
    void exit();

    //Edit
    void undo();
    void cut();
    void copy();
    void paste();
    void delete_selection();
    void select_all();
    void time_date();

    //Help
    void about_lutepad();
    void about_qt();

    //Resize editor
    void resize();
};

#endif // LUTEPADMAINWINDOW_H

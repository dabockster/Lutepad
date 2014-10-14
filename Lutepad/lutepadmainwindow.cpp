/* Steven Bock
   January 27th, 2014
   SOURCES: Stack Overflow, Cplusplus.com, Qt Docs

   Bitcoin/Dogecoin GitHub Repos used as reference for
   Object-Oriented approach
 */

#include "lutepadmainwindow.h"
#include "ui_lutepadmainwindow.h"
#include <iostream>

LutepadMainWindow::LutepadMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LutepadMainWindow),
    about_qt_item(0)
{
    //restore_window_size();
    ui->setupUi(this);

    //Set window title
    QString default_title = QString("Untitled");
    set_title(default_title);

    //Build the editor - WOULD NOT FUNCTION CORRECTLY IN SEPARATE CPP FILE
    QWidget *main = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    editor = new QPlainTextEdit;
    mainLayout->addWidget(editor);
    main->setLayout(mainLayout);
    setCentralWidget(main);

    //Assemble QActions
    assemble_actions();

    //Assemble menus
    assemble_menus();
}

/*
 * 0 = save
 * 1 = discard
 * 2 = cancel
 */

int LutepadMainWindow::user_save(){
    QMessageBox::StandardButton ask;

    ask = QMessageBox::warning(this, "Save", "Do you want to save this file?",
                                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ask == QMessageBox::Save)
        return 0;
    else if (ask == QMessageBox::Discard)
        return 1;
    return 2;
}

void LutepadMainWindow::set_title(QString fileName){
    setWindowTitle(fileName + " - Lutepad");
}

void LutepadMainWindow::assemble_actions(){
    //File menu
    new_item = new QAction("New", this);
    new_item->setShortcuts(QKeySequence::New);
    connect(new_item, SIGNAL(triggered()), this, SLOT(new_file()));

    open_item = new QAction("Open...", this);
    open_item->setShortcuts(QKeySequence::Open);
    connect(open_item, SIGNAL(triggered()), this, SLOT(open_file()));

    save_item = new QAction("Save", this);
    save_item->setShortcuts(QKeySequence::Save);
    connect(save_item, SIGNAL(triggered()), this, SLOT(save_file()));

    print_item = new QAction("Print...", this);
    print_item->setShortcuts(QKeySequence::Print);
    connect(print_item, SIGNAL(triggered()), this, SLOT(print()));

    exit_item = new QAction("Exit", this);
    connect(exit_item, SIGNAL(triggered()), this, SLOT(exit()));


    //Edit Menu
    undo_item = new QAction("Undo", this);
    undo_item->setShortcuts(QKeySequence::Undo);
    connect(undo_item, SIGNAL(triggered()), this, SLOT(undo()));

    cut_item = new QAction("Cut", this);
    cut_item->setShortcuts(QKeySequence::Cut);
    connect(cut_item, SIGNAL(triggered()), this, SLOT(cut()));

    copy_item = new QAction("Copy", this);
    copy_item->setShortcuts(QKeySequence::Copy);
    connect(copy_item, SIGNAL(triggered()), this, SLOT(copy()));

    paste_item = new QAction("Paste", this);
    paste_item->setShortcuts(QKeySequence::Paste);
    connect(paste_item, SIGNAL(triggered()), this, SLOT(paste()));

    delete_item = new QAction("Delete", this);
    delete_item->setShortcuts(QKeySequence::Delete);
    connect(delete_item, SIGNAL(triggered()), this, SLOT(delete_selection()));

    find_item = new QAction("Find", this);
    find_item->setShortcuts(QKeySequence::Find);
    connect(find_item, SIGNAL(triggered()), this, SLOT(find()));

    select_all_item = new QAction("Select All", this);
    select_all_item->setShortcuts(QKeySequence::SelectAll);
    connect(select_all_item, SIGNAL(triggered()), this, SLOT(select_all()));

    time_date_item = new QAction("Time/Date", this);
    time_date_item->setShortcut(Qt::Key_F5);
    connect(time_date_item, SIGNAL(triggered()), this, SLOT(time_date()));

    //Help Menu
    about_lutepad_item = new QAction("About Lutepad", this);
    connect(about_lutepad_item, SIGNAL(triggered()), this, SLOT(about_lutepad()));

    about_qt_item = new QAction("About Qt", this);
    connect(about_qt_item, SIGNAL(triggered()), this, SLOT(about_qt()));
}

void LutepadMainWindow::assemble_menus(){

    /**********File menu**********/
    file_menu = menuBar()->addMenu("File");

    file_menu->addAction(new_item);
    file_menu->addAction(open_item);
    file_menu->addAction(save_item);

    file_menu->addSeparator();

    file_menu->addAction(print_item);

    file_menu->addSeparator();

    file_menu->addAction(exit_item);

    /**********Edit menu**********/
    edit_menu = menuBar()->addMenu("Edit");

    edit_menu->addAction(undo_item);

    edit_menu->addSeparator();

    edit_menu->addAction(cut_item);
    edit_menu->addAction(copy_item);
    edit_menu->addAction(paste_item);
    edit_menu->addAction(delete_item);

    edit_menu->addSeparator();

    edit_menu->addAction(find_item);

    edit_menu->addSeparator();

    edit_menu->addAction(select_all_item);
    edit_menu->addAction(time_date_item);

    /**********Help menu**********/
    help_menu = menuBar()->addMenu("Help");
    help_menu->addAction(about_lutepad_item);
    help_menu->addAction(about_qt_item);
}



//SIGNALS
void LutepadMainWindow::new_file(){
    int save = user_save();
    if(save == 0)
        save_file();
    else if(save == 2)
        return;

    editor->clear();
    set_title("Untitled");
    statusBar()->showMessage("New file generated.", 2000);
}

void LutepadMainWindow::open_file(){
    if(user_save() == 1){ //if the user decides to open a file
        //store the file name from the file browser
        QString f_n = QFileDialog::getOpenFileName();
        if (!f_n.isEmpty()){
            QFile file(f_n);
            file.open(QIODevice::ReadOnly);
            QTextStream file_in(&file);

            //read in the file and add it to the editor
            editor->setPlainText(file_in.readAll());

            file.close();

            set_title(f_n);
        }

    }

}

void LutepadMainWindow::save_file(){
        //store the file name from the file browser
        QString f_n = QFileDialog::getSaveFileName();
        if (!f_n.isEmpty()){
            QFile file(f_n);
            file.open(QIODevice::WriteOnly);
            QTextStream file_out(&file);

            //output the file
            file_out << editor->toPlainText();

            file.close();

            statusBar()->showMessage("File saved.", 2000);
        }
}

void LutepadMainWindow::print(){
    //Instantiate printer
    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPrinter::Letter);
    printer.setOrientation(QPrinter::Portrait);

    printer.setOutputFormat(QPrinter::NativeFormat);

    //prompt the user
    QPrintDialog *dialog_window = new QPrintDialog(&printer, this);
    dialog_window->setWindowTitle("Print");
    dialog_window->show();
    if (dialog_window->exec() == QDialog::Accepted){
        //Print the page
        editor->print(&printer);
        statusBar()->showMessage("Printing...", 2000);
    }

    delete dialog_window;

}

void LutepadMainWindow::exit(){
    int save = user_save(); //get user_save value

    if(save == 0) //if user chooses to save
        save_file();
    else if(save == 2) //if user chooses to cancel
        return;

    close();

}

void LutepadMainWindow::undo(){
    //grab current widget
    QWidget * grabbed = QApplication::focusWidget();

    //press CTRL+Z
    QApplication::postEvent(grabbed, new QKeyEvent(QEvent::KeyPress, Qt::Key_Z, Qt::ControlModifier));

    //release CTRL+Z
    QApplication::postEvent(grabbed, new QKeyEvent(QEvent::KeyRelease, Qt::Key_Z, Qt::ControlModifier));

}

void LutepadMainWindow::cut(){
    //grab current widget
    QWidget * grabbed = QApplication::focusWidget();

    //press CTRL+X
    QApplication::postEvent(grabbed, new QKeyEvent(QEvent::KeyPress, Qt::Key_X, Qt::ControlModifier));

    //release CTRL+x
    QApplication::postEvent(grabbed, new QKeyEvent(QEvent::KeyRelease, Qt::Key_X, Qt::ControlModifier));
}

void LutepadMainWindow::copy(){
    //grab current widget
    QWidget * grabbed = QApplication::focusWidget();

    //press CTRL+C
    QApplication::postEvent(grabbed, new QKeyEvent(QEvent::KeyPress, Qt::Key_C, Qt::ControlModifier));

    //release CTRL+C
    QApplication::postEvent(grabbed, new QKeyEvent(QEvent::KeyRelease, Qt::Key_C, Qt::ControlModifier));

}

void LutepadMainWindow::paste(){
    //grab current widget
    QWidget * grabbed = QApplication::focusWidget();

    //press CTRL+V
    QApplication::postEvent(grabbed, new QKeyEvent(QEvent::KeyPress, Qt::Key_V, Qt::ControlModifier));

    //release CTRL+V
    QApplication::postEvent(grabbed, new QKeyEvent(QEvent::KeyRelease, Qt::Key_V, Qt::ControlModifier));

}

void LutepadMainWindow::delete_selection(){
    //grab current widget
    QWidget * grabbed = QApplication::focusWidget();

    //press DEL
    QApplication::postEvent(grabbed, new QKeyEvent(QEvent::KeyPress, Qt::Key_Delete, Qt::ControlModifier));

    //release DEL
    QApplication::postEvent(grabbed, new QKeyEvent(QEvent::KeyRelease, Qt::Key_Delete, Qt::ControlModifier));
}

void LutepadMainWindow::find(){
    //create find box
    QDialog * find_box = new QDialog;

    //set fixed size
    find_box->resize(400, 200);
    find_box->setMinimumSize(QSize(400, 200));
    find_box->setMaximumSize(QSize(400, 200));

    //set title
    find_box->setWindowTitle("Find");

    //Top panel
    QWidget * topPanel = new QWidget;
    QVBoxLayout * findLayout = new QVBoxLayout;
    topPanel->setLayout(findLayout);
    QLabel * finder_display = new QLabel("Find:");
    findLayout->addWidget(finder_display);
    QLineEdit * find_input = new QLineEdit;
    findLayout->addWidget(find_input);

    //Bottom Panel
    QWidget * bottomPanel = new QWidget;
    QHBoxLayout * buttonLayout = new QHBoxLayout;
    bottomPanel->setLayout(buttonLayout);
    QPushButton * findButton = new QPushButton("Find");
    buttonLayout->addWidget(findButton);

    //assemble the pieces
    QVBoxLayout * mainFindLayout = new QVBoxLayout;
    mainFindLayout->addWidget(topPanel);
    mainFindLayout->addWidget(bottomPanel);
    find_box->setLayout(mainFindLayout);

    //open the box
    find_box->open();

    //connect buttons
    QString arg = find_input->text();

    QSignalMapper * signal_mapper = new QSignalMapper(this);
    signal_mapper->setMapping(findButton, arg);

    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(find_next(QString)));
}

void LutepadMainWindow::find_next(QString arg){
    QTextCursor cursor;
        while(!editor->find(arg)){
        editor->moveCursor(cursor.NextBlock);
    }
    cursor.beginEditBlock();
}

void LutepadMainWindow::select_all(){
    //grab current widget
    QWidget * grabbed = QApplication::focusWidget();

    //press CTRL+A
    QApplication::postEvent(grabbed, new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::ControlModifier));

    //release CTRL+A
    QApplication::postEvent(grabbed, new QKeyEvent(QEvent::KeyRelease, Qt::Key_A, Qt::ControlModifier));
}

void LutepadMainWindow::time_date(){
    QDateTime date_time(QDateTime::currentDateTime());

    editor->appendPlainText(date_time.toString());
}

void LutepadMainWindow::about_lutepad(){
    aboutlutepad * ui = new aboutlutepad;
    ui->open();
}

void LutepadMainWindow::about_qt(){
    QMessageBox * about = new QMessageBox;
    about->aboutQt(this, "About Qt");
}

void LutepadMainWindow::resize(){
    if(width() > editor->width() || height() > editor->height()){
        editor->adjustSize();
    }
}

LutepadMainWindow::~LutepadMainWindow()
{
    delete ui;
}

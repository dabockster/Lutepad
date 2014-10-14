#include "aboutlutepad.h"
#include "ui_aboutlutepad.h"
#include <QDesktopServices>
#include <QUrl>

aboutlutepad::aboutlutepad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutlutepad)
{
    ui->setupUi(this);
}

aboutlutepad::~aboutlutepad()
{
    delete ui;
}

void aboutlutepad::on_info_3_linkActivated(const QString &link)
{
    QDesktopServices * services = new QDesktopServices();
    services->openUrl(QUrl(link));
}

void aboutlutepad::on_label_linkActivated(const QString &link)
{
    QDesktopServices * services = new QDesktopServices();
    services->openUrl(QUrl(link));
}

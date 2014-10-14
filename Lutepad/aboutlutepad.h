#ifndef ABOUTLUTEPAD_H
#define ABOUTLUTEPAD_H

#include <QDialog>

namespace Ui {
class aboutlutepad;
}

class aboutlutepad : public QDialog
{
    Q_OBJECT
    
public:
    explicit aboutlutepad(QWidget *parent = 0);
    ~aboutlutepad();
    
private slots:
    void on_info_3_linkActivated(const QString &link);
    void on_label_linkActivated(const QString &link);

private:
    Ui::aboutlutepad *ui;

};

#endif // ABOUTLUTEPAD_H

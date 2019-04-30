#ifndef GILLIGAN_H
#define GILLIGAN_H

#include <QMainWindow>

namespace Ui {
class Gilligan;
}

class Gilligan : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gilligan(QWidget *parent = 0);
    ~Gilligan();

private:
    Ui::Gilligan *ui;

public slots:
    void password_changed();
    void score_valid();
    void generate_password();
    void verify_password();
};




#endif // GILLIGAN_H

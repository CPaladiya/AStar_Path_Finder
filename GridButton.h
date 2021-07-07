#ifndef GRIDBUTTON_H
#define GRIDBUTTON_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <QTextStream>
#include <QPushButton>
#include <QThread>

//QTextStream out(stdout);

class GridButton : public QPushButton{
    
    Q_OBJECT

public:
    GridButton(QWidget *parent = nullptr);
    ~GridButton();

};

#endif
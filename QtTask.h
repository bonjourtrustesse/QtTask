#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtTask.h"

class QtTask : public QMainWindow
{
    Q_OBJECT

public:
    QtTask(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtTaskClass ui;
};

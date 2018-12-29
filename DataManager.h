#pragma once

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "AggregationXY.h"
#include "qcustomplot.h"

class DataManager : public QWidget
{
    Q_OBJECT

public:
    DataManager(QWidget *parent = nullptr);
    ~DataManager() = default;

    void initDataInput();                                       //!< Инициализация полей ввода данных
    void showCoorSystem();                                      //!< Инициализаця системы координат
    void addGraphs();                                           //!< Добавление графиков 

private slots:
    /*! Слот вызова переименования графика */
    void legendDoubleClicked(QCPLegend *legend, QCPAbstractLegendItem *item);

    /*! Слот вызова отображения координат графика */
    void showPointToolTip(QMouseEvent* event);

    /*! Слот вызова построения графиков */
    void plotGraphs();

    /*! Слот изменения значения шага интерполяции */
    void changeValue();

private:

    double interpolationStep_ = 0;         //!< Шаг интерполяции

    QLineEdit entryStep;                   //!< Поле ввода шага интерполяции
    QCustomPlot cPlot;                     //!< Виджет построения графиков
    QComboBox interpolationChoose;         //!< Выбор вида интерполяции
    QCPItemText *textItem;                 //!< Отображение координат на графике
    QLineEdit xStats;
    QLineEdit yStats;
    QLineEdit xNewStats;
    QLineEdit yNewStats;
};
#endif
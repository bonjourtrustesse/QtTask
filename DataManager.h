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

    void initDataInput();                                       //!< ������������� ����� ����� ������
    void showCoorSystem();                                      //!< ������������ ������� ���������
    void addGraphs();                                           //!< ���������� �������� 

private slots:
    /*! ���� ������ �������������� ������� */
    void legendDoubleClicked(QCPLegend *legend, QCPAbstractLegendItem *item);

    /*! ���� ������ ����������� ��������� ������� */
    void showPointToolTip(QMouseEvent* event);

    /*! ���� ������ ���������� �������� */
    void plotGraphs();

    /*! ���� ��������� �������� ���� ������������ */
    void changeValue();

private:

    double interpolationStep_ = 0;         //!< ��� ������������

    QLineEdit entryStep;                   //!< ���� ����� ���� ������������
    QCustomPlot cPlot;                     //!< ������ ���������� ��������
    QComboBox interpolationChoose;         //!< ����� ���� ������������
    QCPItemText *textItem;                 //!< ����������� ��������� �� �������
    QLineEdit xStats;
    QLineEdit yStats;
    QLineEdit xNewStats;
    QLineEdit yNewStats;
};
#endif
#pragma once

#ifndef AGGREGATIONXY_H
#define AGGREGATIONXY_H

#include <QObject>
#include <QVector>

struct Coordinates {                                                //!< ��������� �������� x � y

public: 
    QVector <double> x, y;
};

class AggregationXY : public QObject
{
    Q_OBJECT

public:
    AggregationXY(QObject *parent = nullptr);
    ~AggregationXY() = default;

    Coordinates parseXY();                                          //!< ���������� ��������� �� �����

    /*! ������ ����� �������� x � y � ������������� ��������
    * \param x ������ ����������� �������� X
    * \param y ������ ����������� �������� Y
    * \param step ��� ������������
    */
    Coordinates CalcNewLagranjData(QVector<double> x, QVector<double> y, double step);

    /*! ������ ����� �������� x � y ������ ������������� �������(������)
    * \param x ������ ����������� �������� X
    * \param y ������ ����������� �������� Y
    * \param step ��� ������������
    */
    Coordinates CalcNewNewtonData(QVector<double> x, QVector<double> y, double step);


    Coordinates CalcNewLinearData(QVector<double> x, QVector<double> y, double step);

private:
    /*! ������ �������� ������� � �����, ������������� ��������
    * \param x ������ �������� X
    * \param y ������ �������� Y
    * \param X �������� X ��� ������� ����� ��������� f(x)
    */
    double Lagranj(QVector<double> x, QVector<double> y, double X);

    /*! ������ �������� ������� � ����� ������ ������������� �������(������)
    * \param x ������ �������� X
    * \param y ������ �������� Y
    * \param X �������� X ��� ������� ����� ��������� f(x)
    */
    double Newton(QVector<double> x, QVector<double> y, double X);


    double Linear(QVector<double> x, QVector<double> y, double X);
};
#endif
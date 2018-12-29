#pragma once

#ifndef AGGREGATIONXY_H
#define AGGREGATIONXY_H

#include <QObject>
#include <QVector>

struct Coordinates {                                                //!< Структура значений x и y

public: 
    QVector <double> x, y;
};

class AggregationXY : public QObject
{
    Q_OBJECT

public:
    AggregationXY(QObject *parent = nullptr);
    ~AggregationXY() = default;

    Coordinates parseXY();                                          //!< Считывание координат из файла

    /*! Расчет новых значений x и y с интерполяцией лагранжа
    * \param x вектор изначальных значений X
    * \param y вектор изначальных значение Y
    * \param step шаг интерполяции
    */
    Coordinates CalcNewLagranjData(QVector<double> x, QVector<double> y, double step);

    /*! Расчет новых значений x и y первой интерполяцией Ньютона(вперед)
    * \param x вектор изначальных значений X
    * \param y вектор изначальных значение Y
    * \param step шаг интерполяции
    */
    Coordinates CalcNewNewtonData(QVector<double> x, QVector<double> y, double step);


    Coordinates CalcNewLinearData(QVector<double> x, QVector<double> y, double step);

private:
    /*! Расчет значения функции в точке, интерполяцией лагранжа
    * \param x вектор значений X
    * \param y вектор значение Y
    * \param X значение X при котором нужно вычислить f(x)
    */
    double Lagranj(QVector<double> x, QVector<double> y, double X);

    /*! Расчет значения функции в точке первой интерполяцией Ньютона(вперед)
    * \param x вектор значений X
    * \param y вектор значение Y
    * \param X значение X при котором нужно вычислить f(x)
    */
    double Newton(QVector<double> x, QVector<double> y, double X);


    double Linear(QVector<double> x, QVector<double> y, double X);
};
#endif
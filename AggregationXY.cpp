#include <fstream>

#include "AggregationXY.h"
#include "DataManager.h"

AggregationXY::AggregationXY(QObject *parent)
    : QObject(parent)
{
}

Coordinates AggregationXY::parseXY()
{
    Coordinates coords;
    QMap<double, double> points;  
    std::ifstream f("points.txt");
    double x_i, y_i;
    while (true) {
        f >> x_i >> y_i;
        coords.x.push_back(x_i);
        coords.y.push_back(y_i);
        if (f.eof())
            break;
    }
    return coords;
}

double AggregationXY::Lagranj(QVector<double> x, QVector<double> y, double X)
{
    if (x.size() != y.size())
        return 0;

    const int n = x.size();

    double result = 0;

    for (size_t i = 0; i < n; ++i)
    {
        double l = 1;

        for (size_t j = 0; j < n; ++j)
            if (i != j)
                l *= (X - x[j]) / (x[i] - x[j]);

        result += y[i] * l;
    }

    return result;
}

double AggregationXY::Newton(QVector<double> x, QVector<double> y, double X)
{   
    if (x.size() != y.size())
        return 0;

    const int n = x.size();

    double result = y[0], F, m;
    for (size_t i = 1; i < n; i++) {
        F = 0;
        for (size_t j = 0; j <= i; j++) {//следующее слагаемое полинома
            m = 1;
            //считаем знаменатель разделенной разности
            for (size_t k = 0; k <= i; k++) {
                if (k != j)
                    m *= (x[j] - x[k]);
            }
            //считаем разделенную разность
            F += y[j] / m;
        }
        //домножаем разделенную разность на скобки (x-x[0])...(x-x[i-1])
        for (size_t k = 0; k < i; k++)
            F *= (X - x[k]);
        result += F;//полином
    }
    return result;
}

double AggregationXY::Linear(QVector<double> x, QVector<double> y, double X)
{
    if (x.size() != y.size())
        return 0;

    const int n = x.size();

    ////static QVector<double> k = { (y[1] - y[0]) / (x[1] - x[0]),
    ////                        (y[2] - y[1]) / (x[2] - x[1]),
    ////                        (y[3] - y[2]) / (x[3] - x[2]) };
    ////static QVector<double> b = { y[0] - k[0] * x[0],
    ////                        y[1] - k[1] * x[1],
    ////                        y[2] - k[2] * x[2] };


    //for (size_t i = 0; i < n - 1; ++i)
    //    if (X == x[i]){
    //        return y[i];
    //    }
    //    //else{
    //    //    if (X >= x[i] && X <= x[i + 1])
    //    //        return k[i] * X + b[i];
    //    //}

    return 0.0;
}

Coordinates AggregationXY::CalcNewLagranjData(QVector<double> X, QVector<double> Y, double step)
{
    const auto startPoints = parseXY();
    
    Coordinates newPoints;

    const auto first = X[0];
    const auto last = X[X.size() - 1];

    for (double i = first; i <= last;) {
        newPoints.x.push_back(i);
        i += step;
    }

    for (const auto i : X){
        //if(!std::find(newPoints.x.begin(), newPoints.x.end(), i))
            newPoints.x.push_back(i);
    }
   
   std::sort(newPoints.x.begin(), newPoints.x.end());


    for (auto i : newPoints.x)
        newPoints.y.push_back(Lagranj(X, Y, i));

    return newPoints;
}

Coordinates AggregationXY::CalcNewNewtonData(QVector<double> X, QVector<double> Y, double step)
{
    const auto startPoints = parseXY();

    Coordinates newPoints;

    const auto first = X[0];
    const auto last = X[X.size() - 1];

    for (double i = first; i <= last;) {
        newPoints.x.push_back(i);
        i += step;
    }

    for (auto i : X) {
        //if (!std::find(newPoints.x.begin(), newPoints.x.end(), i))
            newPoints.x.push_back(i);
    }

    std::sort(newPoints.x.begin(), newPoints.x.end());


    for (auto i : newPoints.x)
        newPoints.y.push_back(Newton(X, Y, i));

    return newPoints;
}

Coordinates AggregationXY::CalcNewLinearData(QVector<double> X, QVector<double> Y, double step)
{
    const auto startPoints = parseXY();

    Coordinates newPoints;

    const auto first = X[0];
    const auto last = X[X.size() - 1];

    for (double i = first; i <= last;) {
        newPoints.x.push_back(i);
        i += step;
    }

    for (auto i : X) {
        //if (!std::find(newPoints.x.begin(), newPoints.x.end(), i))
        newPoints.x.push_back(i);
    }

    std::sort(newPoints.x.begin(), newPoints.x.end());


    for (auto i : newPoints.x)
        newPoints.y.push_back(Linear(X, Y, i));

    return newPoints;
}

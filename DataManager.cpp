#include "DataManager.h"
#include "qcustomplot.h"

DataManager::DataManager(QWidget *parent)
    : QWidget(parent)
{
    initDataInput();
    showCoorSystem();
    textItem = new QCPItemText(&cPlot);

    connect(&cPlot, &QCustomPlot::mouseMove, this, &DataManager::showPointToolTip);
    connect(&entryStep, &QLineEdit::textChanged, this, &DataManager::changeValue);
}

void DataManager::initDataInput()
{
    auto mainLayout = new QGridLayout;

    interpolationChoose.addItem("Lagranj");
    interpolationChoose.addItem("Newton");
    interpolationChoose.addItem("Linear");

    auto exitBtn = new QPushButton("&Exit");
    connect(exitBtn, SIGNAL(clicked()), qApp, SLOT(quit()));

    auto startBtn = new QPushButton("&Plot the graph");
    startBtn->setFixedSize(100, 25); 
    connect(startBtn, SIGNAL(clicked()), this, SLOT(plotGraphs()));

    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);
    auto validator = new QDoubleValidator;
    validator->setLocale(locale);
    entryStep.setValidator(validator);

    xStats.setReadOnly(true);
    yStats.setReadOnly(true);
    xNewStats.setReadOnly(true);
    yNewStats.setReadOnly(true);

    auto graphLayout = new QHBoxLayout;
    graphLayout->addWidget(&cPlot);

    setLayout(mainLayout);

    mainLayout->addWidget(new QLabel("Choose interpolation: "), 0, 0);
    mainLayout->addWidget(&interpolationChoose, 0, 1);
    mainLayout->addWidget(new QLabel("Interpolation step:"), 1, 0);
    mainLayout->addWidget(&entryStep, 1, 1);
    mainLayout->addWidget(new QLabel("X coordinates:"), 3, 0);
    mainLayout->addWidget(&xStats, 3, 1);
    mainLayout->addWidget(new QLabel("New X coordinates:"), 3, 2);
    mainLayout->addWidget(&xNewStats, 3, 3);
    mainLayout->addWidget(new QLabel("Y coordinates:"), 4, 0);
    mainLayout->addWidget(&yStats, 4, 1);
    mainLayout->addWidget(new QLabel("New Y coordinates:"), 4, 2);
    mainLayout->addWidget(&yNewStats, 4, 3);
    mainLayout->addWidget(startBtn, 5, 1);
    mainLayout->addLayout(graphLayout, 6, 0, 4, 4);
    mainLayout->addWidget(exitBtn, 11, 6);
    mainLayout->columnStretch(1);
}

void DataManager::showCoorSystem()
{
    addGraphs();

    cPlot.xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    cPlot.yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    cPlot.xAxis->setLabel("x Axis");
    cPlot.yAxis->setLabel("y Axis");

    cPlot.xAxis->setRange(-3, 3);
    cPlot.yAxis->setRange(-3, 3);

    cPlot.replot();
    cPlot.setWindowTitle("QCustomPlot");
    cPlot.resize(400, 400);
    cPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                          QCP::iSelectPlottables | QCP::iSelectAxes |
                          QCP::iSelectLegend);


    cPlot.legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    cPlot.legend->setFont(legendFont);
    cPlot.legend->setSelectedFont(legendFont);
    cPlot.legend->setSelectableParts(QCPLegend::spItems);
    connect(&cPlot, SIGNAL(legendDoubleClick(QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)),
        this, SLOT(legendDoubleClicked(QCPLegend*, QCPAbstractLegendItem*)));
}

void DataManager::addGraphs()
{
    cPlot.addGraph();
    cPlot.graph(0)->setPen(QPen(Qt::red));
    cPlot.graph(0)->rescaleAxes();
    cPlot.graph(0)->setName("New Graph");

    QCPScatterStyle myScatter;
    myScatter.setShape(QCPScatterStyle::ssCircle);
    myScatter.setPen(QPen(Qt::black, 1.5));
    myScatter.setBrush(Qt::white);
    cPlot.graph(0)->setScatterStyle(myScatter);

    cPlot.addGraph();
    cPlot.graph(1)->setPen(QPen(Qt::black));
    cPlot.graph(1)->rescaleAxes();
    cPlot.graph(1)->setName("Original graph");
}

void DataManager::showPointToolTip(QMouseEvent * event)
{
    double x = cPlot.xAxis->pixelToCoord(event->pos().x());
    double y = cPlot.yAxis->pixelToCoord(event->pos().y());
    textItem->setText(QString("(%1, %2)").arg(x).arg(y));
    textItem->position->setCoords(QPointF(x, y));
    textItem->setFont(QFont(font().family(), 10));
    cPlot.replot();
}

void DataManager::changeValue()
{
    auto newValue = entryStep.text().toDouble();
    interpolationStep_ = newValue;
}

void DataManager::plotGraphs()
{
    AggregationXY aggr;
    auto points = aggr.parseXY();

    if (interpolationChoose.currentIndex() == 0){
        if (interpolationStep_ == NULL){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("You didnt input interpolation step, do it!");
            msgBox.exec();
            return;
        }
    auto newPoints = aggr.CalcNewLagranjData(points.x, points.y, interpolationStep_);
    cPlot.graph(0)->setData(newPoints.x, newPoints.y);
    cPlot.graph(1)->setData(points.x, points.y);
    cPlot.replot();

    xStats.clear();
    yStats.clear();
    xNewStats.clear();
    yNewStats.clear();
    for (auto i : points.y) {
        yStats.insert(QString::number(i));
        yStats.insert("\t");
    }
    for (auto i : points.x) {
        xStats.insert(QString::number(i));
        xStats.insert("\t");
    }
    for (auto i : newPoints.y) {
        yNewStats.insert(QString::number(i));
        yNewStats.insert("\t");
    }
    for (auto i : newPoints.x) {
        xNewStats.insert(QString::number(i));
        xNewStats.insert("\t");
    }

    }

    if (interpolationChoose.currentIndex() == 1) {
        if (interpolationStep_ == NULL){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("You didnt input interpolation step, do it!");
            msgBox.exec();
            return;
        }
        auto newPoints = aggr.CalcNewNewtonData(points.x, points.y, interpolationStep_);
        cPlot.graph(0)->setData(newPoints.x, newPoints.y);
        cPlot.graph(1)->setData(points.x, points.y);
        cPlot.replot();
    }

    if (interpolationChoose.currentIndex() == 2) {
        if (interpolationStep_ == NULL) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("You didnt input interpolation step, do it!");
            msgBox.exec();
            return;
        }
        auto newPoints = aggr.CalcNewLinearData(points.x, points.y, interpolationStep_);
        cPlot.graph(0)->setData(newPoints.x, newPoints.y);
        cPlot.graph(1)->setData(points.x, points.y);
        cPlot.replot();

        xStats.clear();
        yStats.clear();
        xNewStats.clear();
        yNewStats.clear();
        for (auto i : points.y) {
            yStats.insert(QString::number(i));
            yStats.insert("\t");
        }
        for (auto i : points.x) {
            xStats.insert(QString::number(i));
            xStats.insert("\t");
        }
        for (auto i : newPoints.y) {
            yNewStats.insert(QString::number(i));
            yNewStats.insert("\t");
        }
        for (auto i : newPoints.x) {
            xNewStats.insert(QString::number(i));
            xNewStats.insert("\t");
        }
    }
}

void DataManager::legendDoubleClicked(QCPLegend * legend, QCPAbstractLegendItem * item)
{
    if (item)
    {
        QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
        bool ok;
        QString newName = QInputDialog::getText(this, "Change graph name", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
        if (ok)
        {
            plItem->plottable()->setName(newName);
            cPlot.replot();
        }
    }
}
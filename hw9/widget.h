#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QGraphicsWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QChart>
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE
#include <string>
#include <fstream>
#include <QString>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void showFileDialog();
    void drawGraph();
    void invalidStartEnd();
    void fileUnopenedError();
    void plot(int i,int j);
    void fileFormatError();

private:
    Ui::Widget *ui;
    QPushButton *button;
    QPushButton *button2;
    QComboBox *box1;
    QComboBox *box2;
    QLabel *label1;
    QLabel *label2;
    QChart *chart;
    QChartView *view;
    QLineSeries *series;
    vector<int> demands;
};
#endif // WIDGET_H

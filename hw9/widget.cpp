#include "widget.h"
#include "ui_widget.h"

#define N_HR 24
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("hw9");
    button=new QPushButton(this);
    button->setText("Select files");
    box1=new QComboBox(this);
    box1->setEditText("Start");
    box1->setGeometry(0,button->height(),box1->width(),box1->height());
    box2=new QComboBox(this);
    box2->setEditText("End");
    box2->setGeometry(0,box1->y()+box1->height(),box2->width(),box2->height());
    for(int i=0;i<N_HR;i++) {
        box1->addItem(QString::number(i));
        box2->addItem(QString::number(i));
    }
    label1=new QLabel(this);
    label2=new QLabel(this);
    label1->setGeometry(box1->x()+box1->width(),box1->y(),label1->width(),label1->height());
    label2->setGeometry(box2->x()+box2->width(),box2->y(),label2->width(),label2->height());
    label1->setText("Start");
    label2->setText("End");

    button2=new QPushButton(this);
    button2->setGeometry(0,box2->y()+box2->height(),button2->width(),button2->height());
    button2->setText("Draw graph");

    connect(button,&QPushButton::clicked,this,&Widget::showFileDialog);
    connect(button2,&QPushButton::clicked,this,&Widget::drawGraph);

    chart=NULL;
    view=NULL;
}

void Widget::showFileDialog(){
    QString filename=QFileDialog::getOpenFileName();
    if(!filename.isEmpty()&&!filename.endsWith("csv",Qt::CaseInsensitive)) {fileFormatError();return;}
    ifstream file;
    int hour,demand;
    char comma;
    string s;
    stringstream ss;
    file.open(filename.toStdString());
    getline(file,s,'\n');
    while(getline(file,s,'\n')){
        ss.str(s);
        ss>>hour>>comma>>demand;
        demands.push_back(demand);
        ss.clear();
    }
}

void Widget::invalidStartEnd(){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Error when drawing graph");
    msgBox.setInformativeText("Start month should be smaller than end month!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void Widget::fileUnopenedError(){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("Error when opening file");
    msgBox.setInformativeText("File is not opened!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void Widget::fileFormatError(){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("Error when opening file");
    msgBox.setInformativeText("File format is wrong!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void Widget::drawGraph(){
    int i=box1->currentIndex();
    int j=box2->currentIndex();
    if(i>j) {invalidStartEnd();return;}
    else plot(i,j);
}

void Widget::plot(int i,int j){
    //cout<<"Draw!"<<endl;
    if(demands.empty()) {fileUnopenedError();return;}
    if(!chart){
        chart=new QChart;
        series=new QLineSeries;

        int max=0;

        for(int k=i;k<=j;k++) {
            series->append(k,demands[k]);
            if(demands[k]>max) max=demands[k];
        }


        chart->addSeries(series);
        QValueAxis *x=new QValueAxis;
        x->setRange(i,j);
        x->setTickCount(j-i+1);
        x->setLabelFormat("%d");
        QValueAxis *y=new QValueAxis;
        y->setRange(0,(max/100)*100+1000);
        y->setLabelFormat("%d");
        y->setTickCount(((max/100)*100+1000)/1000);
        chart->setAxisX(x,series);
        chart->setAxisY(y,series);

        view=new QChartView(this);
        view->setGeometry(0,button2->y()+button2->height(),800,400);
        view->setChart(chart);
        view->show();
    }else{
        delete chart;
        view->close();
        delete view;
        view=new QChartView(this);
        chart=new QChart;
        series=new QLineSeries;
        int max=0;

        for(int k=i;k<=j;k++) {
            series->append(k,demands[k]);
            if(demands[k]>max) max=demands[k];
        }
        chart->addSeries(series);

        QValueAxis *x=new QValueAxis;
        x->setRange(i,j);
        x->setTickCount(j-i+1);
        x->setLabelFormat("%d");
        QValueAxis *y=new QValueAxis;
        y->setRange(0,(max/100)*100+1000);
        y->setLabelFormat("%d");
        y->setTickCount(((max/100)*100+1000)/1000);
        chart->setAxisX(x,series);
        chart->setAxisY(y,series);

        view->setGeometry(0,button2->y()+button2->height(),800,400);
        view->setChart(chart);
        view->show();

    }
}

Widget::~Widget()
{
    delete ui;
}


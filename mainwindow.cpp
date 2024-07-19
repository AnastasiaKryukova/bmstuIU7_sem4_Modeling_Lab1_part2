#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{

    QString a = ui->lineEdit->text();
    QString b = ui->lineEdit_2->text();
    double aa = a.toDouble();
    double bb = b.toDouble();

    QString SKO = ui->lineEdit_3->text();
    QString sigma = ui->lineEdit_4->text();
    double sko = SKO.toDouble();
    double math_exp = sigma.toDouble();



//    double math_exp = 0;
//    double sko = 1;
    double pi = 3.14;
    double e = 2.718;
    //double a = -5; //Начало интервала, где рисуем график по оси Ox
    //double b =  5; //Конец интервала, где рисуем график по оси Ox
    double h = 0.01; //Шаг, с которым будем пробегать по оси Ox
    int N = (bb - aa) / h + 2; //Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N), y(N); //Массивы координат точек
    QVector<double> xx(N), yy(N); //Массивы координат точек

    //Вычисляем наши данные
    int i=0;
    //Пробегаем по всем точкам
    for (double X = aa; X <= bb; X += h)
    {
      x[i] = X;
      y[i] = (1/(sko*pow((2*pi), 0.5))) * pow(e,-(pow((X - math_exp), 2)/(2*pow(sko, 2))));;//Формула нашей функции
      i++;
    }

    ui->widget->clearGraphs();//Если нужно, но очищаем все графики

    //Добавляем один график в widget
    ui->widget->addGraph();

    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);

    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("f(x)");

    //Установим область, которая будет показываться на графике
    ui->widget->xAxis->setRange(aa, bb);//Для оси Ox

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    double minY = y[0], maxY = y[0];

    for (int i = 1; i < N; i++)
    {
      if (y[i] < minY) minY = y[i];
      if (y[i] > maxY) maxY = y[i];
    }

    ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

    //И перерисуем график на нашем widget
    ui->widget->replot();

    int j = 0;
//    for (double X = a; X <= b; X += h)
//    {
//      xx[j] = X;
//      yy[j] = (1/(sko*pow((2*pi), 0.5))) * ((pow(e,-(pow((xx[j+1] - math_exp), 2)/(2*pow(sko, 2)))))-(pow(e,-(pow((xx[j] - math_exp), 2)/(2*pow(sko, 2))))));
//      j++;
//      xx.push_back(xx[j]);
//    }

    for (double X = aa; X <= bb; X += h)
    {
      xx[j] = X;
      yy[j] = 0.5 + 0.5*erf((xx[j]-math_exp)/(sko*pow(2,0.5)));
      //yy[j] = 0.5 + 0.5*erf(xx[j]/pow(2,0.5));
      j++;
    }



    ui->widget_2->addGraph();
    ui->widget_2->graph(0)->setData(xx,yy);
    ui->widget_2->xAxis->setLabel("x");
    ui->widget_2->yAxis->setLabel("F(x)");

    ui->widget_2->xAxis->setRange(aa, bb);//Для оси Ox


    double minYY = yy[0], maxYY = yy[0];

    for (int j = 1; j < N; j++)
    {
      if (yy[j] < minYY) minYY = yy[j];
      if (yy[j] > maxYY) maxYY = yy[j];
    }

    ui->widget_2->yAxis->setRange(minYY, maxYY);//Для оси Oy


    ui->widget_2->replot();


}





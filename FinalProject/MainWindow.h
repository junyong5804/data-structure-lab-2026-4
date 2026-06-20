#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMap>
#include <QVector>
#include <QPoint>

struct Flight
{
    QString destination;
    int distance;
    QString price;
    QString time;
};

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = nullptr);

private:

    QLabel *mapLabel;
    QLabel *lineLabel;
    QLabel *infoLabel;

    QString startAirport;
    QString endAirport;

    bool selectingStart;

    QMap<QString,QVector<Flight>> graph;
    QMap<QString,QPoint> airportPos;

    QPoint lineStart;
    QPoint lineEnd;

    void createAirportButton(
        QWidget *parent,
        QString airport,
        int x,
        int y
    );

    void searchFlight();

    void drawRoute();
};

#endif






1
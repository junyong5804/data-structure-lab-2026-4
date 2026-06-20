#include "MainWindow.h"

#include <QPushButton>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1200,800);

    selectingStart = true;

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    //--------------------------------
    // 지도
    //--------------------------------

    mapLabel = new QLabel(central);

    mapLabel->setPixmap(
        QPixmap("korea_airports.jpg")
            .scaled(
                700,
                700,
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
            )
    );

    mapLabel->setGeometry(
        20,20,700,700
    );

    //--------------------------------
    // 노선 레이어
    //--------------------------------

    lineLabel = new QLabel(central);

    lineLabel->setGeometry(
        20,20,700,700
    );

    lineLabel->setAttribute(
        Qt::WA_TransparentForMouseEvents
    );

    //--------------------------------
    // 공항 좌표
    //--------------------------------

    airportPos["김포"] = QPoint(210,150);
    airportPos["광주"] = QPoint(220,430);
    airportPos["여수"] = QPoint(320,490);
    airportPos["포항"] = QPoint(500,290);
    airportPos["부산"] = QPoint(460,430);
    airportPos["제주"] = QPoint(250,600);

    //--------------------------------
    // 그래프
    //--------------------------------

    graph["김포"] =
    {
        {"제주",450,"79,000원","1시간 10분"},
        {"부산",325,"89,000원","1시간"},
        {"광주",270,"89,000원","55분"},
        {"여수",320,"99,000원","55분"},
        {"포항",280,"109,000원","1시간"}
    };

    graph["부산"] =
    {
        {"제주",290,"69,000원","1시간"}
    };

    graph["광주"] =
    {
        {"제주",180,"79,000원","1시간"}
    };

    graph["여수"] =
    {
        {"제주",190,"89,000원","1시간"}
    };

    graph["포항"] =
    {
        {"제주",330,"119,000원","1시간"}
    };

    //--------------------------------
    // 정보창
    //--------------------------------

    infoLabel = new QLabel(central);

    infoLabel->setGeometry(
        760,100,330,350
    );

    infoLabel->setWordWrap(true);

    infoLabel->setStyleSheet(
        "background:#1565c0;"
        "color:white;"
        "font-size:16px;"
        "padding:15px;"
        "border-radius:10px;"
    );

    infoLabel->setText(
        "출발 공항을 선택하세요."
    );

    //--------------------------------
    // 공항 버튼
    //--------------------------------

    createAirportButton(
        central,"김포",210,150);

    createAirportButton(
        central,"광주",220,430);

    createAirportButton(
        central,"여수",320,490);

    createAirportButton(
        central,"포항",500,290);

    createAirportButton(
        central,"부산",460,430);

    createAirportButton(
        central,"제주",250,600);

    //--------------------------------
    // 예매 버튼
    //--------------------------------

    QPushButton *reserveBtn =
        new QPushButton(
            "예매하기",
            central
        );

    reserveBtn->setGeometry(
        800,500,130,50
    );

    connect(
        reserveBtn,
        &QPushButton::clicked,
        this,
        [=]()
        {
            if(startAirport.isEmpty()
               || endAirport.isEmpty())
            {
                QMessageBox::warning(
                    this,
                    "오류",
                    "노선을 선택하세요."
                );
                return;
            }

            QMessageBox::information(
                this,
                "예매 완료",
                startAirport +
                " → " +
                endAirport +
                "\n예매가 완료되었습니다."
            );
        }
    );

    //--------------------------------
    // 출발지 변경
    //--------------------------------

    QPushButton *changeStartBtn =
        new QPushButton(
            "출발지 변경",
            central
        );

    changeStartBtn->setGeometry(
        950,500,130,50
    );

    connect(
        changeStartBtn,
        &QPushButton::clicked,
        this,
        [=]()
        {
            selectingStart = true;

            startAirport.clear();
            endAirport.clear();

            infoLabel->setText(
                "새 출발지를 선택하세요."
            );

            QPixmap clear(700,700);
            clear.fill(Qt::transparent);

            lineLabel->setPixmap(clear);
        }
    );
}

void MainWindow::createAirportButton(
    QWidget *parent,
    QString airport,
    int x,
    int y
)
{
    QPushButton *btn =
        new QPushButton(parent);

    btn->setGeometry(
        x - 60,
        y - 60,
        160,
        160
    );

    btn->setStyleSheet(
        "background:transparent;"
        "border:none;"
    );

    connect(
        btn,
        &QPushButton::clicked,
        this,
        [=]()
        {
            // 출발지 선택

            if(selectingStart)
            {
                startAirport = airport;

                selectingStart = false;

                infoLabel->setText(
                    "출발지 : "
                    + startAirport +
                    "\n\n도착지를 선택하세요."
                );

                return;
            }

            // 같은 공항 클릭 무시

            if(startAirport == airport)
                return;

            // 도착지 계속 변경 가능

            endAirport = airport;

            searchFlight();
        }
    );
}

void MainWindow::searchFlight()
{
    for(const Flight &f
        : graph[startAirport])
    {
        if(f.destination == endAirport)
        {
            lineStart =
                airportPos[startAirport];

            lineEnd =
                airportPos[endAirport];

            drawRoute();

            infoLabel->setText(
                "출발 : "
                + startAirport +

                "\n도착 : "
                + endAirport +

                "\n\n거리 : "
                + QString::number(
                    f.distance
                )
                + " km"

                "\n가격 : "
                + f.price +

                "\n비행시간 : "
                + f.time
            );

            return;
        }
    }

    infoLabel->setText(
        "해당 노선이 없습니다."
    );
}

void MainWindow::drawRoute()
{
    QPixmap pix(700,700);

    pix.fill(
        Qt::transparent
    );

    QPainter painter(
        &pix
    );

    painter.setRenderHint(
        QPainter::Antialiasing
    );

    // 파란색 얇은 노선

    painter.setPen(
        QPen(
            QColor(0,120,255),
            2
        )
    );

    painter.drawLine(
        lineStart,
        lineEnd
    );

    lineLabel->setPixmap(
        pix
    );

    lineLabel->raise();
}

1
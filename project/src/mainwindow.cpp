#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include<QDebug>
#include <QString>
#include<QFileDialog>
#include<QtCore>
#include <QTextEdit>
#include <QDateTime>
#include <QtSql>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include "QDir"
#include <QtPlugin>
#include <QSqlDriver>

#define __DEBUGGER__


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEditFirstName->setText("Name");
    ui->lineEditLastName->setText("LastName");
    ui->lineEditPhone->setText("15--");
    ui->lineEditAddress->setText("Av. ________  N ____ Dto:_");
    ui->lineEditemail->setText("@gmail.com");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

int *year=new int ;
int *mon=new int ;
int *day=new int ;
int *hour=new int ;
int *min=new int ;
int *sec=new int ;
int *mide=new int ;

int *lengthMax=new int;
*lengthMax=560;

char namePDF[120];
char dateTime[40],stringText[40];

QDateTime UTC(QDateTime::currentDateTimeUtc());
QDateTime local(UTC.toLocalTime());

QByteArray captureFisrtName=ui->lineEditFirstName->text().toLatin1();
QByteArray captureLastName=ui->lineEditLastName->text().toLatin1();
QByteArray capturePhone=ui->lineEditPhone->text().toLatin1();
QByteArray captureFisrtAddress=ui->lineEditAddress->text().toLatin1();
QByteArray captureFisrtEmail=ui->lineEditemail->text().toLatin1();

QLineF line(0, 120, 600, 120);

QPrinter printer;
QPainter painter;

    time_t  time=UTC.toTime_t();
    time=time-10800;
    *year=(UTC.toTime_t()/31556926);

    printer.setOutputFormat(QPrinter::PdfFormat);

    *sec=time%60;

    *min=(time/60)%60;
    //qDebug() <<"min"<<min;

    *hour=(time/3600)%24;
    //qDebug() <<"hour"<<hour;

    *day=(time/(3600*24))%31;
  //  qDebug() <<"day"<<day;

    *mon=(((time-(time/31556926)))/2629743%12)+1;

  //  qDebug() <<"month"<<mon;

    sprintf(namePDF,"/Users/leonardoamaya/Documents/QtProjects/QtPdf/Presupuesto%d-%02d-%02d %02d %02d %02d.pdf",(*year+1970),*mon,*day,*hour,*min,*sec);
//     sprintf(namePDF,"/Users/leonardoamaya/QtProjects/QtPdf/Pres.pdf");

    sprintf(dateTime,"%2d / %2d / %4d",*day,*mon,(*year+1970));
    printer.setOutputFileName(namePDF);

    delete year;
    delete mon;
    delete day;
    delete hour;
    delete min;
    delete sec;

    if (! painter.begin(&printer)) { // failed to open file
        qWarning("failed to open file, is it writable?");          
        return ;
    }


    painter.setPen(Qt::gray);

    painter.setFont(QFont("Helvetica", 6, QFont::Bold));

    strcpy(stringText,"X");
    *mide=(*lengthMax-(strlen(stringText)))/2;
    painter.drawText(*mide, 10,stringText);

    strcpy(stringText,"Documento");
*mide=(*lengthMax-(strlen(stringText)))/2;
    painter.drawText(*mide, 20,stringText);

    strcpy(stringText,"no Valido");
*mide=(*lengthMax-(strlen(stringText)))/2;
    painter.drawText(*mide, 30,stringText);

    strcpy(stringText,"como factura");
*mide=(*lengthMax-(strlen(stringText)))/2;
    painter.drawText(*mide, 40,stringText);


//Titles

painter.setFont(QFont("Helvetica", 11, QFont::Bold));
painter.drawText( 450, 70,dateTime);

    *mide=(*lengthMax-(strlen("Presupuesto"))*8)/2;
    painter.drawText(*mide, 200, "Presupuesto");

   *mide=(*lengthMax-(strlen("Lio Design")*8))/2;
    painter.drawText(*mide, 240, "Lio Design");

    delete mide;


//Data Clients

painter.setFont(QFont("Helvetica", 11, QFont::Normal));

    painter.drawText(20, 80, "Nombre:");
    painter.drawText(20, 100, "Apellido:");
    painter.drawText(20, 120, "Telefono:");
    painter.drawText(20, 140, "Direccion:");
    painter.drawText(20, 160, "e-mail:");

painter.setFont(QFont("Helvetica", 11, QFont::Bold));
    painter.drawText(100, 80,captureFisrtName );
    painter.drawText(100, 100, captureLastName);
    painter.drawText(100, 120, capturePhone);
    painter.drawText(100, 140, captureFisrtAddress);
    painter.drawText(100, 160, captureFisrtEmail);

//Lines

    line.setLine(0,45,*lengthMax,45);
    painter.drawLine(line);

    line.setLine(0,250,*lengthMax,250);
    painter.drawLine(line);

    line.setLine(0,750,*lengthMax,750);
    painter.drawLine(line);

    //Config Puff

    painter.setPen(Qt::black);
    painter.setFont(QFont("Helvetica", 11, QFont::Normal));



    if(ui->checkBoxPuff1->isChecked()){
    painter.drawText(100, 400, "*   Puff 1   x unidad $ ");
    }

    if(ui->checkBoxPuff2->isChecked()){
    painter.drawText(100, 450, "*   Puff 2   x unidad $ ");
    }

    if(ui->checkBoxPuff3->isChecked()){
    painter.drawText(100, 500, "*   Puff 3   x unidad $ ");
    }

  if(ui->checkBoxSofa1->isChecked()){
    painter.drawText(100, 650, "*   Sofa 1  x unidad $ ");
    }

    delete lengthMax;
    painter.end();
}




void MainWindow::funcion(int value){

    QPluginLoader loader("/usr/local/lib/libqsqlmysql.dylib");
    loader.load();
    qDebug() << loader.errorString();

    qDebug() << "drivers: "<< QSqlDatabase::drivers();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("12345");
    db.setDatabaseName("ClientDatabase");

            QSqlQuery query( "select * from People" );

    switch (value) {

    case 1:
#ifdef __DEBUGGER__

        qDebug()  <<"Crear pdf"<<value;

#endif
        //MainWindow::on_pushButton_clicked();
        break;

    case 2:
        #if defined(__DEBUGGER__)
            qDebug()  <<"Crear base de datos"<<value;
        #endif
        if(db.open())  {
            //--- we're good! ---
            qDebug()  << "Database open\n";

            //--- run a query and print data returned ---


            query.exec( "CREATE TABLE IF NOT EXISTS People(id INTEGER UNIQUE PRIMARY KEY, FirstName VARCHAR(31), lastName VARCHAR(31),phone INT,address VARCHAR(31),mail VARCHAR(31))" );

             if(query.exec())
             {
                int b=0;
                qDebug()  <<"Table created";
                b=  query.exec( "LOAD DATA LOCAL INFILE '/Users/leonardoamaya/Documents/sourcecpp/database/agenda_database.csv' INTO TABLE clientdatabase.people FIELDS TERMINATED BY ';' lines terminated by '\r'");
#if defined(__DEBUGGER__)
                qDebug()  <<"Value B:" <<b;
#endif
             }

             if ( !query.isActive() )
                qDebug() <<"Step One" << "Query Error" + query.lastError().text();

            else while (query.next()) {
                    int Id = query.value(0).toInt();
                    QString word = query.value(1).toString();
                    qDebug()  <<"Step Duo" << QString( "%1\t%2\n").arg(Id).arg( word );
                    }

            query.exec();

            db.close();
        }
        else
        {
            //ui->textBox->append(db.lastError().text());
           // qDebug()  <<append(db.lastError().text());
             qDebug()  <<db.lastError().text();
        }
        break;

    case 3:
             qDebug()  <<"Add user"<<value;
        break;

    case 4 :
             qDebug()  <<"clear table People";
            query.prepare( "TRUNCATE people" );
            break;

    default:
        break;
    }
}


void MainWindow::on_pushButtonCreateDataBase_clicked()
{
MainWindow::funcion(1);
}


void MainWindow::on_pushButtonAddUser_clicked()
{
    MainWindow::funcion(2);
}

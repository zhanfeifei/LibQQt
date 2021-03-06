#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qqtsvgwidget.h"
#include "qqtsvgpushbutton.h"
#include "qqt-qt.h"
#include <QObject>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    //QString svg = QString ( "/Users/abel/Develop/b0-toolskits/macLibraries/Qt/Examples/Qt-5.9.2/svg/svgviewer/files/bubbles.svg" );
    QString svg = QString ( "/Users/abel/Downloads/2916415846_lanrentuku.com/aa.svg" );
    ui->w->setSvgFile ( svg );

    ui->b0->iconTable() [BTN_NORMAL] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir.svg";
    ui->b0->iconTable() [BTN_HOVER] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir.svg";
    ui->b0->iconTable() [BTN_PRESS] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir_press.svg";
    ui->b0->renderToVariable();

    ui->c0->iconTable() [BTN_NORMAL] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir.svg";
    ui->c0->iconTable() [BTN_HOVER] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir.svg";
    ui->c0->iconTable() [BTN_PRESS] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir_press.svg";
    ui->c0->renderToVariable();
    ui->r0->iconTable() [BTN_NORMAL] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir.svg";
    ui->r0->iconTable() [BTN_HOVER] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir.svg";
    ui->r0->iconTable() [BTN_PRESS] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir_press.svg";
    ui->r0->renderToVariable();
    ui->r1->iconTable() [BTN_NORMAL] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir.svg";
    ui->r1->iconTable() [BTN_HOVER] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir.svg";
    ui->r1->iconTable() [BTN_PRESS] = "/Users/abel/Develop/d1-product/App/skin/default/bt_stir_press.svg";
    ui->r1->renderToVariable();

    ui->p0->setSvgFile ( "/Users/abel/Develop/d1-product/App/skin/default/bk_progress_background.svg",
                         "/Users/abel/Develop/d1-product/App/skin/default/bk_progress_trunk.svg" );
    ui->p0->setRange ( 0, 100 );
    ui->p0->setValue ( 60 );

    QTimer* timer = new QTimer ( this );
    timer->setInterval ( 100 );
    timer->setSingleShot ( false );
    QObject::connect ( timer, SIGNAL ( timeout() ),
                       this, SLOT ( updateProgress() ) ) ;
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateProgress()
{
    static int i = 0;
    ui->p0->setValue ( i++ % 100 );
}

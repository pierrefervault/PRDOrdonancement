#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include "generationinstance.h"
#include "resolutioninstance.h"
/*#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>*/

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

void FenetrePrincipale::on_actionG_n_rer_des_instances_triggered()
{
    GenerationInstance generationInstance;
    if(generationInstance.exec()==QDialog::Accepted)
    {
        generationInstance.reject();
    }
}

void FenetrePrincipale::on_actionQuitter_l_application_triggered()
{
    close();
}

void FenetrePrincipale::on_actionR_soudre_des_instances_triggered()
{
    ResolutionInstance resolutionInstance;
    if(resolutionInstance.exec()==QDialog::Accepted)
    {
        resolutionInstance.reject();
    }
}

void FenetrePrincipale::on_actionGraphique_triggered()
{
/*    QwtPlot* plot = new QwtPlot();

    plot->setTitle( "Plot Demo" );
    plot->setCanvasBackground( Qt::white );
    plot->setAxisScale( QwtPlot::yLeft, 0.0, 10.0 );
    plot->insertLegend( new QwtLegend() );

    ui->horizontalLayout->addWidget(plot); // the app crashes here.

    plot->show();*/
}

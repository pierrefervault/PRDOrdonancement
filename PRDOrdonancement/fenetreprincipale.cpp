#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include "generationinstance.h"
#include "resolutioninstance.h"
#include "comparaisonsolution.h"
#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);
}

/**
 * @brief Destructeur de la Fenêtre Principale
 *
 */
FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

/**
 * @brief Action effectuée lors du clic sur le bouton de génération d'instance
 *
 */
void FenetrePrincipale::on_actionG_n_rer_des_instances_triggered()
{
    GenerationInstance generationInstance;
    if(generationInstance.exec()==QDialog::Accepted)
    {
        generationInstance.reject();
    }
}

/**
 * @brief Action effectuée lors du clic sur le bouton permetant de quitter l'application
 *
 */
void FenetrePrincipale::on_actionQuitter_l_application_triggered()
{
    close();
}

/**
 * @brief Action effectuée lors du clic sur le bouton de résolution d'instance
 *
 */
void FenetrePrincipale::on_actionR_soudre_des_instances_triggered()
{
    ResolutionInstance resolutionInstance;
    if(resolutionInstance.exec()==QDialog::Accepted)
    {
        resolutionInstance.reject();
    }
}

void FenetrePrincipale::on_actionComparer_des_m_thodes_de_r_solutions_triggered()
{
    ComparaisonSolution comparaisonSolution;
    if(comparaisonSolution.exec()==QDialog::Accepted)
    {
        comparaisonSolution.reject();
    }

    /*QwtPlot * plot = new QwtPlot();
    plot->setTitle( "Plot Demo" );
    plot->setCanvasBackground( Qt::white );
    plot->setAxisScale( QwtPlot::yLeft, 0.0, 10.0 );
    plot->insertLegend( new QwtLegend() );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( plot );

    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setTitle( "Some Points" );
    curve->setPen( Qt::blue, 4 ),
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    curve->setSymbol( symbol );

    QPolygonF points;
    points << QPointF( 0.0, 4.4 ) << QPointF( 1.0, 3.0 )
        << QPointF( 2.0, 4.5 ) << QPointF( 3.0, 6.8 )
        << QPointF( 4.0, 7.9 ) << QPointF( 5.0, 7.1 );
    curve->setSamples( points );

    curve->attach( plot );

    plot->resize( 600, 400 );
    plot->show();*/
}

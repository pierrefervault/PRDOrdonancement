#include "calculcomparaison.h"
#include "fstream"

#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

CalculComparaison::CalculComparaison()
{

}

map<unsigned int,map<QString,unsigned int>> CalculComparaison::calculGap(map<unsigned int,vector<Resultat>> tableauComparaison){

    map<unsigned int,map<QString,unsigned int>> tableauGap;

    for (map<unsigned int,vector<Resultat>>::iterator it=tableauComparaison.begin(); it!=tableauComparaison.end(); ++it)
    {
        cout << "Element" << endl;

        vector<unsigned int> solutionOptimal;
        for (std::vector<Resultat>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            if(it2->getFichierResultat().contains("resolutionMip1")){
                solutionOptimal = it2->getSolutions();
            }
        }
        //cout << solutionOptimal.size() << endl;
        for (std::vector<Resultat>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            double gapSolution = 0;
            for(unsigned int i = 0 ; i < it2->getSolutions().size() ; i++){
                gapSolution += (double)it2->getSolutions()[i] / (double)solutionOptimal[i];
            }
            gapSolution /= it2->getSolutions().size();
            tableauGap[it->first][it2->getFichierResultat()] = (double)(100 - (100 * gapSolution));

        }
    }

    for (std::map<unsigned int,map<QString,unsigned int>>::iterator it=tableauGap.begin(); it!=tableauGap.end(); ++it)
    {
        for (std::map<QString,unsigned int>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            cout << it->first << " => " << it2->first.toStdString() << " => " << it2->second << '\n';
        }
    }

    return tableauGap;

}

map<unsigned int,map<QString,unsigned int>> CalculComparaison::calculPourcentageSolutionOptimale(map<unsigned int, vector<Resultat> > tableauComparaison){

    map<unsigned int,map<QString,unsigned int>> tableauPourcentageSolutionOptimale;

    for (map<unsigned int,vector<Resultat>>::iterator it=tableauComparaison.begin(); it!=tableauComparaison.end(); ++it)
    {
        cout << "Element" << endl;

        vector<unsigned int> solutionOptimal;
        for (std::vector<Resultat>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            if(it2->getFichierResultat().contains("resolutionMip1")){
                solutionOptimal = it2->getSolutions();
            }
        }
        //cout << solutionOptimal.size() << endl;
        for (std::vector<Resultat>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            double pourcentageSolutionOptimale = 0;
            for(unsigned int i = 0 ; i < it2->getSolutions().size() ; i++){
                if (it2->getSolutions()[i] == solutionOptimal[i])
                pourcentageSolutionOptimale++;
            }
            pourcentageSolutionOptimale /= it2->getSolutions().size();
            tableauPourcentageSolutionOptimale[it->first][it2->getFichierResultat()] = (double)(100 * pourcentageSolutionOptimale);
            //it2->second = (double)(100 * gapSolution);
        }
    }

    for (std::map<unsigned int,map<QString,unsigned int>>::iterator it=tableauPourcentageSolutionOptimale.begin(); it!=tableauPourcentageSolutionOptimale.end(); ++it)
    {
        for (std::map<QString,unsigned int>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            cout << it->first << " => " << it2->first.toStdString() << " => " << it2->second << '\n';
        }
    }

    return tableauPourcentageSolutionOptimale;
}

map<unsigned int,map<QString,unsigned int>> CalculComparaison::calculPourcentageTempsResolution(map<unsigned int, vector<Resultat> > tableauComparaison){

    map<unsigned int,map<QString,unsigned int>> tableauPourcentageTempsResolution;

    for (map<unsigned int,vector<Resultat>>::iterator it=tableauComparaison.begin(); it!=tableauComparaison.end(); ++it)
    {
        cout << "Element" << endl;

        vector<double> tempsResolutionOptimal;
        for (std::vector<Resultat>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            if(it2->getFichierResultat().contains("resolutionMip1")){
                tempsResolutionOptimal = it2->getTempsExecution();
            }
        }
        //cout << solutionOptimal.size() << endl;
        for (std::vector<Resultat>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            double pourcentageTempsResolution = 0;
            for(unsigned int i = 0 ; i < it2->getSolutions().size() ; i++){
                pourcentageTempsResolution += (double)it2->getTempsExecution()[i] / (double)tempsResolutionOptimal[i];
            }
            pourcentageTempsResolution /= it2->getTempsExecution().size();
            tableauPourcentageTempsResolution[it->first][it2->getFichierResultat()] = (double)(100 * pourcentageTempsResolution);
            //it2->second = (double)(100 * gapSolution);
        }
    }

    for (std::map<unsigned int,map<QString,unsigned int>>::iterator it=tableauPourcentageTempsResolution.begin(); it!=tableauPourcentageTempsResolution.end(); ++it)
    {
        for (std::map<QString,unsigned int>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            cout << it->first << " => " << it2->first.toStdString() << " => " << it2->second << '\n';
        }
    }

    return tableauPourcentageTempsResolution;

}

void CalculComparaison::afficherGraphique(map<unsigned int,vector<Resultat>> tableauComparaison, QString typeComparaison){

    map<unsigned int,map<QString,unsigned int>> tableauComparaisonGap = calculPourcentageTempsResolution(tableauComparaison);

    cout << "Plot" << endl;
    QwtPlot * plot = new QwtPlot();
    plot->setTitle( "Gap des différentes méthodes de résolution" );
    plot->setCanvasBackground( Qt::white );
    plot->setAxisScale( QwtPlot::yLeft, 0.0, 100.0);//fichierSolutionOptimale.split("/")[2].toDouble());
    plot->insertLegend( new QwtLegend() );

    cout << "PlotGrid" << endl;
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( plot );

    cout << "PlotCurve" << endl;
    QwtPlotCurve *curveAffectation1CCmaxMaxRessources = new QwtPlotCurve();
    curveAffectation1CCmaxMaxRessources->setTitle( "Affectation1 CCmaxMaxRessources" );
    curveAffectation1CCmaxMaxRessources->setPen( Qt::blue, 4 ),
    curveAffectation1CCmaxMaxRessources->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve *curveAffectation2CCmaxMaxRessources = new QwtPlotCurve();
    curveAffectation2CCmaxMaxRessources->setTitle( "Affectation2 CCmaxMaxRessources" );
    curveAffectation2CCmaxMaxRessources->setPen( Qt::green, 4 ),
    curveAffectation2CCmaxMaxRessources->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve *curveAffectation1CCmaxSommeRessources = new QwtPlotCurve();
    curveAffectation1CCmaxSommeRessources->setTitle( "Affectation1 CCmaxSommeRessources" );
    curveAffectation1CCmaxSommeRessources->setPen( Qt::black, 4 ),
    curveAffectation1CCmaxSommeRessources->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve *curveAffectation2CCmaxSommeRessources = new QwtPlotCurve();
    curveAffectation2CCmaxSommeRessources->setTitle( "Affectation2 CCmaxSommeRessources" );
    curveAffectation2CCmaxSommeRessources->setPen( Qt::yellow, 4 ),
    curveAffectation2CCmaxSommeRessources->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve *curveAffectation1SommeRessources = new QwtPlotCurve();
    curveAffectation1SommeRessources->setTitle( "Affectation1 SommeRessources" );
    curveAffectation1SommeRessources->setPen( Qt::gray, 4 ),
    curveAffectation1SommeRessources->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve *curveAffectation2SommeRessources = new QwtPlotCurve();
    curveAffectation2SommeRessources->setTitle( "Affectation2 SommeRessources" );
    curveAffectation2SommeRessources->setPen( Qt::darkBlue, 4 ),
    curveAffectation2SommeRessources->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve *curveAffectation1MoyenneRessourcesSousEnsembles = new QwtPlotCurve();
    curveAffectation1MoyenneRessourcesSousEnsembles->setTitle( "Affectation1 MoyenneRessourcesSousEnsembles" );
    curveAffectation1MoyenneRessourcesSousEnsembles->setPen( Qt::darkGreen, 4 ),
    curveAffectation1MoyenneRessourcesSousEnsembles->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtPlotCurve *curveAffectation2MoyenneRessourcesSousEnsembles = new QwtPlotCurve();
    curveAffectation2MoyenneRessourcesSousEnsembles->setTitle( "Affectation2 MoyenneRessourcesSousEnsembles" );
    curveAffectation2MoyenneRessourcesSousEnsembles->setPen( Qt::darkMagenta, 4 ),
    curveAffectation2MoyenneRessourcesSousEnsembles->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    cout << "PlotSymbol" << endl;
    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );

    QPolygonF pointsAffectation1CCmaxMaxRessources;
    QPolygonF pointsAffectation2CCmaxMaxRessources;
    QPolygonF pointsAffectation1CCmaxSommeRessources;
    QPolygonF pointsAffectation2CCmaxSommeRessources;
    QPolygonF pointsAffectation1SommeRessources;
    QPolygonF pointsAffectation2SommeRessources;
    QPolygonF pointsAffectation1MoyenneRessourcesSousEnsembles;
    QPolygonF pointsAffectation2MoyenneRessourcesSousEnsembles;

    for (std::map<unsigned int,map<QString,unsigned int>>::iterator it=tableauComparaisonGap.begin(); it!=tableauComparaisonGap.end(); ++it)
    {
        for (std::map<QString,unsigned int>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            if (it2->first.contains("Affectation1-CCmaxMaxRessources")) pointsAffectation1CCmaxMaxRessources << QPointF( it->first, it2->second);
            if (it2->first.contains("Affectation2-CCmaxMaxRessources")) pointsAffectation2CCmaxMaxRessources << QPointF( it->first, it2->second);
            if (it2->first.contains("Affectation1-CCmaxSommeRessources")) pointsAffectation1CCmaxSommeRessources << QPointF( it->first, it2->second);
            if (it2->first.contains("Affectation2-CCmaxSommeRessources")) pointsAffectation2CCmaxSommeRessources << QPointF( it->first, it2->second);
            if (it2->first.contains("Affectation1-SommeRessources")) pointsAffectation1SommeRessources << QPointF( it->first, it2->second);
            if (it2->first.contains("Affectation2-SommeRessources")) pointsAffectation2SommeRessources << QPointF( it->first, it2->second);
            if (it2->first.contains("Affectation1-MoyenneRessourcesSousEnsembles")) pointsAffectation1MoyenneRessourcesSousEnsembles << QPointF( it->first, it2->second);
            if (it2->first.contains("Affectation2-MoyenneRessourcesSousEnsembles")) pointsAffectation2MoyenneRessourcesSousEnsembles << QPointF( it->first, it2->second);
        }
    }

    cout << "PlotSetSymbol" << endl;
    curveAffectation1CCmaxMaxRessources->setSymbol( symbol );
    curveAffectation2CCmaxMaxRessources->setSymbol( symbol );
    curveAffectation1CCmaxSommeRessources->setSymbol( symbol );
    curveAffectation2CCmaxSommeRessources->setSymbol( symbol );
    curveAffectation1SommeRessources->setSymbol( symbol );
    curveAffectation2SommeRessources->setSymbol( symbol );
    curveAffectation1MoyenneRessourcesSousEnsembles->setSymbol( symbol );
    curveAffectation2MoyenneRessourcesSousEnsembles->setSymbol( symbol );

    cout << "PlotSetSamples" << endl;
    curveAffectation1CCmaxMaxRessources->setSamples( pointsAffectation1CCmaxMaxRessources );
    curveAffectation2CCmaxMaxRessources->setSamples( pointsAffectation2CCmaxMaxRessources );
    curveAffectation1CCmaxSommeRessources->setSamples( pointsAffectation1CCmaxSommeRessources );
    curveAffectation2CCmaxSommeRessources->setSamples( pointsAffectation2CCmaxSommeRessources );
    curveAffectation1SommeRessources->setSamples( pointsAffectation1SommeRessources );
    curveAffectation2SommeRessources->setSamples( pointsAffectation2SommeRessources );
    curveAffectation1MoyenneRessourcesSousEnsembles->setSamples( pointsAffectation1MoyenneRessourcesSousEnsembles );
    curveAffectation2MoyenneRessourcesSousEnsembles->setSamples( pointsAffectation2MoyenneRessourcesSousEnsembles );

    cout << "PlotAttach" << endl;
    curveAffectation1CCmaxMaxRessources->attach( plot );
    curveAffectation2CCmaxMaxRessources->attach( plot );
    curveAffectation1CCmaxSommeRessources->attach( plot );
    curveAffectation2CCmaxSommeRessources->attach( plot );
    curveAffectation1SommeRessources->attach( plot );
    curveAffectation2SommeRessources->attach( plot );
    curveAffectation1MoyenneRessourcesSousEnsembles->attach( plot );
    curveAffectation2MoyenneRessourcesSousEnsembles->attach( plot );

    cout << "PlotResize" << endl;
    plot->resize( 1200, 800 );

    plot->show();

}

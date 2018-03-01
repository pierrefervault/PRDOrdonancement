#include "workercomparaison.h"
#include "fstream"
#include "calculcomparaison.h"

#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

WorkerComparaison::WorkerComparaison(QString dossierResultat, QString typeComparaison, int nbrRessources, int nbrMachines){
    this->dossierResultat = dossierResultat;
    this->typeComparaison = typeComparaison;
    this->nbrRessources = nbrRessources;
    this->nbrMachines = nbrMachines;
}

WorkerComparaison::~WorkerComparaison(){

}

void WorkerComparaison::process(){

    QString dossierResultat = this->dossierResultat;
    QFileInfo path(dossierResultat);

    QStringList filter;
    filter << "*-"+QString::number(nbrRessources)+"-"+QString::number(nbrMachines)+".data";

    cout << filter[0].toStdString() << endl;

    QDirIterator it(dossierResultat, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList files;
    while (it.hasNext())
        files << it.next();
    files.sort();

    std::list<QString> list = files.toStdList();

    map<unsigned int,vector<Resultat>> tableauComparaison;

    for(std::list<QString>::iterator it = list.begin() ; it != list.end() ; ++it){

        QString fichier = *it;

        Resultat resultat;

        resultat.chargerResultat(fichier);

        tableauComparaison[fichier.split("/")[fichier.split("/").size()-4].toInt()].push_back(resultat);

    }

    CalculComparaison calculComparaison;

    if (this->typeComparaison == "Gap"){
        emit updateLayout(calculComparaison.calculGap(tableauComparaison), this->typeComparaison);
    }
    if (this->typeComparaison == "PourcentageSolutionsOptimales"){
        emit updateLayout(calculComparaison.calculPourcentageSolutionOptimale(tableauComparaison), this->typeComparaison);
    }
    if (this->typeComparaison == "PourcentageTempsResolutionExacte"){
        emit updateLayout(calculComparaison.calculPourcentageTempsResolution(tableauComparaison), this->typeComparaison);
    }


/*
    std::ifstream f(fichierSolutionOptimale.toStdString());

    if (!f)
    {
        cout << fichierSolutionOptimale.toStdString() <<" invalid file" << endl;
    }

    string line;

    vector<vector<unsigned int>> solution;
    vector<vector<double>> tempsSolution;

    vector <unsigned int> solutionOptimale;
    vector<double> tempsSolutionOptimale;

    while(getline(f,line)) {
        cout << line << endl ;
        getline(f,line);

        getline(f,line);
        QString ligneOptimale = QString::fromStdString(line);
        unsigned int optimal = ligneOptimale.split("=")[1].toInt();
        solutionOptimale.push_back(optimal);

        getline(f,line);
        QString tempsEcoule = QString::fromStdString(line);
        tempsSolutionOptimale.push_back(tempsEcoule.split(":")[1].toDouble());

        getline(f,line);
        for (int i = 0; i < fichierSolutionOptimale.split("/")[4].toInt() ; i++){
            getline(f,line);
        }

        getline(f,line);
        for (unsigned int i = 0; i < optimal ; i++){
            getline(f,line);
        }
    }

    f.close();

    solution.push_back(solutionOptimale);
    tempsSolution.push_back(tempsSolutionOptimale);

    f.open(fichierAffectation1CCmaxSommeRessources.toStdString());

    vector <unsigned int> solutionAffectation1CCmaxSommeRessources;
    vector<double> tempsAffectation1CCmaxSommeRessources;

    while(getline(f,line)) {
        cout << line << endl ;
        getline(f,line);

        getline(f,line);
        QString ligneOptimale = QString::fromStdString(line);
        unsigned int optimal = ligneOptimale.split("=")[1].toInt();
        solutionAffectation1CCmaxSommeRessources.push_back(optimal);

        getline(f,line);
        QString tempsEcoule = QString::fromStdString(line);
        tempsAffectation1CCmaxSommeRessources.push_back(tempsEcoule.split(":")[1].toDouble());

        getline(f,line);
        for (int i = 0; i < fichierSolutionOptimale.split("/")[4].toInt() ; i++){
            getline(f,line);
        }

        getline(f,line);
        for (unsigned int i = 0; i < optimal ; i++){
            getline(f,line);
        }
    }

    f.close();

    solution.push_back(solutionAffectation1CCmaxSommeRessources);
    tempsSolution.push_back(tempsAffectation1CCmaxSommeRessources);

    for(unsigned int i = 0; i < solutionOptimale.size(); i++){
        cout << solutionOptimale.at(i) << endl;
    }

    for(unsigned int i = 0; i < tempsSolutionOptimale.size(); i++){
        cout << tempsSolutionOptimale.at(i) << endl;
    }

    for(unsigned int i = 0; i < solutionAffectation1CCmaxSommeRessources.size(); i++){
        cout << solutionAffectation1CCmaxSommeRessources.at(i) << endl;
    }

    for(unsigned int i = 0; i < tempsAffectation1CCmaxSommeRessources.size(); i++){
        cout << tempsAffectation1CCmaxSommeRessources.at(i) << endl;
    }

    QwtPlot * plot = new QwtPlot();
    plot->setTitle( "Comparaison méthode de résolution" );
    plot->setCanvasBackground( Qt::white );
    plot->setAxisScale( QwtPlot::yLeft, 0.0, fichierSolutionOptimale.split("/")[2].toDouble());
    plot->insertLegend( new QwtLegend() );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( plot );

    QwtPlotCurve *curveOptimale = new QwtPlotCurve();
    curveOptimale->setTitle( "Solutions Exactes" );
    curveOptimale->setPen( Qt::blue, 4 ),
    curveOptimale->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    curveOptimale->setSymbol( symbol );

    QPolygonF points;
    for(unsigned int i = 0; i < solutionOptimale.size(); i++){
        points << QPointF( i, solutionOptimale.at(i));
    }*/
    /*points << QPointF( 0.0, 4.4 ) << QPointF( 1.0, 3.0 )
        << QPointF( 2.0, 4.5 ) << QPointF( 3.0, 6.8 )
        << QPointF( 4.0, 7.9 ) << QPointF( 5.0, 7.1 );*/
    /*curveOptimale->setSamples( points );

    curveOptimale->attach( plot );

    QwtPlotCurve *curveCcmax = new QwtPlotCurve();
    curveCcmax->setTitle( "Ccmax" );
    curveCcmax->setPen( Qt::red, 4 ),
    curveCcmax->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    curveCcmax->setSymbol( symbol );

    QPolygonF pointsCcmax;
    for(unsigned int i = 0; i < solutionAffectation1CCmaxSommeRessources.size(); i++){
        pointsCcmax << QPointF( i, solutionAffectation1CCmaxSommeRessources.at(i));
    }*/
    /*points << QPointF( 0.0, 4.4 ) << QPointF( 1.0, 3.0 )
        << QPointF( 2.0, 4.5 ) << QPointF( 3.0, 6.8 )
        << QPointF( 4.0, 7.9 ) << QPointF( 5.0, 7.1 );*/
    /*curveCcmax->setSamples( pointsCcmax );

    curveCcmax->attach( plot );

    plot->resize( 600, 400 );
    plot->show();*/

    emit finished();
}


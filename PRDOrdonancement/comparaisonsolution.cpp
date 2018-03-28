#include "comparaisonsolution.h"
#include "ui_comparaisonsolution.h"

/**
 * @brief Constructeur de la classe ComparaisonSolution
 *
 * @param parent
 */
ComparaisonSolution::ComparaisonSolution(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComparaisonSolution)
{
    ui->setupUi(this);
    this->setWindowTitle("Comparaison des méthodes de résolution");
}

/**
 * @brief Destructeur de la classe ComparaisonSolution
 *
 */
ComparaisonSolution::~ComparaisonSolution()
{
    delete ui;
}

/**
 * @brief Action réalisée lors du clic sur le bouton permettant de choisir un dossier de résultat
 *
 */
void ComparaisonSolution::on_choisirDossierPushButton_clicked()
{
    QFileDialog fenetreDossier;
    QString repertoireCourant = QDir::currentPath();
    QString dossierInstance = fenetreDossier.getExistingDirectory(this,
         tr("Instance directory"), "./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!dossierInstance.isNull()){
        dossierInstance = dossierInstance.split(repertoireCourant+"/").at(1);
        this->ui->choisirDossierLineEdit->setText(dossierInstance);
    }
}

/**
 * @brief Action réalisée lors du clic sur le bouton permettant de valider la comparaison
 *
 */
void ComparaisonSolution::on_validerPushButton_clicked()
{
    QString dossierInstance = this->ui->choisirDossierLineEdit->text();

    if (dossierInstance != NULL){
        if (this->ui->typeComparaisonComboBox->currentText() == "Calcul Gap"){
            executionComparaison(dossierInstance,"Gap",this->ui->nbrRessourcesSpinBox->text().toInt(), this->ui->nbrMachinesSpinBox->text().toInt());
        }
        if (this->ui->typeComparaisonComboBox->currentText() == "Pourcentage de solutions optimales"){
            executionComparaison(dossierInstance,"PourcentageSolutionsOptimales",this->ui->nbrRessourcesSpinBox->text().toInt(), this->ui->nbrMachinesSpinBox->text().toInt());
        }
        if (this->ui->typeComparaisonComboBox->currentText() == "Pourcentage du temps de résolution par méthode exacte"){
            executionComparaison(dossierInstance,"PourcentageTempsResolutionExacte",this->ui->nbrRessourcesSpinBox->text().toInt(), this->ui->nbrMachinesSpinBox->text().toInt());
        }
        //accept();
    }
    else{
        QMessageBox messageBox;
        messageBox.critical(0,"Erreur","Le dossier de Résultat n'est pas spécifié");
        messageBox.setFixedSize(500,200);
    }
}

/**
 * @brief Execute la comparaison de solution
 *
 * @param dossierResultat Le dossier de résultat que l'on souhaite comparer
 * @param typeComparaison Le type de comparaison que l'on souhaite effectuer
 * @param nbrRessources Le nombre de ressources de chaque fichier de resultat
 * @param nbrMachines Le nombre de machines de chaque fichier de resultat
 */
void ComparaisonSolution::executionComparaison(QString dossierInstance, QString typeResolution, unsigned int nbrRessources, unsigned int nbrMachines)
{
    QThread* thread = new QThread;
    //cout << fichierInstance << " " << fichierResultat << endl;
    WorkerComparaison * workerComparaison = new WorkerComparaison(dossierInstance, typeResolution, nbrRessources, nbrMachines);
    workerComparaison->moveToThread(thread);
    //connect(workerComparaison, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
    connect(thread, SIGNAL (started()), workerComparaison, SLOT (process()));
    connect(workerComparaison, SIGNAL (finished()), thread, SLOT (quit()));
    connect(workerComparaison, SIGNAL (finished()), workerComparaison, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    qRegisterMetaType<map<unsigned int,map<QString,unsigned int>>>("map<unsigned int,map<QString,unsigned int>>");
    connect(workerComparaison, SIGNAL (updateLayout(map<unsigned int,map<QString,unsigned int>>, QString)),
            this, SLOT (updateLayout(map<unsigned int,map<QString,unsigned int>>, QString)));
    thread->start();
}

/**
 * @brief Action réalisée lors du clic sur le bouton permettant d'annuler la comparaison
 *
 */
void ComparaisonSolution::on_annulerPushButton_clicked()
{
    reject();
}

/**
 * @brief Permet de mettre à jour le layout contenant le graphique de comparaison
 *
 * @param tableauComparaison Le tableau de comparaison contenant toute les données nécessaires à l'affichage du graphique
 * @param typeComparaison Le type de comparaison que nous avons effectué
 */
void ComparaisonSolution::updateLayout(map<unsigned int,map<QString,unsigned int>> tableauComparaison, QString typeComparaison){

    if (this->ui->tableauRadioButton->isChecked()){

        QTableView * tableView = new QTableView();

        unsigned int idColonne = 0;
        unsigned int idLigne = 0;

        QStandardItemModel *model = new QStandardItemModel(tableauComparaison.size(), 9, this);
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Nombre de jobs")));

        for (std::map<QString,unsigned int>::iterator it2=tableauComparaison.begin()->second.begin(); it2!=tableauComparaison.begin()->second.end(); ++it2){
            idColonne++;
            if (it2->first.contains("Affectation1-CCmaxMaxRessources")) model->setHorizontalHeaderItem(idColonne, new QStandardItem("Affectation1-CCmaxMaxRessources"));
            if (it2->first.contains("Affectation2-CCmaxMaxRessources")) model->setHorizontalHeaderItem(idColonne, new QStandardItem("Affectation2-CCmaxMaxRessources"));
            if (it2->first.contains("Affectation1-CCmaxSommeRessources")) model->setHorizontalHeaderItem(idColonne, new QStandardItem("Affectation1-CCmaxSommeRessources"));
            if (it2->first.contains("Affectation2-CCmaxSommeRessources")) model->setHorizontalHeaderItem(idColonne, new QStandardItem("Affectation2-CCmaxSommeRessources"));
            if (it2->first.contains("Affectation1-SommeRessources")) model->setHorizontalHeaderItem(idColonne, new QStandardItem("Affectation1-SommeRessources"));
            if (it2->first.contains("Affectation2-SommeRessources")) model->setHorizontalHeaderItem(idColonne, new QStandardItem("Affectation2-SommeRessources"));
            if (it2->first.contains("Affectation1-MoyenneRessourcesSousEnsembles")) model->setHorizontalHeaderItem(idColonne, new QStandardItem("Affectation1-MoyenneRessourcesSousEnsembles"));
            if (it2->first.contains("Affectation2-MoyenneRessourcesSousEnsembles")) model->setHorizontalHeaderItem(idColonne, new QStandardItem("Affectation2-MoyenneRessourcesSousEnsembles"));
            if (it2->first.contains("Mip1")) model->setHorizontalHeaderItem(idColonne, new QStandardItem("Mip1"));
            if (it2->first.contains("Mip2")) model->setHorizontalHeaderItem(idColonne, new QStandardItem("Mip2"));
        }

        tableView->setModel(model);

        for (std::map<unsigned int,map<QString,unsigned int>>::iterator it=tableauComparaison.begin(); it!=tableauComparaison.end(); ++it)
        {
            idColonne = 0;
            QStandardItem * valeur = new QStandardItem(QString::number(it->first));
            model->setItem(idLigne,idColonne,valeur);
            for (std::map<QString,unsigned int>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
                idColonne++;
                QStandardItem * valeurHeuristique = new QStandardItem(QString::number(it2->second)+QString(" %"));
                model->setItem(idLigne,idColonne,valeurHeuristique);
            }
            idLigne++;
        }

        tableView->resizeColumnsToContents();

        QLabel * titre = new QLabel();

        if (typeComparaison == "Gap") titre->setText("Gap des différentes méthodes de résolution" );
        if (typeComparaison == "PourcentageSolutionsOptimales") titre->setText("Pourcentage de solutions optimales");
        if (typeComparaison == "PourcentageTempsResolutionExacte") titre->setText("Pourcentage du temps de résolution par méthode exacte");

        QFont font( "Arial", 18, QFont::Bold);

        titre->setFont(font);

        this->ui->verticalLayout->addWidget(titre);

        this->ui->verticalLayout->addWidget(tableView);
    }

    if (this->ui->graphiqueRadioButton->isChecked()){
        QwtPlot * plot = new QwtPlot();

        if (typeComparaison == "Gap") plot->setTitle( "Gap des différentes méthodes de résolution" );
        if (typeComparaison == "PourcentageSolutionsOptimales") plot->setTitle("Pourcentage de solutions optimales");
        if (typeComparaison == "PourcentageTempsResolutionExacte") plot->setTitle("Pourcentage du temps de résolution par méthode exacte");

        plot->setCanvasBackground( Qt::white );
        plot->setAxisScale( QwtPlot::yLeft, 0.0, 100.0);
        plot->insertLegend( new QwtLegend() );

        QwtPlotGrid *grid = new QwtPlotGrid();
        grid->attach( plot );

        QwtPlotCurve *curveAffectation1CCmaxMaxRessources = new QwtPlotCurve();
        curveAffectation1CCmaxMaxRessources->setTitle( "Affectation1 CCmaxMaxRessources" );
        curveAffectation1CCmaxMaxRessources->setPen( Qt::blue, 4 ),
        curveAffectation1CCmaxMaxRessources->setRenderHint( QwtPlotItem::RenderAntialiased, true );
        QwtSymbol *symbolAffectation1CCmaxMaxRessources = new QwtSymbol( QwtSymbol::Ellipse, QBrush( Qt::blue ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
        curveAffectation1CCmaxMaxRessources->setSymbol( symbolAffectation1CCmaxMaxRessources );

        QwtPlotCurve *curveAffectation2CCmaxMaxRessources = new QwtPlotCurve();
        curveAffectation2CCmaxMaxRessources->setTitle( "Affectation2 CCmaxMaxRessources" );
        curveAffectation2CCmaxMaxRessources->setPen( Qt::green, 4 ),
        curveAffectation2CCmaxMaxRessources->setRenderHint( QwtPlotItem::RenderAntialiased, true );
        QwtSymbol *symbolAffectation2CCmaxMaxRessources = new QwtSymbol( QwtSymbol::Ellipse, QBrush( Qt::green ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
        curveAffectation2CCmaxMaxRessources->setSymbol( symbolAffectation2CCmaxMaxRessources );

        QwtPlotCurve *curveAffectation1CCmaxSommeRessources = new QwtPlotCurve();
        curveAffectation1CCmaxSommeRessources->setTitle( "Affectation1 CCmaxSommeRessources" );
        curveAffectation1CCmaxSommeRessources->setPen( Qt::black, 4 ),
        curveAffectation1CCmaxSommeRessources->setRenderHint( QwtPlotItem::RenderAntialiased, true );
        QwtSymbol *symbolAffectation1CCmaxSommeRessources = new QwtSymbol( QwtSymbol::Ellipse, QBrush( Qt::black ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
        curveAffectation1CCmaxSommeRessources->setSymbol( symbolAffectation1CCmaxSommeRessources );

        QwtPlotCurve *curveAffectation2CCmaxSommeRessources = new QwtPlotCurve();
        curveAffectation2CCmaxSommeRessources->setTitle( "Affectation2 CCmaxSommeRessources" );
        curveAffectation2CCmaxSommeRessources->setPen( Qt::yellow, 4 ),
        curveAffectation2CCmaxSommeRessources->setRenderHint( QwtPlotItem::RenderAntialiased, true );
        QwtSymbol *symbolAffectation2CCmaxSommeRessources = new QwtSymbol( QwtSymbol::Ellipse, QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
        curveAffectation2CCmaxSommeRessources->setSymbol( symbolAffectation2CCmaxSommeRessources );

        QwtPlotCurve *curveAffectation1SommeRessources = new QwtPlotCurve();
        curveAffectation1SommeRessources->setTitle( "Affectation1 SommeRessources" );
        curveAffectation1SommeRessources->setPen( Qt::gray, 4 ),
        curveAffectation1SommeRessources->setRenderHint( QwtPlotItem::RenderAntialiased, true );
        QwtSymbol *symbolAffectation1SommeRessources = new QwtSymbol( QwtSymbol::Ellipse, QBrush( Qt::gray ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
        curveAffectation1SommeRessources->setSymbol( symbolAffectation1SommeRessources );

        QwtPlotCurve *curveAffectation2SommeRessources = new QwtPlotCurve();
        curveAffectation2SommeRessources->setTitle( "Affectation2 SommeRessources" );
        curveAffectation2SommeRessources->setPen( Qt::darkBlue, 4 ),
        curveAffectation2SommeRessources->setRenderHint( QwtPlotItem::RenderAntialiased, true );
        QwtSymbol *symbolAffectation2SommeRessources = new QwtSymbol( QwtSymbol::Ellipse, QBrush( Qt::darkBlue ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
        curveAffectation2SommeRessources->setSymbol( symbolAffectation2SommeRessources );

        QwtPlotCurve *curveAffectation1MoyenneRessourcesSousEnsembles = new QwtPlotCurve();
        curveAffectation1MoyenneRessourcesSousEnsembles->setTitle( "Affectation1 MoyenneRessourcesSousEnsembles" );
        curveAffectation1MoyenneRessourcesSousEnsembles->setPen( Qt::darkGreen, 4 ),
        curveAffectation1MoyenneRessourcesSousEnsembles->setRenderHint( QwtPlotItem::RenderAntialiased, true );
        QwtSymbol *symbolAffectation1MoyenneRessourcesSousEnsembles = new QwtSymbol( QwtSymbol::Ellipse, QBrush( Qt::darkGreen ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
        curveAffectation1MoyenneRessourcesSousEnsembles->setSymbol( symbolAffectation1MoyenneRessourcesSousEnsembles );

        QwtPlotCurve *curveAffectation2MoyenneRessourcesSousEnsembles = new QwtPlotCurve();
        curveAffectation2MoyenneRessourcesSousEnsembles->setTitle( "Affectation2 MoyenneRessourcesSousEnsembles" );
        curveAffectation2MoyenneRessourcesSousEnsembles->setPen( Qt::darkMagenta, 4 ),
        curveAffectation2MoyenneRessourcesSousEnsembles->setRenderHint( QwtPlotItem::RenderAntialiased, true );
        QwtSymbol *symbolAffectation2MoyenneRessourcesSousEnsembles = new QwtSymbol( QwtSymbol::Ellipse, QBrush( Qt::darkMagenta ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
        curveAffectation2MoyenneRessourcesSousEnsembles->setSymbol( symbolAffectation2MoyenneRessourcesSousEnsembles );

        QPolygonF pointsAffectation1CCmaxMaxRessources;
        QPolygonF pointsAffectation2CCmaxMaxRessources;
        QPolygonF pointsAffectation1CCmaxSommeRessources;
        QPolygonF pointsAffectation2CCmaxSommeRessources;
        QPolygonF pointsAffectation1SommeRessources;
        QPolygonF pointsAffectation2SommeRessources;
        QPolygonF pointsAffectation1MoyenneRessourcesSousEnsembles;
        QPolygonF pointsAffectation2MoyenneRessourcesSousEnsembles;

        for (std::map<unsigned int,map<QString,unsigned int>>::iterator it=tableauComparaison.begin(); it!=tableauComparaison.end(); ++it)
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

        curveAffectation1CCmaxMaxRessources->setSamples( pointsAffectation1CCmaxMaxRessources );
        curveAffectation2CCmaxMaxRessources->setSamples( pointsAffectation2CCmaxMaxRessources );
        curveAffectation1CCmaxSommeRessources->setSamples( pointsAffectation1CCmaxSommeRessources );
        curveAffectation2CCmaxSommeRessources->setSamples( pointsAffectation2CCmaxSommeRessources );
        curveAffectation1SommeRessources->setSamples( pointsAffectation1SommeRessources );
        curveAffectation2SommeRessources->setSamples( pointsAffectation2SommeRessources );
        curveAffectation1MoyenneRessourcesSousEnsembles->setSamples( pointsAffectation1MoyenneRessourcesSousEnsembles );
        curveAffectation2MoyenneRessourcesSousEnsembles->setSamples( pointsAffectation2MoyenneRessourcesSousEnsembles );

        curveAffectation1CCmaxMaxRessources->attach( plot );
        curveAffectation2CCmaxMaxRessources->attach( plot );
        curveAffectation1CCmaxSommeRessources->attach( plot );
        curveAffectation2CCmaxSommeRessources->attach( plot );
        curveAffectation1SommeRessources->attach( plot );
        curveAffectation2SommeRessources->attach( plot );
        curveAffectation1MoyenneRessourcesSousEnsembles->attach( plot );
        curveAffectation2MoyenneRessourcesSousEnsembles->attach( plot );

        this->ui->verticalLayout->addWidget(plot);
    }

}

/**
 * @brief Action réalisée lors du clic sur le bouton permettant de nettoyer le layout contenant le graphique de comparaison
 *
 */
void ComparaisonSolution::on_netoyerLayoutPushButton_clicked()
{
    QLayoutItem * item;
    QWidget * widget;
    while ((item = this->ui->verticalLayout->takeAt(0))) {
        if ((widget = item->widget()) != 0) {widget->hide(); delete widget;}
        else {delete item;}
    }
}

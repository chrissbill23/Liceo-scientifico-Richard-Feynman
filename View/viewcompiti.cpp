#include "viewcompiti.h"
#include "compitoparserxml.h"
#include "../Controller/controllercompitiuser.h"
#include "popupdialog.h"
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>

int ViewCompiti::maxPerPage = 2;

ViewCompiti::ViewCompiti(ControllerCompitiUser *c) : Finestre(c), lay(0), Materia(0), classe(0), ctrl(c)
{
    compiti = ctrl->codiciCompiti();
    int tot = compiti.size();
    totPage = tot/ maxPerPage;
    if(tot % maxPerPage > 0 || tot == 0)
        ++totPage;
    currPage = 1;
}

QComboBox *ViewCompiti::Materie()
{
    if(Materia)
        delete Materia;
    Materia = new QComboBox(this);
    Materia->setFixedSize(300,50);
    Materia->setFont(QFont("Times",12));

    Materia->addItem("Tutte le materie", -1);

    list<string> l = ctrl->MaterieInsegnate();

    for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it){
        Materia->addItem(QString::fromStdString(*it), QString::fromStdString(*it));
    }
    return Materia;
}

QComboBox *ViewCompiti::Classi()
{
    if(classe)
        delete classe;
    classe = new QComboBox(this);
    classe->setFixedSize(300,50);
    classe->setFont(QFont("Times",12));

    classe->addItem("Tutte le classi", -1);

    vector<string> v = ctrl->Classi();

    for(vector<string>::const_iterator it = v.begin(); it != v.end(); ++it){
        classe->addItem(QString::fromStdString(*it), QString::fromStdString(*it));
    }

    return classe;
}

vector<string> ViewCompiti::giveLista() const
{
    return compiti;
}

bool ViewCompiti::sortbyMateria()
{
    if(Materia->itemData(Materia->currentIndex()).toInt() != -1){

        ctrl->SortcodiciCompitibyMateria(compiti,Materia->itemData(Materia->currentIndex()).toString());
        currPage = 1;
        int tot = compiti.size();
        totPage = tot/ maxPerPage;
        if(tot % maxPerPage > 0 || tot == 0)
            ++totPage;
    }
    return true;
}

bool ViewCompiti::sortbyClasse()
{
    if(classe->itemData(classe->currentIndex()).toInt() != -1){
    ctrl->SortcodiciCompitibyClasse(compiti,classe->itemData(classe->currentIndex()).toString());
    int tot = compiti.size();
    currPage = 1;
    totPage = tot/ maxPerPage;
    if(tot % maxPerPage > 0 || tot == 0)
        ++totPage;
    }
    return true;
}

bool ViewCompiti::sort()
{
    compiti = ctrl->codiciCompiti();
    return (Materia && sortbyMateria() ) && (classe && sortbyClasse());
}

void ViewCompiti::reloadWindow()
{
    compiti = ctrl->codiciCompiti();
    currPage = 1;
    int tot = compiti.size();
    totPage = tot/ maxPerPage;
    if(tot % maxPerPage > 0 || tot == 0)
        ++totPage;
}

int ViewCompiti::TotPage() const
{
    return totPage;
}

void ViewCompiti::parseCompitoFile(const QString & codice) const
{
    const QString formato = ctrl->getCompitoFormato(codice);
    if(formato == "xml"){
        CompitoParserXml temp(codice, ctrl);
        temp.parse();
        temp.setFixedSize(900,700);
        temp.exec();
    }
    else{
         viewPdfFile(ctrl->getPdfCompitoPath(codice));
    }
}


void ViewCompiti::FiltraRisultati()
{
    bool check = sort() ;
    if(check){
        reloadWindow();
    }
}

void ViewCompiti::commentaRisp(const QString &codice, int risposta) const
{
    popUpDialog temp(1,3);

    QTextEdit* t = new QTextEdit(&temp);
    temp.push_back_Widget(t);
    QPushButton* b = new QPushButton("Ok",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(accept()));
    temp.push_back_Widget(b);
    temp.setFixedSize(600,600);
    if(temp.exec() == QDialog::Accepted){
        if(!ctrl->commentaRispCompito(codice,risposta, temp.findChild<QTextEdit*>()-> toPlainText()))
        {
            QMessageBox::information(&temp, "Errore","E' avvenuto un errore");
        }
        else QMessageBox::information(&temp, "Errore","Commento salvato");
    }
}

void ViewCompiti::viewCommento(const QString &codice, int risposta) const
{
    if(!ctrl->HasRispCompitoCom(codice, risposta)){
        QMessageBox::information(const_cast<ViewCompiti*>(this), "","Non ci sono ancora commenti");
    }
    else{
        popUpDialog temp(1,1);
        QLabel* t = new QLabel(ctrl->getRispCompComment(codice,risposta));
        temp.push_back_Widget(t);
        temp.setFixedSize(700,500);
        temp.exec();
    }
}

void ViewCompiti::elimCompito(const QString &codice)
{
    if(QMessageBox::information(this, "ATTENZIONE!!!","Eliminando il compito/esercizio, non sarà più"
                                                    " possibile recuperarlo con i suoi elaborati.\n\n"
                                                    "Sei sicuro di voler continuare ?",
                             QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes){
        if(ctrl->eliminaCompito(codice)){
            QMessageBox::information(this, "","Eliminato con successo!");
            reloadWindow();
        }
        else QMessageBox::information(this, "Errore","E' avvenuto un errore");
    }
    else QMessageBox::information(this,"", "Annullato con successo!");
}

void ViewCompiti::Header()
{
    if(lay)
        delete lay;
    lay = new QGridLayout(this);
    QPushButton* b = new QPushButton("Torna indietro", this);
    b->setFixedSize(300,40);
    b->setStyleSheet("background-color: green; color: white;");
    connect(b,SIGNAL(clicked(bool)),this,SLOT(TornaIndietro()));
    lay->addWidget(b,0,0,1,1,Qt::AlignLeft);
    setLayout(lay);
}

void ViewCompiti::setTotPage(int tot)
{
    totPage = tot;
}

QGridLayout *ViewCompiti::giveLayout() const
{
    return lay;
}

void ViewCompiti::goNext()
{
    if(currPage < totPage)
    currPage++;
}

void ViewCompiti::goPrev()
{
    if(currPage > 1)
        currPage--;
}

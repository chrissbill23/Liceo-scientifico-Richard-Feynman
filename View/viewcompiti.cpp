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

int ViewCompiti::maxPerPage = 10;

ViewCompiti::ViewCompiti(ControllerCompitiUser *c) : Finestre(c), lay(0), Materia(0), classe(0), ctrl(c)
{
    compiti = ctrl->codiciCompiti();
    int tot = compiti.size();
    totPage = tot/ maxPerPage;
    if(tot % maxPerPage > 0 || tot == 0)
        ++totPage;
    currPage = 1;
    setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
}

QComboBox *ViewCompiti::Materie()
{
    if(Materia)
        delete Materia;
    Materia = new QComboBox(this);
    Materia->setFixedSize(300,40);
    Materia->setFont(QFont("Times",10));

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
    classe->setFixedSize(300,40);
    classe->setFont(QFont("Times",10));

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
        temp.setFixedSize(800,700);
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
    if(ctrl->HasRispCompitoCom(codice, risposta)){
        QMessageBox::information(0,"","Ha già commentato questo elaborato");
        return;
    }
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
        else QMessageBox::information(&temp, "","Commento salvato");
    }
}

void ViewCompiti::viewCommento(const QString &codice, int risposta) const
{
    if(!ctrl->HasRispCompitoCom(codice, risposta)){
        QMessageBox::information(0, "","Non ci sono ancora commenti");
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
    if(QMessageBox::information(0, "ATTENZIONE!!!","Eliminando il compito/esercizio, non sarà più"
                                                    " possibile recuperarlo con i suoi elaborati.\n\n"
                                                    "Sei sicuro di voler continuare ?",
                             QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes){
        if(ctrl->eliminaCompito(codice)){
            QMessageBox::information(0, "","Eliminato con successo!");
            FiltraRisultati();
        }
        else QMessageBox::information(0, "Errore","E' avvenuto un errore");
    }
    else QMessageBox::information(0,"", "Annullato con successo!");
}

void ViewCompiti::Header()
{
    if(lay)
        delete lay;
    lay = new QGridLayout(this);
    QPushButton* b = new QPushButton("Indietro", this);
    b->setFixedSize(150,40);
    b->setFont(QFont("Times",11));
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(TornaIndietro()));
    lay->addWidget(b,0,0,1,1,Qt::AlignLeft);
    setLayout(lay);
}

void ViewCompiti::setTotPage(int tot)
{
    totPage = tot;
}

void ViewCompiti::InfoCompito(const QString & code) const
{
    popUpDialog temp(1,17);
    temp.setFixedSize(700,500);


    QFont f("Times",14);
    f.setBold(true);
    QFont f2("Times",12);

    QLabel* lab = new QLabel("Data: ",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);
    const QString& date = ctrl->getCompitoData(code);
    lab = new QLabel(date, &temp);
    lab->setFont(f2);
    temp.push_back_Widget(lab);

    lab = new QLabel("Titolo: ",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);
    const QString& tit = ctrl->getCompitoTitolo(code);
    lab = new QLabel(tit, &temp);
    lab->setFont(f2);
    temp.push_back_Widget(lab);
    temp.setWindowTitle(tit);

    lab = new QLabel("Autore: ",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);
    lab = new QLabel(ctrl->getCompitoAutore(code), &temp);
    lab->setFont(f2);
    temp.push_back_Widget(lab);

    lab = new QLabel("Descrizione: ",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);
    lab = new QLabel(ctrl->getCompitoDescrizione(code), &temp);
    lab->setFont(f2);
    temp.push_back_Widget(lab);

    lab = new QLabel("Materia: ",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);
    lab = new QLabel(ctrl->getCompitoMateria(code), &temp);
    lab->setFont(f2);
    temp.push_back_Widget(lab);

    lab = new QLabel("Classi assegnate: ",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);
    lab = new QLabel(&temp);
    list<string> l = ctrl->classiCompito(code);
    for(list<string>:: const_iterator it4 = l.begin(); it4 != l.end(); ++ it4){
        lab->setText(lab->text() + QString::fromStdString(*it4)+". ");
    }
    lab->setFont(f2);
    temp.push_back_Widget(lab);

    temp.exec();
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

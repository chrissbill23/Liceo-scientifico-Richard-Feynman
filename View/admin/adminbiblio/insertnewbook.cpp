#include "insertnewbook.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include <QFileDialog>
#include <QMessageBox>
#include <algorithm>

int InsertNewBook::maxCategorie = 4;
void InsertNewBook::anniEdizioni()
{
    int anno = QDate::currentDate().year();

    annoEdizione->addItem("Seleziona anno edizione",-1);

    for(int i = anno; i >= 1920; --i)
        annoEdizione->addItem(QString::number(i),i);
}

void InsertNewBook::LoadCategorie()
{
  categorie.clear();
        vector<string> v = ctrl->CategorieBiblio();
        std::sort(v.begin(),v.end());
        for(int i = 0; i<maxCategorie; ++i){
            QComboBox* temp = new QComboBox(this);
            temp->addItem("Seleziona categoria "+QString::number(i+1), -1);
            for(vector<string>::const_iterator it = v.begin(); it != v.end(); ++it){
                const QString& cat = QString::fromStdString(*it);
                temp->addItem(cat,cat);
            }
            categorie.push_back(temp);
        }
}

InsertNewBook::InsertNewBook(ControllerAdminBiblio *c, QWidget *parent) : QDialog(parent), ctrl(c), form(new QScrollArea(this)),
    lay(new QVBoxLayout(this)),titolo(0), autore(0),copertina(0), file(0), annoEdizione(0),
    Descrizione(0)
{
    form->setWidget(loadDialog());
    form->setWidgetResizable(true);
    lay->addWidget(form);
}

QGroupBox *InsertNewBook::loadDialog()
{

    QGroupBox* temp = new QGroupBox;
    titolo = new QLineEdit(temp);
    autore = new QLineEdit(temp);
    copertina = new QLineEdit(temp);
    file = new QLineEdit(temp);
    annoEdizione = new QComboBox(this);
    anniEdizioni();
    Descrizione = new QTextEdit(this);
    LoadCategorie();

    QVBoxLayout* layTemp = new QVBoxLayout(temp);

    QLabel* lab = new QLabel("I campi contrassegnati (*) sono obbligatori", temp);
    lab->setFont(QFont("Times", 12));
    layTemp->addWidget(lab,0,Qt::AlignTop);

    QFont f("Times",14);

    lab = new QLabel("(*) Titolo: ", temp);
    lab->setFont(f);
    layTemp->addWidget(lab,0,Qt::AlignTop);
    layTemp->addWidget(titolo,0,Qt::AlignTop);

    lab = new QLabel("Autore: ", temp);
    lab->setFont(f);
    layTemp->addWidget(lab,0,Qt::AlignTop);
    layTemp->addWidget(autore,0,Qt::AlignTop);

    layTemp->addWidget(annoEdizione,0,Qt::AlignTop);

    lab = new QLabel("(*) Descrizione: ", temp);
    lab->setFont(f);
    layTemp->addWidget(lab,0,Qt::AlignTop);
    layTemp->addWidget(Descrizione,0,Qt::AlignTop);

    lab = new QLabel("Categorie ( un massimo di "+QString::number(maxCategorie)+"): ", temp);
    lab->setFont(f);
    layTemp->addWidget(lab,0,Qt::AlignTop);
    for(int i = 0; i < maxCategorie; ++i)
    layTemp->addWidget(categorie[i],0,Qt::AlignTop);

    lab = new QLabel("(*)Carica file (.pdf): ", temp);
    lab->setFont(f);
    layTemp->addWidget(lab,0,Qt::AlignTop);
    file->setFixedHeight(50);
    QPushButton* b = new QPushButton("Sfoglia",temp);
    b->setFixedSize(200,50);
    b->setFont(QFont("Times",11));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(loadFile()));
    QHBoxLayout* layTemp2 = new QHBoxLayout;
    layTemp2->addWidget(file,1);
    layTemp2->addWidget(b,0);
    layTemp->addLayout(layTemp2);

    lab = new QLabel("Copertina: ", temp);
    lab->setFont(f);
    layTemp->addWidget(lab,0,Qt::AlignTop);
    copertina->setFixedHeight(50);
    b = new QPushButton("Sfoglia",temp);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(loadCopertina()));
    b->setFixedSize(200,50);
    b->setFont(QFont("Times",11));
    layTemp2 = new QHBoxLayout;
    layTemp2->addWidget(copertina,1);
    layTemp2->addWidget(b,0);
    layTemp->addLayout(layTemp2);

    b = new QPushButton("Salva", temp);
    layTemp->addWidget(b,0,Qt::AlignTop);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(salva()));

    b = new QPushButton("Annulla", temp);
    layTemp->addWidget(b,0,Qt::AlignTop);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(close()));


    temp->setLayout(layTemp);

return temp;

}

void InsertNewBook::loadFile() const
{
    QString fileName = QFileDialog::getOpenFileName(file,
            tr("Seleziona il file"), "",
            tr(" (*.pdf)"));

        if (fileName.isEmpty())
            return;
        else {
            file->setText(fileName);
        }
}

void InsertNewBook::loadCopertina() const
{
    QString fileName = QFileDialog::getOpenFileName(file,
            tr("Seleziona il file"), "",
            tr(" (*.jpg)"));

        if (fileName.isEmpty())
            return;
        else {
            copertina->setText(fileName);
        }
}

void InsertNewBook::salva()
{
    const QString& tit = titolo->text();
    const QString& aut = autore->text();
    const QString& copert = copertina->text();
    const QString& fil = file->text();
    QString annoEd = "";
    if(annoEdizione->itemData(annoEdizione->currentIndex()).toInt() != -1)
     annoEd = annoEdizione->itemData(annoEdizione->currentIndex()).toString();
    const QString& descr = Descrizione->toPlainText();

    if(tit != "" && descr != ""  && fil != "" ){
        const QString& codice = ctrl->aggiungiNuovoLibro(tit,descr,fil);
        if(codice != ""){
            bool check = true;
            if(aut !="")
                check = ctrl->ModificaAutorelibro(codice,aut);
            if(annoEd !="")
                check = ctrl->ModificaAnnoEdizione(codice,annoEd);
            if(copert !="")
                check = ctrl->ModificaCopertinaLibro(codice, copert);

                for(unsigned int i = 0; i < categorie.size(); ++i){
                    const QString& ris = categorie[i]->itemData(categorie[i]->currentIndex()).toString();
                    if(ris != "-1")
                        check = ctrl->aggiungiCategoriaAlibro(codice,ris);
                }
                if(check){
                QMessageBox::information(this, "", "Salvato con successo!");
                QWidget* p = form->widget();
                if(p)
                    delete p;
                form->setWidget(loadDialog());
                form->setWidgetResizable(true);
                return;
            }
        }
       QMessageBox::information(this, "Errore", codice);

    }
    else QMessageBox::information(this, "Errore", "Tutti i campi obbligatori devono essere compilati");
}

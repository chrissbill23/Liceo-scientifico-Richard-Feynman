#include "updateinfobook.h"
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
int updateInfoBook::maxCategorie = 4;
void updateInfoBook::anniEdizioni()
{
    int anno = QDate::currentDate().year();

    annoEdizione->addItem(ctrl->daiAnnoEdizioneLibro(codebook),ctrl->daiAnnoEdizioneLibro(codebook));

    for(int i = anno; i >= 1920; --i)
        annoEdizione->addItem(QString::number(i),i);
}

void updateInfoBook::LoadCategorie()
{

          vector<string> l = ctrl->CategorieBiblio();
          std::sort(l.begin(),l.end());
          list<string> l2 = ctrl->daiCategorieLibro(codebook);
          list<string>::const_iterator it2 = l2.begin();
          for(int i = 0; i<maxCategorie; ++i){

              QComboBox* temp = new QComboBox(this);
              if(it2 != l2.end()){
              temp->addItem(QString::fromStdString(*it2), QString::fromStdString(*it2));
              ++it2;
              }
              else
                  temp->addItem("Seleziona categoria "+QString::number(i+1), -1);
              for(vector<string>::const_iterator it = l.begin(); it != l.end(); ++it){
                  const QString& cat = QString::fromStdString(*it);
                  temp->addItem(cat,cat);
              }
              categorie.push_back(temp);
          }
}

updateInfoBook::updateInfoBook(const QString &codice, ControllerAdminBiblio* c, QWidget* parent) :QDialog(parent), ctrl(c),codebook(codice),
    form(new QScrollArea(this)),
    lay(new QVBoxLayout(this)),titolo(0), autore(0),copertina(0), annoEdizione(0), Descrizione(0)
{
    form->setWidget(loadDialog());
    form->setWidgetResizable(true);
    lay->addWidget(form);
}

QGroupBox *updateInfoBook::loadDialog()
{

    QGroupBox* temp = new QGroupBox;
    titolo = new QLineEdit(temp);
    autore = new QLineEdit(temp);
    copertina = new QLineEdit(temp);
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
    titolo->setText(ctrl->daiTitoloLibro(codebook));
    layTemp->addWidget(titolo,0,Qt::AlignTop);

    lab = new QLabel("Autore: ", temp);
    lab->setFont(f);
    layTemp->addWidget(lab,0,Qt::AlignTop);
    autore->setText(ctrl->daiAutoreLibro(codebook));
    layTemp->addWidget(autore,0,Qt::AlignTop);

    lab = new QLabel("Anno Edizione: ", temp);
    lab->setFont(f);
    layTemp->addWidget(lab,0,Qt::AlignTop);
    layTemp->addWidget(annoEdizione,0,Qt::AlignTop);

    lab = new QLabel("(*) Descrizione: ", temp);
    lab->setFont(f);
    layTemp->addWidget(lab,0,Qt::AlignTop);
    Descrizione->setText(ctrl->daiDescrizioneLibro(codebook));
    layTemp->addWidget(Descrizione,0,Qt::AlignTop);

    lab = new QLabel("Categorie ( un massimo di "+QString::number(maxCategorie)+"): ", temp);
    lab->setFont(f);
    layTemp->addWidget(lab,0,Qt::AlignTop);
    for(int i = 0; i < maxCategorie; ++i)
    layTemp->addWidget(categorie[i],0,Qt::AlignTop);

    lab = new QLabel("Copertina: ", temp);
    lab->setFont(f);
    layTemp->addWidget(lab,0,Qt::AlignTop);
    copertina->setFixedHeight(50);
    QPushButton* b = new QPushButton("Sfoglia",temp);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(loadCopertina()));
    b->setFixedSize(200,50);
    b->setFont(QFont("Times",11));
    QHBoxLayout* layTemp2 = new QHBoxLayout;
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

void updateInfoBook::loadCopertina() const
{
    QString fileName = QFileDialog::getOpenFileName(copertina,
            tr("Seleziona il file"), "",
            tr(" (*.jpg)"));

        if (fileName.isEmpty())
            return;
        else {
            copertina->setText(fileName);
        }
}

void updateInfoBook::salva()
{
    const QString& tit = titolo->text();
    const QString& aut = autore->text();
    const QString& copert = copertina->text();
    QString annoEd = "";
    if(annoEdizione->itemData(annoEdizione->currentIndex()).toInt() != -1)
     annoEd = annoEdizione->itemData(annoEdizione->currentIndex()).toString();
    const QString& descr = Descrizione->toPlainText();

    if(tit != "" && descr != ""){
        const QString& codice = codebook;
            bool check = true;
            if(tit != "")
                check = ctrl->ModificaTitololibro(codice,tit);
            if(descr != "")
                check = ctrl->ModificaDescrizione(codice,descr);
            if(aut !="")
                check = ctrl->ModificaAutorelibro(codice,aut);
            if(annoEd !="")
                check = ctrl->ModificaAnnoEdizione(codice,annoEd);
            if(copert !="")
                check = ctrl->ModificaCopertinaLibro(codice, copert);

            check = ctrl->eliminaCategorieLibro(codebook);
                for(unsigned int i = 0; i < categorie.size() && check; ++i){
                    const QString& ris = categorie[i]->itemData(categorie[i]->currentIndex()).toString();
                    if(ris != "-1")
                        check = ctrl->aggiungiCategoriaAlibro(codice,ris);
                }
                if(check){
                QMessageBox::information(0, "", "Salvato con successo!");
                close();
            }
           else QMessageBox::information(0, "Errore", "Errore fatale nel salvataggio");

    }
    else QMessageBox::information(0, "Errore", "Tutti i campi obbligatori devono essere compilati");
}

#include "createfilecompito.h"
#include "../../../Controller/controllerprof.h"
#include "createcompito.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QRegExp>

QWidget *createFileCompito::InsertInMateria()
{
    if(Materia)
        delete Materia;
    Materia = new QComboBox(this);
    Materia->setFixedSize(300,50);
    Materia->setFont(QFont("Times",12));

    Materia->addItem("Seleziona la materia", -1);

    list<string> l = ctrl->MaterieInsegnate();

    for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it){
        Materia->addItem(QString::fromStdString(*it), QString::fromStdString(*it));
    }
    return Materia;
}

QWidget *createFileCompito::InsertInClasse()
{
    if(classe)
        delete classe;
    classe = new QComboBox(this);
    classe->setFixedSize(300,50);
    classe->setFont(QFont("Times",12));

    classe->addItem("Seleziona la classe", -1);

    vector<string> v = ctrl->Classi();

    for(vector<string>::const_iterator it = v.begin(); it != v.end(); ++it){
        classe->addItem(QString::fromStdString(*it), QString::fromStdString(*it));
    }

    return classe;
}

bool createFileCompito::isOk()
{
    error->setText("");
    error->setStyleSheet("color: red;");

    if(Materia->itemData(Materia->currentIndex()).toInt() == -1){
       error->setText("Errore: Selezionare la materia");
       return false;
    }
    if(classe->itemData(classe->currentIndex()).toInt() == -1){
       error->setText("Errore: Selezionare la classe");
       return false;
    }
    if(titolo->text() == ""){
       error->setText("Errore: Inserire un titolo");
       return false;
    }
    return true;
}

createFileCompito::createFileCompito(ControllerProf* c, QWidget* parent) :  QGroupBox(parent), ctrl(c),
    Materia(0), classe(0), titolo(0), Descrizione(0),
    lay(0),error(0), genitore(dynamic_cast<CreateCompito*>(parent))
{

}

void createFileCompito::setMessage(QLabel *p)
{
    if(p){
    if(error){
        delete error;
    }
    error = p;
    lay->insertWidget(0,error,0);
    }
}

void createFileCompito::loadHeader()
{
    if(error)
        delete error;
    if(lay)
        delete lay;
    if(Descrizione)
        delete Descrizione;
    if(titolo)
        delete titolo;
    if(classe)
        delete classe;
    if(Materia)
        delete Materia;
    QWidget* p = InsertInMateria();
    QWidget* p2 = InsertInClasse();
    titolo = new QLineEdit(this);
    Descrizione = new QTextEdit(this);
    lay = new QVBoxLayout(this);
    error = new QLabel("",this);

    error->setFont(QFont("Times", 13));
    lay->addWidget(error,0);

    lay->addWidget(p,0,Qt::AlignTop|Qt::AlignCenter);
    lay->addWidget(p2,0,Qt::AlignTop|Qt::AlignCenter);

    QLabel* lab = new QLabel("Titolo ( 50 caratteri al massimo ): ", titolo);
    lab->setFont(QFont("Times",14));
    lay->addWidget(lab,0,Qt::AlignTop);
    titolo->setFixedHeight(50);
    titolo->setMaxLength(50);
    titolo->setFont(QFont("Times",14));
    lay->addWidget(titolo,0,Qt::AlignTop);

    lab = new QLabel("Breve descrizione: ", Descrizione);
    lab->setFont(QFont("Times",14));
    lay->addWidget(lab,0,Qt::AlignTop);
    Descrizione->setFont(QFont("Times",14));
    lay->addWidget(Descrizione,0,Qt::AlignTop);
}

ControllerProf *createFileCompito::giveController() const
{
    return ctrl;
}

QComboBox *createFileCompito::giveMateria() const
{
    return Materia;
}

QComboBox *createFileCompito::giveClasse() const
{
    return classe;
}

QLineEdit *createFileCompito::giveTitolo() const
{
    return titolo;
}

QTextEdit *createFileCompito::giveDescr() const
{
    return Descrizione;
}

QVBoxLayout *createFileCompito::giveLayout() const
{
    return lay;
}

QLabel *createFileCompito::giveError() const
{
    return error;
}

CreateCompito *createFileCompito::giveGrandParent() const
{
    return genitore;
}

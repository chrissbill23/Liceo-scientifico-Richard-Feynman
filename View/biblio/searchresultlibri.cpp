#include "searchresultlibri.h"
#include "bibliobutton.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>
#include <QComboBox>
#include <QScrollArea>
#include <QDate>
#include <algorithm>

int SearchResultLibri::maxPerPage = 10;
void SearchResultLibri::InsertInCategoriaLibri()
{
    vector<string> v = getController()->CategorieBiblio();
    std::sort(v.begin(),v.end());

    categoriaLibri->addItem("Tutte le categorie", -1);

    for(vector<string>::const_iterator it = v.begin(); it != v.end(); ++it){
        const QString& cat = QString::fromStdString(*it);
        categoriaLibri->addItem(cat,cat);
    }

}

void SearchResultLibri::InserInAnnoEdizione()
{
    int anno = QDate::currentDate().year();

    annoEdizione->addItem("Anni edizione",-1);

    for(int i = anno; i >= 1920; --i)
        annoEdizione->addItem(QString::number(i),i);
}

void SearchResultLibri::setCodiciLibri(const vector<string> &v)
{
    codiciLibri.clear();
    codiciLibri = v;
}

QGroupBox *SearchResultLibri::loadPage(int indice)
{
    QGroupBox* contenuto = new QGroupBox;
    contenuto->setStyleSheet("QGroupBox{border: 0;}");

    QGridLayout* temp = new QGridLayout(contenuto);
    contenuto->setLayout(temp);

    QLabel* title = new QLabel("LIBRI", contenuto);
    title->setStyleSheet("QLabel{"
                         "padding-bottom: 0.4em; "
                         "border-bottom: 2px solid black;"
                         "border-radius: 0;}");

    title->setFont(QFont("Times", 15));
    title->setFixedHeight(50);

    temp->addWidget(title,0,0,1,6);


    QFont f("Times", 13);

    QLabel* lab = new QLabel("Codice Libro", contenuto);
    lab->setFont(f);
    temp->addWidget(lab,3,0,1,1,Qt::AlignTop);

    lab = new QLabel("Titolo", contenuto);
    lab->setFont(f);
    temp->addWidget(lab,3,1,1,1,Qt::AlignTop);

    lab = new QLabel("Autore", contenuto);
    lab->setFont(f);
    temp->addWidget(lab,3,2,1,1,Qt::AlignTop);

    lab = new QLabel("Anno Edizione", contenuto);
    lab->setFont(f);
    temp->addWidget(lab,3,3,1,1,Qt::AlignTop);

    int tot = codiciLibri.size();
    if(tot > indice){
        Controller* ctrl = getController();
        lab = new QLabel(QString::number(codiciLibri.size())+" risultati", contenuto);
        if(searchBox->text() != "")
            lab->setText(lab->text()+" per \""+searchBox->text()+"\"");
        lab->setFont(f);
        temp->addWidget(lab,2,0,1,3,Qt::AlignTop);

        int row = 4;
        int it = indice;
        for(; it < tot && it < maxPerPage*currPage; ++it){
            const QString& code = QString::fromStdString(codiciLibri[it]);
            lab = new QLabel(code, contenuto);
            lab->setFont(f);
            temp->addWidget(lab,row,0,1,1,Qt::AlignTop);

            lab = new QLabel(ctrl->daiTitoloLibro(code), contenuto);
            lab->setFont(f);
            temp->addWidget(lab,row,1,1,1,Qt::AlignTop);

            lab = new QLabel(ctrl->daiAutoreLibro(code), contenuto);
            lab->setFont(f);
            temp->addWidget(lab,row,2,1,1,Qt::AlignTop);

            lab = new QLabel(ctrl->daiAnnoEdizioneLibro(code), contenuto);
            lab->setFont(f);
            temp->addWidget(lab,row,3,1,1,Qt::AlignTop);

            bibliobutton* b = new bibliobutton("vedi libro", code,false,"",this);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(100,30);
            b->setStyleSheet("QPushButton{"
                             "background-color: green;"
                             "border: 2px solid;"
                             "border-radius: 5px 5px 5px 5px; "
                             "color: white;}"
                             "QPushButton:pressed {"
                             "background-color:#003300;}");
            connect(b,SIGNAL(clicked(bool)),b,SLOT(viewLibro()));
            temp->addWidget(b,row,4,1,1,Qt::AlignTop);

            b = new bibliobutton("info libro", code,false,"",this);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(100,30);
            b->setStyleSheet("QPushButton{"
                             "background-color: green;"
                             "border: 2px solid;"
                             "border-radius: 5px 5px 5px 5px; "
                             "color: white;}"
                             "QPushButton:pressed {"
                             "background-color:#003300;}");
            connect(b,SIGNAL(clicked(bool)),b,SLOT(viewInfoLibro()));
            temp->addWidget(b,row,5,1,1,Qt::AlignTop);

            ++row;
        }

        lab = new QLabel("pagina "+QString::number(currPage)+"/"+QString::number(totPage));
        lab->setFont(f);
        temp->addWidget(lab,row+2,2,1,1,Qt::AlignHCenter);
        QIcon i1;
        if(currPage > 1){
            i1.addPixmap(QPixmap(":/Database/immagini/prev.png"));
            QPushButton* b = new QPushButton(contenuto);
            b->setIcon(i1);
            b->setFixedSize(200,40);
            b->setIconSize(QSize(200,40));
            b->setStyleSheet("QPushButton{"
                             "background-color: #336699;"
                             "border: 2px solid;"
                             "border-radius: 5px 5px 5px 5px; "
                             "color: white;}"
                             "QPushButton:pressed {"
                             "background-color:#003300;}");
            b->setCursor(QCursor(Qt::PointingHandCursor));
            temp->addWidget(b,row+2,0,1,1,Qt::AlignLeft);
            connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
        }

        if(it < tot){
            i1.addPixmap(QPixmap(":/Database/immagini/next.png"));
            QPushButton* b2 = new QPushButton(contenuto);
            b2->setIcon(i1);
            b2->setFixedSize(200,40);
            b2->setIconSize(QSize(200,40));
            b2->setStyleSheet("QPushButton{"
                              "background-color: #336699;"
                              "border: 2px solid;"
                              "border-radius: 5px 5px 5px 5px; "
                              "color: white;}"
                              "QPushButton:pressed {"
                              "background-color:#003300;}");
            b2->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b2,SIGNAL(clicked(bool)),this,SLOT(goNext()));
            temp->addWidget(b2,row+2,5,1,1,Qt::AlignRight);
        }



    }
    else{
        lab = new QLabel("0 Libri trovati", contenuto);
        lab->setFont(f);
        temp->addWidget(lab,2,0,1,1);
    }
    return contenuto;
}

SearchResultLibri::SearchResultLibri(Controller *c, QWidget *parent):FinestreBiblioteca(c,parent), head(0),sc(0),
categoriaLibri(0), annoEdizione(0), searchBox(new QLineEdit(this)), lay(0),currPage(1),totPage(1)
{
    codiciLibri = getController()->CodiciLibri();
    setStyleSheet("background-color: none;");
}

vector<string> SearchResultLibri::daiCodiciLibri() const
{
    return codiciLibri;
}

QVBoxLayout *SearchResultLibri::giveLayout() const
{
    return lay;
}

void SearchResultLibri::searchBook(const QString &key)
{
    codiciLibri = getController()->findCodiciBook(key);
    searchBox->setText(key);
}

void SearchResultLibri::loadWindow()
{
    if(!sc)
        sc = new QScrollArea(this);
    FinestreBiblioteca::Header();
    Header();
    BodyAndFooter();
    setWindowTitle("Tutti i libri");
}

void SearchResultLibri::reloadWindow()
{
    if(!sc)
        sc = new QScrollArea(this);
    BodyAndFooter();
}

void SearchResultLibri::reloadCodici()
{
    codiciLibri = getController()->CodiciLibri();
}

void SearchResultLibri::Header()
{
   head = new QGroupBox(this);
   head->setStyleSheet("QGroupBox{border: 0;}");
   categoriaLibri = new QComboBox;
   InsertInCategoriaLibri();
   annoEdizione = new QComboBox;
   InserInAnnoEdizione();

   if(FinestreBiblioteca:: giveLayout()){
   lay = new QVBoxLayout;
   }
   else lay = new QVBoxLayout(this);

   categoriaLibri->setStyleSheet("border: 2px solid white; background-color: white; color: black;");
   categoriaLibri->setFont(QFont("Times",12));
   connect(categoriaLibri,SIGNAL(currentIndexChanged(int)),this,SLOT(Sort()));
   annoEdizione->setStyleSheet("border: 2px solid white; background-color: white; color: black;");
   annoEdizione->setFont(QFont("Times",12));
   connect(annoEdizione,SIGNAL(currentIndexChanged(int)),this,SLOT(Sort()));

   QGridLayout* temp = new QGridLayout(head);

   QLabel* lab = new QLabel("Ordina per: ", head);
   lab->setFont(QFont("Times",13));
   temp->addWidget(lab,1,0,1,1);

   temp->addWidget(categoriaLibri, 1,1,1,1);

   InserInAnnoEdizione();

   temp->addWidget(annoEdizione,1,2,1,1);

   searchBox->setPlaceholderText("Cerca un libro");
   searchBox-> setStyleSheet("width: 15em; "
                             "height: 2em; "
                             "background-color: white; "
                             "border-radius: 0;"
                             "color: black;"
                             "padding-left: 0.5em;");
   searchBox->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
   searchBox->setFont(QFont("Times",11));
   QPushButton* b = new QPushButton("Cerca", head);
   b->setFixedSize(150, 30);
   b->setCursor(QCursor(Qt::PointingHandCursor));
   b->setStyleSheet("QPushButton{"
                           "background-color: green;"
                           "border: 2px solid;"
                           "border-radius: 5px 5px 5px 5px; "
                           "color: white;}"
                           "QPushButton:pressed {"
                           "background-color:#003300;}");
   connect(b,SIGNAL(clicked(bool)),this,SLOT(Sort()));

   temp->addWidget(searchBox,1,3);
   temp->addWidget(b,1,4);
   head->setLayout(temp);

   lay->addWidget(head);
   if(FinestreBiblioteca::giveLayout()){
     FinestreBiblioteca::giveLayout()->addLayout(lay,1,0,1,4);
   }
   else
   setLayout(lay);



}

void SearchResultLibri::BodyAndFooter()
{
    currPage = 1;
    totPage = codiciLibri.size() / maxPerPage;
    if(codiciLibri.size() % maxPerPage != 0 || totPage == 0)
        ++totPage;
    sc->setWidget(loadPage(0));
    sc->setWidgetResizable(true);
    lay->addWidget(sc);
}

void SearchResultLibri::viewPdfFile(const QString & path) const
{
    const QString& path2 = getController()->daiPercorsoLibro(path);
    Finestre::viewPdfFile(path2);
}

void SearchResultLibri::Sort()
{
    Controller* ctrl = getController();
    codiciLibri = ctrl->CodiciLibri();
    if(searchBox->text() != "")
        codiciLibri = ctrl->findCodiciBook(searchBox->text());
    else codiciLibri = ctrl->CodiciLibri();
   const QString& cat = categoriaLibri->itemData(categoriaLibri->currentIndex()).toString();
   const QString& anno = annoEdizione->itemData(annoEdizione->currentIndex()).toString();

   if(cat != "-1")
       ctrl->SortLibriByCategoria(codiciLibri,cat);
   if(anno != "-1")
        ctrl->SortLibriByAnnoEdizione(codiciLibri,anno);

   reloadWindow();
}

void SearchResultLibri::SortCan()
{
    Controller* ctrl = getController();
    codiciLibri = ctrl->CodiciLibri();
    if(searchBox->text() != "")
        codiciLibri = ctrl->findCodiciBook(searchBox->text());
    else codiciLibri = ctrl->CodiciLibri();
   const QString& cat = categoriaLibri->itemData(categoriaLibri->currentIndex()).toString();
   const QString& anno = annoEdizione->itemData(annoEdizione->currentIndex()).toString();

   if(cat != "-1")
       ctrl->SortLibriByCategoria(codiciLibri,cat);
   if(anno != "-1")
        ctrl->SortLibriByAnnoEdizione(codiciLibri,anno);
}

void SearchResultLibri::goNext()
{
    currPage++;
    sc->setWidget(loadPage((currPage-1)*maxPerPage));
    sc->setWidgetResizable(true);
}

void SearchResultLibri::goPrev()
{
    if(currPage > 1){
        currPage--;
        sc->setWidget(loadPage((currPage-1)*maxPerPage));
        sc->setWidgetResizable(true);
    }
}

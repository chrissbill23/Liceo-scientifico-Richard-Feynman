#ifndef SEARCHRESULTLIBRI_H
#define SEARCHRESULTLIBRI_H

#include "finestrebiblioteca.h"
#include "../../Controller/Controller.h"
class QGroupBox;
class QComboBox;
class QVBoxLayout;
class QLineEdit;
class QScrollArea;
class SearchResultLibri : public FinestreBiblioteca
{
    Q_OBJECT
private:
   vector<string> codiciLibri;
   QGroupBox* head;
   QScrollArea* sc;
   QComboBox* categoriaLibri;
   QComboBox* annoEdizione;
   QLineEdit* searchBox;
   QVBoxLayout* lay;
   int currPage;
   int totPage;

   void InsertInCategoriaLibri();
   void InserInAnnoEdizione();
protected:
   static int maxPerPage;
   void setCodiciLibri(const vector<string>& v);
public:
    SearchResultLibri(Controller* c, QWidget* parent = 0);
    vector<string> daiCodiciLibri()const;
    QVBoxLayout* giveLayout()const;
    void searchBook(const QString &key);
    void loadWindow();
    void reloadCodici();
protected:
    void Header();
    void BodyAndFooter();
    virtual QGroupBox* loadPage(int);
public slots:
    void reloadWindow();
    void viewPdfFile(const QString&)const;
    void Sort();
    void SortCan();
    virtual void goNext();
    virtual void goPrev();
};

#endif // SEARCHRESULTLIBRI_H

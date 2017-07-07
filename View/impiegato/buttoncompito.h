#ifndef BUTTONCOMPITO_H
#define BUTTONCOMPITO_H

#include <QPushButton>
class ViewCompiti;
class buttonCompito : public QPushButton
{
    Q_OBJECT
private:
    ViewCompiti* fi;
    QString codice;
    bool risposta;
    int Indicerisposta;
    QString pathRisposta;
public:
    buttonCompito(const QString& text, const QString& c, ViewCompiti *parent, bool r = false, int i = -1, const QString& p ="" );
public slots:
    void cancellaCompito()const;
    void ShowCompito()const;
    void viewElaborati()const;
    void viewElaborato() const;
    void commentaRispCompito()const;
    void viewcommentRisp()const;
    void elimCompito();
    void aggiungiClasse();
    void Dettagli()const;
};

#endif // BUTTONCOMPITO_H

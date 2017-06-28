#-------------------------------------------------
#
# Project created by QtCreator 2016-12-15T13:02:13
#
#-------------------------------------------------

QT       += core gui xml printsupport

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = progetto-pao-2017
TEMPLATE = app


SOURCES += main.cpp\
    Modello/Utente.cpp \
    Modello/impiegato.cpp \
    Modello/studente.cpp \
    Modello/filexml.cpp \
    View/login.cpp \
    Controller/controllerstud.cpp \
    Controller/controllerprof.cpp \
    View/studenti/homepagestud.cpp \
    Controller/controllerimpiegato.cpp \
    Controller/loginController.cpp \
    Controller/Controller.cpp \
    View/impiegato/segr/homepagesegretari.cpp \
    Modello/biblioteca.cpp \
    View/finestre.cpp \
    View/studenti/finestrestudenti.cpp \
    View/stackfinestre.cpp \
    View/impiegato/finestreimpiegato.cpp \
    Modello/professore.cpp \
    View/impiegato/segr/finestresegretari.cpp \
    Modello/segretario.cpp \
    Controller/controllersegretario.cpp \
    View/impiegato/prof/finestreprof.cpp \
    View/impiegato/prof/homepageprof.cpp \
    Modello/presidente.cpp \
    Controller/controllerpreside.cpp \
    View/impiegato/presid/finestrepreside.cpp \
    View/impiegato/presid/homepagepreside.cpp \
    Modello/messaggio.cpp \
    Modello/email.cpp \
    Modello/admin.cpp \
    View/admin/finestreadmin.cpp \
    Controller/controlleradmin.cpp \
    View/biblio/finestrebiblioteca.cpp \
    View/biblio/homebiblio.cpp \
    View/impiegato/segr/formaddstudent.cpp \
    View/impiegato/segr/editremovestud.cpp \
    View/impiegato/inviamessdialog.cpp \
    View/impiegato/tuttiimess.cpp \
    View/impiegato/messaggioview.cpp \
    View/impiegato/buttonmail.cpp \
    Modello/contattomail.cpp \
    View/gruppoview.cpp \
    View/studenti/homegruppostud.cpp \
    View/tuttiipostgruppo.cpp \
    Modello/gruppo.cpp \
    View/buttongroup.cpp \
    View/post.cpp \
    View/searchgroup.cpp \
    View/popupdialog.cpp \
    View/impiegato/agendabox.cpp \
    View/impiegato/notifichemailbox.cpp \
    View/impiegato/listamail.cpp \
    View/impiegato/prof/compitiniwidgbox.cpp \
    View/impiegato/prof/createcompito.cpp \
    View/impiegato/prof/createxmlcompito.cpp \
    View/impiegato/prof/domandarispmult.cpp \
    View/impiegato/prof/domandaaperta.cpp \
    View/impiegato/prof/domandecompito.cpp \
    View/impiegato/prof/loadpdfcompito.cpp \
    View/impiegato/prof/createfilecompito.cpp \
    View/impiegato/buttoncompito.cpp \
    View/viewcompiti.cpp \
    View/impiegato/prof/viewcompitiprof.cpp \
    View/compitoparser.cpp \
    View/compitoparserxml.cpp \
    View/studenti/viewcompitistud.cpp \
    Modello/adminbiblio.cpp \
    Controller/controlleradminbiblio.cpp \
    View/biblio/bibliobutton.cpp \
    View/biblio/searchresultlibri.cpp \
    View/biblio/primopianowidg.cpp \
    View/biblio/tuttelecategorie.cpp \
    View/impiegato/segr/buttongeststud.cpp \
    View/impiegato/segr/formeditstudinfo.cpp \
    Modello/gruppouser.cpp \
    Controller/controllergruppouser.cpp \
    View/studenti/personalspacegroupstud.cpp \
    View/formaddpostgroup.cpp \
    View/groupboxrispostepost.cpp \
    View/impiegato/presid/gestionepersonale.cpp \
    View/impiegato/presid/gestioneprofgroupbox.cpp \
    View/impiegato/presid/gestionesegrgroupbox.cpp \
    View/impiegato/presid/formaddimpiegato.cpp \
    View/impiegato/presid/buttongestimp.cpp \
    View/impiegato/presid/gestclassi.cpp \
    View/impiegato/presid/buttongestclassi.cpp \
    View/admin/adminbiblio/buttonadminbiblio.cpp \
    View/admin/adminbiblio/finestreadminbiblio.cpp \
    View/admin/adminbiblio/gestionecat.cpp \
    View/admin/adminbiblio/gestionelibri.cpp \
    View/admin/adminbiblio/gestioneprimopiano.cpp \
    View/admin/adminbiblio/homepageadminbiblio.cpp \
    View/admin/adminbiblio/insertnewbook.cpp \
    View/admin/adminbiblio/updateinfobook.cpp \
    View/admin/adminbiblio/updatelogo.cpp \
    View/admin/adminsist/finestreadminsist.cpp \
    View/admin/adminsist/homepageadminsist.cpp \
    Modello/adminsistema.cpp \
    Controller/controlleradminsistema.cpp \
    Modello/compitiuser.cpp \
    Controller/controllercompitiuser.cpp \
    View/admin/adminsist/formaddpreside.cpp \
    View/admin/adminsist/gestgruppi.cpp \
    View/admin/adminsist/formeditgroup.cpp \
    View/admin/adminsist/gestpostsgroup.cpp

HEADERS  += \
    Modello/Utente.h \
    Modello/impiegato.h \
    Modello/studente.h \
    Modello/container.h \
    Modello/filexml.h \
    View/login.h \
    Controller/controllerstud.h \
    Controller/controllerprof.h \
    View/studenti/homepagestud.h \
    Controller/controllerimpiegato.h \
    Controller/loginController.h \
    Controller/Controller.h \
    View/impiegato/segr/homepagesegretari.h \
    Modello/biblioteca.h \
    View/finestre.h \
    View/studenti/finestrestudenti.h \
    View/stackfinestre.h \
    View/impiegato/finestreimpiegato.h \
    View/impiegato/segr/finestresegretari.h \
    Controller/controllersegretario.h \
    Modello/professore.h \
    Modello/segretario.h \
    View/impiegato/prof/finestreprof.h \
    View/impiegato/prof/homepageprof.h \
    Modello/presidente.h \
    Controller/controllerpreside.h \
    View/impiegato/presid/finestrepreside.h \
    View/impiegato/presid/homepagepreside.h \
    Modello/admin.h \
    Modello/messaggio.h \
    Modello/email.h \
    View/admin/finestreadmin.h \
    Controller/controlleradmin.h \
    View/biblio/finestrebiblioteca.h \
    View/biblio/homebiblio.h \
    View/impiegato/segr/formaddstudent.h \
    View/impiegato/segr/editremovestud.h \
    View/impiegato/inviamessdialog.h \
    View/impiegato/tuttiimess.h \
    View/impiegato/messaggioview.h \
    View/impiegato/buttonmail.h \
    Modello/contattomail.h \
    View/gruppoview.h \
    View/studenti/homegruppostud.h \
    View/tuttiipostgruppo.h \
    Modello/gruppo.h \
    View/buttongroup.h \
    View/post.h \
    View/searchgroup.h \
    View/popupdialog.h \
    View/impiegato/agendabox.h \
    View/impiegato/notifichemailbox.h \
    View/impiegato/listamail.h \
    View/impiegato/prof/compitiniwidgbox.h \
    View/impiegato/prof/createcompito.h \
    View/impiegato/prof/createxmlcompito.h \
    View/impiegato/prof/domandarispmult.h \
    View/impiegato/prof/domandaaperta.h \
    View/impiegato/prof/domandecompito.h \
    View/impiegato/prof/loadpdfcompito.h \
    View/impiegato/prof/createfilecompito.h \
    View/impiegato/buttoncompito.h \
    View/viewcompiti.h \
    View/impiegato/prof/viewcompitiprof.h \
    View/compitoparser.h \
    View/compitoparserxml.h \
    View/studenti/viewcompitistud.h \
    Modello/adminbiblio.h \
    Controller/controlleradminbiblio.h \
    View/biblio/bibliobutton.h \
    View/biblio/searchresultlibri.h \
    View/biblio/primopianowidg.h \
    View/biblio/tuttelecategorie.h \
    View/impiegato/segr/buttongeststud.h \
    View/impiegato/segr/formeditstudinfo.h \
    Modello/gruppouser.h \
    Controller/controllergruppouser.h \
    View/studenti/personalspacegroupstud.h \
    View/formaddpostgroup.h \
    View/groupboxrispostepost.h \
    View/impiegato/presid/gestionepersonale.h \
    View/impiegato/presid/gestioneprofgroupbox.h \
    View/impiegato/presid/gestionesegrgroupbox.h \
    View/impiegato/presid/formaddimpiegato.h \
    View/impiegato/presid/buttongestimp.h \
    View/impiegato/presid/gestclassi.h \
    View/impiegato/presid/buttongestclassi.h \
    View/admin/adminbiblio/buttonadminbiblio.h \
    View/admin/adminbiblio/finestreadminbiblio.h \
    View/admin/adminbiblio/gestionecat.h \
    View/admin/adminbiblio/gestionelibri.h \
    View/admin/adminbiblio/gestioneprimopiano.h \
    View/admin/adminbiblio/homepageadminbiblio.h \
    View/admin/adminbiblio/insertnewbook.h \
    View/admin/adminbiblio/updateinfobook.h \
    View/admin/adminbiblio/updatelogo.h \
    View/admin/adminsist/finestreadminsist.h \
    View/admin/adminsist/homepageadminsist.h \
    Modello/adminsistema.h \
    Controller/controlleradminsistema.h \
    Modello/compitiuser.h \
    Controller/controllercompitiuser.h \
    View/admin/adminsist/formaddpreside.h \
    View/admin/adminsist/gestgruppi.h \
    View/admin/adminsist/formeditgroup.h \
    View/admin/adminsist/gestpostsgroup.h

DISTFILES +=

RESOURCES += \
    file.qrc



#ifndef GRUPPO_H
#define GRUPPO_H

#include "filexml.h"
class Gruppo
{
private:
    class Post{
    private:
        class risposta{
        public:
            string data;
            string membro;
            string testo;
            risposta(const string& d, const string &m, const string& t);
        };
        vector<risposta>v;
    public:
        string pathtoDb;
        string data;
        string autore;
        string titolo;
        string testo;
        Post(const string& path);
        int totRisposte()const;
        string daiDataRisposta(unsigned int i)const;
        string daiAutoreRisposta(unsigned int i)const;
        string daiTestoRisposta(unsigned int i)const;
        bool IsThereAnswOf(const string& membro)const;
        bool addRisposta(const string& data, const string& utente, const string& testo);

    };

filexml file;
vector<Post> v;
public:
    Gruppo(string pathDB);
    Gruppo();
    string daiNome()const;
    int totPost()const;
    int totRisposteAPost(unsigned int i)const;
    string daiDataPost(unsigned int i)const;
    string daiAutorePost(unsigned int i)const;
    string daiTitoloPost(unsigned int i)const;
    string daiTestoPost(unsigned int i)const;
    string daiDataRisposta(unsigned int i, unsigned int j)const;
    string daiAutoreRisposta(unsigned int i, unsigned int j)const;
    string daiTestoRisposta(unsigned int i, unsigned int j)const;
    list<string> daiRispostaAPost(unsigned int i, int j)const;
    list<string> daiMembri()const;
    bool addMember(const string& nUtente);
    bool addPost(const string& data, const string& autore,
                 const string& titolo, const string& testo);
    bool addRispostaToPost(unsigned int i, const string& data, const string& utente, const string& testo);
    vector<int> daiIndexesPostOf(const string&)const;
    vector<int> daiIndexesPostWithAnswOf(const string&)const;
    vector<int> searchPost(const string& keyword)const;
    bool removeMember(const string & member);
    bool removePost(unsigned int i);
    const filexml& InfoGruppo()const;
};

#endif // GRUPPO_H

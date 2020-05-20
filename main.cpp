#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <exception>
#include <typeinfo>
#include <set>

class InvalidSum : public std::exception
{
    const char* exceptie;
public:
    InvalidSum(const char* exceptie ="") : exceptie(exceptie) {}

    const char* what() const noexcept
    {
        return exceptie;
    }
};


template <class T>
class Gestiune
{
    static int nr_plati;
    T* plati;
    friend T;
public:
    Gestiune()
    {
        plati = new T[100];
    }

    ~Gestiune()
    {
        delete[] plati;
    }

    friend std::istream &operator>>(std::istream &f, T& p);

    friend std::ostream &operator<<(std::ostream &g, Gestiune<T>& G)
    {
        for(int i=1; i <= G.nr_plati; ++i)
        {
            g<<G.plati[i]<<'\n';
        }
    return g;
    }

    Gestiune<T> &operator+=(const T& other)
    {
        this-> plati[nr_plati] = other;
        return *this;
    }

    void getNrPlati()
    {
        std::cout<<this->nr_plati<<'\n';
    }
};

template <class T> int Gestiune<T>::nr_plati = 0;


class PlataCard;
class PlataCash;
class PlataCec;


std::map <int, std::string> m;


Gestiune<PlataCash> B;
Gestiune<PlataCec> C;


class Plata
{
protected:
    int zi;
    int luna;
    int an;
    int ora;
    int minute;
    int suma;
    static int count;
    int id;
public:
    Plata(): ora(0), minute(0), zi(0), luna(0), an(0), suma(0), id(0) {}

    Plata(int ora, int minute, int zi, int luna, int an, int suma) : ora(ora), minute(minute), zi(zi), luna(luna), an(an), suma(suma)
    {}

    Plata(const Plata &other)
    {
        this->ora = other.ora;
        this->minute = other.minute;
        this->zi = other.zi;
        this->luna = other.luna;
        this->an = other.an;
        this->suma = other.suma;
        this->id = other.id;
    }

    virtual ~Plata()
    {
        ora = 0;
        minute = 0;
        zi = 0;
        luna = 0;
        an = 0;
        suma = 0;
        id = 0;
        count--;
    }

    Plata& operator= ( const Plata& other)
    {
        this->ora = other.ora;
        this->minute = other.minute;
        this->zi = other.zi;
        this->luna = other.luna;
        this->an = other.an;
        this->suma = other.suma;
        this->id = other.id;
        return *this;
    }

    friend std::istream &operator>>(std::istream &f, Plata& p);

    virtual void afisare(std::ostream &g)
    {
        g<<"Momentul platii: "<<this->ora<<':'<<this->minute<<"    "<<this->zi<<'.'<<this->luna<<'.'<<this->an<<'\n'<<"ID :"<<this->id<<'\n'<<"Suma: "<<this->suma<<'\n';
    }

    friend std::ostream &operator<<(std::ostream &g, Plata& p);

    static int getPlati()
    {
        return count;
    }

};

int Plata::count=0;

std::istream &operator>>(std::istream &f, Plata& p)
{
    std::cout<<"Introduceti ora:";
    f>>p.ora;
    std::cout<<"Introduceti minutele:";
    f>>p.minute;
    std::cout<<"Introduceti ziua:";
    f>>p.zi;
    std::cout<<"Introduceti luna:";
    f>>p.luna;
    std::cout<<"Introduceti anul:";
    f>>p.an;
    std::cout<<"Introduceti suma:";
    f>>p.suma;
    if(p.suma<=0)
    {
        throw InvalidSum("Suma invalida");
    }
    p.id = ++p.count;
    return f;
}

std::ostream &operator<<(std::ostream &g, Plata& p)
{
    p.afisare(g);
    return g;
}






// a a a a



class PlataCard: public Plata
{
    std::string nr_card;
    std::string nume_client;
    friend Gestiune<PlataCard>;
public:
    PlataCard(): Plata(), nr_card(""), nume_client("") {}

    PlataCard(int ora, int minute, int zi, int luna, int an, int suma, std::string nr_card, std::string nume_client) : Plata(ora, minute, zi, luna, an, suma), nr_card(nr_card), nume_client(nume_client)
    {}

    PlataCard(const PlataCard &other)
    {
        this->ora = other.ora;
        this->minute = other.minute;
        this->zi = other.zi;
        this->luna = other.luna;
        this->an = other.an;
        this->suma = other.suma;
        this->id = other.id;
        this->nr_card = other.nr_card;
        this->nume_client = other.nume_client;
    }

    virtual ~PlataCard()
    {
        ora = 0;
        minute = 0;
        zi = 0;
        luna = 0;
        an = 0;
        suma = 0;
        id = 0;
        nr_card="";
        nume_client="";
    }

    PlataCard& operator= ( const PlataCard& other)
    {
        this->ora = other.ora;
        this->minute = other.minute;
        this->zi = other.zi;
        this->luna = other.luna;
        this->an = other.an;
        this->suma = other.suma;
        this->id = other.id;
        this->nr_card = other.nr_card;
        this->nume_client = other.nume_client;
        return *this;
    }

    friend std::istream &operator>>(std::istream &f, PlataCard& p);

    void afisare(std::ostream &g)
    {
        Plata::afisare(g);
        g<<"Tip plata: Card\n"<<"Numar card: "<<this->nr_card<<"\nNume client: "<<this->nume_client<<'\n';
    }

    friend std::ostream &operator<<(std::ostream &g, PlataCard& p);

};



template<>
class Gestiune<PlataCard>
{
    static int nr_plati;
    int nr_clienti;
    std::set <std::string> clienti;
    PlataCard* plati;
    friend PlataCard;
public:
    Gestiune()
    {
        nr_clienti = 0;
        plati = new PlataCard[100];
    }

    ~Gestiune()
    {
        delete[] plati;
    }

    friend std::istream &operator>>(std::istream &f, PlataCard& p);

    friend std::ostream &operator<<(std::ostream &g, Gestiune<PlataCard>& G)
    {
        for(int i=1; i <= G.nr_plati; ++i)
        {
            g<<G.plati[i]<<'\n';
        }
    return g;
    }

    Gestiune<PlataCard> &operator+=(const PlataCard& other)
    {
        this-> plati[nr_plati] = other;
        this->clienti.insert(other.nume_client);
        nr_clienti = this->clienti.size();
        return *this;
    }

    void getNrPlati()
    {
        std::cout<<this->nr_plati<<'\n';
    }
    void AfisareClienti()
    {
        std::cout<<"Numar clienti: "<<nr_clienti<<'\n'<<"Numele clientilor: ";
        for(auto x: clienti)
        {
            std::cout<<x;
            if(x != *--clienti.end())std::cout<<", ";
        }
        std::cout<<'\n';
    }
};

int Gestiune<PlataCard>::nr_plati = 0;

Gestiune<PlataCard> A;


std::istream &operator>>(std::istream &f, PlataCard& p)
{
    f >> static_cast<Plata&>( p );
    std::cout<<"Introduceti numarul cardului:";
    f>>p.nr_card;
    std::cout<<"Introduceti numele clientului:";
    f>>p.nume_client;
    std::cout<<'\n';
    Gestiune<PlataCard>::nr_plati++;
    A+=p;
    m[p.id]="Card";
    return f;
}

std::ostream &operator<<(std::ostream &g, PlataCard& p)
{
    p.afisare(g);
    std::cout<<'\n';
    return g;
}








class PlataCash: public Plata
{
public:
    PlataCash(): Plata() {}

    PlataCash(int ora, int minute, int zi, int luna, int an, int suma) : Plata(ora, minute, zi, luna, an, suma) {}

    PlataCash(const PlataCash &other)
    {
        this->ora = other.ora;
        this->minute = other.minute;
        this->zi = other.zi;
        this->luna = other.luna;
        this->an = other.an;
        this->suma = other.suma;
        this->id = other.id;
    }

    virtual ~PlataCash()
    {
        ora = 0;
        minute = 0;
        zi = 0;
        luna = 0;
        an = 0;
        suma = 0;
        id = 0;
    }

    PlataCash& operator= ( const PlataCash& other)
    {
        this->ora = other.ora;
        this->minute = other.minute;
        this->zi = other.zi;
        this->luna = other.luna;
        this->an = other.an;
        this->suma = other.suma;
        this->id = other.id;
        return *this;
    }

    friend std::istream &operator>>(std::istream &f, PlataCash& p);

    void afisare(std::ostream &g)
    {
        Plata::afisare(g);
        g<<"Tip plata: Cash\n";
    }

    friend std::ostream &operator<<(std::ostream &g, PlataCash& p);
};

std::istream &operator>>(std::istream &f, PlataCash& p)
{
    f >> static_cast<Plata&>( p );
    std::cout<<'\n';
    Gestiune<PlataCash>::nr_plati++;
    B+=p;
    m[p.id]="Cash";
    return f;
}

std::ostream &operator<<(std::ostream &g, PlataCash& p)
{
    p.afisare(g);
    std::cout<<'\n';
    return g;
}





class PlataCec: public Plata
{
    std::string nume_client;
public:
    PlataCec(): Plata(), nume_client(""){}

    PlataCec(int ora, int minute, int zi, int luna, int an, int suma, std::string nume_client) : Plata(ora, minute, zi, luna, an, suma), nume_client(nume_client)
    {}

    PlataCec(const PlataCec &other)
    {
        this->ora = other.ora;
        this->minute = other.minute;
        this->zi = other.zi;
        this->luna = other.luna;
        this->an = other.an;
        this->suma = other.suma;
        this->id = other.id;
        this->nume_client = other.nume_client;
    }

    virtual ~PlataCec()
    {
        ora = 0;
        minute = 0;
        zi = 0;
        luna = 0;
        an = 0;
        suma = 0;
        id = 0;
    }

    PlataCec& operator= ( const PlataCec& other)
    {
        this->ora = other.ora;
        this->minute = other.minute;
        this->zi = other.zi;
        this->luna = other.luna;
        this->an = other.an;
        this->suma = other.suma;
        this->id = other.id;
        this->nume_client = other.nume_client;
        return *this;
    }

    friend std::istream &operator>>(std::istream &f, PlataCec& p);

    void afisare(std::ostream &g)
    {
        Plata::afisare(g);
        g<<"Tip plata: Cec\n"<<"Nume client: "<<this->nume_client<<'\n';
    }

    friend std::ostream &operator<<(std::ostream &g, PlataCec& p);
};

std::istream &operator>>(std::istream &f, PlataCec& p)
{
    f >> static_cast<Plata&>( p );
    std::cout<<"Introduceti numele clientului:";
    f >> p.nume_client;
    std::cout<<'\n';
    Gestiune<PlataCec>::nr_plati++;
    C+=p;
    m[p.id]="Cec";
    return f;
}

std::ostream &operator<<(std::ostream &g, PlataCec& p)
{
    p.afisare(g);
    std::cout<<'\n';
    return g;
}










void meniu()
{
    std::cout << "MENIU\n";
    std::cout << "1. Introducere plata.\n";
    std::cout << "2. Afisare plati.\n";
    std::cout << "3. Afisare clienti care au platit prin card.\n";
    std::cout << "4. Inchidere meniu.\n";
}

int main()
{
    std::vector<Plata*> platiTotale;
    /*
    PlataCard p;
    PlataCec q;
    PlataCash c;
    std::cin>>c;
    std::cout<<c<<p<<q;
    */
    std::string s;
    int caz, tip;
    do
    {
        meniu();
        std::cin>>caz;
        if(caz==1)
        {
            std::cout<<"Introduceti tipul platii. ( 1 = card, 2 = cash, 3 = cec)\n";
            std::cin>>tip;
            if(tip==1)
            {
                PlataCard* p = new PlataCard;
                try
                {
                    std::cin >> *p;
                }catch(std::exception& e)
                {
                    std::cout<<e.what()<<'\n';
                    continue;
                }
                platiTotale.push_back(p);
            }
            else if(tip==2)
            {
                PlataCash* p = new PlataCash;
                try
                {
                    std::cin >> *p;
                }catch(std::exception& e)
                {
                    std::cout<<e.what()<<'\n';
                    continue;
                }
                platiTotale.push_back(p);
            }
            else if(tip==3)
            {
                PlataCec* p = new PlataCec;
                try
                {
                    std::cin >> *p;
                }catch(std::exception& e)
                {
                    std::cout<<e.what()<<'\n';
                    continue;
                }
                platiTotale.push_back(p);
            }

            continue;
        }
        else if(caz==2)
        {
            std::cout<<"Introduceti tipul platii. ( 0 = toate platile, 1 = card, 2 = cash, 3 = cec)\n";
            std::cin>>tip;
            std::cout<<"Numar plati de tipul selectat: ";
            if(tip==0)
            {
                std::cout<<Plata::getPlati()<<"\n\n";
                for(auto x: platiTotale)
                {
                    x->afisare(std::cout);
                    std::cout<<'\n';
                }
            }
            else if(tip==1)
            {
                A.getNrPlati();
                std::cout<<'\n'<<A;
            }
            else if(tip==2)
            {
                B.getNrPlati();
                std::cout<<'\n'<<B;
            }
            else if(tip==3)
            {
                C.getNrPlati();
                std::cout<<'\n'<<C;
            }
            else
            {
                std::cout<<"Tip invalid.\n";
            }
            continue;
        }
        else if(caz==3)
        {
            A.AfisareClienti();
        }
        else if(caz==4)
        {
            break;
        }
        else
        {
            std::cout<<"Optiune invalida. Incercati din nou.\n";
        }

    }
    while(true);

    return 0;
}

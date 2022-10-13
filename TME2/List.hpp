#pragma once
template <typename T>
class List
{
    class Chainon
    {
        T data;
        Chainon *next;
        Chainon(T data, Chainon *next = nullptr) : data(data), next(next) {}
        ~Chainon()
        {
            delete next;
        }
    };
    Chainon *tete;

public:
    List() : tete(nullptr) {}
    ~List()
    {
        Chainon *suiv;
        while (tete)
        {
            suiv = tete->next;
            delete tete;
            tete = suiv;
        }
    }

    T &operator[](size_t index)
    {
        Chainon *courant = tete;
        for (size_t i(0); i < index; ++i)
        {
            courant = courant->next;
        }
        return courant->data;
    }

    void push_front(const T &val)
    {
        tete = new Chainon(val, tete);
    }

    bool empty()
    {
        return !tete;
    }
    void push_back(const T &val)
    {
        if (!tete)
        {
            tete = new Chainon(val);
        }
        Chainon *courant = tete;
        Chainon *precedent;
        while (courant)
        {
            precedent = courant;
            courant = courant->next;
        }
        Chainon *newChainon = new Chainon(val);
        precedent->next = newChainon;
    }
};
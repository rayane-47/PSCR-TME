#include "Compte.h"

using namespace std;

namespace pr
{
	void Compte::crediter(unsigned int val)
	{
		unique_lock<recursive_mutex> g(m);
		solde += val;
		cout << "crediter " << val << " solde " << solde << endl;
	}
	bool Compte::debiter(unsigned int val)
	{
		unique_lock<recursive_mutex> g(m);
		bool doit = solde >= val;
		if (doit)
		{
			solde -= val;
		}
		cout << "debiter " << val << " solde " << solde << endl;
		return doit;
	}
	int Compte::getSolde() const
	{
		unique_lock<recursive_mutex> g(m);
		return solde;
	}
	// NB : vector exige Copyable, mais mutex ne l'est pas...
	Compte::Compte(const Compte &other)
	{
		other.m.lock();
		solde = other.solde;
		other.m.unlock();
	}
	std::recursive_mutex &Compte::getMutex() const
	{
		return m;
	}
	void Compte::setReading(bool b) const
	{
		reading = b;
	}
	bool Compte::getReading() const
	{
		return reading;
	}
}

#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr
{

	void Banque::transfert(size_t deb, size_t cred, unsigned int val)
	{

		Compte &debiteur = comptes[deb];
		Compte &crediteur = comptes[cred];
		if (debiteur.getReading() || crediteur.getReading())
		{
			cout << "transfert impossible durant la lecture" << endl;
			return;
		}
		// Q4:
		// lock both mutexes simultaneously to avoid deadlock
		std::lock(debiteur.getMutex(), crediteur.getMutex());
		if (debiteur.debiter(val))
		{
			crediteur.crediter(val);
		}
		debiteur.getMutex().unlock();
		cout << "compte debiteur deverrouille" << endl;
		crediteur.getMutex().unlock();
		cout << "compte crediteur deverrouille" << endl;
	}
	size_t Banque::size() const
	{
		return comptes.size();
	}
	bool Banque::comptabiliser(int attendu) const
	{

		int bilan = 0;
		int id = 0;

		{
			// std::unique_lock<std::mutex> g(m_banque);
			for (const auto &compte : comptes)
			{
				compte.setReading(true);
				if (compte.getSolde() < 0)
				{
					cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
				}
				cout << "Compte " << id << " : " << compte.getSolde() << endl;
				bilan += compte.getSolde();
				id++;
			}
			for (auto &compte : comptes)
			{
				compte.setReading(false);
			}
		}
		if (bilan != attendu)
		{
			cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
		}
		return bilan == attendu;
	}
	void Banque::afficher() const
	{
		// std::unique_lock<std::mutex> g(m_banque);
		int id = 0;
		for (const auto &compte : comptes)
		{
			cout << "Compte " << id << " : " << compte.getSolde() << endl;
			++id;
		}
	}
}

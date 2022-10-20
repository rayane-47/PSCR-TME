#include "Banque.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

const int NB_THREAD = 40;
const int NB_COMPTES = 5;
int main()
{
	vector<thread> threads;
	// TODO : creer des threads qui font ce qui est demandé
	pr::Banque b(NB_COMPTES, 3000);
	b.afficher();
	for (int i(0); i < NB_THREAD; ++i)
	{
		threads.emplace_back([&b]
							 {
			for (int j(0); j < 1000; ++j)
			{
				srand(time(NULL));
				b.transfert(rand() % b.size(), rand() % b.size(), rand() % 100);
				cout << "thread n° " << this_thread::get_id() << " transfert effectue" << endl;
				//sleep 
				this_thread::sleep_for(chrono::milliseconds(2));
			} });
	}
	for (auto &t : threads)
	{
		t.join();
	}

	// TODO : tester solde = NB_THREAD * JP
	cout << "Solde attendu : " << NB_COMPTES * 3000 << endl;
	cout << "Solde comptabilisé : " << b.comptabiliser(NB_COMPTES * 3000) << endl;
	return 0;
}

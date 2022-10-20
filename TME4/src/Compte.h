#pragma once
#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>
namespace pr
{

	class Compte
	{
		mutable std::recursive_mutex m;
		mutable std::atomic<bool> reading;
		int solde;

	public:
		Compte(int solde = 0) : solde(solde), reading(false) {}
		Compte(const Compte &other);
		void crediter(unsigned int val);
		bool debiter(unsigned int val);
		int getSolde() const;
		void setReading(bool b) const;
		bool getReading() const;
		std::recursive_mutex &getMutex() const;
	};

}

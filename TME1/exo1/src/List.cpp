
// Faute 01: Il manque le #include "List.h"
#include "List.h"
// Faute 02: il manque le #include "cstddef" pour pouvoir utiliser le type size_t
#include "cstddef"
namespace pr
{

	// ******************* Chainon
	// Faute 04: Le ; en plus a la fin du constructeur
	Chainon::Chainon(const std::string &data, Chainon *next) : data(data), next(next) {}

	// Erreur à l'execution, on retourne len et on ne fait pas appel a la methode length() de la classe Chainon

	size_t Chainon::length()
	{
		size_t len = 1;
		if (next != nullptr)
		{
			len += next->length();
		}
		return len;
	}

	// Faute 03: la signature de la méthode print est incomplete, il manque le const a la fin

	void Chainon::print(std::ostream &os) const
	{
		os << data;
		if (next != nullptr)
		{
			os << ", ";
			next->print(os);
		}
		// Faute à l'execution: on doit tester si next est différent de nullptr avant d'afficher son contenu
	}

	// ******************  List
	const std::string &List::operator[](size_t index) const
	{
		Chainon *it = tete;
		for (size_t i = 0; i < index; i++)
		{
			it = it->next;
		}
		return it->data;
	}

	void List::push_back(const std::string &val)
	{
		if (tete == nullptr)
		{
			tete = new Chainon(val);
		}
		else
		{
			Chainon *fin = tete;
			while (fin->next)
			{
				fin = fin->next;
			}
			fin->next = new Chainon(val);
		}
	}

	// Faute 06: Redifinition de la methode push_front de la classe List precedement définit dans le fichier List.h

	/*void List::push_front (const std::string& val) {
		tete = new Chainon(val,tete);
	}
	*/
	// Faute 05: empty() est une méthode de la classe List

	bool List::empty()
	{
		return tete == nullptr;
	}

	size_t List::size() const
	{
		if (tete == nullptr)
		{
			return 0;
		}
		else
		{
			return tete->length();
		}
	}

	// Faute 07: La redefinition de l'operateur << aprtient au namespace pr et doit etre dedans

	std::ostream &operator<<(std::ostream &os, const pr::List &vec)
	{
		os << "[";
		if (vec.tete != nullptr)
		{
			vec.tete->print(os);
		}
		os << "]";
		return os;
	}

} // namespace pr
	
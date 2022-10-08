#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include "HashMap.hpp"
#include <functional>
int main()
{
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re(R"([^a-zA-Z])");

	// Comptage du  nombre de mots differents

	// En utilisant un vector
	// vector<pair<string, int>> v_frequences_mots;

	// En utilisant une HashMap
	HashMap<string, int> frequences_mots_map;

	size_t nb_mots_differents = 0;
	std::vector<string> keys;
	while (input >> word)
	{
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace(word, re, "");
		// passe en lowercase
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		if (!frequences_mots_map.find(word))
		{
			frequences_mots_map[word] = 1;
			nb_mots_differents++;
			keys.push_back(word);
		}
		else
		{
			frequences_mots_map[word]++;
		}

		// Check if vector contains word
		/*
		auto it = find_if(v_frequences_mots.begin(), v_frequences_mots.end(), [&](const auto &pair)
						  { return pair.first == word; });
		if (it == v_frequences_mots.end())
		{
			nb_mots_differents++;
			// Push new word and frequency
			v_frequences_mots.push_back(make_pair(word, 1));
		}
		else
		{
			(*it).second++;
		}
		*/
		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": " << word << endl;
		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
	cout << "Parsing took "
		 << duration_cast<milliseconds>(end - start).count()
		 << "ms.\n";

	cout << "Found a total of " << nombre_lu << " words." << endl;
	cout << "the total of different words is: " << nb_mots_differents << endl;
	/*
	for (auto &i : v_frequences_mots)
	{
		if (i.first == "war")
		{
			cout << "Le nombre d'occurences du mot " << i.first << "est " << i.second << endl;
		}

		if (i.first == "peace")
		{
			cout << "Le nombre d'occurences du mot " << i.first << "est " << i.second << endl;
		}
		if (i.first == "toto")
		{
			cout << "Le nombre d'occurences du mot " << i.first << "est " << i.second << endl;
		}
	}
	*/
	cout << "Le nombre d'occurences du mot war est " << frequences_mots_map["war"] << endl;
	cout << "Le nombre d'occurences du mot peace est " << frequences_mots_map["peace"] << endl;
	cout << "Le nombre d'occurences du mot toto est " << frequences_mots_map["toto"] << endl;

	std::vector<pair<string, int>> frequences;
	for (auto key : keys)
	{
		frequences.push_back(make_pair(key, frequences_mots_map[key]));
	}

	// Trie les mots par ordre décroissant de fréquence
	std::sort(frequences.begin(), frequences.end(), [](const auto &a, const auto &b)
			  { return a.second > b.second; });

	// Print first 10
	cout << "Top 10 words" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << frequences[i].first << " " << frequences[i].second << endl;
	}
	return 0;
}

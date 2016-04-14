#include "Slav.h"
#include <fstream>

using namespace std;

vector <string> Slav::names;
int Slav::_counter = 0;

void Slav::init()
{
	srand(time(NULL));
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

Slav::Slav()
{
	static int amountOfNames = (init(), names.size()); // leniwa inicjalizacja 
	// zmiennej amountOfNames zostanie przypisane liczba wszystkich imion wczytanych z pliku. 
	// liczba imion zawiera się w names.size() po uprzednim wywolaniu funkcji init()
	_name = names[rand() % amountOfNames];
	_id = _counter++;
}

string Slav::description()
{
	return string("  ") + _name + " [" + to_string(_id) + "]";
}
gender Slav::which_gender()
{
	return (_name[_name.length()-1]=='a') ? woman : man;
}
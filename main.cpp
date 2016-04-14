// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);
void show_gender(Slav*, int);

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);
	show_gender(slavs,n);
	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	vectorOfSlavs.push_back(slavs);
	for(int i=1;i<n;i++)
		vectorOfSlavs.insert(vectorOfSlavs.begin()+ rand()%vectorOfSlavs.size(), &slavs[i]); 

	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze
		vector <Slav *>::iterator it_vec;
		for( it_vec=vectorOfSlavs.begin();it_vec!=vectorOfSlavs.end();it_vec++)
			cout<<(*it_vec)->description()<<endl;

	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.
	for(int i=n-1;i>=0;i--)
	{
		setOfSlavs.insert(vectorOfSlavs[i]);
		vectorOfSlavs.pop_back();
	}
	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	set<Slav*>::iterator it_set=setOfSlavs.begin();
  	set<Slav*>::iterator it_set_remove=setOfSlavs.begin();
 	while(it_set!=setOfSlavs.end())
 	{															
 	while(it_set!=setOfSlavs.end())
 	{															
  		mapOfSlavs[*it_set++]=*it_set++;
  		setOfSlavs.erase(it_set_remove++);
  		setOfSlavs.erase(it_set_remove++);
	}
	}
	
	// Wykorzystując iterator, wyświetl wszystkie pary Słowian
	map <Slav*, Slav*>::iterator it_map=mapOfSlavs.begin();
	
	while(it_map!=mapOfSlavs.end())
	{
			cout<<(it_map->first)->description()<<" -> "<<(it_map->second)->description()<<endl;
			it_map++;
	}
	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	for(int i=0;i<n;i++)
		queueOfSlavs.push(&slavs[i]);
	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu.
	while(queueOfSlavs.empty()==0)
	{
	stackOfSlavs.push(queueOfSlavs.front());
	queueOfSlavs.pop();
	}
	REPORT_ADAPTERS;
	// Wyświetl Słowian zdejmowanych ze stosu.
	while(stackOfSlavs.empty()==0)
	{
		cout<<stackOfSlavs.top()->description()<<endl;
		stackOfSlavs.pop();
	}
	REPORT_ADAPTERS;
}
void show_gender(Slav *slavs,int n)
{
	map < gender,vector<Slav*> > mapOfGender;
	for(int i=0;i<n;i++)
		(slavs[i].which_gender()== man) ? mapOfGender[man].push_back(slavs+i) : mapOfGender[woman].push_back(slavs+i);	
	
	cout<<"\n mans: \n";
	for(int i=0;i<mapOfGender[man].size();i++)
		cout<<mapOfGender[man][i] -> description()<<endl;

	cout<<"womans:\n";
	for(int i=0;i<mapOfGender[woman].size();i++)
		cout<<mapOfGender[woman][i] -> description()<<endl;

}
void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}

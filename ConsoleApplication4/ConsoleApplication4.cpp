// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class Herbivore abstract
{
protected:
	int Weight;		
	bool Life;	
public:
	virtual void EatGrass() = 0;
	virtual void Show() = 0;
	virtual int GetWeight() = 0;
	virtual void SetLife(bool dead) = 0;			
};

class Wildebeest : public Herbivore
{
public:
	Wildebeest() {	
		Weight = 30;			
		Life = true;	
	}	
	void EatGrass()
	{
		if (Life == true) {	
			Weight += 10;	
			cout << "The wildebeest ate! +10 to weight" << endl;	
		}
	}
	int GetWeight()
	{
		return Weight;		
	}		
	void SetLife(bool dead)			
	{
		Life = dead;		
	}	
	void Show()
	{
		cout << "Weight: " << Weight << endl;
		if (Life == true) {
			cout << "Wildebeest is alife!" << endl;
		}
		else {
			cout << "Wildebeest is dead!" << endl;
		}
	}
};

class Bison : public Herbivore 
{
public:
	Bison() 
	{
		Weight = 783;		
		Life = true;	
	}
	void EatGrass()
	{
		if (Life == true)	
		{
			Weight += 10;
			cout << "The Bison ate! +10 to weight" << endl;	
		}
	}
	int GetWeight()	
	{
		return Weight;	
	}
	void SetLife(bool dead)
	{
		Life = dead;
	}
	void Show()
	{
		cout << "Weight: " << Weight << endl;
		if (Life == true) {
			cout << "Bison is alife!" << endl;	
		}
		else {
			cout << "Bison is dead!" << endl;	
		}
	}	
};

class Carnivore abstract 
{
protected:	
	int Power;	
	int HerbivoreWeight;
	Herbivore* herbivore;
public:
	virtual void Eat() = 0;
	virtual void Show() = 0;	
	virtual int GetPower() = 0;		
};

class Lion : public Carnivore
{
public:
	Lion() 
	{
		Power = 100;	
	}
	void Eat() 
	{		
		herbivore = new Wildebeest();		
		HerbivoreWeight = herbivore->GetWeight();				
		if (HerbivoreWeight > Power)	
		{
			cout << "The herbivore's weight is greater than the lion's strength! -10 to strength" << endl;	
			Power -= 10;		
		}
		else {
			cout << "Lion ate animal! +10 strength" << endl;		
			Power += 10;	
		}	
	}
	int GetPower()	
	{
		return Power;	
	}
	void Show() 
	{
		cout << "Lion power: " << Power << endl;	
	}
};

class Wolf : public Carnivore
{
public:
	Wolf()
	{
		Power = 65;	
	}
	void Eat()	
	{
		herbivore = new Bison();		
		HerbivoreWeight = herbivore->GetWeight();	
		if (HerbivoreWeight > Power)	
		{
			cout << "The herbivore's weight is greater than the wolf's strength! -10 to strength" << endl;
			Power -= 10;
		}
		else {
			cout << "Wolf ate animal! +10 strength" << endl;		
			Power += 10;
		}
	}
	int GetPower()	
	{
		return Power;	
	}
	void Show()	
	{
		cout << "Wolf power: " << Power << endl;	
	}
};

class Continent abstract 
{
public:
	virtual Herbivore* CreateHerbivore() abstract;	
	virtual Carnivore* CreateCarnivore() abstract;	
};	

class Africa : public Continent 
{
public:
	Herbivore* CreateHerbivore() override
	{
		return new Wildebeest();	
	}
	Carnivore* CreateCarnivore()
	{
		return new Lion();	
	}
};

class NorthAmerica : public Continent	
{
public:
	Herbivore* CreateHerbivore() override
	{
		return new Bison();	
	}
	Carnivore* CreateCarnivore()		
	{	
		return new Wolf();	
	}
};

class Client 
{
	Herbivore* herbivore;	
	Carnivore* carnivore;	
	int checkWeight;	
public:
	Client(Continent* factory)
	{
		herbivore = factory->CreateHerbivore();	
		carnivore = factory->CreateCarnivore();	
	}
	void EatHerbivore() 
	{
		herbivore->EatGrass();	
		herbivore->Show();	
	}
	void EatCarnivore() 
	{
		carnivore->Eat();	
		carnivore->Show();	
		if (herbivore->GetWeight() < carnivore->GetPower()) {
			herbivore->SetLife(false);	
		}
	}
};

int main()
{
	Continent* continent = new Africa();
	Client *client = new Client(continent);
	cout << "EatHerbivore: " << endl;	
	client->EatHerbivore();
	cout << endl;	
	cout << "Carnivore: " << endl;	
	client->EatCarnivore();	
	cout << endl;	
	cout << "EatHerbivore: " << endl;		
	client->EatHerbivore();		
	delete continent;	
	delete client;		

	cout << "----------------------------------------------" << endl;	

	continent = new NorthAmerica();	
	client = new Client(continent);	
	cout << "Bison: " << endl;
	client->EatHerbivore();		
	cout << endl;	
	cout << "Wolf: " << endl;
	client->EatCarnivore();	
	cout << endl;	
	cout << "Bison: " << endl;	
	client->EatHerbivore();	
	delete continent;	
	delete client;	


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#include <iostream>
#include <ctime>
#include<vector>
using namespace std;

__interface Product {
	string GetName();
};

class Fridge {
	vector<string> products;
public:
	virtual ~Fridge(){}
	void AddProduct(Product* product) {
		products.push_back(product->GetName());
	}

	void RemoveProduct(Product* product) {
		for (int i = 0; i < products.size(); i++)
		{
			if (product->GetName() == products[i])
				products.erase(products.begin() + i);
		}
	}

	int GetCountSomeProduct(string name_product) {
		int count = 0;
		for (int i = 0; i < products.size(); i++) {
			if (name_product == products[i])
				count++;
		}
		return count;
	}
};

__interface Dish{
	void Print();
};

__interface RawProduct : public Product{ 	
};

__interface Vegetable : public Product{ 	
};

class Tomato : public Vegetable {
	string name = "tomato";
public:
	virtual ~Tomato(){}
	string GetName() {
		return name;
	}
};

class Cucumber : public Vegetable {
	string name = "cucumber";
public:
	virtual ~Cucumber() {}
	string GetName() {
		return name;
	}
};

class Varenyk : public RawProduct {
	string name = "varenyk";
public:
	virtual ~Varenyk(){}
	string GetName() {
		return name;
	}
};

class BoiledVarenyk : public Dish {
public:	
	virtual ~BoiledVarenyk() {}
	void Cook(Fridge* fridge, RawProduct* product1){
		if (fridge->GetCountSomeProduct(product1->GetName()) <= 0)
			throw"error";
	}
	void Print() {
		cout << "boiled varenyk\n";
	}
};

class Egg : public RawProduct {
	string name = "egg";
public:
	virtual ~Egg() {}
	string GetName() {
		return name;
	}
};

class BoiledEgg : public Dish {
public:
	virtual ~BoiledEgg() {}

	void Cook(Fridge* fridge, RawProduct* product1) {
		if (fridge->GetCountSomeProduct(product1->GetName()) > 0)
			cout << "boiled eggs count " << fridge->GetCountSomeProduct(product1->GetName()) << "\n";
	}

	void Print() {
		cout << "boiled egg\n";
	}
};

class FryedEgg : public Dish{
public:
	virtual ~FryedEgg() {}

	void Cook(Fridge* fridge, RawProduct* product1){
		if (fridge->GetCountSomeProduct(product1->GetName()) > 0)
			cout << "fryed eggs count " << fridge->GetCountSomeProduct(product1->GetName()) << "\n";
	}

	void Print() {
		cout << "fryed egg\n";
	}
};


class Salad : public Dish{	
public:
	virtual ~Salad() {
	}
	void Cook(Fridge* fridge, Vegetable* product1, Vegetable* product2) {
		if(fridge->GetCountSomeProduct(product1->GetName()) > 2 && fridge->GetCountSomeProduct(product2->GetName()) > 2)
			cout << "salad ingredients\n" << product1->GetName() << "\n" << product2->GetName();
	}

	void Print() {
		cout << "salad\n";
	}
};

__interface Timetable {
	Dish* Cook(Fridge* fridge);
};

class MorningDish : public Timetable {
public:
	virtual ~MorningDish(){}
	Dish* Cook(Fridge* fridge) {
		// Boiled Eggs
		if (fridge->GetCountSomeProduct("egg") > 0)
			return new FryedEgg;
		else
			throw"error";
	}
};

class LunchDish : public Timetable {
public:
	virtual ~LunchDish(){}
	Dish* Cook(Fridge* fridge) {
	//Varenyky}
		if (fridge->GetCountSomeProduct("varenyk") > 0)
			return new BoiledVarenyk;
		else
			throw"error";
	}
};

class EveningDish : public Timetable {
public:
	virtual ~EveningDish(){}
	Dish* Cook(Fridge* fridge) {
	//Salad
		if (fridge->GetCountSomeProduct("tomato") > 0 || fridge->GetCountSomeProduct("cucumber") > 0)
			return new Salad;
		else
			throw"error";
	}
};

class Chef {
protected:
	Fridge* fridge = nullptr;
	Timetable* timetable = nullptr;
public:
	Chef() {
		fridge = new Fridge;
	}

	Dish* Cook(Fridge* fridge, Timetable* product) {
		return product->Cook(fridge);
	}

	Dish* Boil(RawProduct* product) {
		if (product->GetName().compare("varenyk"))
			return new BoiledVarenyk;
		else if (product->GetName().compare("egg"))
			return new BoiledEgg;
	}

	//void SetProduct(Product* product){}
	Fridge* ViewFridge(){
		return fridge;
	}

	void SetTimetable(Timetable* timetable) {
		if (this->timetable == nullptr) 
			delete this->timetable;
		this->timetable = timetable;
	}
};


int main(){
	Chef chef;
	Fridge fridge;
	Egg a;
	Egg b;
	Tomato t;
	Cucumber f;
	Varenyk v;
	fridge.AddProduct(&a);
	fridge.AddProduct(&b);
	fridge.AddProduct(&f);
	fridge.AddProduct(&v);
	fridge.AddProduct(&t);
	auto product = chef.Cook(&fridge, new MorningDish);
	product->Print();
}

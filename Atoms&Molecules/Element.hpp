#include <string>
#include <vector>
#include <stdexcept>
#include <exception>
#include <iostream>
using namespace std;

class Element{
private:
	const string name;
	const string symbol;
	const int atomicNumber;//==protons
	const string block;
	const float electroNegativity;
public:
	Element() = delete;
	
	const int getAtomicNumber() const{
		return atomicNumber;
	}

	const string& getName() const {
		return name;
	}

	const string& getSymbol() const {
		return symbol;
	}

	const string& getBlock() const {
		return block;
	}

	const float getElectronegativity() const {
		return electroNegativity;
	}
private:
	friend class PeriodicTable;
 	Element(int atomicNumber, const string& name, const string& symbol, const string& block, float electroNegativity) : 
		atomicNumber(atomicNumber), name(name), symbol(symbol), block(block), electroNegativity(electroNegativity) {}
};
#pragma once
#include "PeriodicTable.hpp"
#include "AtomValidator.hpp"

enum TypeOfAtom {
	NEGATIVE_ION = -1,
	NEUTRAL_ION = 0,
	POSITIVE_ION = 1
};

class Atom
{
public:
	Atom() = delete;

	Atom(int protons, int neutrons, const vector<int>& electrons, const vector<float>& position) {
		AtomValidator::validateCoordinates(position);
		AtomValidator::validateElectrons(electrons);
		this->element = PeriodicTable::getInstance().getElementByNumber(protons);
		AtomValidator::validateAtomRealism(element->getAtomicNumber(), neutrons, electrons);
		this->position = position;
		this->neutrons = neutrons;
		this->protons = protons;
		this->electrons = electrons;
		setTypeOfAtom();
	}

	void addElectron() {
		size_t n = electrons.size();
		if ((n * n) * 2 == electrons[n-1]) {
			if (n == 7) {
				throw runtime_error("Max electrons capacity reached");
			}
			electrons.push_back(1);
			try {
				AtomValidator::validateAtomRealism(element->getAtomicNumber(), neutrons, electrons);
				return;
			}
			catch (const exception& e) {
				electrons.pop_back();
				cerr << "Unrealistic atom, reason: " << e.what();
				throw e;
			}
		}
		electrons[n-1]++;
		try {
			AtomValidator::validateAtomRealism(element->getAtomicNumber(), neutrons, electrons);
		}
		catch (const exception& e) {
			electrons[n-1]--;
			cerr << "Unrealistic atom, reason: " << e.what();
			throw e;
		}
	}

	void removeElectron() {
		size_t index = electrons.size()-1;
		if (index == 0 && electrons[index] == 0) {
			throw runtime_error("Minimum amount of electrons reached");
		}
		try {
			--electrons[index];
			AtomValidator::validateAtomRealism(element->getAtomicNumber(), neutrons, electrons);
			if (electrons[index] == 0 && index != 0) 
				electrons.pop_back();
			return;
		}
		catch (const exception& e) {
			electrons[index]++;
			cerr << "Unrealistic atom, reason: " << e.what();
			throw e;
		}
	}

	TypeOfAtom getCharge() const{
		return type;
	}

	const vector < float > & getPositions() const {
		return position;
	}

	const vector<int>& getElectrons() const {
		return electrons;
	}
	
	unsigned getTotalElectrons() const {
		unsigned sum = 0;
		for (size_t i = 0; i < electrons.size(); i++) 
			sum += electrons[i];
		return sum;
	}

	const Element* getElement() const {
		return element;
	}

	const int getMass() const{
		return protons + neutrons;
	}

	int getValance() const { //valance = electrons left until filling the most outer electron shell which exists
		int n = electrons.size();
		return ((n * n) * 2) - electrons[n - 1];
	}

	int getProtons() const {
		return protons;
	}

	int getNeutrons()const {
		return neutrons;
	}

	const TypeOfAtom getType() const {
		return type;
	}
private:
	void setTypeOfAtom() {
		if (neutrons > protons)
			type = TypeOfAtom::NEGATIVE_ION;
		else if (neutrons == protons)
			type = TypeOfAtom::NEUTRAL_ION;
		else
			type = TypeOfAtom::POSITIVE_ION;
	}

	vector<int> electrons;
	vector<float> position; //[0] = x, [1] = y, [2] = z
	const Element* element;
	TypeOfAtom type = TypeOfAtom::NEUTRAL_ION; 
	int protons;
	int neutrons;
};

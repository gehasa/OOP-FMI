#pragma once
#include "MoleculeValidator.hpp"
#include "Prints.hpp"

class Molecule {
public:
	void addAtoms(Atom&& atom) {
		if (AtomValidator::isFullAtom(atom.getElectrons())) {
			throw invalid_argument("Full atoms don't bond");
			return;
		}
		MoleculeValidator::validateCoordinates(atoms, atom);
		decompose();
		usedElectronsInBonds.push_back(atom.getValance());
		atoms.push_back(std::move(atom));
		recompose();
	}
	
	void addAtoms(vector<Atom>&& atoms) {
		vector<Atom> toAdd;

		for (size_t i = 0; i < atoms.size(); i++) {
			if (AtomValidator::isFullAtom(atoms[i].getElectrons())) {
				cout << "Full atoms don't bond, atom info\n";
				Prints::getInstance().printAtomInfo(atoms[i]);
				cout << '\n';
				continue;
			}
			MoleculeValidator::validateCoordinates(this->atoms, atoms[i]);
			toAdd.push_back(std::move(atoms[i]));
		}
		decompose();
		for (size_t i = 0; i < toAdd.size();i++) {
			this->usedElectronsInBonds.push_back(toAdd[i].getValance());
			this->atoms.push_back(std::move(toAdd[i]));
		}
		recompose();
	}

	void addAtoms(const Atom& atom) {
		if (AtomValidator::isFullAtom(atom.getElectrons())) {
			cerr << "Full atoms don't bond\n";
			return;
		}
		MoleculeValidator::validateCoordinates(atoms, atom);
		decompose();
		usedElectronsInBonds.push_back(atom.getValance());
		atoms.push_back(atom);
		recompose();
	}

	void addAtoms(const vector<Atom>& atoms) {
		vector<Atom> toAdd;
		for (size_t i = 0; i < atoms.size(); i++) {
			if (AtomValidator::isFullAtom(atoms[i].getElectrons())) {
				cout << "Full atoms don't bond, atom info\n";
				Prints::getInstance().printAtomInfo(atoms[i]);
				cout << '\n';
				continue;
			}
			MoleculeValidator::validateCoordinates(this->atoms, atoms[i]);
			toAdd.push_back(atoms[i]);
		}
		decompose();
		for (size_t i = 0; i < toAdd.size();i++) {
			this->usedElectronsInBonds.push_back(toAdd[i].getValance());
			this->atoms.push_back(std::move(toAdd[i]));
		}
		recompose();
	}

	const vector<Atom>& getBondedAtoms() const{
		return atoms;
	}

	const string& getName() const {
		return name;
	}

	void setMoleculeName(const string& name) {
		this->name = name;
	}

	friend class MoleculeBuilder;

private:

	vector<Atom>& getBondedAtomsByRef() {
		return atoms;
	}

	void decompose() {
		for (size_t i = 0; i < unbondedAtoms.size(); i++) {
			usedElectronsInBonds.push_back(unbondedAtoms[i].getValance());
			atoms.push_back(std::move(unbondedAtoms[i])); //instead of deep copy we just move pointers
		}
		unbondedAtoms.clear(); //freeing memory for pushbacks later(not the best way because of allocation but its simpler in code)
		for (size_t i = 0; i < atoms.size();i++) {
			usedElectronsInBonds[i] = atoms[i].getValance();
		}
	}


	void recompose() {
		size_t len = atoms.size();
		for (size_t i = 0; i < len; i++) {
			for (size_t j = 0; j < len; j++) {
				if (i == j) 
					continue;

				if (MoleculeValidator::areAvaliableForBonding(bonds, usedElectronsInBonds, atoms[i], atoms[j], i , j)) {
					bonds.push_back({ &atoms[i], &atoms[j] });
					usedElectronsInBonds[i]++;
					usedElectronsInBonds[j]++;
				}
			}
		}
		removeAtomsNotInBonds();
	}

	
	void removeAtomsNotInBonds() {
		size_t len = atoms.size();
		if (len == 1)
			return;

		for (size_t i = 0; i < len; i++) {
			if (MoleculeValidator::amountOfBonds(atoms[i], bonds) == 0) {
				cout << "Atom on index " << i << " was not bonded.\n"; //Not throwing at the end of the method because nothing happens
				unbondedAtoms.push_back(std::move(atoms[i]));
				atoms.erase(atoms.begin() + i); 
				usedElectronsInBonds.erase(usedElectronsInBonds.begin() + i);
			}
		}
	}

	string name;
	vector<uint8_t> usedElectronsInBonds;
	vector<Atom> atoms;
	vector<Atom> unbondedAtoms;
	vector<vector<Atom*>> bonds; //since atoms can be the same i am thinking of using their adress in the mem
};

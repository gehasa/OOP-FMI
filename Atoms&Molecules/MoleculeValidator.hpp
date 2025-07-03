#pragma once
#include "Atom.hpp"

constexpr uint8_t MAX_COORDINATES = 3;
constexpr uint8_t FOUR_BONDS_MAX_ATOMIC_NUMBER = 20;
constexpr uint8_t MAX_BONDS_LIGHT = 4;
constexpr uint8_t MAX_BONDS_HEAVY = 6;

class AtomValidator;

class MoleculeValidator {
public:
	static void validateCoordinates(const vector<Atom>& atoms, const Atom& atom) {
		size_t counterElem = 0;
		size_t len = atoms.size();
		for (unsigned i = 0; i < len; i++) {
			uint8_t counterXYZ = 0;
			for (unsigned j = 0; j < MAX_COORDINATES; j++) {
				double maxDistanceDiffrence = abs(atom.getPositions()[j] - (atoms[i].getPositions())[j]);
				if (maxDistanceDiffrence < 0.5 || maxDistanceDiffrence > 2.5) {
					counterXYZ++;
					if (counterXYZ == MAX_COORDINATES)
						counterElem++;
				}
			}
		}
		if(counterElem == len && len > 1)
			throw invalid_argument("Unrealistic positioning for current molecule");
	}
												//alot of function arguments but for the OOP glory is necessary
	static bool areAvaliableForBonding(const vector<vector<Atom*>>& bonds,const vector<uint8_t>& usedElectronsInBonds,const Atom& atom1, const Atom& atom2,
																					size_t atom1Index, size_t atom2index) {
		if ((atom1.getValance() - usedElectronsInBonds[atom1Index] -
			(atom2.getValance() - usedElectronsInBonds[atom2index]) >= 0)) {

			if ((atom1.getElement()->getAtomicNumber() <= FOUR_BONDS_MAX_ATOMIC_NUMBER && amountOfBonds(atom1,bonds) < MAX_BONDS_LIGHT) &&
				(atom2.getElement()->getAtomicNumber() <= FOUR_BONDS_MAX_ATOMIC_NUMBER && amountOfBonds(atom2, bonds) < MAX_BONDS_LIGHT))
				return true;

			else if ((atom1.getElement()->getAtomicNumber() > FOUR_BONDS_MAX_ATOMIC_NUMBER && amountOfBonds(atom1, bonds) < MAX_BONDS_HEAVY) &&
				(atom2.getElement()->getAtomicNumber() > FOUR_BONDS_MAX_ATOMIC_NUMBER && amountOfBonds(atom2, bonds) < MAX_BONDS_HEAVY))
				return true;
		}
		return false;
	}

	static unsigned amountOfBonds(const Atom& atom, const vector<vector<Atom*>> & bonds) {
		unsigned counter = 0;
		for (unsigned i = 0; i < bonds.size(); i++) {
			if (&atom == bonds[i][0] || &atom == bonds[i][1])
				counter++;
		}
		return counter;
	}
};
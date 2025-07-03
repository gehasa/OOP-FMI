#pragma once
#include "Molecule.hpp"

class MoleculeBuilder {
public:
	static void bondMolecules(Molecule& mol1, Molecule& mol2) {
		mol1.addAtoms(mol2.getBondedAtomsByRef());
	}
};
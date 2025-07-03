#pragma once
#include <fstream>
#include "Molecule.hpp"

class FileHandler {
public:
	static void saveToXYZFile(const char* filePath , const Molecule& molecule) {
		ofstream file(filePath);
		if (!file) {
			throw runtime_error("Problem with file!");
		}
		
		const vector<Atom>& atoms = molecule.getBondedAtoms();
		size_t amountOfAtoms = atoms.size();
		file << amountOfAtoms; file << '\n';
		file << molecule.getName() << '\n';
		for (size_t i = 0; i < amountOfAtoms; i++) {
			const vector<float>& pos = atoms[i].getPositions();

			file << atoms[i].getElement()->getSymbol() << ' ' <<
				pos[0] << ' ' << pos[1] << ' ' << pos[2] << '\n';
		}
		file.close();
	}

    static vector<Molecule> loadMoleculesFromXYZFile(const string& filePath) {
        ifstream file(filePath);
        if (!file) {
            throw runtime_error("Cannot open input file");
        }

        vector<Molecule> molecules;
        string line;
        while (getline(file, line)) {
            unsigned atomCount = stoi(line);
            string moleculeName;
            getline(file, moleculeName);

            Molecule mol;
            mol.setMoleculeName(moleculeName);

            for (size_t i = 0; i < atomCount; ++i) {
                string symbol;
                float x, y, z;
                file >> symbol >> x >> y >> z;
                getline(file, line); //making sure i am on the line below

                const Element* elem = PeriodicTable::getInstance().getElementBySymbol(symbol);
                int protons = elem->getAtomicNumber();
                int neutrons = protons; //the elements in the periodic table are all neutral

                vector<int> electrons;
                int electronsLeft = protons;
                int currShell = 0;

                while (electronsLeft > 0) {
                    if (electrons.size() <= currShell) {
                        electrons.push_back(0); 
                    }

                    int capacity = 2 * ((currShell + 1) * (currShell + 1));
                    if (electrons[currShell] < capacity) {
                        electrons[currShell]++;
                        electronsLeft--;
                    }
                    else {
                        currShell++;
                    }
                }

                Atom atom(protons, neutrons, electrons, { x, y, z });
                mol.addAtoms(std::move(atom));
            }

            molecules.push_back(mol);
            getline(file, line);
        }
        file.close();
        return molecules;
    }

};
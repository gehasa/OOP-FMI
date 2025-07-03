#include "Atom.hpp"

constexpr unsigned MAX_ROWS = 9;
constexpr unsigned MAX_COLLUMS = 18;
static constexpr unsigned MAX_ATOMIC_NUMBER = 118;
static constexpr unsigned MAX_NEUTRONS = 176;
static constexpr unsigned MAX_ELECTRONS = 280;

class Prints {
public:

    static Prints& getInstance() {
        static Prints instance;
        return instance;
    }

    void printElementInfo(const Element* element) const{
        cout << "Element Name: " << element->getName() << '\n';
        cout << "Symbol: " << element->getSymbol() << '\n';
        cout << "Atomic Number (Protons): " << element->getAtomicNumber() << '\n';
        cout << "Block: " << element->getBlock() << '\n';
        cout << "Electronegativity: " << element->getElectronegativity() << '\n';
    }

	void printAtomInfo(const Atom& atom) const {
		printElementInfo(atom.getElement());
		cout << "Neutrons: " << atom.getNeutrons() << '\n';

		int totalElectrons = 0;
		cout << "Electrons in each shell: ";
		const vector<int> electrons = atom.getElectrons();
		for (size_t i = 0; i < electrons.size(); ++i) {
			cout << electrons[i];
			totalElectrons += electrons[i];
			if (i != electrons.size() - 1) cout << ", ";
		}
		cout << '\n';

		cout << "Total Electrons: " << totalElectrons << '\n';

		cout << "Charge State: ";
		switch (atom.getType()) {
		case TypeOfAtom::NEGATIVE_ION:
			cout << "Negative Ion\n";
			break;
		case TypeOfAtom::NEUTRAL_ION:
			cout << "Neutral Atom\n";
			break;
		case TypeOfAtom::POSITIVE_ION:
			cout << "Positive Ion\n";
			break;
		}

		cout << "Mass Number: " << atom.getMass() << '\n';
	}

    void printTable() const{
        unsigned currElemNum = 0;
        unsigned currElemSym = 0;

        for (unsigned i = 1; i <= MAX_ROWS; i++) {
            if (i == 1) {
                printRowAtomicNumbers(currElemNum, currElemNum, 1, 1);
                currElemNum++;
                printBlanks(2, 17);
                printRowAtomicNumbers(currElemNum, currElemNum, MAX_COLLUMS, MAX_COLLUMS);
                currElemNum++;
                cout << '\n';
                printRowSymbols(currElemSym, currElemSym, 1, 1);
                currElemSym++;
                printBlanks(2, 17);
                printRowSymbols(currElemSym, currElemSym, MAX_COLLUMS, MAX_COLLUMS);
                currElemSym++;
                cout << '\n';
            }
            if (i == 2 || i == 3) {
                printRowAtomicNumbers(currElemNum, currElemNum, 1, 2);
                currElemNum += 2;
                printBlanks(3, 12);
                printRowAtomicNumbers(currElemNum, ((MAX_COLLUMS - 13) + currElemNum), 13, MAX_COLLUMS);
                currElemNum = ((MAX_COLLUMS - 13) + currElemNum);
                currElemNum++;
                cout << '\n';
                printRowSymbols(currElemSym, currElemSym, 1, 2);
                currElemSym += 2;
                printBlanks(3, 12);
                printRowSymbols(currElemSym, ((MAX_COLLUMS - 13) + currElemSym), 13, MAX_COLLUMS);
                currElemSym = ((MAX_COLLUMS - 13) + currElemSym);
                currElemSym++;
                cout << '\n';
            }
            if (i == 4 || i == 5) {
                printRowAtomicNumbers(currElemNum, (currElemNum + MAX_COLLUMS - 1), 1, MAX_COLLUMS);
                currElemNum += MAX_COLLUMS;
                cout << '\n';
                printRowSymbols(currElemSym, (currElemSym + MAX_COLLUMS - 1), 1, MAX_COLLUMS);
                currElemSym += MAX_COLLUMS;
                cout << '\n';
            }
            if (i == 6 || i == 7) {
                printRowAtomicNumbers(currElemSym, currElemSym + 1, 1, 2);
                currElemNum++;
                currElemNum += MAX_COLLUMS - 3;
                printRowAtomicNumbers(currElemNum, currElemNum + 15, 3, MAX_COLLUMS);
                currElemNum += 15 + 1;
                cout << '\n';
                printRowSymbols(currElemSym, currElemSym + 1, 1, 2);
                currElemSym++;
                currElemSym += MAX_COLLUMS - 3;
                printRowSymbols(currElemSym, currElemSym + 15, 3, MAX_COLLUMS);
                currElemSym += 15 + 1;
                cout << '\n';
            }
            if (i > 7) {
                if (i == 8) {
                    currElemNum = 56;
                    currElemSym = 56;
                }
                else {
                    currElemNum = 88;
                    currElemSym = 88;
                }
                printBlanks(1, 2);
                printRowAtomicNumbers(currElemNum, (MAX_COLLUMS - 2) + currElemNum, 3, MAX_COLLUMS - 2);
                printBlanks(MAX_COLLUMS - 2, MAX_COLLUMS);
                currElemNum += (MAX_COLLUMS - 2);
                cout << '\n';
                printBlanks(1, 2);
                printRowSymbols(currElemSym, (MAX_COLLUMS - 2) + currElemSym, 3, MAX_COLLUMS - 2);
                printBlanks(MAX_COLLUMS - 2, MAX_COLLUMS);
                currElemSym += (MAX_COLLUMS - 2);
                cout << '\n';
            }
        } //Didn't want to be hardcodded, but reading it now it's even more confusing :D
            //but already put too much effort into it so i will leave it here with for cycle asweel :)

        //Hardcodded version(also effective because the table will hardly ever change):

        //// Row 1
        //printRowAtomicNumbers(0, 0, 1, 1);
        //printBlanks(2, MAX_COLLUMS - 1);
        //printRowAtomicNumbers(1, 1, MAX_COLLUMS, MAX_COLLUMS);
        //cout << '\n';
        //printRowSymbols(0, 0, 1, 1);
        //printBlanks(2, MAX_COLLUMS - 1);
        //printRowSymbols(1, 1, MAX_COLLUMS, MAX_COLLUMS);
        //cout << '\n';

        //// Row 2
        //printRowAtomicNumbers(2, 3, 1, 2);
        //printBlanks(3, MAX_COLLUMS - 6);
        //printRowAtomicNumbers(4, 9, MAX_COLLUMS - 5, MAX_COLLUMS);
        //cout << '\n';
        //printRowSymbols(2, 3, 1, 2);
        //printBlanks(3, MAX_COLLUMS - 6);
        //printRowSymbols(4, 9, MAX_COLLUMS - 5, MAX_COLLUMS);
        //cout << '\n';

        //// Row3
        //printRowAtomicNumbers(10, 11, 1, 2);
        //printBlanks(3, MAX_COLLUMS - 6);
        //printRowAtomicNumbers(12, 17, MAX_COLLUMS - 5, MAX_COLLUMS);
        //cout << '\n';
        //printRowSymbols(10, 11, 1, 2);
        //printBlanks(3, MAX_COLLUMS - 6);
        //printRowSymbols(12, 17, MAX_COLLUMS - 5, MAX_COLLUMS);
        //cout << '\n';

        //// Row 4
        //printRowAtomicNumbers(18, 35, 1, MAX_COLLUMS);
        //cout << '\n';
        //printRowSymbols(18, 35, 1, MAX_COLLUMS);
        //cout << '\n';

        //// Row 5
        //printRowAtomicNumbers(36, 53, 1, MAX_COLLUMS);
        //cout << '\n';
        //printRowSymbols(36, 53, 1, MAX_COLLUMS);
        //cout << '\n';

        //// Row 6
        //printRowAtomicNumbers(54, 55, 1, 2);
        //printBlanks(3, MAX_COLLUMS - 15);
        //printRowAtomicNumbers(56, 71, 3, MAX_COLLUMS);
        //cout << '\n';
        //printRowSymbols(54, 55, 1, 2);
        //printBlanks(3, MAX_COLLUMS - 15);
        //printRowSymbols(56, 71, 3, MAX_COLLUMS);
        //cout << '\n';

        //// Row7
        //printRowAtomicNumbers(72, 73, 1, 2);
        //printBlanks(3, MAX_COLLUMS - 15);
        //printRowAtomicNumbers(74, 89, 3, MAX_COLLUMS);
        //cout << '\n';
        //printRowSymbols(72, 73, 1, 2);
        //printBlanks(3, MAX_COLLUMS - 15);
        //printRowSymbols(74, 89, 3, MAX_COLLUMS);
        //cout << '\n';

        //// Row 8
        //printBlanks(1, 2);
        //printRowAtomicNumbers(56, 70, 3, MAX_COLLUMS - 2);
        //printBlanks(MAX_COLLUMS - 1, MAX_COLLUMS);
        //cout << '\n';
        //printBlanks(1, 2);
        //printRowSymbols(56, 70, 3, MAX_COLLUMS - 2);
        //printBlanks(MAX_COLLUMS - 1, MAX_COLLUMS);
        //cout << '\n';

        //// Row9
        //printBlanks(1, 2);
        //printRowAtomicNumbers(88, 102, 3, MAX_COLLUMS - 2);
        //printBlanks(MAX_COLLUMS - 1, MAX_COLLUMS);
        //cout << '\n';
        //printBlanks(1, 2);
        //printRowSymbols(88, 102, 3, MAX_COLLUMS - 2);
        //printBlanks(MAX_COLLUMS - 1, MAX_COLLUMS);
        //cout << '\n';
    }


    void printElementsByBlock(const string& block) const{
        for (unsigned i = 0; i < tableElements.size(); i++) {
            if (block == tableElements[i].getBlock()) {
                printElement(tableElements[i]);
            }
        }
    }

    void printElementByAtomicNumber(unsigned number) const{
        for (unsigned i = 0; i < tableElements.size(); i++) {
            if (number == tableElements[i].getAtomicNumber()) {
                printElement(tableElements[i]);
                return;
            }
        }
    }

    void printElementByName(const string& name) const{
        for (unsigned i = 0; i < tableElements.size(); i++) {
            if (name == tableElements[i].getName()) {
                printElement(tableElements[i]);
                return;
            }
        }
    }

    void printElementBySymbol(const string& symbol) const {
        for (unsigned i = 0; i < tableElements.size(); i++) {
            if (symbol == tableElements[i].getSymbol()) {
                printElement(tableElements[i]);
                return;
            }
        }
    }


private:

    const vector<Element>& tableElements;

    Prints() : tableElements(PeriodicTable::getInstance().getElements()) {}
    ~Prints() {}
    Prints(const Prints& other) = delete;
    Prints& operator=(const Prints& other) = delete;
    Prints(Prints&& other) = delete;
    Prints& operator=(Prints&& other) = delete;

	void printBlanks(unsigned startCollum, unsigned endCollum) const {
		while (startCollum <= endCollum) {
			cout << ' ';
			startCollum++;
		}
	}

	void printRowAtomicNumbers(unsigned startingElemAtomicNumber, unsigned endingElemAtomicNumber, unsigned startingCollum, unsigned endingCollum) const {
		for (unsigned i = startingCollum; i <= endingCollum; i++) {
			cout << ++startingElemAtomicNumber << ' ';
		}
	}

	void printRowSymbols(unsigned startingElem, unsigned endingElem, unsigned startingCollum, unsigned endingCollum) const {
		for (unsigned i = startingCollum; i <= endingCollum; i++) {
			cout << tableElements[startingElem++].getSymbol() << ' ';
		}
	}

	void printElement(const Element& elem) const {
		cout << "Name: " << elem.getName() << '\n';
		cout << "Symbol: " << elem.getSymbol() << '\n';
		cout << "Atomic Number: " << elem.getAtomicNumber() << '\n';
		cout << "Block: " << elem.getBlock() << '\n';
		cout << "----------------------------\n";
	}
};
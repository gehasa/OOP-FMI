#pragma once
#include "Element.hpp"

//https://www.geeksforgeeks.org/implementation-of-singleton-class-in-cpp/ for creating a singleton class
//https://www.youtube.com/watch?v=PPup1yeU45I


class PeriodicTable {
public:
    static PeriodicTable& getInstance() {
        static PeriodicTable instance;
        return instance;
    }

    const vector<Element>& getElements() const {
        return tableElements;
    }

    const Element* getElementBySymbol(const string& symbol) const {
        for (size_t i = 0; i < 118; i++) {
            if (tableElements[i].getSymbol() == symbol) {
                return &tableElements[i];
            }
        }
        throw runtime_error("Unknown element symbol: " + symbol);
    }

    const Element* getElementByNumber(int atomicNumber) const{
        if (atomicNumber < 1 || atomicNumber > 118) throw invalid_argument("Invalid atomic number");
        for (unsigned i = 0; i < tableElements.size(); i++) {
            if (tableElements[i].atomicNumber == atomicNumber) {
                return &tableElements[i];
            }
        }
    }
private:
    PeriodicTable() {}
    ~PeriodicTable() {}
    PeriodicTable(const PeriodicTable& other) = delete;
    PeriodicTable& operator=(const PeriodicTable& other) = delete;
    PeriodicTable(PeriodicTable&& other) = delete;
    PeriodicTable& operator=(PeriodicTable&& other) = delete;

    //chatGPT used for the generation of the vector
    const vector<Element> tableElements = {
        { 1, "Hydrogen", "H", "s-block", 2.20f },
        { 2, "Helium", "He", "s-block", 0.00f },
        { 3, "Lithium", "Li", "s-block", 0.98f },
        { 4, "Beryllium", "Be", "s-block", 1.57f },
        { 5, "Boron", "B", "p-block", 2.04f },
        { 6, "Carbon", "C", "p-block", 2.55f },
        { 7, "Nitrogen", "N", "p-block", 3.04f },
        { 8, "Oxygen", "O", "p-block", 3.44f },
        { 9, "Fluorine", "F", "p-block", 3.98f },
        { 10, "Neon", "Ne", "p-block", 0.00f },
        { 11, "Sodium", "Na", "s-block", 0.93f },
        { 12, "Magnesium", "Mg", "s-block", 1.31f },
        { 13, "Aluminum", "Al", "p-block", 1.61f },
        { 14, "Silicon", "Si", "p-block", 1.90f },
        { 15, "Phosphorus", "P", "p-block", 2.19f },
        { 16, "Sulfur", "S", "p-block", 2.58f },
        { 17, "Chlorine", "Cl", "p-block", 3.16f },
        { 18, "Argon", "Ar", "p-block", 0.00f },
        { 19, "Potassium", "K", "s-block", 0.82f },
        { 20, "Calcium", "Ca", "s-block", 1.00f },
        { 21, "Scandium", "Sc", "d-block", 1.36f },
        { 22, "Titanium", "Ti", "d-block", 1.54f },
        { 23, "Vanadium", "V", "d-block", 1.63f },
        { 24, "Chromium", "Cr", "d-block", 1.66f },
        { 25, "Manganese", "Mn", "d-block", 1.55f },
        { 26, "Iron", "Fe", "d-block", 1.83f },
        { 27, "Cobalt", "Co", "d-block", 1.88f },
        { 28, "Nickel", "Ni", "d-block", 1.91f },
        { 29, "Copper", "Cu", "d-block", 1.90f },
        { 30, "Zinc", "Zn", "d-block", 1.65f },
        { 31, "Gallium", "Ga", "p-block", 1.81f },
        { 32, "Germanium", "Ge", "p-block", 2.01f },
        { 33, "Arsenic", "As", "p-block", 2.18f },
        { 34, "Selenium", "Se", "p-block", 2.55f },
        { 35, "Bromine", "Br", "p-block", 2.96f },
        { 36, "Krypton", "Kr", "p-block", 3.00f },
        { 37, "Rubidium", "Rb", "s-block", 0.82f },
        { 38, "Strontium", "Sr", "s-block", 0.95f },
        { 39, "Yttrium", "Y", "d-block", 1.22f },
        { 40, "Zirconium", "Zr", "d-block", 1.33f },
        { 41, "Niobium", "Nb", "d-block", 1.60f },
        { 42, "Molybdenum", "Mo", "d-block", 2.16f },
        { 43, "Technetium", "Tc", "d-block", 1.90f },
        { 44, "Ruthenium", "Ru", "d-block", 2.20f },
        { 45, "Rhodium", "Rh", "d-block", 2.28f },
        { 46, "Palladium", "Pd", "d-block", 2.20f },
        { 47, "Silver", "Ag", "d-block", 1.93f },
        { 48, "Cadmium", "Cd", "d-block", 1.69f },
        { 49, "Indium", "In", "p-block", 1.78f },
        { 50, "Tin", "Sn", "p-block", 1.96f },
        { 51, "Antimony", "Sb", "p-block", 2.05f },
        { 52, "Tellurium", "Te", "p-block", 2.10f },
        { 53, "Iodine", "I", "p-block", 2.66f },
        { 54, "Xenon", "Xe", "p-block", 2.60f },
        { 55, "Cesium", "Cs", "s-block", 0.79f },
        { 56, "Barium", "Ba", "s-block", 0.89f },
        { 57, "Lanthanum", "La", "f-block", 1.10f },
        { 58, "Cerium", "Ce", "f-block", 1.12f },
        { 59, "Praseodymium", "Pr", "f-block", 1.13f },
        { 60, "Neodymium", "Nd", "f-block", 1.14f },
        { 61, "Promethium", "Pm", "f-block", 1.13f },
        { 62, "Samarium", "Sm", "f-block", 1.17f },
        { 63, "Europium", "Eu", "f-block", 1.20f },
        { 64, "Gadolinium", "Gd", "f-block", 1.20f },
        { 65, "Terbium", "Tb", "f-block", 1.10f },
        { 66, "Dysprosium", "Dy", "f-block", 1.22f },
        { 67, "Holmium", "Ho", "f-block", 1.23f },
        { 68, "Erbium", "Er", "f-block", 1.24f },
        { 69, "Thulium", "Tm", "f-block", 1.25f },
        { 70, "Ytterbium", "Yb", "f-block", 1.10f },
        { 71, "Lutetium", "Lu", "f-block", 1.27f },
        { 72, "Hafnium", "Hf", "d-block", 1.30f },
        { 73, "Tantalum", "Ta", "d-block", 1.50f },
        { 74, "Tungsten", "W", "d-block", 2.36f },
        { 75, "Rhenium", "Re", "d-block", 1.90f },
        { 76, "Osmium", "Os", "d-block", 2.20f },
        { 77, "Iridium", "Ir", "d-block", 2.20f },
        { 78, "Platinum", "Pt", "d-block", 2.28f },
        { 79, "Gold", "Au", "d-block", 2.54f },
        { 80, "Mercury", "Hg", "d-block", 2.00f },
        { 81, "Thallium", "Tl", "p-block", 1.62f },
        { 82, "Lead", "Pb", "p-block", 2.33f },
        { 83, "Bismuth", "Bi", "p-block", 2.02f },
        { 84, "Polonium", "Po", "p-block", 2.00f },
        { 85, "Astatine", "At", "p-block", 2.20f },
        { 86, "Radon", "Rn", "p-block", 0.00f },
        { 87, "Francium", "Fr", "s-block", 0.70f },
        { 88, "Radium", "Ra", "s-block", 0.90f },
        { 89, "Actinium", "Ac", "f-block", 1.10f },
        { 90, "Thorium", "Th", "f-block", 1.30f },
        { 91, "Protactinium", "Pa", "f-block", 1.50f },
        { 92, "Uranium", "U", "f-block", 1.38f },
        { 93, "Neptunium", "Np", "f-block", 1.36f },
        { 94, "Plutonium", "Pu", "f-block", 1.28f },
        { 95, "Americium", "Am", "f-block", 1.13f },
        { 96, "Curium", "Cm", "f-block", 1.28f },
        { 97, "Berkelium", "Bk", "f-block", 1.30f },
        { 98, "Californium", "Cf", "f-block", 1.30f },
        { 99, "Einsteinium", "Es", "f-block", 1.30f },
        { 100, "Fermium", "Fm", "f-block", 1.30f },
        { 101, "Mendelevium", "Md", "f-block", 1.30f },
        { 102, "Nobelium", "No", "f-block", 1.30f },
        { 103, "Lawrencium", "Lr", "f-block", 1.30f },
        { 104, "Rutherfordium", "Rf", "d-block", 1.30f },
        { 105, "Dubnium", "Db", "d-block", 1.30f },
        { 106, "Seaborgium", "Sg", "d-block", 1.30f },
        { 107, "Bohrium", "Bh", "d-block", 1.30f },
        { 108, "Hassium", "Hs", "d-block", 1.30f },
        { 109, "Meitnerium", "Mt", "d-block", 1.30f },
        { 110, "Darmstadtium", "Ds", "d-block", 1.30f },
        { 111, "Roentgenium", "Rg", "d-block", 1.30f },
        { 112, "Copernicium", "Cn", "d-block", 1.30f },
        { 113, "Nihonium", "Nh", "p-block", 1.30f },
        { 114, "Flerovium", "Fl", "p-block", 1.30f },
        { 115, "Moscovium", "Mc", "p-block", 1.30f },
        { 116, "Livermorium", "Lv", "p-block", 1.30f },
        { 117, "Tennessine", "Ts", "p-block", 1.30f },
        { 118, "Oganesson", "Og", "p-block", 0.00f }
    };
};
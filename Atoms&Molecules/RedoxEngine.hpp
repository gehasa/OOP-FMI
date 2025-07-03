#pragma once
#include "Atom.hpp"

class RedoxEngine {
public:
    static void oxidize(Atom& donor) {
        try {
            donor.removeElectron();
            cout << donor.getElement()->getSymbol() << " lost an electron.\n";
        }
        catch (const std::exception& e) {
            cerr << "Oxidation failed: " << e.what() << '\n';
            throw e;
        }
    }

    static void reduce(Atom& acceptor) {
        try {
            acceptor.addElectron();
            cout << acceptor.getElement()->getSymbol() << " gained an electron.\n";
        }
        catch (const std::exception& e) {
            cerr << "Reduction failed: " << e.what() << '\n';
            throw e;
        }
    }

    static void performRedox(Atom& giver, Atom& reciever) {
        try {
            giver.removeElectron();
            reciever.addElectron();
            cout << giver.getElement()->getSymbol() << " was oxidized; "
                << reciever.getElement()->getSymbol() << " was reduced.\n";
        }
        catch (const std::exception& e) {
            cerr << "Redox failed: " << e.what() << '\n';
            throw e;
        }
    }
};
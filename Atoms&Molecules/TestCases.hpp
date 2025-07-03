#pragma once
#include "MoleculeBuilder.hpp"
#include "FileHandler.hpp"

//when unrealistic coordinates are given to an atoms in a molecule it begins to look funny
//https://pubchem.ncbi.nlm.nih.gov/ - for accurate atom's coordinates
//ChatGPT used for test cases!

class TestCases {
public:
    // ---------- ELEMENT + ATOM TESTS ----------

    static void testBasicElementAccess() {
        cout << "== Test: Basic Element Access ==\n";
        const Element* oxygen = PeriodicTable::getInstance().getElementByNumber(8);
        cout << oxygen->getName() << " " << oxygen->getSymbol() << " EN=" << oxygen->getElectronegativity() << "\n\n";
    }

    static void testUnstableIsotope() {
        cout << "== Test: Unstable Isotope ==\n";
        try {
            Atom unstable(6, 20, { 2, 4 }, { 0, 0, 0 });
        }
        catch (const exception& e) {
            cout << "Caught: " << e.what() << "\n\n";
        }
    }

    static void testNegativeNeutrons() {
        cout << "== Test: Negative Neutrons ==\n";
        try {
            Atom invalid(6, -1, { 2, 4 }, { 0, 0, 0 });
        }
        catch (const exception& e) {
            cout << "Caught: " << e.what() << "\n\n";
        }
    }

    static void testTooManyElectronsInShell() {
        cout << "== Test: Too Many Electrons in Shell ==\n";
        try {
            Atom atom(6, 6, { 2, 10 }, { 0, 0, 0 }); // max is 8 in 2nd shell
        }
        catch (const exception& e) {
            cout << "Caught: " << e.what() << "\n\n";
        }
    }

    static void testAddExcessElectrons() {
        cout << "== Test: Add Electron Until Full Shell ==\n";
        Atom atom(6, 6, { 2, 7 }, { 0, 0, 0 });
        try {
            atom.addElectron(); // fills second shell
            atom.addElectron(); // triggers new shell
            atom.addElectron(); // adds to third shell
        }
        catch (const exception& e) {
            cout << "Caught: " << e.what() << "\n\n";
        }
    }

    static void testRemoveAllElectrons() {
        cout << "== Test: Remove Electron Beyond Min ==\n";
        Atom atom(6, 6, { 2, 1 }, { 0, 0, 0 });
        try {
            atom.removeElectron();
            atom.removeElectron();
        }
        catch (const exception& e) {
            cout << "Caught: " << e.what() << "\n\n";
        }
    }

    // ---------- MOLECULE TESTS ----------

    static void testValidBonding_H2O() {
        cout << "== Test: H2O Bonding ==\n";
        Molecule mol;
        Atom o(8, 8, { 2, 6 }, { 0, 0, 0 });
        Atom h1(1, 0, { 1 }, { -1, 0, 0 });
        Atom h2(1, 0, { 1 }, { 1, 0, 0 });
        mol.addAtoms(std::move(o));
        mol.addAtoms(std::move(h1));
        mol.addAtoms(std::move(h2));
        cout << "Bonded atoms: " << mol.getBondedAtoms().size() << "\n\n";
    }

    static void testInvalidBondingTooClose() {
        cout << "== Test: Invalid Bonding (Too Close) ==\n";
        try {
            Molecule mol;
            Atom h1(1, 0, { 1 }, { 0.0f, 0.0f, 0.0f });
            Atom h2(1, 0, { 1 }, { 0.1f, 0.0f, 0.0f }); // too close
            mol.addAtoms(std::move(h1));
            mol.addAtoms(std::move(h2));
        }
        catch (const exception& e) {
            cout << "Caught: " << e.what() << "\n\n";
        }
    }

    static void testMoleculeBonding() {
        cout << "== Test: Molecule Bonding ==\n";
        Molecule mol1, mol2;
        mol1.addAtoms(Atom(6, 6, { 2, 4 }, { -1.0f, 0.0f, 0.0f }));
        mol2.addAtoms(Atom(1, 0, { 1 }, { 1.5f, 0.0f, 0.0f }));
        MoleculeBuilder::bondMolecules(mol1, mol2);
        cout << "Combined atoms: " << mol1.getBondedAtoms().size() << "\n\n";
    }

    static void testMoleculeFileWrite() {
        cout << "== Test: Write to File (Valid Molecule) ==\n";
        Molecule mol;
        mol.addAtoms(Atom(6, 6, { 2, 4 }, { 0, 0, 0 }));
        mol.addAtoms(Atom(1, 0, { 1 }, { 1.0f, 0.0f, 0.0f }));
        try {
            FileHandler::saveToXYZFile("output.xyz", mol);
            cout << "File saved successfully.\n\n";
        }
        catch (const exception& e) {
            cout << "Caught file error: " << e.what() << "\n\n";
        }
    }

    static void testFileWriteEmptyMolecule() {
        cout << "== Test: Write Empty Molecule to File ==\n";
        Molecule mol;
        try {
            FileHandler::saveToXYZFile("empty.xyz", mol);
        }
        catch (const exception& e) {
            cout << "Caught: " << e.what() << "\n\n";
        }
    }

    static void testMassiveMolecule() {
        cout << "== Test: Large Molecule Stress Test ==\n";
        Molecule mol;
        for (int i = 0; i < 30; ++i) {
            float pos = i * 1.0f;
            mol.addAtoms(Atom(6, 6, { 2, 4 }, { pos, 0.0f, 0.0f }));
        }
        cout << "Large molecule: " << mol.getBondedAtoms().size() << " atoms\n\n";
    }

    static void makeWater() {
        Molecule m;
        m.addAtoms({
            Atom(1, 0, {1}, {0.9572f, 0.0000f, 0.0000f}),  // H
            Atom(1, 0, {1}, { -0.2390f, 0.9270f, 0.0000f }),     // H
            Atom(8, 8, {2,6}, {0.0000f, 0.0000f, 0.0000f}) // O (center)
        });
        m.setMoleculeName("Water");
        FileHandler::saveToXYZFile("Water.xyz", m);
    }

    static void makeSalt() {
        Molecule m;
        m.addAtoms({
            Atom(11, 12, {2,8,1}, {0.0000f, 0.0000f, 0.0000f}),  // Na
            Atom(17, 18, {2,8,7}, {2.360f, 0.0000f, 0.0000f})    // Cl (distance ~2.36 Å)
            });
        m.setMoleculeName("SodiumChloride");
        FileHandler::saveToXYZFile("SodiumChloride.xyz", m);
    }

    static void makeSulfuricAcid() {
        Molecule m;
        m.addAtoms({
            Atom(16, 16, {2,8,6}, {0.0000f, 0.0000f, 0.0000f}),  // S (center)
            Atom(8, 8, {2,6}, {1.430f, 0.0000f, 0.0000f}),       // O (double bonded)
            Atom(8, 8, {2,6}, {-1.430f, 0.0000f, 0.0000f}),      // O (double bonded)
            Atom(8, 8, {2,6}, {0.0000f, 1.430f, 0.0000f}),       // O (single bonded)
            Atom(8, 8, {2,6}, {0.0000f, -1.430f, 0.0000f}),      // O (single bonded)
            Atom(1, 0, {1}, {0.0000f, 1.970f, 0.890f}),          // H (attached to O)
            Atom(1, 0, {1}, {0.0000f, -1.970f, -0.890f})         // H (attached to O)
            });
        m.setMoleculeName("SulfuricAcid");
        FileHandler::saveToXYZFile("SulfuricAcid.xyz", m);
    }

    static void makeAmmonia() {
        Molecule m;
        m.addAtoms({
            Atom(7, 7, {2,5}, {0.0000f, 0.0000f, 0.0000f}),      // N (center)
            Atom(1, 0, {1}, {0.9377f, 0.0000f, 0.3816f}),        // H
            Atom(1, 0, {1}, {-0.4688f, 0.8121f, 0.3816f}),       // H
            Atom(1, 0, {1}, {-0.4688f, -0.8121f, 0.3816f})       // H
            });
        m.setMoleculeName("Ammonia");
        FileHandler::saveToXYZFile("Ammonia.xyz", m);
    }

    static void makeCarbonDioxide() {
        Molecule m;
        m.addAtoms({
            Atom(6, 6, {2,4}, {0.0000f, 0.0000f, 0.0000f}),      // C (center)
            Atom(8, 8, {2,6}, {-1.160f, 0.0000f, 0.0000f}),      // O
            Atom(8, 8, {2,6}, {1.160f, 0.0000f, 0.0000f})        // O
            });
        m.setMoleculeName("CarbonDioxide");
        FileHandler::saveToXYZFile("CarbonDioxide.xyz", m);
    }

    static void makeCalciumCarbonate() {
        Molecule m;
        m.addAtoms({
            Atom(20, 20, {2,8,8,2}, {0.0000f, 0.0000f, 0.0000f}), // Ca (center)
            Atom(6, 6, {2,4}, {1.0000f, 0.0000f, 0.0000f}),       // C
            Atom(8, 8, {2,6}, {1.5300f, 0.9000f, 0.0000f}),       // O
            Atom(8, 8, {2,6}, {1.5300f, -0.9000f, 0.0000f}),      // O
            Atom(8, 8, {2,6}, {2.5300f, 0.0000f, 0.0000f})        // O
            });
        m.setMoleculeName("CalciumCarbonate");
        FileHandler::saveToXYZFile("CalciumCarbonate.xyz", m);
    }

    static void makeHydrochloricAcid() {
        Molecule m;
        m.addAtoms({
            Atom(1, 0, {1}, {0.0000f, 0.0000f, 0.0000f}),      // H
            Atom(17, 18, {2,8,7}, {1.270f, 0.0000f, 0.0000f})  // Cl (bond length ~1.27 Å)
            });
        m.setMoleculeName("HydrochloricAcid");
        FileHandler::saveToXYZFile("HydrochloricAcid.xyz", m);
    }

    static void makeSodiumHydroxide() {
        Molecule m;
        m.addAtoms({
            Atom(11, 12, {2,8,1}, {0.0000f, 0.0000f, 0.0000f}),  // Na
            Atom(8, 8, {2,6}, {1.02f, 0.0000f, 0.0000f}),        // O
            Atom(1, 0, {1}, {1.58f, 0.758f, 0.0000f})            // H
            });
        m.setMoleculeName("SodiumHydroxide");
        FileHandler::saveToXYZFile("SodiumHydroxide.xyz", m);
    }

    static void makeIronOxide() {
        Molecule m;
        m.addAtoms({
            Atom(26, 30, {2,8,14,2}, {0.0000f, 0.0000f, 0.0000f}),  // Fe
            Atom(26, 30, {2,8,14,2}, {2.90f, 0.0000f, 0.0000f}),   // Fe (Fe–Fe distance ~2.9 Å)
            Atom(8, 8, {2,6}, {1.45f, 1.45f, 0.0000f}),            // O
            Atom(8, 8, {2,6}, {4.35f, 1.45f, 0.0000f}),            // O
            Atom(8, 8, {2,6}, {2.90f, 2.90f, 0.0000f})             // O
            });
        m.setMoleculeName("IronOxide");
        FileHandler::saveToXYZFile("IronOxide.xyz", m);
    }

    static void makePotassiumNitrate() {
        Molecule m;
        m.addAtoms({
            Atom(19, 20, {2,8,8,1}, {0.0000f, 0.0000f, 0.0000f}),   // K
            Atom(7, 7, {2,5}, {1.47f, 0.00f, 0.00f}),               // N
            Atom(8, 8, {2,6}, {2.90f, 0.89f, 0.00f}),               // O
            Atom(8, 8, {2,6}, {2.90f, -0.89f, 0.00f}),              // O
            Atom(8, 8, {2,6}, {1.96f, 1.76f, 0.00f})                // O
            });
        m.setMoleculeName("PotassiumNitrate");
        FileHandler::saveToXYZFile("PotassiumNitrate.xyz", m);
    }

    static void makeAspirin() {
        Molecule m;
        m.addAtoms({
            Atom(8, 8, {2, 6}, {1.2333f, 0.5540f, 0.7792f}),        // O1
            Atom(8, 8, {2, 6}, {-0.6952f, -2.7148f, -0.7502f}),     // O2
            Atom(8, 8, {2, 6}, {0.7958f, -2.1843f, 0.8685f}),       // O3
            Atom(8, 8, {2, 6}, {1.7813f, 0.8105f, -1.4821f}),       // O4
            Atom(6, 6, {2, 4}, {-0.0857f, 0.6088f, 0.4403f}),       // C5
            Atom(6, 6, {2, 4}, {-0.7927f, -0.5515f, 0.1244f}),      // C6
            Atom(6, 6, {2, 4}, {-0.7288f, 1.8464f, 0.4133f}),       // C7
            Atom(6, 6, {2, 4}, {-2.1426f, -0.4741f, -0.2184f}),     // C8
            Atom(6, 6, {2, 4}, {-2.0787f, 1.9238f, 0.0706f}),       // C9
            Atom(6, 6, {2, 4}, {-2.7855f, 0.7636f, -0.2453f}),      // C10
            Atom(6, 6, {2, 4}, {-0.1409f, -1.8536f, 0.1477f}),      // C11
            Atom(6, 6, {2, 4}, {2.1094f, 0.6715f, -0.3113f}),       // C12
            Atom(6, 6, {2, 4}, {3.5305f, 0.5996f, 0.1635f}),        // C13
            Atom(1, 0, {1}, {-0.1851f, 2.7545f, 0.6593f}),          // H14
            Atom(1, 0, {1}, {-2.7247f, -1.3605f, -0.4564f}),        // H15
            Atom(1, 0, {1}, {-2.5797f, 2.8872f, 0.0506f}),          // H16
            Atom(1, 0, {1}, {-3.8374f, 0.8238f, -0.5090f}),         // H17
            Atom(1, 0, {1}, {3.7290f, 1.4184f, 0.8593f}),           // H18
            Atom(1, 0, {1}, {4.2045f, 0.6969f, -0.6924f}),          // H19
            Atom(1, 0, {1}, {3.7105f, -0.3659f, 0.6426f}),          // H20
            Atom(1, 0, {1}, {-0.2555f, -3.5916f, -0.7337f}),        // H21
            });
        m.setMoleculeName("Aspirin");
        FileHandler::saveToXYZFile("Aspirin.xyz", m);
    }

    static void makeCaffeine() {
        Molecule m;
        m.addAtoms({
            // Purine ring carbons and nitrogens (approx coords)
            Atom(6, 6, {2,4}, {0.000f, 1.400f, 0.000f}),  // C1
            Atom(7, 7, {2,5}, {1.214f, 0.700f, 0.000f}),  // N1
            Atom(6, 6, {2,4}, {2.428f, 1.400f, 0.000f}),  // C2
            Atom(7, 7, {2,5}, {3.642f, 0.700f, 0.000f}),  // N2
            Atom(6, 6, {2,4}, {4.856f, 1.400f, 0.000f}),  // C3
            Atom(7, 7, {2,5}, {4.856f, 2.800f, 0.000f}),  // N3

            // Oxygens (carbonyl groups)
            Atom(8, 8, {2,6}, {2.428f, 2.800f, 0.000f}),  // O1
            Atom(8, 8, {2,6}, {5.700f, 0.000f, 0.000f}),  // O2

            // Methyl groups (simplified)
            Atom(6, 6, {2,4}, {-1.000f, 1.400f, 0.000f}), // methyl C1
            Atom(1, 0, {1}, {-1.700f, 2.100f, 0.000f}),   // H methyl
            Atom(6, 6, {2,4}, {5.700f, 3.500f, 0.000f}),  // methyl C2
            Atom(1, 0, {1}, {6.400f, 4.200f, 0.000f}),    // H methyl
            Atom(6, 6, {2,4}, {3.000f, -0.500f, 0.000f}), // methyl C3
            Atom(1, 0, {1}, {3.700f, -1.200f, 0.000f})    // H methyl
            });
        m.setMoleculeName("Caffeine");
        FileHandler::saveToXYZFile("Caffeine.xyz", m);
    }

    static void makeIbuprofen() {
        Molecule m;
        m.addAtoms({
            // Benzene ring carbons (approx coords)
            Atom(6, 6, {2,4}, {0.000f, 1.400f, 0.000f}),  // C1
            Atom(6, 6, {2,4}, {1.214f, 0.700f, 0.000f}),  // C2
            Atom(6, 6, {2,4}, {1.214f, -0.700f, 0.000f}), // C3
            Atom(6, 6, {2,4}, {0.000f, -1.400f, 0.000f}), // C4
            Atom(6, 6, {2,4}, {-1.214f, -0.700f, 0.000f}),// C5
            Atom(6, 6, {2,4}, {-1.214f, 0.700f, 0.000f}), // C6

            // Carboxyl group
            Atom(6, 6, {2,4}, {2.500f, 1.200f, 0.000f}),  // C (carboxyl)
            Atom(8, 8, {2,6}, {3.000f, 2.300f, 0.000f}),  // O (carbonyl)
            Atom(8, 8, {2,6}, {3.100f, 0.900f, 0.000f}),  // O (hydroxyl)

            // Isobutyl side chain (simplified)
            Atom(6, 6, {2,4}, {-2.700f, 1.400f, 0.000f}), // C (alpha)
            Atom(6, 6, {2,4}, {-3.900f, 2.000f, 0.000f}), // C (beta)
            Atom(6, 6, {2,4}, {-4.800f, 1.000f, 0.000f}), // C (gamma)
            Atom(1, 0, {1}, {-5.800f, 1.300f, 0.000f}),   // H gamma
            Atom(1, 0, {1}, {-4.800f, 0.000f, 0.900f}),   // H gamma
            Atom(1, 0, {1}, {-4.800f, 0.000f, -0.900f}),  // H gamma

            // Hydrogens (simplified)
            Atom(1, 0, {1}, {0.000f, 2.500f, 0.000f}),    // H on benzene
            Atom(1, 0, {1}, {1.900f, 1.400f, 0.000f})     // H on benzene
            });
        m.setMoleculeName("Ibuprofen");
        FileHandler::saveToXYZFile("Ibuprofen.xyz", m);
    }

    static void makePentaerythritolTetranitrate() {
        Molecule m;
        m.addAtoms({
            // Central carbon atoms (tetrahedral approx)
            Atom(6, 6, {2,4}, {0.000f, 0.000f, 0.000f}),      // C1 (central carbon)
            Atom(6, 6, {2,4}, {1.520f, 1.020f, 0.000f}),      // C2 (connected to C1)
            Atom(6, 6, {2,4}, {-1.520f, 1.020f, 0.000f}),     // C3
            Atom(6, 6, {2,4}, {-1.520f, -1.020f, 0.000f}),    // C4
            Atom(6, 6, {2,4}, {1.520f, -1.020f, 0.000f}),     // C5

            // Hydrogens on central carbons (approximate)
            Atom(1, 0, {1}, {0.000f, 0.000f, 1.090f}),        // H on C1
            Atom(1, 0, {1}, {2.050f, 1.650f, 0.000f}),        // H on C2
            Atom(1, 0, {1}, {-2.050f, 1.650f, 0.000f}),       // H on C3
            Atom(1, 0, {1}, {-2.050f, -1.650f, 0.000f}),      // H on C4
            Atom(1, 0, {1}, {2.050f, -1.650f, 0.000f}),       // H on C5

            // Oxygen atoms of nitrate groups (approximate positions)
            // Nitrate group 1 attached to C1
            Atom(7, 7, {2,5}, {0.000f, 0.000f, -1.400f}),     // N1
            Atom(8, 8, {2,6}, {0.800f, 0.000f, -2.200f}),     // O1a
            Atom(8, 8, {2,6}, {-0.800f, 0.800f, -1.800f}),    // O1b
            Atom(8, 8, {2,6}, {-0.800f, -0.800f, -1.800f}),   // O1c

            // Nitrate group 2 attached to C2
            Atom(7, 7, {2,5}, {2.500f, 1.200f, 0.000f}),      // N2
            Atom(8, 8, {2,6}, {3.200f, 1.800f, -0.600f}),     // O2a
            Atom(8, 8, {2,6}, {2.800f, 0.800f, 0.900f}),      // O2b
            Atom(8, 8, {2,6}, {1.700f, 1.900f, -0.400f}),     // O2c

            // Nitrate group 3 attached to C3
            Atom(7, 7, {2,5}, {-2.500f, 1.200f, 0.000f}),     // N3
            Atom(8, 8, {2,6}, {-1.800f, 1.800f, -0.600f}),    // O3a
            Atom(8, 8, {2,6}, {-2.200f, 0.800f, 0.900f}),     // O3b
            Atom(8, 8, {2,6}, {-3.300f, 1.900f, -0.400f}),    // O3c

            // Nitrate group 4 attached to C4
            Atom(7, 7, {2,5}, {-1.500f, -2.200f, 0.000f}),    // N4
            Atom(8, 8, {2,6}, {-1.000f, -2.900f, -0.600f}),   // O4a
            Atom(8, 8, {2,6}, {-2.100f, -2.300f, 0.900f}),    // O4b
            Atom(8, 8, {2,6}, {-1.300f, -1.700f, -0.400f})    // O4c
            });
        m.setMoleculeName("PentaerythritolTetranitrate");
        FileHandler::saveToXYZFile("PentaerythritolTetranitrate.xyz", m);
    }

    // Function to call all make functions
    static void generateAllMolecules() {
        makeWater();
        makeSalt();
        makeSulfuricAcid();
        makeAmmonia();
        makeCarbonDioxide();
        makeCalciumCarbonate();
        makeHydrochloricAcid();
        makeSodiumHydroxide();
        makeIronOxide();
        makePotassiumNitrate();
        makeAspirin();
        makeCaffeine();
        makeIbuprofen();
        makePentaerythritolTetranitrate();
    }

    static void testAtomChargeType() {
        cout << "== Test: Atom Charge Classification ==\n";
        Atom neg(6, 7, { 2, 4 }, { 0, 0, 0 });
        Atom neu(6, 6, { 2, 4 }, { 0, 0, 0 });
        Atom pos(6, 5, { 2, 4 }, { 0, 0, 0 });

        cout << "Negative type: " << (neg.getType() == NEGATIVE_ION ? "OK" : "Fail") << '\n';
        cout << "Neutral type: " << (neu.getType() == NEUTRAL_ION ? "OK" : "Fail") << '\n';
        cout << "Positive type: " << (pos.getType() == POSITIVE_ION ? "OK" : "Fail") << "\n\n";
    }

    static void testAddRemoveElectronBehavior() {
        cout << "== Test: Add/Remove Electron Behavior ==\n";
        Atom atom(6, 6, { 2, 7 }, { 0, 0, 0 });
        atom.addElectron(); // should create new shell
        atom.addElectron(); // adds to new shell
        atom.removeElectron(); // removes from outer shell
        atom.removeElectron(); // back to shell 2

        const vector<int>& e = atom.getElectrons();
        cout << "Shells after operations: ";
        for (auto x : e) cout << x << ' ';
        cout << "\n\n";
    }

    static void testValenceComputation() {
        cout << "== Test: Valence Calculation ==\n";
        Atom atom(6, 6, { 2, 4 }, { 0, 0, 0 });
        cout << "Valence: " << atom.getValance() << " (Expected: 4)\n\n";
    }

    static void testPeriodicLookupByNumber() {
        cout << "== Test: Periodic Table Lookup by Atomic Number ==\n";
        const Element* el = PeriodicTable::getInstance().getElementByNumber(8);
        cout << "Symbol: " << el->getSymbol() << ", Name: " << el->getName() << "\n\n";
    }

    static void testSaveAndLoadXYZ() {
        cout << "== Test: Save & Reload XYZ Molecule ==\n";
        Molecule m;
        m.setMoleculeName("TestXYZ");
        m.addAtoms({
            Atom(1, 0, {1}, {0.0f, 0.0f, 0.0f}),
            Atom(8, 8, {2,6}, {0.0f, 0.0f, 1.0f})
            });

        FileHandler::saveToXYZFile("testxyz.xyz", m);
        vector<Molecule> loaded = FileHandler::loadMoleculesFromXYZFile("testxyz.xyz");
        cout << "Loaded molecule: " << loaded[0].getName() << " with " << loaded[0].getBondedAtoms().size() << " atoms\n\n";
    }

    static void testBondingLogic() {
        cout << "== Test: Bonding Two Molecules ==\n";
        Molecule m1, m2;
        m1.addAtoms(Atom(6, 6, { 2, 4 }, { -1.0f, 0.0f, 0.0f }));
        m2.addAtoms(Atom(1, 0, { 1 }, { 1.5f, 0.0f, 0.0f }));

        MoleculeBuilder::bondMolecules(m1, m2);
        cout << "After bonding: " << m1.getBondedAtoms().size() << " atoms total\n\n";
    }

    static void testAtomValidatorRejection() {
        cout << "== Test: AtomValidator Realism Check ==\n";
        try {
            Atom a(6, 30, { 2, 4 }, { 0, 0, 0 });
        }
        catch (const exception& e) {
            cout << "Caught expected: " << e.what() << "\n\n";
        }
    }

    static void testFullAtomRejection() {
        cout << "== Test: Reject Full Atom from Bonding ==\n";
        Molecule m;
        Atom full(2, 2, { 2 }, { 0, 0, 0 }); // He
        m.addAtoms(full); // should print warning but not throw
        cout << "Atoms in molecule: " << m.getBondedAtoms().size() << " (Expected: 0)\n\n";
    }



    static void testAll() {

        TestCases::testBasicElementAccess();
        TestCases::testUnstableIsotope();
        TestCases::testNegativeNeutrons();
        TestCases::testTooManyElectronsInShell();
        TestCases::testAddExcessElectrons();
        TestCases::testRemoveAllElectrons();

        TestCases::testAtomChargeType();
        TestCases::testAddRemoveElectronBehavior();
        TestCases::testValenceComputation();
        TestCases::testPeriodicLookupByNumber();
        TestCases::testSaveAndLoadXYZ();
        TestCases::testBondingLogic();
        TestCases::testAtomValidatorRejection();
        TestCases::testFullAtomRejection();



        //generateAllMolecules();
        //createWaterMolecule();
        /*testBasicElementAccess();
        testUnstableIsotope();
        testNegativeNeutrons();
        testTooManyElectronsInShell();
        testAddExcessElectrons();
        testRemoveAllElectrons();

        testValidBonding_H2O();
        testInvalidBondingTooClose();
        testMoleculeBonding();

        testMoleculeFileWrite();
        testFileWriteEmptyMolecule();
        testMassiveMolecule();*/
    }
};


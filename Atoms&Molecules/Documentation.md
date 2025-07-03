# Atoms & Molecules

**Author:** Tsvetan Kotuzov

This project simulates atoms and molecules, focusing on the principles of inorganic chemistry. It models how atoms bond, how molecules are built, and includes engines for simulating chemical reactions like redox processes.

---

## How the Project Works

### PeriodicTable (Singleton)

- The class `PeriodicTable` is a **singleton**, ensuring only one instance exists.
- **Elements** can only be created through `PeriodicTable`.
- Whenever an element is needed, `PeriodicTable::getInstance()` is called to fetch the single shared instance.

---

### Element

- Represents a chemical element.
- Can only be created by `PeriodicTable`.
- Stores:
  - Symbol
  - Name
  - Atomic number (protons)

---

### Atom

- Holds a pointer to an `Element` from the `PeriodicTable`.
- Provides:
  - Symbol, name, atomic number via the linked `Element`
  - Valence electron calculations
- Created only if validated by `AtomValidator`.

---

### AtomValidator

- Validates:
  - Physical realism of the atom
  - Coordinates when creating atoms

---

### Molecule

- A **collection of atoms** bonded together.
- Handles:
  - Creating bonds following inorganic chemistry rules
  - Decomposing and recomposing bonds to track electron usage
    - Enables future support for lone pairs and accurate bonding models

---

### MoleculeBuilder

- Utility for building molecules by using methods from the `Molecule` class.

---

### MoleculeValidator

- Validates:
  - Coordinates of atoms
  - Whether two atoms can bond
  - How many bonds an atom has

---

### RedoxEngine

- Executes:
  - Oxidation reactions
  - Reduction reactions
  - Ion exchange reactions

---

### Prints

- Singleton class for **console output**.
- Singleton used to avoid redundant copies and to maintain a constant reference to the `PeriodicTable`.

---

### TestCases

- A class for experimenting with the system.
- Many test cases generated with ChatGPT.
- For realistic molecules, real coordinates are used from:
  [PubChem](https://pubchem.ncbi.nlm.nih.gov/)

---

## Notable Methods

- **`PeriodicTable::getInstance`**  
  Returns the single instance of `PeriodicTable` for memory efficiency.

- **`Molecule::addAtom`**  
  Overloaded to support:
  - Move semantics
  - Vector operations

- **`Atom::getValance`**  
  Returns how many electrons are needed to fill the outermost electron shell.

---

## Future Additions

- Lone pair electron handling
- Support for:
  - Organic chemistry
  - Physical chemistry
  - Analytical chemistry
  - Biochemistry
- MOL file handling for molecule import/export

---

## Resources

- **Singleton Pattern**
  - [GeeksforGeeks](https://www.geeksforgeeks.org/implementation-of-singleton-class-in-cpp/)
  - [Singleton Pattern - YouTube](https://www.youtube.com/watch?v=PPup1yeU45I)

- **Test Cases**
  - [ChatGPT](https://chatgpt.com/)
  - [PubChem Database](https://pubchem.ncbi.nlm.nih.gov/)

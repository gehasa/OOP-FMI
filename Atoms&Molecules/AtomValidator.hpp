#pragma once
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class AtomValidator {
private:
	AtomValidator() = delete;
	~AtomValidator() = delete;
	AtomValidator(const AtomValidator&) = delete;
	AtomValidator& operator=(const AtomValidator&) = delete;
	AtomValidator(AtomValidator&&) = delete;
	AtomValidator& operator=(AtomValidator&&) = delete;
public:
	static void validateElectrons(const vector<int>& electrons) {
		for (unsigned i = 0; i < electrons.size(); i++) {
			if (electrons[i] < 0) throw invalid_argument("Electron's number can't be negative");
			unsigned n = i + 1;
			if (electrons[i] > 2 * (n * n)) throw invalid_argument("Invalid electrons count in shell No: " + std::to_string(i + 1) + '\n');
		}
	}

	static void validateAtomRealism(int protons, int neutrons, const vector<int>& electrons) {
		if (neutrons < 0) throw invalid_argument("Invalid neutrons");
		if (protons <= 0) throw invalid_argument("Invalid protons");

		int electronsSum = 0;
		for (unsigned i = 0; i < electrons.size(); i++) {
			electronsSum += electrons[i];
		}
		if (electronsSum < 0) throw invalid_argument("Invalid electrons");

		if (electronsSum <= 0 || electronsSum > protons * 4) throw invalid_argument("Bad proton to electron ratio");

		if (protons == 1 && neutrons == 0) {
			return;
		}

		double ratio = static_cast<double>(neutrons) / protons;
		if (ratio < 0.5 || ratio > 2.5) throw invalid_argument("Highly unstable isotope");
	}

	static void validateCoordinates(const vector<float>& position) {
		for (unsigned i = 0; i < position.size(); i++) {
			if (abs(position[i]) > 30.00) throw invalid_argument("Position is off boundaries"); //to be in boundaries for the rendering program
		}
	}

	static void validateLonePairs(uint8_t pairs) {
		if (pairs > 4) throw invalid_argument("Lone pairs can't exceed 4");
	}

	static bool isFullAtom(const vector<int>& electrons) {
		size_t n = electrons.size();
		int temp = (n * n) * 2;
		int temp2 = electrons[n - 1];
		return temp == temp2;
	}
};
/* 
Fatima Ishtiaq
section E
23i-0696
*/

#include <iostream>
using namespace std;
#include"ComputerComponents.h";

int main() {
	cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
	cout << "////////////////////////////////////////////////////////// Welcome //////////////////////////////////////////////////////////" << endl;
	cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
	cout << endl;
	int ch;
	do {
		cout << "Enter the option of your choice: " << endl;
		cout << "1. PC" << endl;
		cout << "2. MAC" << endl;
		cin >> ch;
	} while (ch != 1 && ch != 2);
	cout << endl;
	if (ch == 1) {
		checks::check = true;
	}
	if (checks::check) {
		IntelAMDCPU IntAmdCpu;
		cout << "The CPU has successfully been made." << endl;
		cout << endl;
		GPU g;
		cout << endl;
		PhysicalMemory pm;
		cout << endl;
		MainMemory mm;
		cout << endl;

		int b_r = 0;
		string s;

		s = "VGI";
		Port p1;
		cout << endl;
		p1.setType(s);
		b_r = p1.getBaudRate();

		s = "I/O";
		Port p2;
		cout << endl;
		p2.setType(s);
		p2.setBaudRate(b_r);

		s = "USB";
		Port p3;
		cout << endl;
		p3.setType(s);
		p3.setBaudRate(b_r);

		s = "HDMI";
		Port p4;
		cout << endl;
		p4.setType(s);
		p4.setBaudRate(b_r);


		int temp = checks::num_ports;
		MotherBoard m(mm, &p1, &p2, &p3, &p4, temp);
		cout << "Mother board has successfully been created." << endl;
		cout << endl;

		IA_Computer comp(&pm, &m, &IntAmdCpu);
		HDD hdd;
		NetworkCard nc;
		PowerSupply ps;
		Battery b;
		Case c;
		ComputerAssembly_PC CA(&comp, &hdd, &g, &nc, &ps, &b, &c);
		cout << "The Computer Assembly has successfully been made." << endl;
		cout << endl << endl << endl;
		cout << "Your PC has finally been created" << endl;

		CA.display();
	}
	else {
		AppleSiliconCPU appleSiliconCpu;
		cout << endl;
		cout << "The CPU has successfully been made." << endl;
		cout << endl;
		PhysicalMemory pm;
		cout << endl;
		MainMemory mm;
		cout << endl;

		int b_r = 0;
		string s;

		s = "VGI";
		Port p1;
		cout << endl;
		p1.setType(s);
		b_r = p1.getBaudRate();

		s = "I/O";
		Port p2;
		cout << endl;
		p2.setType(s);
		p2.setBaudRate(b_r);

		s = "USB";
		Port p3;
		cout << endl;
		p3.setType(s);
		p3.setBaudRate(b_r);

		s = "HDMI";
		Port p4;
		cout << endl;
		p4.setType(s);
		p4.setBaudRate(b_r);

		int temp = checks::num_ports;
		MotherBoard m(mm, &p1, &p2, &p3, &p4, temp);
		cout << "Mother board has successfully been created." << endl;
		AS_Computer comp(&pm, &m, &appleSiliconCpu);
		HDD hdd;
		cout << endl;
		NetworkCard nc;
		cout << endl;
		PowerSupply ps;
		cout << endl;
		Battery b;
		cout << endl;
		Case c;
		cout << endl;
		ComputerAssembly_Mac CAM(&comp, &hdd, &nc, &ps, &c, &b);

		cout << "The Computer Assembly has successfully been made." << endl;
		CAM.display();
	}
	return 0;
}

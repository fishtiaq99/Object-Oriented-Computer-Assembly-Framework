#pragma once
#include <iostream>
using namespace std;

struct checks {
    static bool check; //Will be true if we are making a PC
    static bool check2; //Will only take the baud rate once even when 4 ports are created
    static int num_ports; //number of ports: 4
};
bool checks::check = false;
bool checks::check2 = true;
int checks::num_ports = 4;
class ALU {
    //typical values: 
    //ALU macALU(8, 8, 32, 64);
    //ALU pcALU(4, 4, 16, 32);
    //but not necessarily limited to these 
    int NoOfAdders;     //practical ranges: 4-32
    int NoOfSubtractors;//practical ranges: 4-32
    int NoOfRegisters;  //practical ranges: 8-64
    int sizeOfRegisters;//practical ranges: 4-32
public:
    ALU() : NoOfAdders(0), NoOfSubtractors(0), NoOfRegisters(0), sizeOfRegisters(0) { aluInput(); }


    void aluInput() {//only 1 function as it can be used for both PC and Mac
        do {
            cout << "Enter the number of adders (practical range: 4-32): ";
            cin >> NoOfAdders;
        } while (NoOfAdders < 4 || NoOfAdders > 32);

        do {
            cout << "Enter the number of subtractors (practical range: 4-32): ";
            cin >> NoOfSubtractors;
        } while (NoOfSubtractors < 4 || NoOfSubtractors > 32);

        do {
            cout << "Enter the number of registers (practical range: 8-64): ";
            cin >> NoOfRegisters;
        } while (NoOfRegisters < 8 || NoOfRegisters > 64);

        do {
            cout << "Enter the size of registers (practical range: 4-32): ";
            cin >> sizeOfRegisters;
        } while (sizeOfRegisters < 4 || sizeOfRegisters > 32);

    }
    void aluDisplay() {
        cout << "Number of Adders: " << NoOfAdders << endl;
        cout << "Number of Subtractors: " << NoOfSubtractors << endl;
        cout << "Number of Registers: " << NoOfRegisters << endl;
        cout << "Size of Registers: " << sizeOfRegisters << endl;
    }

};

class ControlUnit {
    float clock; //practical range: 1.0 GHz - 5.5 GHz
public:
    ControlUnit() : clock(0.0) { controlunitInput(); }
    void controlunitInput() {
        do {
            cout << "Enter the clock speed (practical range: 1.0 - 5.5): ";
            cin >> clock;
        } while (clock < 1.0 || clock > 5.5);
    }
    void controlunitDisplay() {
        cout << "Clock Speed: " << clock << " GHz" << endl;
    }
};

//class CPU which is composed of ALU and CU: Composition
class CPU {
    ALU alu;
    ControlUnit cu;
public:
    CPU() : alu(), cu() {}
    ALU& getALU() { return alu; }
    ControlUnit& getCU() { return cu; }
    void setALU(ALU& a) { alu = a; }
    void setCU(ControlUnit& c) { cu = c; }
};

//Nvidia, AMD or AppleGPU is a type of GPU (inheritance). Nvidia and AMD GPUs are discrete, while AppleGPU is integrated in the CPU.
class GPU {
    string brand;//Nvidia for PC. Apple for Mac
    int memorySize;//Practical size: 2-32 GB
    double price;

public:
    GPU() : brand(" "), memorySize(0), price(0.0) { InputGPU(); }
    GPU(string& b, int s, double p) : brand(b), memorySize(s), price(p) {}
    string& getBrand() { return brand; }
    void setBrand(string& b) { brand = b; }
    void setMemorySize(int size) { memorySize = size; }
    void setPrice(double p) { price = p; }

    int getMemorySize() { return memorySize; }
    double getPrice() { return price; }
    void InputGPU() {
        if (checks::check) {
            brand = "Nvidia";
            cout << "The brand set is Nvidia as a PC is being created" << endl;
            do {
                cout << "Enter the memory size of the GPU (practical range: 2 - 32): ";
                cin >> memorySize;
            } while (memorySize < 2 || memorySize > 32);
            price = 600;
        }
        else {
            brand = "Apple";
            cout << "The brand set is Apple as a Mac is being created " << endl;
            do {
                cout << "Enter the memory size of the GPU (practical range: 2 - 32): ";//taking it twice idk whyyy
                cin >> memorySize;
            } while (memorySize < 2 || memorySize > 32);
            price = 700;
        }
    }
    void displayGPU() {
        cout << "The brand is " << brand << endl;
        cout << "The memory size is " << memorySize << " GB" << endl;
        cout << "The price is " << price << endl;
    }
};

//Intel / AMD CPUs or AppleSilicon is a CPU: Inheritance 
class IntelAMDCPU : public CPU {
    string architecture;
public:
    IntelAMDCPU(string arch = " ") {
        architecture = arch;
        InputIntelAMDCPU();
    }
    void InputIntelAMDCPU() {
        architecture = "x86";
        cout << "The architecture x86 has been set for Intel/AMD systems" << endl;
    }
    void displayIntelAMDCPU() {
        cout << "The syatem architecture is " << architecture << endl;
    }
};


class AppleSiliconCPU : public CPU { //AppleGPU is integrated in the CPU (Composition)
    string architecture;
    GPU gp;
public:
    AppleSiliconCPU(string arch = " ", GPU gpu = GPU(), CPU cp = CPU()) : CPU(cp), architecture(arch), gp(gpu) {}
    void setArchitecture(string& arch) { architecture = arch; }
    void setGPU(GPU& gpu) { gp = gpu; }
    GPU& getGPU() { return gp; }
    string& getArchitecture() { return architecture; }

    void InputAppleSiliconCPU() {
        architecture = "ARM64";
        cout << "The architecture ARM64 has been set for Apple Silicon systems" << endl;
    }
    void displayAppleSiliconCPU() {
        cout << "The system architecture is " << architecture << endl;
    }
};

class PhysicalMemory {

    string PMbrand;//DDR4 for Intel and AMD systems. LPDDR4/5 for Apple Silicon based systems.
    int capacity;  //practical range: 4GB - 64GB for DDR4. practical range: 2GB - 16GB for LPDDR4
public:
    PhysicalMemory(int c = 0, string pm = " ") : capacity(c), PMbrand(pm) { InputPhysicalMemory(); }
    void setCapacity(int c, string pm) { capacity = c; PMbrand = pm; }
    int getCapacity() { return capacity; }
    void InputPhysicalMemory() {
        if (checks::check) {
            PMbrand = "DDR4";//practical range: 4GB - 64GB
            cout << "The Physical Memory DDR4 has been set for Intel and AMD systems" << endl;
            do {
                cout << "Enter the capacity for the Physical Memory (practical range: 4GB - 64GB): ";
                cin >> capacity;
            } while (capacity < 4 || capacity>64);
        }
        else {
            PMbrand = "LPDDR4/5";//practical range: 2GB - 16GB
            cout << "The Physical Memory LPDDR4/5 has been set for Apple Siliconn systems (practical range: 2GB - 16GB)" << endl;
            do {
                cout << "Enter the capacity for the Physical Memory: ";
                cin >> capacity;
            } while (capacity < 2 || capacity>16);
        }
    }
    void displayPhysicalMemory() {
        cout << "The physical Memory is " << PMbrand << endl;
        cout << "The capacity is " << capacity << " GB" << endl;
    }
};

class MainMemory {
    int capacity;//practical range: 4GB - 64GB
    string technologyType;//silicon and semiconductor

public:
    MainMemory() : capacity(0), technologyType("") { InputMainMemory(); }
    MainMemory(int cap, string& tech) : capacity(cap), technologyType(tech) {}
    int getCapacity() { return capacity; }
    void setCapacity(int cap) { capacity = cap; }
    string& getTechnologyType() { return technologyType; }
    void setTechnologyType(string& tech) { technologyType = tech; }
    void InputMainMemory() {
        int temp;
        do {
            cout << "Enter the technology type of the main memory:\n1.Silicon\n2.Semiconductor\n ";
            cin >> temp;
            if (temp == 1) {
                technologyType = "Silicon";
            }
            else {
                technologyType = "Semiconductor";
            }
        } while (temp != 1 && temp != 2);

        do {
            cout << "Enter the capacity of the main memory (practical range: 4GB - 64GB): ";
            cin >> capacity;
        } while (capacity < 4 || capacity>64);
    }
    void displayMainMemory() {
        cout << "The capacity of the main memory is " << capacity << endl;
        cout << "The technology type is " << technologyType << endl;
    }
};

class Port {
    string type; //VGI Port,I/O Port,USB Port,HDMI Port
    int baud_rate;//typical baud rate ranges can vary from 300 bps to 115200 bps
    Port* link;
public:
    Port() : type(""), baud_rate(0), link(nullptr) {
        if (checks::check2) {
            InputPort();
            checks::check2 = false;
        }
    }
    Port(string& t, int br, Port* l) : type(t), baud_rate(br), link(l) {}
    string& getType() { return type; }
    void setType(string& t) { type = t; }
    int getBaudRate() { return baud_rate; }
    void setBaudRate(int br) { baud_rate = br; }
    void setlink(Port* l) { link = l; }
    Port* getlink() { return link; }
    void InputPort() {
        int temp;
        cout << "4 ports will be included: VGI Port, I/O Port, USB Port, HDMI Port" << endl;
        do {
            cout << "Enter the baud rate practical range (300 bps - 115200 bps) ";
            cin >> temp;
            baud_rate = temp;
        } while (temp < 300 || temp>115200);
    }
    void displayPort() {
        cout << "4 ports have been included: VGI Port, I/O Port, USB Port, HDMI Port " << type << endl;
        cout << "The baud rate is " << baud_rate << "bps" << endl;
    }

};


//class MotherBoard which is composed(Composition) of
//Ports(IO ports, VGI ports etc) and aggregated (Aggregation) 
//with MainMemory :
//for composition, call the destructor of ports in the 
//destructor of the mother board 

class MotherBoard {
    MainMemory* mm;
    Port* start; //ports array of size 4
    int numPorts;

public:
    MotherBoard() : mm(nullptr), start(nullptr), numPorts(0) {}
    MotherBoard(MainMemory& m, Port* p, Port* q, Port* r, Port* s, int n) : mm(new MainMemory(m)), numPorts(n) {
        start = p;
        p = q;
        q = r;
        r = s;
    }
    ~MotherBoard() {
        delete mm;
        Port* current = start;
        while (current != nullptr) {
            Port* temp = current;
            current = current->getlink();
            temp->setlink(nullptr);
        }
        delete mm;
    }

    MainMemory& getMainMemory() { return *mm; }
    void setMainMemory(MainMemory& memory) { *mm = memory; }
    Port* getPorts() { return start; }
    int getNumPorts() { return numPorts; }
};

//Design a class Computer which is aggregated of PhysicalMemory, CPU and MotherBoard (Aggregation)
//These components form the core of a computer system
class IA_Computer {//Computer with the Intel AMD CPU
    PhysicalMemory* pm;
    MotherBoard* mb;
    IntelAMDCPU* cpu;

public:
    IA_Computer() : pm(nullptr), mb(nullptr), cpu(nullptr) {}
    IA_Computer(PhysicalMemory* mem, MotherBoard* m, IntelAMDCPU* i) : pm(mem), mb(m), cpu(i) {}
    ~IA_Computer() {
        delete pm;
        delete mb;
        delete cpu;
    }
    void IAsetPhysicalMemory(PhysicalMemory* mem) { pm = mem; }
    void IAsetMotherBoard(MotherBoard* m) { mb = m; }
    void IAsetCPU(IntelAMDCPU* i) { cpu = i; }
    PhysicalMemory* IAgetPhysicalMemory() { return pm; }
    MotherBoard* IAgetMotherBoard() { return mb; }
    IntelAMDCPU* IAgetCPU() { return cpu; }
};

class AS_Computer {//Computer with the apple silicon CPU
    PhysicalMemory* pm;
    MotherBoard* mb;
    AppleSiliconCPU* cpu;

public:
    AS_Computer() : pm(nullptr), mb(nullptr), cpu(nullptr) {}
    AS_Computer(PhysicalMemory* mem, MotherBoard* m, AppleSiliconCPU* a) : pm(mem), mb(m), cpu(a) {}
    ~AS_Computer() {
        delete pm;
        delete mb;
        delete cpu;
    }
    void ASsetPhysicalMemory(PhysicalMemory* mem) { pm = mem; }
    void ASsetMotherBoard(MotherBoard* m) { mb = m; }
    void ASsetCPU(AppleSiliconCPU* a) { cpu = a; }
    PhysicalMemory* ASgetPhysicalMemory() { return pm; }
    MotherBoard* ASgetMotherBoard() { return mb; }
    AppleSiliconCPU* ASgetCPU() { return cpu; }
};

class HDD { //storage device
    string type; //consumer HDD or NAS HDD
    int capacity; //1TB - 8TB for consumer HDD. 1 TB to 16 TB for NAS HDD
    double price;//$100 for consumer HDD. $150 for NAS HDD

public:
    HDD() : type(""), capacity(0), price(0.0) { InputHDD(); }//BASIC COMPUTERRRRR
    HDD(string& t, int cap, double p)
        : type(t), capacity(cap), price(p) {}
    string& getType() { return type; }
    void setType(string& t) { type = t; }
    int getCapacity() { return capacity; }
    void setCapacity(int cap) { capacity = cap; }
    double getPrice() { return price; }
    void setPrice(double p) { price = p; }
    void InputHDD() {
        int temp;
        do {
            cout << "Enter the type of HDD\n1.Consumer HDD\n2.NAS HDD\n";
            cin >> temp;
            if (temp == 1) {
                type = "Consumer HDD";
                do {
                    cout << "Enter the capacity range for Consumer HDD (practical range: 1TB - 8TB)";
                    cin >> capacity;
                } while (capacity < 1 || capacity>8);
                price = 100;
                break;
            }
            else if (temp == 2) {
                type = "NAS HDD";
                do {
                    cout << "Enter the capacity range for NAS HDD (practical range: 1TB - 16TB)";
                    cin >> capacity;
                } while (capacity < 1 || capacity>16);
                price = 150;
                break;
            }
        } while (1);

    }
    void displayHDD() {
        cout << "The type is " << type << endl;
        cout << "The capacity is " << capacity << "TB" << endl;
    }
};
//both consumer HDDs and NAS HDDs can be used with
//  Intel, AMD, and Apple Silicon-based systems, as 
// long as the system supports the connection interface 
// of the hard disk drive (e.g., SATA, NVMe for SSDs) 
// and the required power supply.

class NetworkCard {
    string type;//Ethernet or Wi-Fi
    int speed;//typical range for ethernet: 10-100 mbps //typical range for wifi: 300-600 mbps
    double price;//$100 for ethernet. $200 for wifi

public:
    NetworkCard() : type(""), speed(0), price(0.0) { InputNetwordCard(); }
    NetworkCard(string& t, int s, double p) : type(t), speed(s), price(p) {}
    void setType(string& t) { type = t; }
    void setPrice(double p) { price = p; }
    void setSpeed(int s) { speed = s; }
    int getSpeed() { return speed; }
    double getPrice() { return price; }
    string& getType() { return type; }
    void InputNetwordCard() {
        int temp;
        do {
            cout << "Enter the type of network card\n1.Ethernet \n2.Wi-Fi\n";
            cin >> temp;
            if (temp == 1) {
                type = "Ethernet";
                do {
                    cout << "Enter the speed range for Ethernet (typical range: 10TB - 100TB)";
                    cin >> speed;
                } while (speed < 10 || speed>100);
                price = 100;
                break;
            }
            else if (temp == 2) {
                type = "Wi-Fi";
                do {
                    cout << "Enter the speed range for Wi-Fi (typical range: 300TB - 600TB)";
                    cin >> speed;
                } while (speed < 300 || speed>600);
                price = 200;
                break;
            }
        } while (1);
    }
    void DisplayNetwordCard() {
        cout << "The type of Network card is " << type << endl;
        cout << "The speed is " << speed << " TB" << endl;
    }

};

class PowerSupply {
    string efficiencyRating;//80 Plus Bronze //80 Plus Gold 
    int wattage;//450-850 watts for 80 Plus Bronze. 550-1000 watts for 80 Plus Gold
    double price;//$100 for 80 Plus Bronze. $150 for 80 Plus Gold

public:
    PowerSupply() : wattage(0), efficiencyRating(""), price(0.0) { InputPowerSupply(); }
    PowerSupply(int w, string& rating, double p) : wattage(w), efficiencyRating(rating), price(p) {}
    void setWattage(int w) { wattage = w; }
    void setEfficiencyRating(string& rating) { efficiencyRating = rating; }
    void setPrice(double p) { price = p; }
    int getWattage() { return wattage; }
    string& getEfficiencyRating() { return efficiencyRating; }
    double getPrice() { return price; }
    void InputPowerSupply() {
        int temp;
        do {
            cout << "Enter the efficiency rating for the power supply\n1.80 Plus Bronze \n2.80 Plus Gold\n";
            cin >> temp;
            if (temp == 1) {
                efficiencyRating = "80 Plus Bronze";
                do {
                    cout << "Enter the wattage for 80 Plus Bronze (typical range: 450-850 watts)";
                    cin >> wattage;
                } while (wattage < 450 || wattage>850);
                price = 100;
                break;
            }
            else if (temp == 2) {
                efficiencyRating = "80 Plus Gold";
                do {
                    cout << "Enter the wattage for 80 Plus Gold (typical range: 550-1000 watts)";
                    cin >> wattage;
                } while (wattage < 550 || wattage>1000);
                price = 150;
                break;
            }
        } while (1);
    }
    void displayPowerSupply() {
        cout << "The efficiency rating is " << efficiencyRating << endl;
        cout << "The wattage is " << wattage << " Watt" << endl;
    }


};

class Battery {
    int capacity;//typical ranage (2000-10000 mAh)
public:
    Battery() : capacity(0) { InputBattery(); }
    Battery(int cap) : capacity(cap) {}
    int getCapacity() const { return capacity; }
    void setCapacity(int cap) { capacity = cap; }
    void InputBattery() {
        do {
            cout << "Enter the capacity the battery (typical range: 2000-10000 mAh)";
            cin >> capacity;
        } while (capacity < 2000 || capacity>10000);
    }
    void displayBattery() {
        cout << "The capacity of the battery is " << capacity << " mAh" << endl;
    }
};

class Case { //only for Mac so just aggregate it in the computer assembly class for Mac.
    string formFactor;//ATX or Micro ATX
    string color;//3 colors to choose from 
    double price;//$50 for ATX. $100 for Micro ATX

public:
    Case() : formFactor(""), color(""), price(0.0) { InputCase(); }
    Case(string& form, string& col, double p) : formFactor(form), color(col), price(p) {}
    string& getFormFactor() { return formFactor; }
    void setFormFactor(string& form) { formFactor = form; }
    string& getColor() { return color; }
    void setColor(string& col) { color = col; }
    double getPrice() const { return price; }
    void setPrice(double p) { price = p; }
    void InputCase() {
        int temp;
        do {
            cout << "Enter the form factor for the Case\n1.ATX \n2.Micro ATX\n";
            cin >> temp;
            if (temp == 1) {
                formFactor = "ATX";
                price = 50;
                break;
            }
            else if (temp == 2) {
                formFactor = "Micro ATX";
                price = 100;
                break;
            }
        } while (1);

        do {
            cout << "Enter the color for the Case\n1.Blue \n2.Green\n3.Brown\n";
            cin >> temp;
            if (temp == 1) {
                color = "Blue";
                break;
            }
            else if (temp == 2) {
                color = "Green";
                break;
            }
            else if (temp == 3) {
                color = "Brown";
                break;
            }
        } while (1);
    }
    void displayCase() {
        cout << "The form factor is " << formFactor << endl;
        cout << "The color is " << color << endl;
    }
};
class ComputerAssembly {
    HDD* storage;
    NetworkCard* networkCard;
    PowerSupply* powerSupply;
    Case* computerCase;
    Battery* battery;

public:
    ComputerAssembly() : storage(nullptr), networkCard(nullptr), powerSupply(nullptr), computerCase(nullptr), battery(nullptr) {}
    ComputerAssembly(HDD* hdd, NetworkCard* nc, PowerSupply* p, Case* c, Battery* b) : storage(hdd), networkCard(nc), powerSupply(p), computerCase(c), battery(b) {}

    ~ComputerAssembly() {
        delete storage;
        delete networkCard;
        delete powerSupply;
        delete computerCase;
        delete battery;
    }

    HDD* getStorage() { return storage; }
    NetworkCard* getNetworkCard() { return networkCard; }
    PowerSupply* getPowerSupply() { return powerSupply; }
    Case* getComputerCase() { return computerCase; }
    Battery* getBattery() { return battery; }
    void setStorage(HDD* hdd) { storage = hdd; }
    void setNetworkCard(NetworkCard* c) { networkCard = c; }
    void setPowerSupply(PowerSupply* p) { powerSupply = p; }
    void setComputerCase(Case* c) { computerCase = c; }
    void setBattery(Battery* b) { battery = b; }
};


class ComputerAssembly_PC : public ComputerAssembly {
    IA_Computer* IAcomputer;
    GPU* graphicsCard;

public:
    ComputerAssembly_PC() : IAcomputer(nullptr), graphicsCard(nullptr) {}
    ComputerAssembly_PC(IA_Computer* a, HDD* b, GPU* c, NetworkCard* d, PowerSupply* e, Battery* f, Case* g)
        : ComputerAssembly(b, d, e, g, f), IAcomputer(a), graphicsCard(c) {
    }

    ~ComputerAssembly_PC() {
        delete IAcomputer;
        delete graphicsCard;
    }

    void display() {
        IAcomputer->IAgetCPU()->getALU().aluDisplay();
        IAcomputer->IAgetCPU()->getCU().controlunitDisplay();
        graphicsCard->displayGPU();
        IAcomputer->IAgetMotherBoard()->getPorts()->displayPort();
        IAcomputer->IAgetMotherBoard()->getMainMemory().displayMainMemory();
        IAcomputer->IAgetPhysicalMemory()->displayPhysicalMemory();
        getStorage()->displayHDD();
        getNetworkCard()->DisplayNetwordCard();
        getPowerSupply()->displayPowerSupply();
        getBattery()->displayBattery();
        getComputerCase()->displayCase();
        cout << "The total price is $";
        cout << calculate_price();
        return;
    }

    double calculate_price() {
        double price = 0;
        price = price + getStorage()->getPrice() + graphicsCard->getPrice() + getNetworkCard()->getPrice() + getPowerSupply()->getPrice() + getComputerCase()->getPrice();
        return price;
    }
};

class ComputerAssembly_Mac : public ComputerAssembly {
    AS_Computer* AScomputer;

public:
    ComputerAssembly_Mac() : AScomputer(nullptr) {}
    ComputerAssembly_Mac(AS_Computer* a, HDD* b, NetworkCard* c, PowerSupply* d, Case* e, Battery* f)
        : ComputerAssembly(b, c, d, e, f), AScomputer(a) {
    }

    ~ComputerAssembly_Mac() {
        delete AScomputer;
    }

    void display() {
        AScomputer->ASgetCPU()->getALU().aluDisplay();
        AScomputer->ASgetCPU()->getCU().controlunitDisplay();
        AScomputer->ASgetMotherBoard()->getPorts()->displayPort();
        AScomputer->ASgetMotherBoard()->getMainMemory().displayMainMemory();
        AScomputer->ASgetPhysicalMemory()->displayPhysicalMemory();
        getStorage()->displayHDD();
        getNetworkCard()->DisplayNetwordCard();
        getPowerSupply()->displayPowerSupply();
        getBattery()->displayBattery();
        getComputerCase()->displayCase();
        cout << "The total price is $";
        cout << calculate_price();
        return;
    }

    double calculate_price() {
        double price = 0;
        price = price + getStorage()->getPrice() + getNetworkCard()->getPrice() + getPowerSupply()->getPrice();
        return price;
    }
};

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Device {
private:
    string name;
    string type;
public:
    Device(const string& deviceType, const string& deviceName) : type(deviceType), name(deviceName) {}
    virtual void poll() {
        cout << name << endl;
        // Некоторая реализация получения данных, которую вам делать
        // не нужно.
    }
};

class ElectricEnergyMeter: public Device {
public:
    ElectricEnergyMeter(const string& deviceType, const string& deviceName): Device(deviceType, deviceName) {}
};

class DisctretSignalInputUnit : public Device {
public:
    DisctretSignalInputUnit(const string& deviceType, const string& deviceName) : Device(deviceType, deviceName) {}
};

class HeatingControlUnit : public Device {
public:
    HeatingControlUnit(const string& deviceType, const string& deviceName) : Device(deviceType, deviceName) {}
};

class SmartHouse {
private:
    vector<Device*> devices;
    string deviceType, deviceName;
    void deviceLoad(string path) {
        ifstream input(path);
        while (input >> deviceType >> deviceName) {
            if (deviceType == "ElectricEnergyMeter") {
                devices.push_back(new ElectricEnergyMeter(deviceType, deviceName));
            }
            else if (deviceType == "DisctretSignalInputUnit") {
                devices.push_back( new DisctretSignalInputUnit(deviceType, deviceName));
            }
            else if (deviceType == "HeatingControlUnit") {
                devices.push_back(new HeatingControlUnit(deviceType, deviceName));
            }
        }
    }
public:
    SmartHouse(string deviceList) {
        deviceLoad(deviceList);
    }
    
    ~SmartHouse() {
        for (auto device : devices) {
            delete device;
        }
    }

    void showInfo() {
        for (auto device : devices) {
            device->poll();
        }
    }

};


int main()
{
    SmartHouse smartHouse("devices.txt");
    smartHouse.showInfo();
}


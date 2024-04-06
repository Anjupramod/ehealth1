// Ensure this library description is only included once
#ifndef eHealthClass_h
#define eHealthClass_h

#include "Arduino.h"

// Library interface description
class eHealthClass {
public:

    // Constructor of the class
    eHealthClass(void);

    // Public Methods
    void initPositionSensor(void);
    void readBloodPressureSensor(void);
    void initPulsioximeter(void);
    float getTemperature(void);
    int getOxygenSaturation(void);
    int getBPM(void);
    float getSkinConductance(void);
    float getSkinResistance(void);
    float getSkinConductanceVoltage(void);
    float getECG(void);
    int getEMG(void);
    uint8_t getBodyPosition(void);
    int getSystolicPressure(int i);
    int getDiastolicPressure(int i);
    int getAirFlow(void);
    void printPosition(uint8_t position);
    void readPulsioximeter(void);
    void airFlowWave(int air);
    void readGlucometer(void);
    uint8_t getGlucometerLength(void);
    uint8_t getBloodPressureLength(void);
    int version(void);
    String numberToMonth(int month);

    // Struct to store data of the glucometer
    struct glucoseData {
        uint8_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minutes;
        uint8_t glucose;
        uint8_t meridian;
    };

    // Vector to store the glucometer measures and dates
    glucoseData glucoseDataVector[8];

    // Struct to store data of the blood pressure sensor
    struct bloodPressureData {
        uint8_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minutes;
        uint8_t systolic;
        uint8_t diastolic;
        uint8_t pulse;
    };

    // Vector to store the blood pressure measures and dates
    bloodPressureData bloodPressureDataVector[8];

private:

    // Private Methods
    void initMMA8452(byte fsr, byte dataRate);
    void MMA8452Standby();
    void MMA8452Active();
    void readRegisters(byte address, int i, byte *dest);
    byte readRegister(uint8_t address);
    void writeRegister(unsigned char address, unsigned char data);
    void portraitLandscapeHandler();
    void bodyPosition(void);
    uint8_t segToNumber(uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F, uint8_t G);
    char swap(char _data);

    // Private Variables
    int systolic;
    int diastolic;
    int BPM;
    int SPO2;
    uint8_t bodyPos;
    byte data[6];
    int accelCount[3];
    float accel[3];
    uint8_t position[8]; // Define size here to avoid flexible array member issue
    uint8_t length;
};

extern eHealthClass eHealth;

#endif

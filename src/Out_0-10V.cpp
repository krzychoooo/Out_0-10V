#include <Out_0-10V.h>

#define NUMCALIBRATEPOINT 11

const uint16_t codes[NUMCALIBRATEPOINT]={58, 459, 858, 1260, 1659, 2060, 2462, 2860, 3257, 3657, 4058};
const uint16_t voltages[NUMCALIBRATEPOINT]={0, 1002, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};

Out_0_10V::Out_0_10V(MCP4725 *MCP4725_Obj){
    this->_MCP4725Obj = MCP4725_Obj;
}

Out_0_10V::~Out_0_10V(){
}

void Out_0_10V::setVoltage(uint16_t miliVolt){
    uint16_t maxMilivolt, minMilivolt, minCode, maxCode;

    if (miliVolt>10000) miliVolt = 10000;
    
    for (size_t i = 0; i < NUMCALIBRATEPOINT; i++){
        if (miliVolt == voltages[i]){
            minMilivolt = maxMilivolt = miliVolt;
            minCode = maxCode = codes[i];
            break;
        }
        
        if (miliVolt < voltages[i]){
            minMilivolt = voltages[i-1];
            maxMilivolt = voltages[i];
            minCode = codes[i-1];
            maxCode = codes[i];
            break;
        }
    }
    

    uint16_t code = map(miliVolt, minMilivolt, maxMilivolt, minCode, maxCode);
    Serial.print("map="); Serial.println(code);
    _MCP4725Obj->setValue(code);
}

void Out_0_10V::begin(uint16_t limes0V, uint16_t limes10V){
    this->_limes0V = limes0V;
    this->_limes10V = limes10V;
}
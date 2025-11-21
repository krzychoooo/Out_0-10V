#include <Out_0-10V.h>


Out_0_10V::Out_0_10V(MCP4725 *MCP4725_Obj){
    this->_MCP4725Obj = MCP4725_Obj;
}

Out_0_10V::~Out_0_10V()
{
}

void Out_0_10V::setVoltage(uint16_t miliVolt){
    uint16_t i = map(miliVolt, 0, 10000, this->_limes0V, this->_limes10V);
    Serial.print("map="); Serial.println(i);
    _MCP4725Obj->setValue(i);

}

void Out_0_10V::begin(uint16_t limes0V, uint16_t limes10V){
    this->_limes0V = limes0V;
    this->_limes10V = limes10V;
}
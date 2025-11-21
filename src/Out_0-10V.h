#ifndef BA4D035E_6024_4C11_BAB6_76DE8DCB088D
#define BA4D035E_6024_4C11_BAB6_76DE8DCB088D

#include <Arduino.h>
#include <MCP4725.h>

class Out_0_10V
{
private:
    uint16_t _limes0V;
    uint16_t _limes10V;
    MCP4725 *_MCP4725Obj;

public:
    void setVoltage(uint16_t miliVvolt);
    void begin(uint16_t limes0V, uint16_t limes10V);

    Out_0_10V(MCP4725 *MCP4725_Obj);
    ~Out_0_10V();
};



#endif /* BA4D035E_6024_4C11_BAB6_76DE8DCB088D */

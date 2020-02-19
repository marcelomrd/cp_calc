#include "cantera/IdealGasMix.h"

#include <cstdio>

using namespace Cantera;

void cp_calc()
{
    IdealGasMix gas("gri30.cti","gri30_mix");
    double temp = 300.0;
    double pres = OneAtm;
    int nsp = gas.nSpecies();

    int type;
    doublereal c[15];
    doublereal minTemp, maxTemp, refPressure;

    MultiSpeciesThermo& sp = gas.speciesThermo();

    doublereal tab_air[] ={1005, 1013, 1029, 1051, 1075, 1098, 1121, 1141, 1159, 1174, 1188, 1200, 1211, 1220, 1229, 1237, 1244, 1250};

    int n, j, i;
    double cp;

    i=0;

    writelog("   Temp      cp_mix      NASA7      Table\n");

    do
    {
        gas.setState_TPY(temp, pres, "O2:0.233,N2:0.767");
        // gas.setState_TPY(temp, pres, "CH4:0.055,O2:0.22,N2:0.725");
        cp = 0.0;
        for (n = 0; n < nsp; n++)
        {
            sp.reportParams(n, type, c, minTemp, maxTemp, refPressure);

            if (temp<1000.0)
            {
                cp = cp + ( c[8] + c[9]*temp + c[10]*pow(temp,2.0) + c[11]*pow(temp,3.0) + c[12]*pow(temp,4.0)) * gas.massFraction(n)/(gas.molecularWeight(n)/1000.0);
            }
            if (temp>=1000.0)
            {
                cp = cp + ( c[1] + c[2]*temp + c[3]*pow(temp,2.0) + c[4]*pow(temp,3.0) + c[5]*pow(temp,4.0)) * gas.massFraction(n)/(gas.molecularWeight(n)/1000.0);
            }
        }

        cp = cp * 8.314;        

        writelog("{:10.4F} {:10.4F} {:10.4F} {:10.4F} \n", gas.temperature(), gas.cp_mass(), cp, tab_air[i]);
        temp = temp + 100.0;
        i=i+1;
    } while(temp<2100.0);
}

int main()
{
    try {
        cp_calc();
    } catch (CanteraError& err) {
        std::cout << err.what() << std::endl;
    }
}


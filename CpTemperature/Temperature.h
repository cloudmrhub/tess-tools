#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include "Data3d.h"
#include "Data1d.h"

class Siminfo;

class Temperature : public Data3d
{


public:

    Temperature(int Tx, int Ty, int Tz);
    ~Temperature();


    void fdtd(Siminfo* SimFDTD, Temperature* Told, Data3d* SAR, Data3d* W, Data3d* W0, Data3d* R, Data3d* Q, Data3d* C, Data3d* K, Data1d* posx, Data1d* posy, Data1d* posz, Data1d* Tblood, Data1d* scaleSAR);

    void fdtdconvec(Siminfo* SimFDTD, Temperature* Told, Data3d* SAR, Data3d* W, Data3d* W0, Data3d* R, Data3d* Q, Data3d* C, Data3d* K, Data1d* posx, Data1d* posy, Data1d* posz, Data1d* Tblood, Data1d* scaleSAR);

    void printtemp(Data3d *R, Data3d *C, Data3d *SAR, Data3d *W, Data3d *Q, Siminfo *SimFDTD, char* filename);
    void printtemp4(Siminfo *SimFDTD, char* filename);

    int checkair(Data3d *R, int i, int j, int k);

};

#endif

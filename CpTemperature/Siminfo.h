#ifndef SIMINFO_H
#define SIMINFO_H
#include "Data3d.h"
#include "Data1d.h"
//#include "Temperature.h"

class Temperature;

class Siminfo
{

public:

    Siminfo(char *fileParams);
    ~Siminfo();

    int Nx, Ny, Nz, zmin, zmax;
    float dx, dy, dz, dt;
    long maxsavetime, sizeT0V, DeltaSave;
    double heatingtime, eps, hconvecparam;
    char outputfile[150];


    void readparam(char *filetoread);

    void readfiles(Temperature* Told, Data3d* SAR, Data3d* W, Data3d* R, Data3d* Q, Data3d* C, Data3d* K, Data1d* posx, Data1d* posy, Data1d* posz, Data1d* Tblood, Data1d* scaleSAR, char* filetoread);


    void set(int posx, int posy, int posz, double data);
    double get(int posx, int posy, int posz);

    //void fdtd(Temperature *T, Temperature *Told, Data3d *SAR, Data3d *W, Data3d *W0, Data3d *R, Data3d *Q, Data3d *C, Data3d *K, Data1d *posx, Data1d *posy, Data1d *posz, Data1d *Tblood, Data1d *scaleSAR);
};

#endif

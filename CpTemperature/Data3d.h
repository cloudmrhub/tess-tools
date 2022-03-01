#ifndef DATA3D_H
#define DATA3D_H

class Data3d
{
protected:
    double ***dataarray;

public:

    Data3d(int Tx, int Ty, int Tz);
    ~Data3d();

    int Nx, Ny, Nz;
    double Air;
    double Blood;

    void set(int posx, int posy, int posz, double data);
    double get(int posx, int posy, int posz);
    void loaddata(long sizeT0V, char *filetoread);
    void copy(Data3d *Orig);
    void airReset();


};

#endif

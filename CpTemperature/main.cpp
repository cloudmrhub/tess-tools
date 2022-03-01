#include <iostream>
#include "Data1d.h"
#include "Data3d.h"
#include "Temperature.h"
#include "Siminfo.h"
#include <stdio.h>

using namespace std;


int main(int argc, char **argv) {

  cout << "Pre Pre";

  //This is a little trick to assign a string
  char* filename;
  string s = "Parameters.dat";
  filename = &s[0];


    Siminfo Fdtd(filename);



    Data3d R(Fdtd.Nx, Fdtd.Ny, Fdtd.Nz);
    Data3d C(Fdtd.Nx, Fdtd.Ny, Fdtd.Nz);
    Data3d W(Fdtd.Nx, Fdtd.Ny, Fdtd.Nz);
    Data3d W0(Fdtd.Nx, Fdtd.Ny, Fdtd.Nz);
    Temperature Told(Fdtd.Nx, Fdtd.Ny, Fdtd.Nz);
    Data3d SAR(Fdtd.Nx, Fdtd.Ny, Fdtd.Nz);
    Data3d Q(Fdtd.Nx, Fdtd.Ny, Fdtd.Nz);
    Data3d K(Fdtd.Nx, Fdtd.Ny, Fdtd.Nz);
    Temperature T(Fdtd.Nx, Fdtd.Ny, Fdtd.Nz);

    cout << "Pre Pos";

    Data1d posx(Fdtd.Nx, Fdtd.dx);
    Data1d posy(Fdtd.Ny, Fdtd.dy);
    Data1d posz(Fdtd.Nz, Fdtd.dz);
    Data1d Tblood(Fdtd.heatingtime);
    Data1d scaleSAR(Fdtd.heatingtime, 1);


    cout << "Pre Load";

    Fdtd.readfiles(&Told, &SAR, &W, &R, &Q, &C, &K, &posx, &posy, &posz, &Tblood, &scaleSAR, filename);



    W0.copy(&W);
    T.copy(&Told);



    //T.fdtd(&Fdtd, &Told, &SAR, &W, &W0, &R, &Q, &C, &K, &posx, &posy, &posz, &Tblood, &scaleSAR);
    T.fdtdconvec(&Fdtd, &Told, &SAR, &W, &W0, &R, &Q, &C, &K, &posx, &posy, &posz, &Tblood, &scaleSAR);


    cout << "Tblood 1 2 =" << Tblood.get(0) << " " << Tblood.get(1) ;
    cout << "posx 1 2 =" << posx.get(0) << " " << posx.get(1);
    cout << "posy 1 2 =" << posy.get(0) << " " << posy.get(1);



    //T.fdtd(&R, &C);

    cout << "R="<< R.get(100, 100, 200) << " + C=" << C.get(19, 20, 21) <<" = Tfdtd =" << T.get(20, 20, 21) << endl;



    return 0;
}



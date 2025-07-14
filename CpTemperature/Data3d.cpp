#include "Data3d.h"
#include <iostream>
//#include <malloc.h>
#include "stdlib.h"
#include <stdio.h>


// Date constructor
Data3d::Data3d(int Tx, int Ty, int Tz)
{
  Nx = Tx;
  Ny = Ty;
  Nz = Tz;
  //std::cout<< "Entrato constructor";
  int i, j, k;
  Air=0;
  Blood=0;
  //std::cout<< "Entrato constructor";
  dataarray = new double**[Nx];
    for(i=0;i<Nx;i++){
      //std::cout<< "Dentro for =" << i <<"\n";
		dataarray[i]=(double**)malloc(Ny*sizeof(double));
		for(j=0;j<Ny;j++){
			dataarray[i][j]=(double*)malloc(Nz*sizeof(double));
		}
    }

    for(i=0;i<Nx;i++){for(j=0;j<Ny;j++){for(k=0;k<Nz;k++){dataarray[i][j][k]=Air;}}}
}

Data3d::~Data3d()
{
  //delete [] dataarray;

  //std::cout<< "Destructor";
}



// Date member function
void Data3d::set(int posx, int posy, int posz, double data){
    dataarray[posx][posy][posz]=data;
}


double Data3d::get(int posx, int posy, int posz)
{
    return dataarray[posx][posy][posz];
}

void Data3d::loaddata(long int sizeT0V, char* filetoread)
{

  FILE *param3;

  char line[150], dummy[100];

  int i, j, k;
  long n;
  double temp;



  param3 = fopen (filetoread, "r");

  if (param3==NULL) {
        printf("File %s not found\n", filetoread);
        exit(0);
    }

  for(n=1; n<=sizeT0V; n++){
	fscanf(param3,"%i %i %i %lf\n",&i,&j,&k,&temp);
	if (i<Nx && i>=0 && j<Ny && j>=0 && k<Nz && k>=0) {
        	dataarray[i][j][k]=temp;
        	}
	}
  fclose(param3);

}

void Data3d::copy(Data3d* Orig)
{
  int i, j, k;
  Air = Orig->Air;
  Blood = Orig->Blood;
  for(i=0; i<Nx; i++) {
    for(j=0; j<Ny; j++) {
      for(k=0; k<Nz; k++) {
	dataarray[i][j][k]=Orig->get(i,j,k);
      }
    }
  }
}

void Data3d::airReset()
{

  int i, j, k;
  for(i=0; i<Nx; i++) {
    for(j=0; j<Ny; j++) {
      for(k=0; k<Nz; k++) {
	dataarray[i][j][k]=Air;
      }
    }
  }

}

#include "Siminfo.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include "Temperature.h"
//#include <malloc.h>

// Date constructor
Siminfo::Siminfo(char* fileParams)
{
  FILE *param;

  param = fopen(fileParams, "r");

  fscanf(param, "Nx = %d\n", &Nx);
  printf("Nx = %d\n", Nx);
  fscanf(param, "Ny = %d\n", &Ny);
  printf("Ny = %d\n", Ny);
  fscanf(param, "Nz = %d\n", &Nz);
  printf("Nz = %d\n", Nz);
  fscanf(param, "dx = %f\n", &dx);
  printf("dx = %f\n", dx);
  fscanf(param, "dy = %f\n", &dy);
  printf("dy = %f\n", dy);
  fscanf(param, "dz = %f\n", &dz);
  printf("dz = %f\n", dz);
  fscanf(param, "dt = %f\n", &dt);
  printf("dt = %f\n", dt);
  fscanf(param, "zmin = %d\n", &zmin);
  printf("zmin = %d\n", zmin);
  fscanf(param, "zmax = %d\n", &zmax);
  printf("zmax = %d\n", zmax);
  fscanf(param, "maxsavetime = %ld\n", &maxsavetime);
  printf("maxsavetime = %ld\n", maxsavetime);
  fscanf(param, "DeltaSave = %ld\n", &DeltaSave);
  printf("DeltaSave = %ld\n", DeltaSave);
  fscanf(param, "heatingtime = %lf\n", &heatingtime);
  printf("heatingtime = %lf\n", heatingtime);
  fscanf(param, "eps = %lf\n", &eps);
  printf("eps = %e\n", eps);

  fclose(param);
}


Siminfo::~Siminfo()
{

}


void Siminfo::readfiles(Temperature* Told, Data3d* SAR, Data3d* W, Data3d* R, Data3d* Q, Data3d* C, Data3d* K, Data1d* posx, Data1d* posy, Data1d* posz, Data1d* Tblood, Data1d* scaleSAR, char* filetoread)
{

  FILE *param;
  char line[150];
  int k;
  int len;

  param = fopen (filetoread, "r");
  for (k=0; k< 13; k++) {
    fgets(line, 190, param);
    //fscanf(param, "%s", line);
    //printf("%s\n", line);
    }

  fscanf(param, "Cblood = %lf\n", &C->Blood);
  printf("Cblood = %lf\n", C->Blood);
  fscanf(param, "Rblood = %lf\n", &R->Blood);
  printf("Rblood = %lf\n", R->Blood);
  fscanf(param, "Tblood = %lf\n", &Told->Blood);
  printf("Tblood = %lf\n", Told->Blood);
  Tblood->defval= Told->Blood;

  fscanf(param, "Wair = %lf\n", &W->Air);
  printf("Wair = %lf\n", W->Air);
  W->airReset();
  fscanf(param, "Rair = %lf\n", &R->Air);
  printf("Rair = %lf\n", R->Air);
  R->airReset();
  fscanf(param, "Cair = %lf\n", &C->Air);
  printf("Cair = %lf\n", C->Air);
  C->airReset();
  fscanf(param, "Kair = %lf\n", &K->Air);
  printf("Kair = %lf\n", K->Air);
  K->airReset();
  fscanf(param, "Qair = %lf\n", &Q->Air);
  printf("Qair = %lf\n", Q->Air);
  Q->airReset();
  fscanf(param, "Tair = %lf\n", &Told->Air);
  printf("Tair = %lf\n", Told->Air);
  Told->airReset();
  fscanf(param, "T0V = %ld\n", &sizeT0V);
  printf("sizeT = %ld\n", sizeT0V);

  fscanf(param, "Toldfile = %s\n", line);

//loadvar(Told, sizeT0V, "Told.dat");

  printf("Reading Told\n");

  Told->loaddata(sizeT0V, line);
  fscanf(param, "SARfile = %s\n", line);

  printf("Reading SAR\n");

  SAR->loaddata(sizeT0V, line);
  fscanf(param, "Wfile = %s\n", line);

  printf("Reading W\n");

  W->loaddata(sizeT0V, line);

  fscanf(param, "Rfile = %s\n", line);

  printf("Reading R\n");

  R->loaddata(sizeT0V, line);
  fscanf(param, "Qfile = %s\n", line);

  printf("Reading Q\n");

  Q->loaddata(sizeT0V, line);
  fscanf(param, "Cfile = %s\n", line);

  printf("Reading C\n");

  C->loaddata(sizeT0V, line);
  fscanf(param, "Kfile = %s\n", line);

  printf("Reading K\n");

  K->loaddata(sizeT0V, line);
  fscanf(param, "outputfile = %s\n", line);

  strcpy(outputfile, line);

  fscanf(param, "Posxfile = %s\n", line);

  printf("Posxfile = %s\n", line);
  posx->loaddata(line);
  fscanf(param, "Posyfile = %s\n", line);

  printf("Posyfile = %s\n", line);
  posy->loaddata(line);
  fscanf(param, "Poszfile = %s\n", line);

  printf("Poszfile = %s\n", line);
  posz->loaddata(line);

  fscanf(param, "Tbloodfile = %s\n", line);
  printf("Tbloodfile = %s\n", line);
  Tblood->loaddata(line);

  fscanf(param, "scaleSARfile = %s\n", line);
  printf("scaleSARfile = %s\n", line);
  scaleSAR->loaddata(line);

  fscanf(param, "hconvec = %lf\n", &hconvecparam);
  printf("hconvec = %lf\n", hconvecparam);

  fclose(param);

}


/*
void Siminfo::fdtd(Temperature *T, Temperature *Told, Data3d *SAR, Data3d *W, Data3d *W0, Data3d *R, Data3d *Q, Data3d *C, Data3d *K, Data1d *posx, Data1d *posy, Data1d *posz, Data1d *Tblood, Data1d *scaleSAR)
{
  double err=1e5;
  double errE=1e5;
  long step=0;
  long brdrstep=0;
  long indtime = 0;
  long timmod;
  int i, j, k;

  double nStep=heatingtime/dt;
  double TempBlood = Tblood->get(0);
  double scalefactor=0;
  double Ttm1;
  double temp, temp1;
  double h1x, h2x, dKdx, dTdx, dT2dx2, gradx, h1y, h2y, dKdy, dTdy, dT2dy2, grady, h1z, h2z, dKdz, dTdz, dT2dz2, gradz;

	//while(errE>eps){
	while(step<nStep && errE>eps){
	//while(step<10){
		step+=1;
		timmod = (long)(step*dt);
		TempBlood = Tblood->get(timmod);
		scalefactor = scaleSAR->get(timmod);

		errE=0;


		for(i=7;i<(Nx-7);i++){
			for(j=7;j<(Ny-7);j++){
				for(k=(zmin)-1;k<(zmin)+1;k++){
					if(R->get(i,j,k)>100){

					Ttm1=Told->get(i,j,k);



					h2x = posx->get(i+1)-posx->get(i);
					h1x = posx->get(i)-posx->get(i-1);

					dKdx = -(h2x/(h1x*(h1x+h2x)))*K->get(i-1,j,k)+((h2x/(h1x*(h1x+h2x)))-(h1x/(h2x*(h1x+h2x))))*K->get(i,j,k)+(h1x/(h2x*(h1x+h2x)))*K->get(i+1,j,k);
					dTdx = -(h2x/(h1x*(h1x+h2x)))*Told->get(i-1,j,k)+((h2x/(h1x*(h1x+h2x)))-(h1x/(h2x*(h1x+h2x))))*Told->get(i,j,k)+(h1x/(h2x*(h1x+h2x)))*Told->get(i+1,j,k);
					dT2dx2= (2/(h1x*(h1x+h2x)))*Told->get(i-1,j,k)+(-(2/(h1x*(h1x+h2x)))-(2/(h2x*(h1x+h2x))))*Told->get(i,j,k)+(2/(h2x*(h1x+h2x)))*Told->get(i+1,j,k);
					gradx = dKdx*dTdx+K->get(i,j,k)*dT2dx2;

					h2y = posy->get(j+1)-posy->get(j);
					h1y = posy->get(j)-posy->get(j-1);
					dKdy = -(h2y/(h1y*(h1y+h2y)))*K->get(i,j-1,k)+((h2y/(h1y*(h1y+h2y)))-(h1y/(h2y*(h1y+h2y))))*K->get(i,j,k)+(h1y/(h2y*(h1y+h2y)))*K->get(i,j+1,k);
					dTdy = -(h2y/(h1y*(h1y+h2y)))*Told->get(i,j-1,k)+((h2y/(h1y*(h1y+h2y)))-(h1y/(h2y*(h1y+h2y))))*Told->get(i,j,k)+(h1y/(h2y*(h1y+h2y)))*Told->get(i,j+1,k);
					dT2dy2= (2/(h1y*(h1y+h2y)))*Told->get(i,j-1,k)+(-(2/(h1y*(h1y+h2y)))-(2/(h2y*(h1y+h2y))))*Told->get(i,j,k)+(2/(h2y*(h1y+h2y)))*Told->get(i,j+1,k);
					grady = dKdy*dTdy+K->get(i,j,k)*dT2dy2;


					h2z = posz->get(k+1)-posz->get(k);
					h1z = posz->get(k)-posz->get(k-1);
					dKdz = -(h2z/(h1z*(h1z+h2z)))*K->get(i,j,k-1)+((h2z/(h1z*(h1z+h2z)))-(h1z/(h2z*(h1z+h2z))))*K->get(i,j,k)+(h1z/(h2z*(h1z+h2z)))*K->get(i,j,k+1);
					dTdz = -(h2z/(h1z*(h1z+h2z)))*Told->get(i,j,k-1)+((h2z/(h1z*(h1z+h2z)))-(h1z/(h2z*(h1z+h2z))))*Told->get(i,j,k)+(h1z/(h2z*(h1z+h2z)))*Told->get(i,j,k+1);
					dT2dz2= (2/(h1z*(h1z+h2z)))*Told->get(i,j,k-1)+(-(2/(h1z*(h1z+h2z)))-(2/(h2z*(h1z+h2z))))*Told->get(i,j,k)+(2/(h2z*(h1z+h2z)))*Told->get(i,j,k+1);
					gradz = dKdz*dTdz+K->get(i,j,k)*dT2dz2;

					temp = gradx+grady+gradz;


						if (T->get(i,j,k) > (39+273) && T->get(i,j,k) <= (44+273)) {

							temp1 = W0->get(i,j,k)*(1+0.8*(T->get(i,j,k)-39-273));
							W->set(i,j,k,temp1);
						}
						if (T->get(i,j,k) > (44+273)) {
							temp1= W0->get(i,j,k)*(1+0.8*5);
							W->set(i,j,k,temp1);
						}
						if (T->get(i,j,k) <= (39+273)) {
							temp1 = W0->get(i,j,k);
							W->set(i,j,k,temp1);
						}


					//With Perfusion
					temp1 =Ttm1+dt/C->get(i,j,k)/R->get(i,j,k)*(temp+scalefactor*SAR->get(i,j,k)*R->get(i,j,k)+(-W->get(i,j,k)*C->Blood*R->Blood*(Ttm1-TempBlood))/6000+Q->get(i,j,k)*R->get(i,j,k));
					T->set(i,j,k,temp1);

					errE+=sqrt((Ttm1-T->get(i,j,k))*(Ttm1-T->get(i,j,k)));




					}
					else {

						temp1=T->Air;
						T->set(i,j,k,temp1);

						}
				}
			}
		}
		errE=errE/Nx/Ny/Nz;
		printf("step= %i, errE= %e\n",step,errE);
		for(i=1;i<(Nx-1);i++){for(j=1;j<(Ny-1);j++){for(k=1;k<(Nz-1);k++){Told->set(i,j,k, T->get(i,j,k));}}}


}
}
*/

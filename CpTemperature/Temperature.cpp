#include "Temperature.h"
#include <iostream>
#include <stdio.h>
# include <math.h>
#include "Siminfo.h"

//#include <malloc.h>

// Date constructor
Temperature::Temperature(int Tx, int Ty, int Tz) : Data3d(Tx, Ty, Tz)
{
  //std::cout<< "Entrato constructor Temperature";
}

Temperature::~Temperature()
{
//std::cout<< "Destructor Temperature";
}


void Temperature::fdtd(Siminfo *SimFDTD, Temperature *Told, Data3d *SAR, Data3d *W, Data3d *W0, Data3d *R, Data3d *Q, Data3d *C, Data3d *K, Data1d *posx, Data1d *posy, Data1d *posz, Data1d *Tblood, Data1d *scaleSAR)
{
  double err=1e5;
  double errE=1e5;
  long step=0;
  long brdrstep=0;
  long indtime = 0;
  long timmod;
  int i, j, k;

  double nStep=SimFDTD->heatingtime/SimFDTD->dt;
  double TempBlood = Tblood->get(0);
  double scalefactor=0;
  double Ttm1;
  double temp, temp1;
  double h1x, h2x, dKdx, dTdx, dT2dx2, gradx, h1y, h2y, dKdy, dTdy, dT2dy2, grady, h1z, h2z, dKdz, dTdz, dT2dz2, gradz;
  char filesave[150];

	//while(errE>eps){
	while(step<nStep && errE>SimFDTD->eps){
	//while(step<10){
		step+=1;
		timmod = (long)(step*SimFDTD->dt);
		TempBlood = Tblood->get(timmod);
		scalefactor = scaleSAR->get(timmod);

		errE=0;


		for(i=7;i<(Nx-7);i++){
			for(j=7;j<(Ny-7);j++){
				for(k=(SimFDTD->zmin)-1;k<(SimFDTD->zmax)+1;k++){
					if(R->get(i,j,k)>50){

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


						if (dataarray[i][j][k] > (39+273) && dataarray[i][j][k] <= (44+273)) {

							temp1 = W0->get(i,j,k)*(1+0.8*(dataarray[i][j][k]-39-273));
							W->set(i,j,k,temp1);
						}
						if (dataarray[i][j][k] > (44+273)) {
							temp1= W0->get(i,j,k)*(1+0.8*5);
							W->set(i,j,k,temp1);
						}
						if (dataarray[i][j][k] <= (39+273)) {
							temp1 = W0->get(i,j,k);
							W->set(i,j,k,temp1);
						}


                    /*if (i==12 && j==43 && k==39) {
                        printf("\t h2x=%f, h1x=%f, dKdx=%f, dTdx=%f, dT2dx2=%f, gradx=%f\n", h2x, h1x, dKdx, dTdx, dT2dx2, gradx);
                        printf("\t h2y=%f, h1y=%f, dKdy=%f, dTdy=%f, dT2dy2=%f, grady=%f\n", h2y, h1y, dKdy, dTdy, dT2dy2, grady);
                        printf("\t h2z=%f, h1z=%f, dKdz=%f, dTdz=%f, dT2dz2=%f, gradz=%f\n", h2z, h1z, dKdz, dTdz, dT2dz2, gradz);
                    }*/


					//With Perfusion
					dataarray[i][j][k]=Ttm1+SimFDTD->dt/C->get(i,j,k)/R->get(i,j,k)*(temp+scalefactor*SAR->get(i,j,k)*R->get(i,j,k)+(-W->get(i,j,k)*C->Blood*R->Blood*(Ttm1-TempBlood))/6000+Q->get(i,j,k)*R->get(i,j,k));

					errE+=sqrt((Ttm1-dataarray[i][j][k])*(Ttm1-dataarray[i][j][k]));




					}
					else {
						dataarray[i][j][k]=Air;

						}
				}
			}
		}
		errE=errE/Nx/Ny/Nz;

		//printf("step= %i, errE= %e, val= %lf, Tblood = %f \n",step,errE, R->get(43,60,44), TempBlood);
		printf("step= %i, errE= %e, val= %lf, Tblood = %f \n",step,errE, dataarray[100][50][50], TempBlood);
		for(i=1;i<(Nx-1);i++){for(j=1;j<(Ny-1);j++){for(k=1;k<(Nz-1);k++){Told->set(i,j,k, dataarray[i][j][k]);}}}

		if (timmod<SimFDTD->maxsavetime) {
			if (timmod%SimFDTD->DeltaSave == 0) {
				sprintf(filesave, "Temp%ld_%s", timmod, SimFDTD->outputfile);
				printtemp4(SimFDTD, filesave);
			}
		}


}


printtemp(R, C, SAR, W, Q, SimFDTD, SimFDTD->outputfile);
}

void Temperature::printtemp(Data3d* R, Data3d* C, Data3d* SAR, Data3d* W, Data3d* Q, Siminfo* SimFDTD, char* filename)
{
int i, j, k;
FILE *out;

//out = fopen(SimFDTD->outputfile, "w");
out = fopen(filename, "w");

for(i=1;i<(Nx-1);i++){for(j=1;j<(Ny-1);j++){for(k=SimFDTD->zmin;k<SimFDTD->zmax+1;k++){

  if (dataarray[i][j][k]!=Air){


    fprintf(out,"%i %i %i %13.11f %13.11f %13.11f %13.11f %13.11f %13.11f\n",i,j,k, dataarray[i][j][k],SAR->get(i,j,k),W->get(i,j,k),R->get(i,j,k), Q->get(i,j,k), C->get(i,j,k));


			}

}}}

fclose(out);

}

void Temperature::fdtdconvec(Siminfo *SimFDTD, Temperature *Told, Data3d *SAR, Data3d *W, Data3d *W0, Data3d *R, Data3d *Q, Data3d *C, Data3d *K, Data1d *posx, Data1d *posy, Data1d *posz, Data1d *Tblood, Data1d *scaleSAR)
{
  double err=1e5;
  double errE=1e5;
  long step=0;
  long brdrstep=0;
  long indtime = 0;
  long timmod;
  int i, j, k;
  int aircheck;

  double nStep=SimFDTD->heatingtime/SimFDTD->dt;
  double TempBlood = Tblood->get(0);
  double scalefactor=0;
  double Ttm1;
  double temp, temp1;
  double h1x, h2x, dKdx, dTdx, dT2dx2, gradx, h1y, h2y, dKdy, dTdy, dT2dy2, grady, h1z, h2z, dKdz, dTdz, dT2dz2, gradz;
  double hconvec, qx, qy, qz;
  char filesave[150];

	//while(errE>eps){
	while(step<nStep && errE>SimFDTD->eps){
	//while(step<10){
		step+=1;
		timmod = (long)(step*SimFDTD->dt);
		TempBlood = Tblood->get(timmod);
		scalefactor = scaleSAR->get(timmod);

		errE=0;


		for(i=7;i<(Nx-7);i++){
			for(j=7;j<(Ny-7);j++){
				for(k=(SimFDTD->zmin)-1;k<(SimFDTD->zmax)+1;k++){
					if(R->get(i,j,k)>50){

                        aircheck= checkair(R, i, j, k);

                        Ttm1=Told->get(i,j,k);

                        h2x = posx->get(i+1)-posx->get(i);
                        h1x = posx->get(i)-posx->get(i-1);

                        h2y = posy->get(j+1)-posy->get(j);
                        h1y = posy->get(j)-posy->get(j-1);

                        h2z = posz->get(k+1)-posz->get(k);
                        h1z = posz->get(k)-posz->get(k-1);

                        if (aircheck>0) {

                            qx =(Told->get(i-1, j, k)-Told->get(i, j, k))/((h1x/(2*K->get(i-1, j, k))+(h1x/(2*K->get(i, j, k)))))+(Told->get(i+1, j, k)-Told->get(i, j, k))/((h2x/(2*K->get(i+1, j, k))+(h2x/(2*K->get(i, j, k)))));
                            gradx = 2*qx/(h1x+h2x);

                            qy =(Told->get(i, j-1, k)-Told->get(i, j, k))/((h1y/(2*K->get(i, j-1, k))+(h1y/(2*K->get(i, j, k)))))+(Told->get(i, j+1, k)-Told->get(i, j, k))/((h2y/(2*K->get(i, j+1, k))+(h2y/(2*K->get(i, j, k)))));
                            grady = 2*qy/(h1y+h2y);

                            qz =(Told->get(i, j, k-1)-Told->get(i, j, k))/((h1z/(2*K->get(i, j, k-1))+(h1z/(2*K->get(i, j, k)))))+(Told->get(i, j, k+1)-Told->get(i, j, k))/((h2z/(2*K->get(i, j, k+1))+(h2z/(2*K->get(i, j, k)))));
                            gradz = 2*qz/(h1z+h2z);

                            hconvec = 0;
                            if (R->get(i-1, j, k)<50) {
                                hconvec = hconvec+2/(h1x+h2x);
                            }
                            if (R->get(i+1, j, k)<50) {
                                hconvec = hconvec+2/(h1x+h2x);
                            }
                            if (R->get(i, j-1, k)<50) {
                                hconvec = hconvec+2/(h1y+h2y);
                            }
                            if (R->get(i, j+1, k)<50) {
                                hconvec = hconvec+2/(h1y+h2y);
                            }
                            if (R->get(i, j, k-1)<50) {
                                hconvec = hconvec+2/(h1z+h2z);
                            }
                            if (R->get(i, j, k+1)<50) {
                                hconvec = hconvec+2/(h1z+h2z);
                            }

                            /*if (Told->get(i,j,k)>0){
                                printf("step = %ld, Told: %e, hconvecparam: %e, grad: %e\n", step, Told->get(i,j,k), hconvec*SimFDTD->hconvecparam*(Air-Told->get(i,j,k)), gradx+grady+gradz);}*/
                            temp = gradx+grady+gradz + hconvec*SimFDTD->hconvecparam*(Air-Told->get(i,j,k));

                        } else {



                            dKdx = -(h2x/(h1x*(h1x+h2x)))*K->get(i-1,j,k)+((h2x/(h1x*(h1x+h2x)))-(h1x/(h2x*(h1x+h2x))))*K->get(i,j,k)+(h1x/(h2x*(h1x+h2x)))*K->get(i+1,j,k);
                            dTdx = -(h2x/(h1x*(h1x+h2x)))*Told->get(i-1,j,k)+((h2x/(h1x*(h1x+h2x)))-(h1x/(h2x*(h1x+h2x))))*Told->get(i,j,k)+(h1x/(h2x*(h1x+h2x)))*Told->get(i+1,j,k);
                            dT2dx2= (2/(h1x*(h1x+h2x)))*Told->get(i-1,j,k)+(-(2/(h1x*(h1x+h2x)))-(2/(h2x*(h1x+h2x))))*Told->get(i,j,k)+(2/(h2x*(h1x+h2x)))*Told->get(i+1,j,k);
                            gradx = dKdx*dTdx+K->get(i,j,k)*dT2dx2;


                            dKdy = -(h2y/(h1y*(h1y+h2y)))*K->get(i,j-1,k)+((h2y/(h1y*(h1y+h2y)))-(h1y/(h2y*(h1y+h2y))))*K->get(i,j,k)+(h1y/(h2y*(h1y+h2y)))*K->get(i,j+1,k);
                            dTdy = -(h2y/(h1y*(h1y+h2y)))*Told->get(i,j-1,k)+((h2y/(h1y*(h1y+h2y)))-(h1y/(h2y*(h1y+h2y))))*Told->get(i,j,k)+(h1y/(h2y*(h1y+h2y)))*Told->get(i,j+1,k);
                            dT2dy2= (2/(h1y*(h1y+h2y)))*Told->get(i,j-1,k)+(-(2/(h1y*(h1y+h2y)))-(2/(h2y*(h1y+h2y))))*Told->get(i,j,k)+(2/(h2y*(h1y+h2y)))*Told->get(i,j+1,k);
                            grady = dKdy*dTdy+K->get(i,j,k)*dT2dy2;


                            dKdz = -(h2z/(h1z*(h1z+h2z)))*K->get(i,j,k-1)+((h2z/(h1z*(h1z+h2z)))-(h1z/(h2z*(h1z+h2z))))*K->get(i,j,k)+(h1z/(h2z*(h1z+h2z)))*K->get(i,j,k+1);
                            dTdz = -(h2z/(h1z*(h1z+h2z)))*Told->get(i,j,k-1)+((h2z/(h1z*(h1z+h2z)))-(h1z/(h2z*(h1z+h2z))))*Told->get(i,j,k)+(h1z/(h2z*(h1z+h2z)))*Told->get(i,j,k+1);
                            dT2dz2= (2/(h1z*(h1z+h2z)))*Told->get(i,j,k-1)+(-(2/(h1z*(h1z+h2z)))-(2/(h2z*(h1z+h2z))))*Told->get(i,j,k)+(2/(h2z*(h1z+h2z)))*Told->get(i,j,k+1);
                            gradz = dKdz*dTdz+K->get(i,j,k)*dT2dz2;

                            temp = gradx+grady+gradz;
                        }

						if (dataarray[i][j][k] > (39+273) && dataarray[i][j][k] <= (44+273)) {

							temp1 = W0->get(i,j,k)*(1+0.8*(dataarray[i][j][k]-39-273));
							W->set(i,j,k,temp1);
						}
						if (dataarray[i][j][k] > (44+273)) {
							temp1= W0->get(i,j,k)*(1+0.8*5);
							W->set(i,j,k,temp1);
						}
						if (dataarray[i][j][k] <= (39+273)) {
							temp1 = W0->get(i,j,k);
							W->set(i,j,k,temp1);
						}


                    /*if (i==12 && j==43 && k==39) {
                        printf("\t h2x=%f, h1x=%f, dKdx=%f, dTdx=%f, dT2dx2=%f, gradx=%f\n", h2x, h1x, dKdx, dTdx, dT2dx2, gradx);
                        printf("\t h2y=%f, h1y=%f, dKdy=%f, dTdy=%f, dT2dy2=%f, grady=%f\n", h2y, h1y, dKdy, dTdy, dT2dy2, grady);
                        printf("\t h2z=%f, h1z=%f, dKdz=%f, dTdz=%f, dT2dz2=%f, gradz=%f\n", h2z, h1z, dKdz, dTdz, dT2dz2, gradz);
                    }*/


					//With Perfusion
					dataarray[i][j][k]=Ttm1+SimFDTD->dt/C->get(i,j,k)/R->get(i,j,k)*(temp+scalefactor*SAR->get(i,j,k)*R->get(i,j,k)+(-W->get(i,j,k)*C->Blood*R->Blood*(Ttm1-TempBlood))/6000+Q->get(i,j,k)*R->get(i,j,k));

					errE+=sqrt((Ttm1-dataarray[i][j][k])*(Ttm1-dataarray[i][j][k]));




					}
					else {
						dataarray[i][j][k]=Air;

						}
				}
			}
		}
		errE=errE/Nx/Ny/Nz;

		//printf("step= %i, errE= %e, val= %lf, Tblood = %f \n",step,errE, R->get(43,60,44), TempBlood);
		printf("step= %i, errE= %e, val= %lf, Tblood = %f \n",step,errE, dataarray[100][50][50], TempBlood);
		for(i=1;i<(Nx-1);i++){for(j=1;j<(Ny-1);j++){for(k=1;k<(Nz-1);k++){Told->set(i,j,k, dataarray[i][j][k]);}}}

		if (timmod<SimFDTD->maxsavetime) {
			if (timmod%SimFDTD->DeltaSave == 0) {
				sprintf(filesave, "Temp%ld_%s", timmod, SimFDTD->outputfile);
				printtemp4(SimFDTD, filesave);
			}
		}


}

printtemp(R, C, SAR, W, Q, SimFDTD, SimFDTD->outputfile);
}

int Temperature::checkair(Data3d* R, int i, int j, int k)
{
    int OK=0;
    if (R->get(i+1,j,k)<50) {
        OK=OK+1;
    }
    if (R->get(i-1,j,k)<50) {
        OK=OK+1;
    }
    if (R->get(i,j+1,k)<50) {
        OK=OK+1;
    }
    if (R->get(i,j-1,k)<50) {
        OK=OK+1;
    }
    if (R->get(i,j,k+1)<50) {
        OK=OK+1;
    }
    if (R->get(i,j,k-1)<50) {
        OK=OK+1;
    }

    return OK;
}




void Temperature::printtemp4(Siminfo *SimFDTD, char* filename) {

int i, j, k;
FILE *out;

//out = fopen(SimFDTD->outputfile, "w");
out = fopen(filename, "w");

for(i=1;i<(Nx-1);i++){for(j=1;j<(Ny-1);j++){for(k=SimFDTD->zmin;k<SimFDTD->zmax+1;k++){

  if (dataarray[i][j][k]!=Air){


    fprintf(out,"%i %i %i %13.11f\n",i,j,k, dataarray[i][j][k]);


			}

}}}

fclose(out);

}

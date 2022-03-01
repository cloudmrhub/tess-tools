#include "Data1d.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

// Date constructor
Data1d::Data1d(long maxvalues, double constval)
{
  //int maxvalues=3;
    N = maxvalues;
    defval = constval;
    dataarray = new double[maxvalues+1];
    int k =0;
    for(k=0; k<=maxvalues; k++) {dataarray[k]=0;}
}

Data1d::~Data1d()
{
  delete [] dataarray;
  //Destructor doesn't work if called in main with array of size > 5
}

void Data1d::dele()
{
  delete [] dataarray;
    std::cout<< "Deleted\n";
}


// Date member function
void Data1d::set(long position, double data){
    if (position < N) {
        dataarray[position] = data;
    }
    else {
        printf("Error setting value out of bounds\n");
    }

}


double Data1d::get(long position)
{
    if (position <= N) {
        return dataarray[position];
    }
    else {
        return dataarray[N];
    }
}

void Data1d::loaddata(char* filetoread)
{

  FILE *pos;

  long k;
  double val;
  double last;
  double valinc;

  last = defval;

  if (strcmp(filetoread, "constant")==0) {

    for (k=0; k<=N; k++) {
      dataarray[k] = defval;
      }

  } else if (strcmp(filetoread, "uniform")==0) {

    valinc =0;

    for (k=0; k<=N; k++) {
      dataarray[k] = valinc;
      valinc = valinc+defval;
      }

  } else {


  pos = fopen (filetoread, "r");

    if (pos==NULL) {
        printf("File %s not found\n", filetoread);
        exit(0);
    }
  fscanf(pos, "%lf\n", &val);
  printf("First val %e\n", val);
  if (val == EOF) {
      dataarray[0] = last;
      dataarray[1] = last;
  }
  else {
      //printf("%d %e\n", k, val);
      dataarray[0] = val;
      dataarray[1] = val;
      last = val;
      //posx[k] = k;
  }

  for (k = 2; k <= N; k++) {
      fscanf(pos, "%lf\n", &val);

      if (val == EOF) {
          dataarray[k] = last;
      }
      else {
      //printf("%d %e\n", k, val);
        dataarray[k] = val;
        last = val;
      //posx[k] = k;
        }
	}

  fclose(pos);
  }
}


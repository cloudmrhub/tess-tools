#ifndef DATA1D_H
#define DATA1D_H

class Data1d
{
private:
    double *dataarray;
    long N;
    
    
public:
    
    Data1d(long maxvalues, double constval=0);
    ~Data1d();
    
    void set(long position, double data);
    double get(long position);
    void dele();
    
    void loaddata(char *filetoread);
    double defval;
    //int test=5;
};

#endif
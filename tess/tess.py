import importlib.resources
import pynico_eros_montin.pynico as pn  
import numpy as np
import pyable_eros_montin.imaginable as ima


#iterate over a 3dimension matrix



def writeVoxelsToFiles(matricesfilenames, S,outputfilename=None):
    #tess works in voxels, so we need to convert the matrixes to voxels
   
    WRITERS=[]
    if outputfilename is None:
        outputfilename=[pn.createRandomTemporaryPathableFromFileName('a.dat').getPosition() for _ in matricesfilenames]

    for of in outputfilename:
        WRITERS.append(open(of,"w"))
    
    MATRICES=[]
    for m in matricesfilenames:
        if m is None:
            MATRICES.append(np.zeros(S))
        else:
            IM=ima.Imaginable(filename=m)
            MATRICES.append(IM.getImageAsNumpy())
   

    for i in range(S[0]):
        for j in range(S[1]):
            for k in range(S[2]):
                for f,m in zip(WRITERS,MATRICES):
                    f.write(f"{i} {j} {k} {m[i,j,k]}\n")
                    
    for f in WRITERS:
        f.close()

    return outputfilename

def findBoundingBoxZ(matrix):
    first_non_zero = None
    last_non_zero = None

    # Iterate through the z-axis
    for z in range(matrix.shape[2]):
        # Check if any non-zero voxel exists in the current z-slice
        if any(matrix[:, :, z].flatten()):
            # If it's the first non-zero voxel, store its index
            if first_non_zero is None:
                first_non_zero = z
            # Update the last non-zero voxel index
            last_non_zero = z
    return first_non_zero, last_non_zero


class Tess:
    def __init__(self):
        self.log=pn.Log({"what":"Tess"})
        O=pn.createRandomTemporaryPathableFromFileName('a.dat')
        self.workingdirectory=O.getPath()
        self.parameterfile=pn.createTemporaryPathableFromFileName('Parameter.dat').getPosition()
        self.status={"mapstodat":False,"space":False,"parametersfile":None}
        # self.parameterfile='/data/PROJECTS/tess/testdata/5594/Parameters.dat'
        self.params=[]
        self.Space=None
        if __package__ is None or __package__ == "":
            exe="_skbuild/linux-x86_64-3.12/setuptools/lib.linux-x86_64-cpython-312/tess/bin/cpptemperature"
        else:
            exe = importlib.resources.files(__package__).joinpath("bin", "cpptemperature")
        print(f"Using executable {exe}")
        self.binfile = str(exe)
        self.params.append({"label":"Nx","name":"Nx","value":None})
        self.params.append({"label":"Ny","name":"Ny","value":None})
        self.params.append({"label":"Nz","name":"Nz","value":None})
        self.params.append({"label":"dx","name":"dx","value":None})
        self.params.append({"label":"dy","name":"dy","value":None})
        self.params.append({"label":"dz","name":"dz","value":None})
        self.params.append({"label":"dt","name":"dt","value":0.2})
        self.params.append({"label":"zmin","name":"zmin","value":None})
        self.params.append({"label":"zmax","name":"zmax","value":None})
        self.params.append({"label":"maxsavetime","name":"maxsavetime","value":-1}) # do not change
        self.params.append({"label":"DeltaSave","name":"DeltaSave","value":10}) #s do not change
        self.params.append({"label":"heatingtime","name":"heatingtime","value":60}) #s
        self.params.append({"label":"eps","name":"eps","value":1e-9}) #ideal zero
        self.params.append({"label":"Cblood","name":"Cblood","value":1057}) #Joule/(Kg*K)
        self.params.append({"label":"Rblood","name":"Rblood","value":3600}) #Kg/m^3
        self.params.append({"label":"Tblood","name":"Tblood","value":309.75}) #K
        self.params.append({"label":"Wair","name":"Wair","value":0}) #mmL/M*Kg M=minuts
        self.params.append({"label":"Rair","name":"Rair","value":1.3}) #Kg/m^3
        self.params.append({"label":"Cair","name":"Cair","value":1006.0}) #Joule/(Kg*K)
        self.params.append({"label":"Kair","name":"Kair","value":0.026}) #Watt/(m*K)
        self.params.append({"label":"Qair","name":"Qair","value":0}) #Watt/kg
        self.params.append({"label":"Tair","name":"Tair","value":296})     #K
        self.params.append({"label":"T0V","name":"T0V","value":None}) #number of non zero voxels
        self.params.append({"label":"Toldfile","name":"Toldfile","value":None}) #K
        self.params.append({"label":"SARfile","name":"SARfile","value":None}) #Watt/(kg)
        self.params.append({"label":"Wfile","name":"Wfile","value":None}) #mmL/M*Kg M=minuts
        self.params.append({"label":"Rfile","name":"Rfile","value":None}) #Kg/m^3
        self.params.append({"label":"Qfile","name":"Qfile","value":None}) #Watt/kg
        self.params.append({"label":"Cfile","name":"Cfile","value":None}) #Joule/(Kg*K)
        self.params.append({"label":"Kfile","name":"Kfile","value":None}) #Watt/(m*K)
        self.params.append({"label":"outputfile","name":"outputfile","value":None}) #K
        self.params.append({"label":"Posxfile","name":"Posxfile","value":"uniform"}) 
        self.params.append({"label":"Posyfile","name":"Posyfile","value":"uniform"}) 
        self.params.append({"label":"Poszfile","name":"Poszfile","value":"uniform"})
        self.params.append({"label":"Tbloodfile","name":"Tbloodfile","value":"constant"})
        self.params.append({"label":"scaleSARfile","name":"scaleSARfile","value":"constant"})
    


    # find in params array the element with label=label and return its value
    def getParam(self, label):
        for p in self.params:
            if p["label"]==label:
                return p["value"]
        return None
    # make the setter for the param with label=label
    def setParam(self, label, value):
        for p in self.params:
            if p["label"]==label:
                p["value"]=value
                return
        raise Exception(f"Param {label} not found")
    
    def setSpace(self, imagefilename):
        self.log.append(f"Space set from {imagefilename}")
        self.Space=ima.Imaginable(filename=imagefilename)
        m=ima.Imaginable(filename=imagefilename)
        Nx,Ny,Nz=m.getImageSize()
        self.setParam("Nx",Nx)
        self.setParam("Ny",Ny)
        self.setParam("Nz",Nz)
        self.log.append(f"Space set to {Nx}x{Ny}x{Nz}")
        dx,dy,dz=[k/1000 for k in m.getImageSpacing()] #space is in meters
        self.setParam("dx",dx)
        self.setParam("dy",dy)
        self.setParam("dz",dz)
        self.log.append(f"Space set to {dx}x{dy}x{dz}")
        T0V=m.getNumberofVoxels()
        self.log.append(f"T0V set to {T0V}")
        # zmin,zmax=findBoundingBoxZ(m.getImageAsNumpy())
        zmin,zmax=0,Nz
        self.setParam("zmin",zmin)
        self.setParam("zmax",zmax)
        self.setParam("T0V",T0V)
        self.status["space"]=True
        return True
    
        
    def writeMapsToDat(self):
        if self.status["mapstodat"]==True:
            return True
        else:
            f=open(self.parameterfile,"w")
            PARAMS=["Wfile","Rfile","Qfile","Cfile","Kfile","Toldfile","SARfile"]
            IMAGES=[]
            for p in PARAMS:
                IMAGES.append(self.getParam(p))
            OUTPUT=writeVoxelsToFiles(IMAGES, [self.getParam("Nx"),self.getParam("Ny"),self.getParam("Nz")])
            for p,o in zip(PARAMS,OUTPUT):
                self.setParam(p,o)

            for p in self.params:
                f.write(f"{p['label']} {p['value']}\n")
            f.close()
            self.status["mapstodat"]=True
            return True
        

    
    def writeParametersFile(self,parameterFilename= None):
        if parameterFilename is not None:
            self.parameterfile=parameterFilename
        if parameterFilename is None or self.status["parametersfile"]==False:
            f=open(self.parameterfile,"w")
            for p in self.params:
                f.write(f"{p['label']} = {p['value']}\n")
            f.close()
            self.status["parametersfile"]=True


    def __calculateTemperature__(self):
        if self.status["mapstodat"]==False:
            self.writeMapsToDat()
        if self.status["space"]==False:
            raise Exception("Space not defined")
        if self.status["parametersfile"] is False:
            self.writeParametersFile()
        O=self.getParam("outputfile")
        if O is None:
            self.setParam("outputfile",pn.createTemporaryPathableFromFileName('outputfile.nii.gz').getPosition())
        self.writeParametersFile()

        b=pn.BashIt()
        b.setCommand(f"{self.binfile} {self.parameterfile}")
        self.log.append(f"Temperature calculation started {self.binfile} {self.parameterfile}")
        b.run()
        self.log.append(f"Temperature calculated")

        return True
    
    def setBloodPerfusionMap(self, imagefilename):
        if pn.Pathable(imagefilename).exists():
            self.setParam("Wfile",imagefilename)
        else:
            raise Exception(f"File {imagefilename} does not exist")
        
    def setMaterialDensityMap(self, imagefilename):
        if pn.Pathable(imagefilename).exists():
            self.setParam("Rfile",imagefilename)
        else:
            raise Exception(f"File {imagefilename} does not exist")
        
    def setMetabolismHeatMap(self, imagefilename):
        if pn.Pathable(imagefilename).exists():
            self.setParam("Qfile",imagefilename)
        else:
            raise Exception(f"File {imagefilename} does not exist")
            

    def setHeatCapacityMap(self, imagefilename):
        if pn.Pathable(imagefilename).exists():
            self.setParam("Cfile",imagefilename)
        else:
            raise Exception(f"File {imagefilename} does not exist")
        
    def setThermalConductivityMap(self, imagefilename):
        if pn.Pathable(imagefilename).exists():
            self.setParam("Kfile",imagefilename)
        else:
            raise Exception(f"File {imagefilename} does not exist")
        
    def setSARMap(self, imagefilename):
        if pn.Pathable(imagefilename).exists():
            self.setParam("SARfile",imagefilename)
        else:
            raise Exception(f"File {imagefilename} does not exist")
        
    def setTOldMap(self, imagefilename):
        if pn.Pathable(imagefilename).exists():
            self.setParam("Toldfile",imagefilename)
        else:
            raise Exception(f"File {imagefilename} does not exist")
        

    def setMask(self, imagefilename):
        self.setParam("mask",imagefilename)
    def setHeatingTime(self, heatingtime):
        self.setParam("heatingtime",heatingtime)
    def setAirParameters(self, d):
        self.setParam("Tair",d["temperature"])
        self.setParam("Wair",d["perfusion"])
        self.setParam("Rair",d["density"])
        self.setParam("Cair",d["capacity"])
        self.setParam("Kair",d["conductivity"])
        self.setParam("Qair",d["metabolism"])
    def setBloodParameters(self,d={'capacity':1057,'density':3600,'temperature':310}):
        self.setParam("Cblood",d["capacity"])
        self.setParam("Rblood",d["density"])
        self.setParam("Tblood",d["temperature"])
    def setDebug(self):
        self.setParam("maxsavetime",0)
        self.setParam("DeltaSave",1)
        self.setParam("outputfile",pn.createTemporaryPathableFromFileName('outputfile.nii.gz').getPosition())

    def getOutput(self, outputfilename=None):
        self.setParam("outputfile",pn.createRandomTemporaryPathableFromFileName('a.dat').getPosition())
        self.__calculateTemperature__()
        F=self.getParam("outputfile")
        if F is None:
            raise Exception("Output file not defined")
        O = readOutputFile(F)
        IM=self.Space.getDuplicate()
        if IM.getImageAsNumpy().shape!=O.shape:
            # Create padded array if difference is ~1 pixel
            n_shape = IM.getImageAsNumpy().shape
            o_shape = O.shape
            pad_width = []
            for n, o in zip(n_shape, o_shape):
                diff = n - o
                if diff > 0:
                    # Add padding evenly on both sides
                    pad_width.append((0, diff))
                    
                else:
                    pad_width.append((0, 0))
                    
            # Pad the smaller array O to match N's dimensions
            O_padded = np.pad(O, pad_width, mode='edge')
            IM.setImageFromNumpy(O_padded)
        else:
            IM.setImageFromNumpy(O)
                

        if outputfilename is not None:
            IM.writeImageAs(outputfilename)
        return IM




def getdfltAir():
    return {'capacity':1006,'density':1.3,'temperature':296,'metabolism':1006,'conductivity':0.026,'perfusion':0}

def getdfltBlood():
    return {'capacity':1057,'density':3600,'temperature':310}

def readOutputFile(fn='a.dat'):
    with open(fn, 'r') as f:
        lines = [line.rstrip('\n') for line in f]
        f.close()
    
    O=[]
    X=0
    Y=0
    Z=0

    while (len(lines)>0):
        g=lines.pop()
        
        x,y,z,v = g.split(" ")
        x,y,z,v = int(x),int(y),int(z),float(v)
        if x>X:
            X=x
        if y>Y:
            Y=y
        if z>Z:
            Z=z
        O.append({"voxel":[x,y,z],"value":v})
    OUT=np.zeros((X+1,Y+1,Z+1))
    for o in O:
        OUT[o["voxel"][0],o["voxel"][1],o["voxel"][2]]=o["value"]
    return OUT






if __name__=="__main__":
    
    A=Tess()
    import os

    A.setSpace('/home/eros/Downloads/hugo-materialdensity.nii.gz')
    A.setHeatingTime(2)
    A.setBloodPerfusionMap('/home/eros/Downloads/hugo-bloodperfusion.nii.gz')
    A.setMaterialDensityMap('/home/eros/Downloads/hugo-materialdensity.nii.gz')
    A.setHeatCapacityMap('/home/eros/Downloads/hugo-heatcapacity.nii.gz')
    A.setSARMap('/home/eros/Downloads/hugo-SAR.nii.gz')
    A.setThermalConductivityMap('/home/eros/Downloads/hugo-thermalconductivity.nii.gz')
    A.setMetabolismHeatMap('/home/eros/Downloads/hugo-metabolism.nii.gz')

    # set blood parameters
    A.setBloodParameters(d={'capacity':1057,'density':3600,'temperature':310})
    # set air parameters
    A.setAirParameters(d={'capacity':1006,'density':1.3,'temperature':296,'metabolism':1006,'conductivity':0.026,'perfusion':0})

    O=A.getOutput('/tmp/a.nii')
    MD=ima.Imaginable('/home/eros/Downloads/hugo-materialdensity.nii.gz')
    M=ima.Imaginable('/home/eros/Downloads/hugo-metabolism.nii.gz')
    
    
    A.log.printWhatHappened()
    
    print(A.params)
    O.viewAxial()
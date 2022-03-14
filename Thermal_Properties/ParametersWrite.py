from scipy.io import loadmat
import numpy as np
from myPy import im



#In the construction, filename is the MATLAB file containing the atlas map and the lookup table
#fileparam is the name of the file containing the parameters of the simulations: "Parameters.dat"
class ThermalProperties(object):
  def __init__(self, filename, fileparam=None):
    #This is the MATLAB part that can be replaced with the NIFTI
    filemat = loadmat(filename)
    #Material is the 3D matrix containing the 3D atlas map
    self.Material = filemat['Material']
    #Tissues is the lookup table
    self.Tissues = filemat['Tissues']
    #dt is the temporal resolution of the simulation
    self.dt = filemat['dt']
    self.dt = self.dt[0][0]
    #heatingtime is the temporal duration of the simulation
    self.heatingtime = filemat['heatingtime']
    self.heatingtime = self.heatingtime[0][0]
    #meshsize is a vector of length 3 indicating the resolution of the mesh
    self.meshsize = filemat['meshsize']
    if (self.meshsize.shape[1]>1):
      self.meshsize = self.meshsize[0]
    print(self.meshsize)
    #Blood is a vector of length 3 containing the thermal properties of the blood
    self.Blood = filemat['Blood']
    if (self.Blood.shape[1]>=1):
      self.Blood = self.Blood[0]
    print(self.Blood)
    #Told is the initial temperature distribution (3D Matrix)
    self.Told = filemat['Tinitial']
    #SAR is the SAR distribution (3D Matrix)
    self.SAR = filemat['SAR']
    N = self.Material.shape

    self.Nx = N[0]
    self.Ny = N[1]
    self.Nz = N[2]
    #self.MatProperties()

 
 

    if fileparam is not None:
      self.paramwritefile(fileparam)


  def getParameterFile(self,fileparam):
    self.paramwritefile(fileparam)

  def MatProperties(self):
    print("Create Material Properties")
    N = self.Material.shape
    self.Nx = N[0]
    self.Ny = N[1]
    self.Nz = N[2]
    self.rho = np.zeros((self.Nx, self.Ny, self.Nz))
    self.C = np.zeros((self.Nx, self.Ny, self.Nz))
    self.W = np.zeros((self.Nx, self.Ny, self.Nz))
    self.Q = np.zeros((self.Nx, self.Ny, self.Nz))
    self.k = np.zeros((self.Nx, self.Ny, self.Nz))

    for a in range(self.Nx):
      print(a)
      for b in range(self.Ny):
        for c in range(self.Nz):
          if (self.Material[a, b, c]>0):
            self.rho[a, b, c] = self.Tissues[self.Material[a, b, c]-1, 0]
            self.C[a, b, c] = self.Tissues[self.Material[a, b, c]-1, 2]
            self.W[a, b, c] = self.Tissues[self.Material[a, b, c]-1, 1]
            self.Q[a, b, c] = self.Tissues[self.Material[a, b, c]-1, 4]
            self.k[a, b, c] = self.Tissues[self.Material[a, b, c]-1, 3]




  
  def createArray3D(self):
    arr = []
    for a in range(self.Nx):
      arr.append([])
      for b in range(self.Ny):
        arr[a].append([])
        for c in range(self.Nz):
          arr[a][b].append(0)
    return arr
          
  def writeMat3D(self, column, filename):
    sizemat = self.Material.shape
    f = open(filename, "w")
    cont = 0
    for a in range(0, sizemat[0]):
      print(a)
      for b in range(0, sizemat[1]):
        for c in range(0, sizemat[2]):
          cont = cont+1
          if (self.Material[a, b, c]>0):
            strtoinsert = str(a) + ' ' + str(b) + ' ' + str(c) + ' ' + ' ' + str(self.Tissues[self.Material[a, b, c], column]) + '\n'
            f.write(strtoinsert)
    f.close()
    return cont


  def writeMat3DTold(self, filename):
    sizemat = self.Material.shape
    f = open(filename, "w")
    cont = 0
    for a in range(0, sizemat[0]):
      print(a)
      for b in range(0, sizemat[1]):
        for c in range(0, sizemat[2]):
          cont = cont+1
          if (self.Material[a, b, c]>0):
            strtoinsert = str(a) + ' ' + str(b) + ' ' + str(c) + ' ' + ' ' + str(self.Told[a, b, c]) + '\n'
            f.write(strtoinsert)
    f.close()
    return cont

  def writeMat3DSAR(self, filename):
    sizemat = self.Material.shape
    f = open(filename, "w")
    cont = 0
    for a in range(0, sizemat[0]):
      print(a)
      for b in range(0, sizemat[1]):
        for c in range(0, sizemat[2]):
          cont = cont+1
          if (self.Material[a, b, c]>0):
            strtoinsert = str(a) + ' ' + str(b) + ' ' + str(c) + ' ' + ' ' + str(self.SAR[a, b, c]) + '\n'
            f.write(strtoinsert)
    f.close()
    return cont

  def paramwritefile(self, fileparam):
    f = open(fileparam, "w")

    strtoinsert = "Nx = " + str(self.Nx) + "\n"
    f.write(strtoinsert)
    
    strtoinsert = "Ny = " + str(self.Ny) + "\n"
    f.write(strtoinsert)
    strtoinsert = "Nz = " + str(self.Nz) + "\n"
    f.write(strtoinsert)

    strtoinsert = "dx = " + str(self.meshsize[0]) + "\n"
    f.write(strtoinsert)
    strtoinsert = "dy = " + str(self.meshsize[1]) + "\n"
    f.write(strtoinsert)
    strtoinsert = "dz = " + str(self.meshsize[2]) + "\n"
    f.write(strtoinsert)
    strtoinsert = "dt = " + str(self.dt) + "\n"
    f.write(strtoinsert)


    self.findminmax()
    strtoinsert = "zmin = " + str(self.zmin) + "\n"
    f.write(strtoinsert)
    strtoinsert = "zmax = " + str(self.zmax) + "\n"
    f.write(strtoinsert)

    strtoinsert = "maxsavetime = -1\n"
    f.write(strtoinsert)
    strtoinsert = "DeltaSave = 10\n"
    f.write(strtoinsert)
    strtoinsert = "heatingtime = " + str(self.heatingtime) + "\n"
    f.write(strtoinsert)

    strtoinsert = "eps = 1e-9\n"
    f.write(strtoinsert)
    strtoinsert = "Cblood = " + str(self.Blood[1]) + "\n"
    f.write(strtoinsert)
    strtoinsert = "Rblood = " + str(self.Blood[0]) + "\n"
    f.write(strtoinsert)
    strtoinsert = "Tblood = " + str(self.Blood[2]) + "\n"
    f.write(strtoinsert)

    strtoinsert = "Wair = " + str(self.Tissues[0, 1]) + "\n"
    f.write(strtoinsert)
    strtoinsert = "Rair = " + str(self.Tissues[0, 0]) + "\n"
    f.write(strtoinsert)
    strtoinsert = "Cair = " + str(self.Tissues[0, 2]) + "\n"
    f.write(strtoinsert)
    strtoinsert = "Kair = " + str(self.Tissues[0, 3]) + "\n"
    f.write(strtoinsert)
    strtoinsert = "Qair = " + str(self.Tissues[0, 4]) + "\n"
    f.write(strtoinsert)
    strtoinsert = "Tair = 296\n"
    f.write(strtoinsert)

    
    self.T0V = self.writeMat3D(0, "R.dat")
    strtoinsert = "T0V = " + str(self.T0V) + "\n"
    f.write(strtoinsert)
    self.writeMat3DTold("Told.dat")
    strtoinsert = "Toldfile = Told.dat\n"
    f.write(strtoinsert)
    self.writeMat3DSAR("SAR.dat")
    strtoinsert = "SARfile = SAR.dat\n"
    f.write(strtoinsert)

    self.writeMat3D(1, "W.dat")
    strtoinsert = "Wfile = W.dat\n"
    f.write(strtoinsert)
    strtoinsert = "Rfile = R.dat\n"
    f.write(strtoinsert)
    self.writeMat3D(4, "Q.dat")
    strtoinsert = "Qfile = Q.dat\n"
    f.write(strtoinsert)
    self.writeMat3D(2, "C.dat")
    strtoinsert = "Cfile = C.dat\n"
    f.write(strtoinsert)
    self.writeMat3D(3, "K.dat")
    strtoinsert = "Kfile = K.dat\n"
    f.write(strtoinsert)
    strtoinsert = "outputfile = Toutput.dat\n"
    f.write(strtoinsert)
    
    strtoinsert = "Posxfile = uniform\n"
    f.write(strtoinsert)
    strtoinsert = "Posyfile = uniform\n"
    f.write(strtoinsert)
    strtoinsert = "Poszfile = uniform\n"
    f.write(strtoinsert)
    strtoinsert = "Tbloodfile = constant\n"
    f.write(strtoinsert)
    strtoinsert = "scaleSARfile = constant\n"
    f.write(strtoinsert)
    
    

    f.close()


  def findminmax(self):
    self.zmin=0
    for c in range(self.Nz):
      print(c)
      for b in range(self.Ny):
        for a in range(self.Nx):
          if (self.Material[a, b, c]>0):
            self.zmin = c
            break
        if (self.zmin>0):
          break
      if (self.zmin>0):
        break
    
    self.zmax=0
    for c in range(self.Nz-1, 0, -1):
      print(c)
      for b in range(self.Ny):
        for a in range(self.Nx):
          if (self.Material[a, b, c]>0):
            self.zmax = c
            break
        if (self.zmax>0):
          break
      if(self.zmax>0):
        break
    print(self.zmin, self.zmax)



class NiftiThermalProperties(ThermalProperties):
  def __init__(self,filename,fileparam=None) -> None:
      super().__init__(filename,fileparam)
      self.MatProperties()
  
  
  def __saveMatimageAs__(self,matimage,filename):
    sizemat = self.Material.shape
    C = np.zeros((self.Nz, self.Ny, self.Nx))
    cont = 0
    for a in range(0, sizemat[0]):
      for b in range(0, sizemat[1]):
        for c in range(0, sizemat[2]):
          cont = cont+1
          if (self.Material[a, b, c]>0):
            C[c,b,a]=matimage[a, b, c] # yes numpy as a different orientation zyx

    o=im.Imaginable()
    o.setImageArray(C)
    o.writeImageAs(filename)
  
  def writeSARAs(self,filename):
    self.__saveMatimageAs__(self.SAR,filename)        
  
  def writeTOldAs(self,filename):
    self.__saveMatimageAs__(self.Told,filename)

  def writeRhoAs(self,filename):
    self.__saveMatimageAs__(self.rho,filename)
  
  def writeCAs(self,filename):
    self.__saveMatimageAs__(self.C,filename)

  def writeWAs(self,filename):
    self.__saveMatimageAs__(self.W,filename)

  def writeQAs(self,filename):
    self.__saveMatimageAs__(self.Q,filename)
    
  def writekAs(self,filename):
    self.__saveMatimageAs__(self.k,filename)
    
 

import Tess

IM='/data/test.mha'



A=Tess.TessMap(inputFileName=IM)

L=A.savePointsCloudAs('/data/PC2.dat')



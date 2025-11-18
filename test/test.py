import importlib.resources
DIR = importlib.resources.files('tess').joinpath('testdata').joinpath('Head')

print(DIR)

import tess.tess as t
A=t.Tess()
import os

A.setSpace(os.path.join(DIR,'MaterialDensity.nii.gz'))
A.setHeatingTime(10)
A.setBloodPerfusionMap(os.path.join(DIR,'BloodPerfusion.nii.gz'))
A.setMaterialDensityMap(os.path.join(DIR,'MaterialDensity.nii.gz'))
A.setHeatCapacityMap(os.path.join(DIR,'HeatCapacity.nii.gz'))
A.setSARMap(os.path.join(DIR,'SAR.nii.gz'))
A.setThermalConductivityMap(os.path.join(DIR,'ThermalConductivity.nii.gz'))
A.setMetabolismHeatMap(os.path.join(DIR,'Metabolism.nii.gz'))
A.setTOldMap(os.path.join(DIR,'TOld.nii.gz'))
# set blood parameters
A.setBloodParameters(d={'capacity':1057,'density':3600,'temperature':310})
# set air parameters

A.setAirParameters(d={'capacity':1006,'density':1.3,'temperature':296,'metabolism':1006,'conductivity':0.026,'perfusion':0})

O=A.getOutput('/tmp/a.nii')
A.log.printWhatHappened()
print(A.params)
O.viewAxial()

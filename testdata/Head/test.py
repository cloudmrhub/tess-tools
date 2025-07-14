import tess.tess as t
A=t.Tess()


A.setSpace('testdata/Head/MaterialDensity.nii.gz')
A.setHeatingTime(10)
A.setBloodPerfusionMap('testdata/Head/BloodPerfusion.nii.gz')
A.setMaterialDensityMap('testdata/Head/MaterialDensity.nii.gz')
A.setHeatCapacityMap('testdata/Head/HeatCapacity.nii.gz')
A.setSARMap('testdata/Head/MaterialDensity.nii.gz')
A.setThermalConductivityMap('testdata/Head/ThermalConductivity.nii.gz')
A.setMetabolismHeatMap('testdata/Head/Metabolism.nii.gz')

# set blood parameters
A.setBloodParameters(d={'capacity':1057,'density':3600,'temperature':310})
# set air parameters
A.setAirParameters(d={'capacity':1006,'density':1.3,'temperature':296,'metabolism':1006,'conductivity':0.026,'perfusion':0})

O=A.getOutput('/tmp/a.nii')
A.log.printWhatHappened()
print(A.params)
O.viewAxial()
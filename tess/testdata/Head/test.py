import tess.tess as t
A=t.Tess()


A.setSpace('MaterialDensity.nii.gz')
A.setHeatingTime(10)
A.setBloodPerfusionMap('BloodPerfusion.nii.gz')
A.setMaterialDensityMap('MaterialDensity.nii.gz')
A.setHeatCapacityMap('HeatCapacity.nii.gz')
A.setSARMap('MaterialDensity.nii.gz')
A.setThermalConductivityMap('ThermalConductivity.nii.gz')
A.setMetabolismHeatMap('Metabolism.nii.gz')

# set blood parameters
A.setBloodParameters(d={'capacity':1057,'density':3600,'temperature':310})
# set air parameters
A.setAirParameters(d={'capacity':1006,'density':1.3,'temperature':296,'metabolism':1006,'conductivity':0.026,'perfusion':0})

O=A.getOutput('/tmp/a.nii')
A.log.printWhatHappened()
print(A.params)
O.viewAxial()
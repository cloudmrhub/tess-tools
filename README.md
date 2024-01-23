# TESS v1

## Installation
1. clone this repo

1. Build cpTemperature
	```
	cd tess
	mkdir build && cd build
	cmake ../CpTemperature; make; make install

	```

## Usage
1. Python (preferred)
1. Bash


### Python
```
import tess.tess as t

A=t.Tess()

# set the image that defines the space
A.setSpace('testdata/Head/MaterialDensity.nii.gz')

# set the position of the bin file
A.binfile='./build/cpptemperature'
#set heating time in s
A.setHeatingTime(10)

# set the needed maps
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

#get the output
O=A.getOutput('/tmp/a.nii')
# explore it if you want
O.viewAxial()

```



## Requirments




[Eros Montin, PhD](https://me.biodimensional.com)
**Forty-six and two are just ahead of me**

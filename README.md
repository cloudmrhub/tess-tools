# TESS v0.0v

## Installation
1. Clone [Tess CU](https://github.com/cloudmrhub-com/TESSCU) 
    ```
    git clone https://github.com/cloudmrhub-com/TESSCU.git
    ```

1. Clone [CMRCode](https://github.com/cloudmrhub-com/CMRCode) 
    ```
    git clone https://github.com/cloudmrhub-com/CMRCode.git
    ```

1. clone [erosmontin](https://github.com/erosmontin)'s [ Image Library ](https://github.com/erosmontin/myPy) and install the environment *em*
    ```
    git clone https://github.com/erosmontin/myPy.git && \
    conda env create -f myPy/environment.yml
    ```
1. Extend the Image library environment for tess
    ```
    conda create --name tess --clone me
    conda activate tess
    pip install -r requirements.txt --user
    ```
1. Build cpTemperature
	```
	cd TESSCU
	mkdir build && cd build
	cmake ../CpTemperature; make; make install

	```

## Usage
1. Python (preferred)
1. Bash
1. docker

### Python
- Set an environment variable with the absolute position of the cppTemperature executable file
    ```
    import os
    os.environ['TESS_BIN'] = '/{pathtothegit}/TESSCU/build/cpptemperature'
    ```
- Instantiate the class
    ```
    import Tess
    T=Tess.Tess()
    ```
- Set the requested matrix
    ```
    T.setMask('/data/test/TESS/Rho.nii.gz')
    T.setMaterialDensityMap('/data/test/TESS/Rho.nii.gz')
    T.setBloodPerfusionMap('/data/test/TESS/W.nii.gz')
    T.setHeatCapacityMap('/data/test/TESS/C.nii.gz')
    T.setSARMap('/data/test/TESS/SAR.nii.gz')
    T.setTermalConductivityMap('/data/test/TESS/k.nii.gz')
    T.setTOldMap('/data/test/TESS/TOld.nii.gz')
    T.setMetabolismHeatMap('/data/test/TESS/Q.nii.gz')
    ```
- Save the output
    ```
    T.saveOutputMapAs('/data/test/TESS/TESTOUTPUT.nii.gz')
    ```





## Requirents
- conda
- 8GB RAM


[Eros Montin, PhD](me.biodimensional.com)
**Forty-six and two are just ahead of me**

# TESS Tools v2

![License](https://img.shields.io/github/license/cloudmrhub/tess-tools)
![GitHub last commit](https://img.shields.io/github/last-commit/cloudmrhub/tess-tools)
![GitHub issues](https://img.shields.io/github/issues/cloudmrhub/tess-tools)
![GitHub forks](https://img.shields.io/github/forks/cloudmrhub/tess-tools)
![GitHub stars](https://img.shields.io/github/stars/cloudmrhub/tess-tools)

**TESS Tools** provides thermal simulation utilities for calculating temperature distributions in volumetric data. It supports both Python and Bash interfaces, enabling researchers and developers to integrate thermal models into their pipelines.

## Quickstart

Run a simulation using the Python API:

```python
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

# set blood parameters
A.setBloodParameters(d={'capacity':1057,'density':3600,'temperature':310})
# set air parameters
A.setAirParameters(d={'capacity':1006,'density':1.3,'temperature':296,'metabolism':1006,'conductivity':0.026,'perfusion':0})

O=A.getOutput('/tmp/a.nii')
A.log.printWhatHappened()
print(A.params)
O.viewAxial()

```

---

# Requiremensts
1. Python 3.10 or newer
1. Virtual environment management (recommended):
   - Python's venv module, or
   - Conda environment
1. C++ compiler and build tools:
   - cmake >=3.18
   - gcc/clang
   - ninja build system

# Installation

```bash
# create and activate an environment
python3 -m venv TESS_ENV
source TESS_ENV/bin/activate

# install tess-tools
pip install git+https://github.com/cloudmrhub/tess-tools.git
```

---

## Versioning


### Version 2 (Current)
- **Name:** `tess-tools`
- **Status:** Actively maintained (main branch).
- **Installation:**
  ```bash
  pip install git+https://github.com/cloudmrhub/tess-tools.git
  ```

---


# Contributors
[*Dr. Eros Montin, PhD*](http://me.biodimensional.com)\
[![GitHub](https://img.shields.io/badge/GitHub-erosmontin-blue)](https://github.com/erosmontin)\
[![ORCID](https://img.shields.io/badge/ORCID-0000--0002--1773--0064-green)](https://orcid.org/0000-0002-1773-0064)\
[![Scopus](https://img.shields.io/badge/Scopus-35604121500-orange)](https://www.scopus.com/authid/detail.uri?authorId=35604121500)


[*Dr. Giuseppe Carluccio, PhD*](https://www.docenti.unina.it/#!/professor/47495553455050454341524c554343494f43524c47505038344130334935343958/riferimenti)\
[![GitHub](https://img.shields.io/badge/GitHub-gcarluccio-blue)](https://github.com/gcarluccio)\
[![ORCID](https://img.shields.io/badge/ORCID-0000--0001--5376--3843-green)](https://orcid.org/0000-0001-5376-3843)\
[![Scopus](https://img.shields.io/badge/Scopus-55589351600-orange)](https://www.scopus.com/authid/detail.uri?authorId=55589351600)


[*Prof. Riccardo Lattanzi, PhD*](https://med.nyu.edu/faculty/riccardo-lattanzi)\
[![GitHub](https://img.shields.io/badge/GitHub-rlattanzi-blue)](https://github.com/rlattanzi)\
[![ORCID](https://img.shields.io/badge/ORCID-0000--0002--8240--5903-green)](https://orcid.org/0000-0002-8240-5903)\
[![Scopus](https://img.shields.io/badge/Scopus-6701330033-orange)](https://www.scopus.com/authid/detail.uri?authorId=6701330033)
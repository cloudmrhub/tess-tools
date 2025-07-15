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

## General
1. Python 3.10 or newer
1. Virtual environment management (recommended):
   - Python's venv module, or
   - Conda environment

## Linux


1. C++ compiler and build tools:
  - gcc (or clang)
  - cmake >= 3.18
  - ninja-build
1. Git
Install via:
```bash
sudo apt-get update && sudo apt-get install -y \
  build-essential cmake ninja-build git
```


## Windows
1. Python 3.10+ from https://www.python.org/downloads/windows/
1. Virtual Environment: venv (default) or conda
1. C++ compiler and build tools:
  - Visual Studio Build Tools (https://visualstudio.microsoft.com/visual-cpp-build-tools/) Select Desktop Development with C++ and C++ CMake tools for Windows
  - Alternative: MinGW-w64 (https://www.mingw-w64.org/) if GCC-style tools are preferred
1. CMake https://cmake.org/download/ >= 3.18
1. Ninja https://github.com/ninja-build/ninja/releases
1. Git https://git-scm.com/download/win

## macOS

1. Python 3.10+ via https://www.python.org/downloads/mac-osx/ or Homebrew
1. Virtual Environment: venv or conda
1. Apple Clang (via Xcode Command Line Tools):

```
xcode-select --install
```
1. Homebrew packages
```
brew install cmake ninja git gcc
```

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
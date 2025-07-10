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
import tess.tess as t

A = t.Tess()
A.setSpace('testdata/Head/MaterialDensity.nii.gz')
A.binfile = './build/cpptemperature'
A.setHeatingTime(10)
A.setBloodPerfusionMap('testdata/Head/BloodPerfusion.nii.gz')
A.setMaterialDensityMap('testdata/Head/MaterialDensity.nii.gz')
A.setHeatCapacityMap('testdata/Head/HeatCapacity.nii.gz')
A.setSARMap('testdata/Head/SAR.nii.gz')
A.setThermalConductivityMap('testdata/Head/ThermalConductivity.nii.gz')
A.setMetabolismHeatMap('testdata/Head/Metabolism.nii.gz')
A.setBloodParameters(d={'capacity':1057, 'density':3600, 'temperature':310})
A.setAirParameters(d={'capacity':1006, 'density':1.3, 'temperature':296, 'metabolism':1006, 'conductivity':0.026, 'perfusion':0})
O = A.getOutput('/tmp/output_temperature.nii.gz')
O.viewAxial()
```

---

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

The **TESS Tools** package has two versions:

### V1 (Deprecated)
- **Name:** `tess`
- **Status:** Deprecated, maintained for backward compatibility.
- **Installation:**
  ```bash
  pip install git+https://github.com/cloudmrhub/tess-tools.git@v1
  ```

### Version 2 (Current)
- **Name:** `tess-tools`
- **Status:** Actively maintained (main branch).
- **Installation:**
  ```bash
  pip install git+https://github.com/cloudmrhub/tess-tools.git
  ```

---

## Key Differences

| Feature                   | Version 1 (`v1`)       | Version 2 (`main`)              |
|---------------------------|------------------------|---------------------------------|
| Maintenance               | Deprecated             | Actively maintained             |
| API                       | Legacy interface       | Improved API, more maps/options |
| Package name              | `tess`                 | `tess-tools`                    |
| Supported platforms       | Linux                  | Linux, macOS, Windows           |

---

## Migration

If you're using **Version 1**, migrate to **Version 2** for new features and updates:

```bash
pip uninstall tess
pip install git+https://github.com/cloudmrhub/tess-tools.git
```

---


# Contributors
[*Dr. Eros Montin, PhD*](http://me.biodimensional.com)\
[![GitHub](https://img.shields.io/badge/GitHub-erosmontin-blue)](https://github.com/erosmontin)\
[![ORCID](https://img.shields.io/badge/ORCID-0000--0002--1773--0064-green)](https://orcid.org/0000-0002-1773-0064)\
[![Scopus](https://img.shields.io/badge/Scopus-35604121500-orange)](https://www.scopus.com/authid/detail.uri?authorId=35604121500)


[*Dr. Giuseppe Carluccio, PhD*](https://www.docenti.unina.it/#!/professor/47495553455050454341524c554343494f43524c47505038344130334935343958/riferimenti)\
[![GitHub](https://img.shields.io/badge/GitHub-gcarlu-blue)](https://github.com/gcarlu)\
[![ORCID](https://img.shields.io/badge/ORCID-0000--0001--5376--3843-green)](https://orcid.org/0000-0001-5376-3843)\
[![Scopus](https://img.shields.io/badge/Scopus-35604121500-orange)](https://www.scopus.com/authid/detail.uri?authorId=35604121500)


[*Prof. Riccardo Lattanzi, PhD*](https://med.nyu.edu/faculty/riccardo-lattanzi)\
[![GitHub](https://img.shields.io/badge/GitHub-rlattanzi-blue)](https://github.com/rlattanzi)\
[![ORCID](https://img.shields.io/badge/ORCID-0000--0002--8240--5903-green)](https://orcid.org/0000-0002-8240-5903)\
[![Scopus](https://img.shields.io/badge/Scopus-6701330033-orange)](https://www.scopus.com/authid/detail.uri?authorId=6701330033)
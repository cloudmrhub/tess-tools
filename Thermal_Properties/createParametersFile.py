import ParametersWrite as p
"""
create some fake data to test,
courtesy of  [Giuseppe Carluccio PhD](giuseppe.carluccio@nyulangone.org)
"""

# p.ThermalProperties('./Thermal_Properties/MaterialProperties.mat','Parameters.dat')


A=p.NiftiThermalProperties('./Thermal_Properties/MaterialProperties.mat')

# A.writeSARAs('/data/test/TESS/SAR.nii.gz')
# A.writeWAs('/data/test/TESS/W.nii.gz')
# A.writeQAs('/data/test/TESS/Q.nii.gz')
# A.writeRhoAs('/data/test/TESS/Rho.nii.gz')
# A.writekAs('/data/test/TESS/k.nii.gz')
# A.writeTOldAs('/data/test/TESS/TOld.nii.gz')
A.writeCAs('/data/test/TESS/C.nii.gz')
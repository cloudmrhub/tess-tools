
import os
"""first of all you need to set an environment variable with the position of the bin file, the absolute position of course
"""

os.environ['TESS_BIN'] = '/data/PROJECTS/TESS/build/cpptemperature'

"""Then you can instantiate the class
"""
import Tess
T=Tess.Tess()

"""At this point the parameter structure is set and we can enter the required maps
"""

# from multiprocessing import Process
# def runInParallel(*fns):
#   proc = []
#   for fn in fns:
#     p = Process(target=fn)
#     p.start()
#     proc.append(p)
#   for p in proc:
#     p.join()

# runInParallel(func1, func2)


T.setMask('/data/test/TESS/Rho.nii.gz')
T.setMaterialDensityMap('/data/test/TESS/Rho.nii.gz')
T.setBloodPerfusionMap('/data/test/TESS/W.nii.gz')
T.setHeatCapacityMap('/data/test/TESS/C.nii.gz')
T.setSARMap('/data/test/TESS/SAR.nii.gz')
T.setTermalConductivityMap('/data/test/TESS/k.nii.gz')
T.setTOldMap('/data/test/TESS/TOld.nii.gz')
T.setMetabolismHeatMap('/data/test/TESS/Q.nii.gz')






T.saveOutputMapAs('/data/test/TESS/TESTOUTPUT.nii.gz')





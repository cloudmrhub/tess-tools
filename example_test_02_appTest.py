
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


T.setMask('/data/PROJECTS/TESS/testdata/TESS/Rho.nii.gz')
T.setMaterialDensityMap('/data/PROJECTS/TESS/testdata/TESS/Rho.nii.gz')
T.setBloodPerfusionMap('/data/PROJECTS/TESS/testdata/TESS/W.nii.gz')
T.setHeatCapacityMap('/data/PROJECTS/TESS/testdata/TESS/C.nii.gz')
T.setSARMap('/data/PROJECTS/TESS/testdata/TESS/SAR.nii.gz')
T.setTermalConductivityMap('/data/PROJECTS/TESS/testdata/TESS/k.nii.gz')
T.setTOldMap('/data/PROJECTS/TESS/testdata/TESS/TOld.nii.gz')
T.setMetabolismHeatMap('/data/PROJECTS/TESS/testdata/TESS/Q.nii.gz')

T.setAirParameters({
    
})




T.saveOutputMapAs('/data/PROJECTS/TESS/testdata/TESS/TESTOUTPUT.nii.gz')





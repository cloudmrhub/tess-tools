
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


T.setMask('/data/tmp/Rho.nii.gz')
T.setMaterialDensityMap('/data/tmp/Rho.nii.gz')
T.setBloodPerfusionMap('/data/tmp/W.nii.gz')
T.setHeatCapacityMap('/data/tmp/C.nii.gz')
T.setSARMap('/data/tmp/SAR.nii.gz')
T.setTermalConductivityMap('/data/tmp/k.nii.gz')
T.setTOldMap('/data/tmp/TOld.nii.gz')
T.setMetabolismHeatMap('/data/tmp/Q.nii.gz')



d=T.getTemplatesForWCRTQKParameters()
d["temperature"]=296
T.setAirParameters(d)


#set Blood Parameters
d2=T.getTemplatesForWCRTQKParameters()
d2["temperature"]=309.75
d2["density"]=3600
d2["capacity"]=1057
T.setBloodParameters(d2)

# set heating time
T.setHeatingTime(5)


T.saveOutputMapAs('/data/tmp/TESTOUTPUT.nii.gz')





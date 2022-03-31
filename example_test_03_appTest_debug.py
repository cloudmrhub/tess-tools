
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

from myPy import im
# S=[20,30,10]
# m=im.createRandomImaginable(imageSize=S)
T.setMask('debug/Rho.nii.gz')
T.setDebug()






T.saveOutputMapAs('/data/PROJECTS/TESS/testdata/TESS/__TESTOUTPUT.nii.gz')






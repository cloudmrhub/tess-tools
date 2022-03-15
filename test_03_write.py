from numpy import size
from myPy import im,mything,me

import Tess

import SimpleITK as sitk





imas=[
    {
    'type':'imaginable2D',
    'imaginable':im.createRandomImaginable(imageSize=[15,5,2]),
    'name':'Temperature',
    'outputName':'Temperature',
    'orientation':2,
    }
    ,{
    'type':'imaginable2D',
    'imaginable':im.createRandomImaginable(imageSize=[15,5,2]),
    'name':'Temperature',
    'outputName':'Temperature',
    'orientation':2,
    }
    ]


O=writeResultsAsCmJSONOutput(imas,'')
import json
with open("file.json", "w") as f:
    #Write it to file
    json.dump(O, f)
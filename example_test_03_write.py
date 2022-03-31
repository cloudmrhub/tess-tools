from numpy import size
from myPy import im,mything,me



from CMRCode.python.cm import writeResultsAsCmJSONOutput





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
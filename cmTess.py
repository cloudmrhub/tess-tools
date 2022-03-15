from Tess import Tess
from CMRCode.python.cm import writeResultsAsCmJSONOutput

class cmTess(Tess):
    def writeCMResults(self,fn):
        O=self.getOuputMap()
        
        rs=[{
            'type':'imaginable2D',
            'imaginable':O,
            'name':'Temperature',
            'outputName':'Temperature',
            'orientation':2,
        }]


        writeResultsAsCmJSONOutput(rs,fn)


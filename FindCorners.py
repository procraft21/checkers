import cv2 as cv
import numpy as np
import json
import functools
class Corners:

    red = ([0,0,0],[0,0,0])

    def __init__(self,fileName : str, showOriginal : bool = False):
        self.img = cv.imread(fileName)
    
        self.output = self.loadFromJson()
        if(showOriginal):
            cv.imshow("displayImage",self.img)
        cv.imshow("Masked", self.getMasked())
        cv.waitKey()

    def onChange(self,a, b, value):
        self.red[a][b] = value
        self.updateMask()

    def getMasked(self):
        return self.output
    
    def updateMask(self):
        print(self.red)
        lower = np.array(self.red[0],dtype="uint8")
        upper = np.array(self.red[1],dtype="uint8")
        mask = cv.inRange(self.img, lower, upper)
        output = cv.bitwise_and(self.img, self.img, mask=mask)
        #cv.imshow("images", self.output)
        return output

    def saveToJson(self,value = 0):
        redDict = {'redMin00' : self.red[0][0] , 'redMax10' : self.red[1][0],"greenMin01" : self.red[0][1] , "greenMax11" : self.red[1][1], "blueMin02" : self.red[0][2] , "blueMax12" : self.red[1][2]}
        with open("RedDefinition", 'w') as writeFile:
            json.dump(redDict, writeFile)

    def loadFromJson(self,value = 0):
        with open("RedDefinition", 'r') as f:
            redDict = json.load(f)
            for pair in redDict.items():
                print(pair)
                row = int(pair[0][-2])
                column = int(pair[0][-1])
                self.red[row][column] = pair[1]
        return self.updateMask()

    def Trackbars(self):
        trackbarName = "Trackbars"
        cv.namedWindow(trackbarName)
        cv.createTrackbar("Red Min", trackbarName,0,255, functools.partial(self.onChange,0,0))
        cv.createTrackbar("Red Max", trackbarName,0,255, functools.partial(self.onChange,1,0))
        cv.createTrackbar("Green Min", trackbarName,0,255, functools.partial(self.onChange,0,1))
        cv.createTrackbar("Green Max", trackbarName,0,255, functools.partial(self.onChange,1,1))
        cv.createTrackbar("Blue Min", trackbarName,0,255, functools.partial(self.onChange,0,2))
        cv.createTrackbar("Blue Max", trackbarName,0,255, functools.partial(self.onChange,1,2))
        cv.createTrackbar("save to json", trackbarName,0,1, self.saveToJson)
        cv.createTrackbar("load from json", trackbarName,0,1, self.loadFromJson)
        cv.waitKey()

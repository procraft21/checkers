import cv2 as cv
import numpy as np
img = cv.imread('checkers.png')
cv.imshow("displayImage",img)
red = ([0,0,0],[0,0,0])

def onChangeRedMin(value):
    red[0][0] = value
    updateMask()
def onChangeRedMax(value):
    red[1][0] = value
    updateMask()
def onChangeGreenMin(value):
    red[0][1] = value
    updateMask()
def onChangeGreenMax(value):
    red[1][1] = value
    updateMask()
def onChangeBlueMin(value):
    red[0][2] = value
    updateMask()
def onChangeBlueMax(value):
    red[1][2] = value
    updateMask()
def updateMask():
    print(red)
    lower = np.array(red[0],dtype="uint8")
    upper = np.array(red[1],dtype="uint8")
    mask = cv.inRange(img, lower, upper)
    output = cv.bitwise_and(img, img, mask=mask)
    cv.imshow("images", output)
    
    
trackbarName = "Trackbars"
cv.namedWindow(trackbarName)
cv.createTrackbar("Red Min", trackbarName,0,255, onChangeRedMin)
cv.createTrackbar("Red Max", trackbarName,0,255, onChangeRedMax)
cv.createTrackbar("Green Min", trackbarName,0,255, onChangeGreenMin)
cv.createTrackbar("Green Max", trackbarName,0,255, onChangeGreenMax)
cv.createTrackbar("Blue Min", trackbarName,0,255, onChangeBlueMin)
cv.createTrackbar("Blue Max", trackbarName,0,255, onChangeBlueMax)

# loop over the boundaries
#for (lower, upper) in boundaries:
#	# create NumPy arrays from the boundaries
#	lower = np.array(lower, dtype = "uint8")
#	upper = np.array(upper, dtype = "uint8")
#	# find the colors within the specified boundaries and apply
#	# the mask
#	mask = cv.inRange(img, lower, upper)
#	output = cv.bitwise_and(img, img, mask = mask)
#	# show the images
#	cv.imshow("images", np.hstack([img, output]))
#	cv.waitKey(0)

cv.waitKey(0)
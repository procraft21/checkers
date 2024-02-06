import FindCorners
import cv2 as cv
coreners = FindCorners.Corners("checkers.png", True)
cv.imshow(coreners.getMasked())
cv.waitKey() 
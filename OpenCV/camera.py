import cv
from datetime import datetime

capture = cv.CreateCameraCapture(0)
img = cv.QueryFrame(capture)
cv.SaveImage("/Users/apple/login_log/log_in_on_" + datetime.now().isoformat() + ".jpg", img)

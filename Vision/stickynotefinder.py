import cv2
import numpy as np

cap = cv2.VideoCapture(1)

while True:
    _, frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

#avg color hsv is like 68,80,83
    # lower_sticky = np.array([79,86,71])
    # upper_sticky = np.array([64,75,84])
    upper_sticky = np.array([53,214,204])
    lower_sticky = np.array([25,181,132])

    mask = cv2.inRange(hsv,lower_sticky,upper_sticky)
    res = cv2.bitwise_and(frame, frame, mask= mask)

    cv2.imshow('frame', frame)
    cv2.imshow('mask', mask)
    cv2.imshow('res', res)

    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break

cv2.destroyAllWindows()
cv2.release()
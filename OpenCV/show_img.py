import cv

if __name__ == '__main__':
    # Open a pic
    image = cv.LoadImage("doodle.jpg")

    # Create a window
    cv.NamedWindow("mywin")

    # Print image
    cv.ShowImage("mywin", image)
    cv.WaitKey(0)
    print "testing"

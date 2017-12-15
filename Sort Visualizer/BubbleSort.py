import pygame
import sys
from random import randint,shuffle
import random
import time
pygame.init()

#To open a window of size 700,700, use the statement below.

DISPLAY_HEIGHT = 500
DISPLAY_WIDTH = 1000
DISPLAY = pygame.display.set_mode((DISPLAY_WIDTH,DISPLAY_HEIGHT))

#To change the title of the window

pygame.display.set_caption("Bubble Sort")

#Color codes

BLACK = pygame.Color(0,0,0)
WHITE = pygame.Color(255,255,255)
GREEN = pygame.Color(0,255,0)
RED = pygame.Color(255,0,0)
BLUE = pygame.Color(0,0,255)

heightList = []
rectWidth = 6
listLength = int(DISPLAY_WIDTH / rectWidth)

color = []
#~~~~~~~~~~loop for random numbers~~~~~~~~~~~~~~~
#for i in range(listLength):
#   #Generate a list of random numbers
#    heightList.append(randint(0,DISPLAY_HEIGHT))
#    #Initialize all the columns to white color
#    color.append(WHITE)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#~~~~~loop for subsequent number plush shuffle of array~~~~~
for i in range(listLength):
    heightList.append(i*3)
    color.append(WHITE)
random.shuffle(heightList)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def draw():
    global heightList
    for i in range(listLength):
        #pygame.draw.rect(screen, color, (x,y,width,height), thickness) draws a rectangle (x,y,width,height) is a Python
        #tuple x,y are the coordinates of the upper left hand corner width, height are the width and height of the
        #rectangle thickness is the thickness of the line. If it is zero, the rectangle is filled

        #pygame.draw.rect(DISPLAY,GREEN,(xList[i], y, rectWidth, -heightList[i]),0)

        pygame.draw.rect(DISPLAY, color[i], (rectWidth * i,  DISPLAY_HEIGHT - heightList[i], rectWidth-1, heightList[i]),0)
    #refresh the values displayed on the screen
    pygame.display.update()

#isSorted=False
sortedCount = 0
trackInt = 0


#while isSorted != True:
#while sortedCount!=listLength:
while True:
    color[-sortedCount]=GREEN
    draw()
    if sortedCount==listLength:
        break
    for i in range(listLength-sortedCount-1):
        color[i]=BLUE
        color[i+1]=RED
        #draw()
        #time.sleep(0.1)

        if heightList[i] > heightList[i+1]:
            heightList[i], heightList[i+1] = heightList[i+1], heightList[i]
            color[i+1] = BLUE

        color[i]=WHITE

        # screen.fill(color) fills the entire screen with the given color
        #clean the display
        DISPLAY.fill(BLACK)
        #print the new values to screen
        draw()

    if sortedCount < listLength:
        sortedCount += 1


    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

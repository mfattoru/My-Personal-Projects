import pygame
import sys
import random
import time
import os

#duration = 0.01  # second



pygame.init()

#To open a window of size X,Y, use the statement below.

DISPLAY_HEIGHT = 500
DISPLAY_WIDTH = 1000
DISPLAY = pygame.display.set_mode((DISPLAY_WIDTH,DISPLAY_HEIGHT))

#To change the title of the window

pygame.display.set_caption("Merge Sort")

#Color codes

BLACK = pygame.Color(0,0,0)
WHITE = pygame.Color(255,255,255)
GREEN = pygame.Color(0,255,0)
RED = pygame.Color(255,0,0)
BLUE = pygame.Color(0,0,255)
YELLOW = pygame.Color(255,255,0)

heightList = []
rectWidth = 6
listLength = int(DISPLAY_WIDTH / rectWidth)

color = []

#start_freq = 440  # Hz
#freq=[]
#for i in range(listLength):
#    freq.append(start_freq+(i*5))


#~~~~~~~~~~loop for random numbers~~~~~~~~~~~~~~~
#for i in range(listLength):
#   #Generate a list of random numbers
#    heightList.append(randint(0,DISPLAY_HEIGHT))
#    #Initialize all the columns to white color
#    color.append(WHITE)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#~~~~~loop for subsequent number plush shuffle of array~~~~~
#num_of_columns = listLength/rectWidth
#multipl_index=1
#while True:
#    if num_of_columns * (multipl_index+1) < DISPLAY_HEIGHT:
#        print("~~~~~~~~~~~~~~~~~~",num_of_columns*multipl_index)
#        multipl_index+=0.25
#    else:
#        break

for i in range(listLength):
    heightList.append(i*3)
    color.append(WHITE)
random.shuffle(heightList)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

print(heightList)

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

sortedCount = 0
DISPLAY.fill(BLACK)

def merge_sort(start,end):
    global color
    global heightList

    DISPLAY.fill(BLACK)
    if end - start <=0:
        for x in range(start,end):
            print(heightList[x])
        return

    middle = (start + end) // 2

    color[middle]=RED
    draw()
    color[start]=BLUE
    draw()
    color[end]=YELLOW
    draw()

    #time.sleep(0.05)

    merge_sort(start, middle)
    merge_sort(middle+1, end)

    merge(start,middle,middle+1,end)


def merge(l_start, l_end, r_start, r_end):
    global color
    global heightList
    start,end = l_start,r_end
    result=[]
    index = l_start
    while index <= r_end:
        if l_start > l_end:
            result.append(heightList[r_start])
            r_start+=1
        elif r_start > r_end:
            result.append(heightList[l_start])
            l_start+=1
        elif heightList[l_start] < heightList[r_start]:
            result.append(heightList[l_start])
            l_start +=1
        else:
            result.append(heightList[r_start])
            r_start+=1

        #os.system('play --no-show-progress --null --channels 1 synth %s sine %f' % (duration, freq[index]))
        color[index]=RED
        draw()
        color[index]=WHITE

        index+=1
        #print("result",result)

    i=0
    for x in range(start,end+1):
        heightList[x]=result[i]
        if start==0 and end == listLength -1:
            color[x]=GREEN
            draw()
        else:
            color[x]=RED
            draw()
            color[x]=WHITE
        #os.system('play --no-show-progress --null --channels 1 synth %s sine %f' % (duration, freq[x]))
        DISPLAY.fill(BLACK)

        #time.sleep(0.05)
        i+=1


merge_sort(0,listLength-1)

print(heightList)

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

import pygame
import time
import random

pygame.init()

WHITE = (255,255,255)
BLACK = (0,0,0)
RED = (255,0,0)
GREEN = (0,255,0)
BLUE = (0,0,255)

DISPLAY_WIDTH = 800
DISPLAY_HEIGHT = 600

gameDisplay = pygame.display.set_mode((DISPLAY_WIDTH,DISPLAY_HEIGHT))
pygame.display.set_caption("Snake")

head_img = pygame.image.load('snakehead15.png')
body_img = pygame.image.load('body15.png')
tail_img = pygame.image.load('tail15.png')


#update all the display at once
#pygame.display.flip()
#update only the area specified, if left empty update the whole display
#pygame.display.update()


clock = pygame.time.Clock()

BLOCK_SIZE = 15
APPLE_THICKNESS = 10
FPS = 10

direction = "right"

font = pygame.font.SysFont(None,25)

def text_objects(text,color):
    textSurface = font.render(text, True, color)
    return textSurface, textSurface.get_rect()


def message_to_screen(msg,color):
    textSurf, textRect = text_objects(msg,color)
    #screen_text = font.render(msg, True, color)
    #gameDisplay.blit(screen_text, [DISPLAY_WIDTH/2 - len(msg)/2,DISPLAY_HEIGHT/2])
    textRect.center = (DISPLAY_WIDTH / 2), (DISPLAY_HEIGHT / 2)
    gameDisplay.blit(textSurf, textRect)

def snake(snake_list,size):

    if direction == "right":
        head = pygame.transform.rotate(head_img,270)
        #body = pygame.transform.rotate(body_img,270)
        #tail = pygame.transform.rotate(tail_img,270)
    if direction == "left":
        head = pygame.transform.rotate(head_img,90)
        #body = pygame.transform.rotate(body_img, 90)
        #tail = pygame.transform.rotate(tail_img, 90)
    if direction == "up":
        head = head_img
        #body = body_img
        #tail = tail_img
    if direction == "down":
        head = pygame.transform.rotate(head_img,180)
        #body = body_img
        #tail = pygame.transform.rotate(tail_img, 180)

    gameDisplay.blit(head,(snake_list[-1][0], snake_list[-1][1]))

    for XnY in snake_list[:-1]:
        #gameDisplay.blit(body, (XnY[0], XnY[1]))
        pygame.draw.rect(gameDisplay, GREEN, [XnY[0], XnY[1], size, size])
    #if len(snake_list)>1:
    #    gameDisplay.blit(tail, (snake_list[0][0], snake_list[0][1]))


def apple():
    x = (random.randrange(0, DISPLAY_WIDTH - APPLE_THICKNESS) // 10) * 10
    y = (random.randrange(0, DISPLAY_HEIGHT - APPLE_THICKNESS) // 10) * 10
    return x, y

def gameLoop():
    global direction
    gameExit = False
    gameOver = False

    lead_x = DISPLAY_WIDTH / 2
    lead_y = DISPLAY_HEIGHT / 2

    lead_x_change = 10
    lead_y_change = 0

    snake_list = []
    snake_length = 1
    # fix hardcode
    appleX,appleY = apple()

    while not gameExit:

        while gameOver == True:
            gameDisplay.fill(WHITE)
            message_to_screen("Game Over, Press C to play or Q to Quit",RED)
            pygame.display.update()

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    gameExit = True
                    gameOver = False
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_q:
                        gameExit = True
                        gameOver = False
                    elif event.key == pygame.K_c:
                        gameOver = False
                        lead_x = DISPLAY_WIDTH / 2
                        lead_y = DISPLAY_HEIGHT / 2
                        lead_x_change = 10
                        lead_y_change = 0
                        # fix hardcode
                        appleX, appleY = apple()
                        snake_list = []
                        snake_length = 1

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                gameExit = True
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    if lead_x_change == 0:
                        lead_x_change = -BLOCK_SIZE
                    lead_y_change = 0
                    direction = "left"
                elif event.key == pygame.K_RIGHT:
                    if lead_x_change == 0:
                        lead_x_change = BLOCK_SIZE
                    lead_y_change = 0
                    direction = "right"
                elif event.key == pygame.K_UP:
                    if lead_y_change == 0:
                        lead_y_change = -BLOCK_SIZE
                    lead_x_change = 0
                    direction = "up"
                elif event.key == pygame.K_DOWN:
                    if lead_y_change == 0:
                        lead_y_change  = BLOCK_SIZE
                    lead_x_change = 0
                    direction = "down"

            # Stop the movement when stopping to press the movement key
            # if event.type == pygame.KEYUP:
            #     if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
            #         lead_x_change = 0
            #     if event.key == pygame.K_UP or event.key == pygame.K_DOWN:
            #         lead_y_change = 0

        if lead_x + BLOCK_SIZE > DISPLAY_WIDTH or lead_x < 0 or lead_y + BLOCK_SIZE > DISPLAY_HEIGHT or lead_y < 0:
            gameOver = True

        lead_x += lead_x_change
        lead_y += lead_y_change
        gameDisplay.fill(WHITE)
        pygame.draw.rect(gameDisplay,RED,[appleX,appleY,APPLE_THICKNESS,APPLE_THICKNESS])

        snake_head = []

        snake_head.append(lead_x)
        snake_head.append(lead_y)

        snake_list.append(snake_head)
        if len(snake_list) > snake_length:
            snake_list.pop(0)

        if snake_head in snake_list[:-1]:
            gameOver = True

        snake(snake_list,BLOCK_SIZE)
        if not gameOver:   # avoid to draw an additional block move before to display the game over message
            pygame.display.update()

        # if lead_x >= appleX and lead_x < appleX + APPLE_THICKNESS and lead_y >= appleY and lead_y < appleY + APPLE_THICKNESS:
        #     appleX,appleY = apple()
        #     snake_length += 1

        #handled the case when the apple can be bigger than the snake (maybe for future bonus malus)
        if (lead_x >= appleX and lead_x < appleX + APPLE_THICKNESS) or (lead_x + BLOCK_SIZE > appleX and lead_x + BLOCK_SIZE < appleX + APPLE_THICKNESS):
            if (lead_y >= appleY and lead_y < appleY + APPLE_THICKNESS) or (lead_y + BLOCK_SIZE > appleY and lead_y + BLOCK_SIZE < appleY + APPLE_THICKNESS):
                appleX, appleY = apple()
                snake_length += 1
        #handled the case if the snake is bigger than the apple (maybe for future bonus malus)
        if(appleX >= lead_x and appleX < lead_x + BLOCK_SIZE) or (appleX + APPLE_THICKNESS > lead_x and appleX + APPLE_THICKNESS < lead_x + BLOCK_SIZE):
            if (appleY >= lead_y and appleY < lead_y + BLOCK_SIZE) or (appleY + APPLE_THICKNESS > lead_y and appleY + APPLE_THICKNESS < lead_y + BLOCK_SIZE):
                appleX, appleY = apple()
                snake_length += 1

        clock.tick(FPS)

    pygame.quit()
    quit()

gameLoop()

import pygame
import random
#################
pygame.init()
#################
screen_width = 480
screen_height = 640
screen = pygame.display.set_mode((screen_width,screen_height))

pygame.display.set_caption("Quiz")

clock = pygame.time.Clock()

## 배경만들기
background = pygame.image.load("C:/tmp/background.png")

## charactor
character = pygame.image.load("C:/tmp/charactor.png")
character_size = character.get_rect().size
character_width = character_size[0]
character_height = character_size[1]
character_x_pos = (screen_width/2) - (character_width / 2)
character_y_pos = screen_height - character_height
to_x = 0
to_y = 0
character_speed = 10


## enemy
enemy = pygame.image.load("C:/tmp/enemy.png")
enemy_size = enemy.get_rect().size
enemy_width = enemy_size[0]
enemy_height = enemy_size[1]
enemy_x_pos = random.randint(0,screen_width-enemy_width)
enemy_y_pos = 0
enemy_speed = 10


running = True
while running:
    dt = clock.tick(30)
    # 2 event
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                to_x -= character_speed
            elif event.key == pygame.K_RIGHT:
                to_x += character_speed
            elif event.key == pygame.K_UP:
                to_y -= character_speed
            elif event.key == pygame.K_DOWN:
                to_y += character_speed
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                to_x = 0
            elif event.key == pygame.K_UP or event.key == pygame.K_DOWN:
                to_y = 0

    # 3 position
    character_x_pos += to_x
    if character_x_pos < 0:
        character_x_pos = 0
    character_y_pos += to_y
    if character_y_pos < 0:
        character_y_pos = 0
    elif character_x_pos > (screen_width - character_width):
        character_x_pos = (screen_width - character_width)
    elif character_y_pos > (screen_height - character_height):
        character_y_pos = (screen_height - character_height)

    # 4
    # 5 display
    screen.blit(background,(0,0))
    screen.blit(character,(character_x_pos,character_y_pos))

    pygame.display.update()

pygame.quit()
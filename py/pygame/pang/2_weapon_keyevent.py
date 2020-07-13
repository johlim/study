import pygame
import random
import os
#################
pygame.init()
#################
screen_width = 640
screen_height = 480
screen = pygame.display.set_mode((screen_width,screen_height))

pygame.display.set_caption("Quiz")

clock = pygame.time.Clock()
current_path = os.path.dirname(__file__)

## 배경만들기
background = pygame.image.load("background.png")
## stage 만들기
stage = pygame.image.load("stage.png")
stage_size = stage.get_rect().size
stage_width = stage_size[0]
stage_height = stage_size[1]


## charactor
character = pygame.image.load("charactor.png")
character_size = character.get_rect().size
character_width = character_size[0]
character_height = character_size[1]
character_x_pos = (screen_width/2) - (character_width / 2)
character_y_pos = screen_height - character_height - stage_height
to_x = 0
to_y = 0
character_speed = 10


## enemy
enemy = pygame.image.load("enemy.png")
enemy_size = enemy.get_rect().size
enemy_width = enemy_size[0]
enemy_height = enemy_size[1]
enemy_x_pos = random.randint(0,screen_width-enemy_width)
enemy_y_pos = 0
enemy_speed = 10

## weapon
weapon = pygame.image.load("weapon.png")
weapon_size = weapon.get_rect().size
weapon_width = weapon_size[0]
weapon_height = weapon_size[1]
weapon_x_pos = random.randint(0,screen_width-weapon_width)
weapon_y_pos = 0
weapon_speed = 10

weapons=[]


running=True

while running:
    dt = clock.tick(30)

    #
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running=False
    
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                to_x -= character_speed
            elif event.key == pygame.K_RIGHT:
                to_x += character_speed
            elif event.key == pygame.K_SPACE:
                weapon_x_pos = character_x_pos+(character_width/2)-(weapon_width/2)
                weapon_y_pos = character_y_pos
                weapons.append([weapon_x_pos,weapon_y_pos])

        if event.type == pygame.KEYUP:
            if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                to_x = 0
    
    character_x_pos += to_x

    if character_x_pos < 0:
        character_x_pos = 0
    elif character_x_pos > (screen_width-character_width):
        character_x_pos = (screen_width-character_width)

    # weapon position update
    weapons = [ [w[0],w[1]-weapon_speed] for w in weapons]
    # remove weapon on top , out of range 
    weapons = [ [w[0],w[1]] for w in weapons if w[1] > 0]


    # 5 display
    screen.blit(background,(0,0))

    for weapon_x_pos , weapon_y_pos in weapons:
        screen.blit(weapon,(weapon_x_pos,weapon_y_pos))

    screen.blit(stage,(0,screen_height-stage_height))
    screen.blit(character,(character_x_pos,character_y_pos))


    pygame.display.update()



pygame.quit()
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

## Ball
ball_images = [
     pygame.image.load("balloon1.png"),
     pygame.image.load("balloon2.png"),
     pygame.image.load("balloon3.png"),
     pygame.image.load("balloon4.png")]

ball_speed_y = [-18,-15,-12,-9]

balls=[]
balls.append({
    "pos_x":50, # X
    "pos_y":50, # Y
    "img_idx" : 0, # ball_images
    "to_x" : 3, # X direction
    "to_y": -6, # Y direction
    "init_speed_y":ball_speed_y[0] #ball_speed_y
})
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

    # ball positon update
    for ball_idx, ball_val in enumerate(balls):
        ball_pos_x = ball_val["pos_x"]
        ball_pos_y = ball_val["pos_y"]
        ball_img_idx = ball_val["img_idx"]

        ball_size = ball_images[ball_img_idx].get_rect().size
        ball_width = ball_size[0]
        ball_height = ball_size[1]
        # check x range limit
        if ball_pos_x < 0 or ball_pos_x > (screen_width - ball_width):
            ball_val["to_x"] = ball_val["to_x"] * -1
        
        # check y range limit
        if ball_pos_y >= (screen_height - stage_height - ball_height):
            ball_val["to_y"] = ball_val["init_speed_y"]
        else:
            ball_val["to_y"] += 0.5

        ball_val["pos_x"] += ball_val["to_x"] 
        ball_val["pos_y"] += ball_val["to_y"] 

    # 5 display
    screen.blit(background,(0,0))

    for weapon_x_pos , weapon_y_pos in weapons:
        screen.blit(weapon,(weapon_x_pos,weapon_y_pos))
    for idx,val in enumerate(balls):
        ball_pos_x = val["pos_x"]
        ball_pos_y = val["pos_y"]
        ball_pos_idx = val["img_idx"]
        screen.blit(ball_images[ball_pos_idx],(ball_pos_x,ball_pos_y))

    screen.blit(stage,(0,screen_height-stage_height))
    screen.blit(character,(character_x_pos,character_y_pos))


    pygame.display.update()



pygame.quit()
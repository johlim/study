# -*- coding: utf-8 -*-
"""
Created on Wed Jul 15 01:02:58 2020

@author: jhlim
"""

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

## background
background = pygame.image.load("background.png")
## stage
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
player_to_x_LEFT=0
player_to_x_RIGHT=0

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
weapon_to_remove=-1
ball_to_remove=-1

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

# Font 
total_time = 100
game_font = pygame.font.Font(None,40)
start_ticks = pygame.time.get_ticks()
game_result="Game Over"
#
running=True


while running:
    dt = clock.tick(30)

    #
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running=False
    
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                player_to_x_LEFT -= character_speed 
            elif event.key == pygame.K_RIGHT:
                player_to_x_RIGHT += character_speed
            elif event.key == pygame.K_SPACE:
                weapon_x_pos = character_x_pos+(character_width/2)-(weapon_width/2)
                weapon_y_pos = character_y_pos
                weapons.append([weapon_x_pos,weapon_y_pos])

        if event.type == pygame.KEYUP:
            if event.key == pygame.K_LEFT:
                player_to_x_LEFT = 0
            elif event.key == pygame.K_RIGHT:
                player_to_x_RIGHT = 0
    
    #character_x_pos += to_x
    character_x_pos += player_to_x_LEFT + player_to_x_RIGHT

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
    
    # 4 collizon
    charactor_rect = character.get_rect()
    charactor_rect.left = character_x_pos
    charactor_rect.top = character_y_pos
    
    for ball_idx, ball_val in enumerate(balls):
        ball_pos_x = ball_val["pos_x"]
        ball_pos_y = ball_val["pos_y"]
        ball_img_idx = ball_val["img_idx"]

        ball_rect = ball_images[ball_img_idx].get_rect()
        ball_rect.left = ball_pos_x
        ball_rect.top = ball_pos_y
    ## ball and charactor collion
        if charactor_rect.colliderect(ball_rect):
            running = False
            break
        
    ## ball and weapon pos process
        for weapon_idx, weapon_val in enumerate(weapons):
            weapon_pos_x = weapon_val[0]
            weapon_pos_y = weapon_val[1]
            
            weapon_rect = weapon.get_rect()
            weapon_rect.left = weapon_pos_x
            weapon_rect.top = weapon_pos_y
            
            ### check
            if weapon_rect.colliderect(ball_rect):
                weapon_to_remove = weapon_idx # weapon idx to be removed
                ball_to_remove = ball_idx # weapon idx to be removed
                
                if (ball_img_idx < 3):
                    # current ball position
                    ball_width = ball_rect.size[0]
                    ball_height = ball_rect.size[1]
                    # prepare small ball size
                    small_ball_rect = ball_images[ball_img_idx + 1].get_rect()
                    small_ball_width = small_ball_rect.size[0]
                    small_ball_height = small_ball_rect.size[1]
                    # left small ball
                    balls.append({
                        "pos_x":ball_pos_x + (ball_width/2) - (small_ball_width/2), # X
                        "pos_y":ball_pos_y + (ball_height/2) - (small_ball_height/2), # Y
                        "img_idx" : ball_img_idx+1, # next small ball_images
                        "to_x" :-3, # X direction
                        "to_y": -6, # Y direction
                        "init_speed_y":ball_speed_y[ball_img_idx+1] #ball_speed_y
                    })
                    # right small ball
                    balls.append({
                        "pos_x":ball_pos_x + (ball_width/2) - (small_ball_width/2), # X
                        "pos_y":ball_pos_y + (ball_height/2) - (small_ball_height/2), # Y
                        "img_idx" : ball_img_idx+1, # next small ball_images
                        "to_x" :+3, # X direction
                        "to_y": -6, # Y direction
                        "init_speed_y":ball_speed_y[ball_img_idx+1] #ball_speed_y
                    })
                break
        else: ## for else
            continue
        break
    # remove ball and weapon to remove
    if ball_to_remove > -1:
        del balls[ball_to_remove]
        ball_to_remove = -1
    if weapon_to_remove > -1:
        del weapons[weapon_to_remove]
        weapon_to_remove = -1
    # Game Over
    if len(balls) == 0:
        game_result = "Mission complete"
        running = False
        
    
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

    # calculate elapse time
    elapsed_time = (pygame.time.get_ticks() - start_ticks) / 1000
    timer = game_font.render("Time : {}".format(int(total_time - elapsed_time)),1,(255, 0, 225))
    screen.blit(timer,(10,10))
    
    if total_time - elapsed_time <= 0:
        game_result = "Time Over"
        running = False
    
    
    pygame.display.update()

# game over message
msg = game_font.render(game_result,1,(255,255,0))
msg_rect = msg.get_rect(center=(int(screen_width/2),int(screen_height/2)))
screen.blit(msg,msg_rect)
    

pygame.time.delay(2000)

pygame.quit()

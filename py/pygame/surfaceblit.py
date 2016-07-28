import pygame
from time import sleep

width=640
height=480
radius=100
stroke=1

pygame.init()

window = pygame.display.set_mode((width,height))
#window.fill(pygame.Color(255,255,255))
background=pygame.image.load("background.png")
theremin=pygame.image.load("theremin.png")
background.convert_alpha()
theremin.convert_alpha()
window.blit(background,(0,0))
window.blit(theremin,(135,50))

while True:
	pygame.display.update()
	sleep(0.2)
	if pygame.QUIT in [e.type for e in pygame.event.get()]:
		break
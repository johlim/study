import pygame
from time import sleep

width=640
height=480
radius=100
stroke=1

pygame.init()

window = pygame.display.set_mode((width,height))
window.fill(pygame.Color(255,128,128))

pen=pygame.Color(122,0,0)
remover=pygame.Color(255,128,128)
while True:
	pygame.draw.circle(window,
		pen,
		(width/2,height/2),
		radius, stroke)
	pygame.display.update()
	sleep(0.2)
	pygame.draw.circle(window,
		remover,
		(width/2,height/2),
		radius, stroke)	
	pygame.display.update()
	width=width-2
	height=height-2
	if height == 1:
		width=640
		height=480
	if pygame.QUIT in [e.type for e in pygame.event.get()]:
		break
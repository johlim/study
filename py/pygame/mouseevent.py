import pygame
from time import sleep
from pygame.locals import *

width=640
height=640
radius=1
stroke=1
mouseX=0
mouseY=0
pygame.init()

window = pygame.display.set_mode((width,height))
window.fill(pygame.Color(255,255,255))

fps=pygame.time.Clock()

while True:
	for event in pygame.event.get():
		if event.type == MOUSEMOTION:
			mouseX, mouseY = event.pos
		if event.type == MOUSEBUTTONDOWN:
			window.fill(pygame.Color(255,128,128))
	radius=(abs(width/2 - mouseX)+abs(height/2 - mouseY))/2 +1
	pygame.draw.circle(window, pygame.Color(255,0,0),	(mouseX,mouseY),	radius, 1)
	pygame.display.update()	
	#sleep(0.5)
	if pygame.QUIT in [e.type for e in pygame.event.get()]:
		break
fps.tick(30)
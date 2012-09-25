from gameglobals import *
import pygame

class Window:
	#data for where important screenbits should go. TODO: window management	
	def __init__(self, screenSize, caption):
		self.screenSize = screenSize
		self.screen = pygame.display.set_mode(screenSize)
		self.caption = pygame.display.set_caption(caption)

	def update(self, surface):
		self.screen.fill(BLACK)
		if surface:
			self.screen.blit(surface, (0,0))
		pygame.display.flip()
#PYGAME THINGS
import pygame
from pygame.locals import *
from pygame.sprite import Sprite, Group
import numpy as np
from numpy import array
from numpy import random
import sys

from gameglobals import *
from state import *
from window import *

class Game:
	def __init__(self, startState, framerate):
		pygame.init()
		self.stateManager = StateManager(self)
		self.stateManager.push(startState)
		self.clock = pygame.time.Clock()
		self.running = True
		self.framerate = framerate
	def initWindow(self, screenSize, caption):
		self.window = Window(screenSize, caption)
	def run(self):
		while self.running:
			elapsedTime = self.clock.tick(self.framerate)
			for event in pygame.event.get():
				if event.type==QUIT:
					self.running = False
				if event.type in (pygame.KEYDOWN, pygame.KEYUP):
					self.stateManager.input(event.type, event.key)
			self.stateManager.update(elapsedTime)
			self.window.update(self.stateManager.getSurface())
		self.shutDown()
	def end(self):
		self.running = False
	def shutDown(self):
		pygame.quit()
		sys.exit()

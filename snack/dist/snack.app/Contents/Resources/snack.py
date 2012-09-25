#PYGAME THINGS
import pygame
from pygame.locals import *
from sys import exit
import random

from gameglobals import *
from state import *
WINDOW_CAPTION = 'Snackington'
GAME_FONT = 'futura'
SCREEN_SIZE = 640,480
GAME_SPEED = 15
DEFAULT_SEGS = 5
BLOCK_SIZE = 20

class Entity():
	def __init__(self):
		self.scene = None
	def __init__(self, scene):
		self.setScene(scene)
		self.sceneInit()
	def sceneInit(self):
		pass
	def setScene(self, scene):
		self.scene = scene
	def getDrawables(self):
		return []
	def update(self):
		pass

class Apple(Entity):
	def __init__(self, scene):
		Entity.__init__(self, scene)
		self.color = RED
		self.drawable = pygame.Surface((self.scene.gridsize, self.scene.gridsize))
		pygame.draw.rect(self.drawable, self.color, Rect(0,0,self.scene.gridsize, self.scene.gridsize), 0)
		self.newApple()
	def getDrawables(self):
		pos = self.position
		gs = self.scene.gridsize
		return [[self.drawable, (pos[0]*gs, pos[1]*gs)]]
	def newApple(self):
		self.position = self.scene.randomPos()
		self.scene.setItem(self.position, 1)
	def sceneInit(self):
		pass

class Snake(Entity):
	'''
	snake.segments: array of positions, 0 is the head, -1 is the tail
	each update, move the tail up on to the head, rather than updating every single segment
	'''
	def __init__(self, scene):
		Entity.__init__(self, scene)
		self.numSegments = DEFAULT_SEGS
		startPos = self.scene.randomPos()
		self.segments = [startPos for x in range(self.numSegments)]
		self.drawable = pygame.Surface((self.scene.gridsize, self.scene.gridsize))
		self.color = random.choice(COLORS)
		pygame.draw.rect(self.drawable, self.color, Rect(0,0,self.scene.gridsize, self.scene.gridsize), 0)
		self.direction = (0,0)
	def sceneInit(self):
		pass
	def setColor(self, color):
		pass
	def setDirection(self, direction):
		if tuple(x + y for x, y in zip(self.direction, direction)) != (0,0): 
			self.direction = direction
	def getDrawables(self):
		return [[self.drawable, (x*self.scene.gridsize, y*self.scene.gridsize)] for (x,y) in self.segments]
	def update(self):
		'''returns 0 if good, 1 if ate apple, 2 if died'''
		if (self.direction == (0,0)): 
			return 0
		else:
			a = self.segments[0]
			b = self.direction
			newHead = (a[0]+b[0], a[1]+b[1])
			oldTail = self.segments.pop()
			if self.scene.inScene(newHead):
				self.segments.insert(0, newHead)
				newHeadItem = self.scene.getItem(newHead)
				self.scene.setItem(newHead, 2)
				if oldTail != self.segments[-1]:
					 self.scene.setItem(oldTail, 0)
				if newHeadItem == 1:
					self.numSegments += 1
					self.segments.append(self.segments[-1])
					return 1
				elif newHeadItem==0:
					return 0
			return 2


class BlockScene:
	'''
	2d array of spaces:
		0 is free
		1 is apple
		2 is snake
	'''
	def __init__(self, screensize, blocksize):
		self.x = screensize[0]/blocksize
		self.y = screensize[1]/blocksize
		self.screensize = screensize
		self.gridsize = blocksize
		self.grid= [[0 for y in range(self.y)] for x in range(self.x)]
	def update(self):
		pass
	def inScene(self, pos):
		return pos[0]<self.x and pos[0] >= 0 and pos[1]<self.y and pos[1]>=0
	def randomPos(self):
		while True:
			newPos = [random.randint(0,self.x-1),random.randint(0,self.y-1)]
			if self.getItem(newPos) == 0:
				return newPos
	def getItem(self, pos):
		return self.grid[pos[0]][pos[1]]
	def setItem(self, pos, variety):
		self.grid[pos[0]][pos[1]] = variety
		return pos
	def emptyBlock(self, pos):
		self.grid[pos[0]][pos[1]] = 0
		return pos

class S_Title(State):
		def managedInit(self):
			titleText = self.manager.game.text("SNACKINGTON T. SNAKE", True, WHITE)
			instText = self.manager.game.text("[P]lay game, [I]nstructions, or [Q]uit", True, WHITE)
			self.drawables.append([titleText, [10,10]])
			self.drawables.append([instText, [10, titleText.get_height()+10]])
			
		def update(self, keys):
			for k in keys:
				if k == K_q:
					self.manager.end()
				elif k == K_i:
					self.manager.push(S_Instructions())
				elif k == K_p:
					self.manager.push(S_Play())

class S_PromptQuit(State):
		def managedInit(self):
			really = self.manager.game.text("Really quit? [y]/[n]", True, WHITE)
			self.drawables.append([really, [10,10]])
		
		def update(self, keys):
			for k in keys:
				if k == K_y:
					self.manager.end()
				elif k == K_n:
					self.manager.swap(S_Pause())

class S_GameOver(State):
	def managedInit(self):
		gameover = self.manager.game.text("GAME OVER", True, WHITE)
		inst = self.manager.game.text("[P]lay again, [B]ack to menu", True, WHITE)
		self.drawables.append([gameover, [10,10]])
		self.drawables.append([inst, [10,gameover.get_height()+10]])
	
	def update(self, keys):
		for k in keys:
			if k == K_p:
				self.manager.swap(S_Play())
			elif k == K_b:
				self.manager.pop()

class S_Pause(State):
		def managedInit(self):
			really = self.manager.game.text("PAUSED", True, WHITE)
			cont = self.manager.game.text("Space to continue...", True, WHITE)
			self.drawables.append([really, [10,10]])
			self.drawables.append([cont, [10,really.get_height()+10]])
		def getDrawables(self):
			return self.manager.prevState().getDrawables() + self.drawables
		def update(self, keys):
			for k in keys:
				if k == K_SPACE:
					self.manager.pop()
				elif k == K_q:
					self.manager.swap(S_PromptQuit())

class S_Instructions(State):
		def __init__(self):
			State.__init__(self)
		def managedInit(self):
			inst = self.manager.game.text("INSTRUCTIONS", True, WHITE)
			arrow = self.manager.game.text("Arrow keys to move", True, WHITE)
			space = self.manager.game.text("Spacebar to pause", True, WHITE)
			quit = self.manager.game.text("'Q' to quit", True, WHITE)
			cont = self.manager.game.text("Press any key to return to menu...", True, YELLOW)
			height = 10
			self.drawables.append([inst, [10,height]])
			height += inst.get_height()
			self.drawables.append([arrow, [10,height]])
			height += arrow.get_height()
			self.drawables.append([space, [10,height]])
			height += space.get_height()
			self.drawables.append([quit, [10,height]])
			height += quit.get_height()
			self.drawables.append([cont, [10,height]])
			height += cont.get_height()
		def update(self, keys):
			if len(keys)>0:
				self.end()


class S_Play(State):
	def managedInit(self):
		self.scene = BlockScene(SCREEN_SIZE, BLOCK_SIZE)
		self.score = 0
		self.snake = Snake(self.scene)
		self.apple = Apple(self.scene)
		self.font = pygame.font.SysFont(GAME_FONT, 24)
		self.upText = self.font.render("UP", True, WHITE)
		self.hiText = self.font.render("HI", True, WHITE)
		self.drawables.append([self.upText, [10,10]])
		self.drawables.append([self.hiText, [SCREEN_SIZE[0]-self.hiText.get_width()-10,10]])
	
	def gameOver(self, score):
		self.manager.game.hiscore = max(self.score, self.manager.game.hiscore)
		self.score = 0
		self.manager.swap(S_GameOver())
	def getDrawables(self):
		upScore = self.font.render(str(self.score), True, WHITE)
		hiScore = self.font.render(str(self.manager.game.hiscore), True, WHITE)
		scores = [[upScore, (self.upText.get_width()+20, 10)], [hiScore, (SCREEN_SIZE[0] - self.hiText.get_width() - hiScore.get_width() - 20, 10)]]
		return self.drawables + scores + self.snake.getDrawables() + self.apple.getDrawables()
	def update(self, keys):		
		colors = {K_1:RED, K_2:ORANGE, K_3:YELLOW, K_4:GREEN, K_5:BLUE, K_6:INDIGO, K_7:VIOLET, K_8:WHITE, K_9:GRAY, K_0:BLACK}
		directions = {K_UP: UP, K_DOWN:DOWN, K_LEFT:LEFT, K_RIGHT:RIGHT}
		for k in keys:
			if k == K_q:
				self.manager.push(S_PromptQuit())
			elif k == K_SPACE:
				self.manager.push(S_Pause())
			elif k in directions.keys():
				self.snake.setDirection(directions[k])
			elif k in colors.keys():
				self.snake.color = colors[k]
		
		snakeVal = self.snake.update()
		if snakeVal == 1:
			self.score += 1
			self.apple.newApple()
		elif snakeVal == 2:
			self.gameOver(self.score)
		

class Window:
	def __init__(self):
		self.screensize = SCREEN_SIZE
		self.screen = pygame.display.set_mode(SCREEN_SIZE)
		self.caption = pygame.display.set_caption(WINDOW_CAPTION)
	
	def update(self, drawables):
		self.screen.fill(BLACK)
		for d in drawables:
			self.screen.blit(d[0], d[1])
		pygame.display.flip()

		
class Game():
	def __init__(self):
		pygame.init()
		self.font = pygame.font.SysFont(GAME_FONT, 24)
		self.window = Window()
		self.stateManager = StateManager(self)
		self.stateManager.push(S_Title())
		self.clock = pygame.time.Clock()
		self.running = True
		self.hiscore = 0
	def run(self):
		while self.running:
			self.clock.tick(GAME_SPEED)
			for event in pygame.event.get():
				if event.type==QUIT:
					self.running = False
				if event.type == pygame.KEYDOWN:
					key = event.key
					self.stateManager.input(key)
			self.stateManager.update()
			self.window.update(self.stateManager.getDrawables())
		self.shutDown()
	def end(self):
		self.running = False
	def shutDown(self):
		exit()	
	def text(self, message, antialias, color):
		return self.font.render(message, antialias, color)


##########
# Main
##########
if __name__ == "__main__":
	game = Game()
	game.run()
	
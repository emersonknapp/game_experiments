from pygame import Surface
from pygame import font

class StateManager:
	def __init__(self, game):
		self.states = []
		self.inputs = []
		self.typedInputs = []
		self.game = game
	def input(self, eventType, value):
		self.inputs.append((eventType, value))
	##Push a new state on top of the stack
	# ex: menus, pause screen 
	def push(self, state):
		state.setManager(self)
		self.states.append(state)
	##Go back one state 
	def pop(self):
		self.states.pop()
		if self.states == []:
			self.end()
	def isEmpty(self):
		return self.states==[]
	##Replace current state with new one		
	def swap(self, newState):
		if self.states == []:
			self.push(newState)
		else:
			self.states.pop()
			self.push(newState)
	def end(self):
		while self.states != []:
			self.states[-1].end()
		self.game.end()
	def getDrawables(self):
		if self.isEmpty(): return []
		return self.currentState().getDrawables()
	def getSurface(self):
		if self.isEmpty(): return []
		return self.currentState().getSurface()
	def update(self, millis=0):
		self.currentState().update(self.inputs, millis)
		self.inputs = []
		
	def currentState(self):
		return self.states[-1]
	def prevState(self):
		if len(self.states) >= 2:
			return self.states[-2]
		else:
			return State()


class State:
	def __init__(self):
		self.scene = None
		self.manager = None
		self.drawables = []
		self.entities = {}
		self.surface = Surface((1,1))
	def managedInit(self):
		pass
	def getDrawables(self):
		return self.drawables
	def getSurface(self):
		return self.surface
	def setManager(self, man):
		self.manager = man
		self.managedInit()
	def update(self, keys, millis=0):
		pass
	def end(self):
		self.manager.pop()

'''		
class Menu(State):
	def __init__(self, mappings):
		State.__init__(self)
		self.mappings = mappings
	def 
'''
		
		
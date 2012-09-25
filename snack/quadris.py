from game import *

WINDOW_CAPTION = 'Quadris'
GAME_FONT = 'trebuchet.ttf'
SCREEN_SIZE = 240, 480
PLAY_SCREEN_SIZE = 240,480
BLOCK_SIZE = 24
GAME_SIZE = 10, 20
FRAMERATE = 40
DEFAULT_BLOCK_SPEED = 4
DEFAULT_SEGS = 5
DEBUG = False

TETR_SQUARE, TETR_LINE, TETR_T, TETR_S, TETR_Z, TETR_L, TETR_J = range(7)
TETR_BLOCKS = [
    #Square
    [
      [[0,0],[1,0],[0,-1],[1,-1]]
    ],
    #Line
    [
      [[0,0],[-1,0],[1,0],[2,0]],
      [[0,0],[0,1],[0,-1],[0,-2]]
    ],
    #T 
    [
      [[0,0],[-1,0],[1,0],[0,-1]],
      [[0,0],[0,1],[-1,0],[0,-1]],
      [[0,0],[-1,0],[1,0],[0,1]],
      [[0,0],[0,1],[1,0],[0,-1]]
    ], 
    #S
    [
      [[0,0],[0,-1],[-1,-1],[1,0]],
      [[0,1],[0,0],[1,0],[1,-1]]
    ],
    #Z
    [
      [[0,0],[-1,0],[0,-1],[1,-1]],
      [[0,1],[0,0],[-1,0],[-1,-1]]
    ],
    #L 
    [
      [[0,0],[1,0],[-1,0],[-1,-1]],
      [[0,0],[-1,1],[0,1],[0,-1]],
      [[0,0],[-1,0],[1,0],[1,1]],
      [[0,0],[0,1],[0,-1],[1,-1]]
    ],
    #J                            
    [
      [[0,0],[1,0],[-1,0],[1,-1]],
      [[0,0],[-1,-1],[0,1],[0,-1]],
      [[0,0],[-1,0],[1,0],[-1,1]],
      [[0,0],[0,1],[0,-1],[1,1]]
    ] 
  ]

class Tetromino():
  def __init__(self, position, scene, blockType):
    self.blockType = blockType
    #TODO: settings for random
    self.centerIndex = 0
    self.rotations = 0
    self.scene = scene
    self.center = list(position)
    self.allData = [[array(x) for x in q] for q in TETR_BLOCKS[self.blockType]]
    self.blocks = [x+position for x in self.allData[self.rotations]]
    self.elapsed = 0
    self.speed = DEFAULT_BLOCK_SPEED
    self.timeToUpdate = 1000/self.speed
    #if DEBUG: print "Init Tet: ", self.timeToUpdate
  def rotate(self):
    if self.blockType==TETR_SQUARE:
      return
    self.scene.remove(self)
    oldPos = list(self.blocks)
    self.rotations = (self.rotations+1) % len(self.allData)
    self.blocks = [x+self.center for x in self.allData[self.rotations]]
    if not self.scene.add(self):
      if DEBUG: 
        print "NO GOOD ROT"
        print oldPos
        print self.blocks
      self.rotations = (self.rotations-1)%len(self.allData)
      self.blocks = oldPos
      self.scene.add(self)
  def updatePosition(self,pos):
    self.scene.remove(self)
    self.blocks = [x+pos for x in self.blocks]
    self.center += pos
    if not self.scene.add(self):
      self.blocks = [x-pos for x in self.blocks]
      self.scene.add(self)
      self.center -= pos
      return False
    return True
  def turbo(self, turboGo):
    if turboGo:
      self.timeToUpdate = 300/self.speed
    else:
      self.timeToUpdate = 1000/self.speed
  def update(self, millis):
    #if DEBUG: print "update tet: elapsed", self.elapsed, " +", millis
    self.elapsed += millis
    if (self.elapsed > self.timeToUpdate):
      self.elapsed -= self.timeToUpdate
      return self.moveDown()
    else:
      return True
  def moveRight(self):
    return self.updatePosition(array([1,0]))
  def moveLeft(self):
    return self.updatePosition(array([-1,0]))
  def moveDown(self):
    return self.updatePosition(array([0,-1]))
      

class S_Title(State):
    def managedInit(self):
      self.surface = Surface(PLAY_SCREEN_SIZE)
      font = pygame.font.Font(GAME_FONT, 24)
      textQuadris = font.render("QUADRIS", True, WHITE)
      textPlay = font.render("[P]lay", True, WHITE)
      textQuit = font.render("[Q]uit", True, WHITE)
      self.surface.fill(BLACK)
      self.surface.blit(textQuadris, (0,0))
      self.surface.blit(textPlay, (0, 50))
      self.surface.blit(textQuit, (0, 100))
    def update(self, keys, millis):
      for e,k in keys:
        if k == K_q:
          self.manager.end()
        if k == K_p:
          self.manager.push(S_Play())
    def getSurface(self):
      return self.surface

class S_GameOver(State):
  def managedInit(self):
    self.surface = Surface(PLAY_SCREEN_SIZE)
    font = pygame.font.Font(GAME_FONT, 24)
    textGameover = font.render("GAME OVER", True, WHITE)
    textAgain = font.render("[P]lay again", True, WHITE)
    textBack = font.render("[B]ack to menu", True, WHITE)
    self.surface.fill(BLACK)
    self.surface.blit(textGameover, (0,0))
    self.surface.blit(textAgain, (0,50))
    self.surface.blit(textBack, (0,100))
  def update(self, keys, millis):
    for e,k in keys:
      if k == K_p:
        self.manager.swap(S_Play())
      elif k == K_b:
        self.manager.pop()  
  def getSurface(self):
    return self.surface   

def chooseNextBlock():
  return random.randint(7)
  #return 0
  
class S_Play(State):
  def managedInit(self):
    self.name = 'S_Play'
    self.scene = QuadrisScene(PLAY_SCREEN_SIZE, GAME_SIZE)
    self.score = 0
    x = np.ceil(GAME_SIZE[0]/2.0)-1
    self.tetStartPos = array([x, GAME_SIZE[1]-1])
    self.activeTetromino = Tetromino(self.tetStartPos, self.scene, chooseNextBlock())
    self.scene.add(self.activeTetromino)
    self.font = pygame.font.SysFont(GAME_FONT, 24)
    self.nameText = self.font.render(self.name, True, WHITE)
    self.textLinesCleared = self.font.render("Lines Cleared: ", True, WHITE)
    self.linesCleared = 0
  def gameOver(self):
    #TODO: r/w hiscore from file
    self.manager.game.hiscore = max(self.score, self.manager.game.hiscore)
    self.score = 0
    self.manager.swap(S_GameOver())
  def getSurface(self):
    surf = Surface(PLAY_SCREEN_SIZE)
    surf.blit(self.scene.getSurface(), (0,0))
    surf.blit(self.font.render("Lines Cleared: "+str(self.linesCleared), True, WHITE), (PLAY_SCREEN_SIZE[0]-140,0))
    return surf
  def update(self, keys, millis):
    for event,k in keys:
      if event == pygame.KEYDOWN:
        if k==K_q:
          #TODO: actual quit
          self.manager.end()
        elif k==K_UP:
          self.activeTetromino.rotate()
        elif k==K_LEFT:
          #move left
          self.activeTetromino.moveLeft()
        elif k==K_RIGHT:
          #move right
          self.activeTetromino.moveRight()
        elif k==K_DOWN:
          self.activeTetromino.turbo(True)
      if event == pygame.KEYUP:
        if k==pygame.K_DOWN:
          self.activeTetromino.turbo(False)
    if not self.activeTetromino.update(millis):
      self.linesCleared  += self.scene.update()
      self.activeTetromino = Tetromino(self.tetStartPos, self.scene, chooseNextBlock())
      if not self.scene.add(self.activeTetromino):
        self.gameOver()

class QuadrisScene():
  def __init__(self, sizePx, sizeSq):
    self.sizePx = sizePx
    self.sizeSq = sizeSq
    self.blockWidth = sizePx[0] / sizeSq[0]
    self.blockHeight = sizePx[1] / sizeSq[1]
    self.data = np.zeros(sizeSq, dtype=int)
    self.surface = Surface(self.sizePx)
  def remove(self, tet):
    for b in tet.blocks:
      self.data[b[0],b[1]] = 0
  def add(self, tet):
    if DEBUG: print "adding tet at ", tet.blocks
    add = True
    for b in tet.blocks:
      add = add and b[0] >= 0 and b[0] < self.sizeSq[0] #x w/in scene
      add = add and b[1] >= 0 and b[1] < self.sizeSq[1] #y w/in scene
      add = add and (self.data[b[0],b[1]] == 0)         #space not already occupied
    if add:
      for b in tet.blocks:
        self.data[b[0],b[1]] = 1
    return add
  def getSurface(self):
    self.surface.fill(BLACK)
    for x in range(self.sizeSq[0]):
      for y in range(self.sizeSq[1]):
        if self.data[x,y] != 0:
          pos = (x*self.blockWidth, self.sizePx[1]-self.blockHeight-y*self.blockHeight)
          r = Rect(pos, (self.blockWidth, self.blockHeight))
          pygame.draw.rect(self.surface, WHITE, r)
    return self.surface
  def update(self):
    onesArray = np.ones(self.sizeSq[1])
    rowsToDelete = [i for i in range(self.sizeSq[1]) if np.all(self.data[:,i])]
    if len(rowsToDelete):
      self.data = np.hstack((np.delete(self.data, rowsToDelete, 1), np.zeros((self.sizeSq[0], len(rowsToDelete)))))
    return len(rowsToDelete)
      
        
    
class QuadrisGame(Game):
  def __init__(self):
    Game.__init__(self, S_Title(), FRAMERATE)
    self.hiscore = 0
    self.initWindow(SCREEN_SIZE, WINDOW_CAPTION)

if __name__ == "__main__":
  game = QuadrisGame()
  game.run()

import pygame
from pygame import sprite
from pygame.locals import *
 
# Define some colors
_black   = (   0,   0,   0)
_white    = ( 255, 255, 255)
_green    = (   0, 255,   0)
_red      = ( 255,   0,   0)
 
SCREEN_SIZE = [640,480] 
SCREEN_CAPTION = "Pygame Screen"

FRAMERATE = 50

class Entity(sprite.Sprite):
    def __init__(self):
      pass
 
def main():
  pygame.init()

  screen = pygame.display.set_mode(SCREEN_SIZE)
  pygame.display.set_caption(SCREEN_CAPTION)
 
  running = True
  clock = pygame.time.Clock()

  while running:
    dt = clock.tick(FRAMERATE)
    
    #Process Events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
          running = False
        elif event.type == pygame.KEYDOWN and event.key == K_q:
          running = False
        else:
          pass
  
    #Game Logic
 
    #Graphics
    screen.fill(_black)
    pygame.display.flip()
 
  pygame.quit()
  
if __name__=="__main__":
  main()
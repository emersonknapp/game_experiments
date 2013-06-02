#include <stdbool.h> // for true and false
 
//SDL_GL_Functions: Copied from gpwiki.org.
#include "SDL.h" // main SDL header
 
//OpenGL stuff :)
#include <GL/gl.h>
#include <GL/glu.h>
 
#define screen_width 640
#define screen_height 480
 
//prototypes:
int InitVideo();
int setup_opengl( int width, int height );
 
//might want to have some parms, options for user
int InitVideo() {
  // Load SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    return false;
  }
  atexit(SDL_Quit); // Clean it up nicely :)
 
  //To use OpenGL, you need to get some information first,
  const SDL_VideoInfo *info = SDL_GetVideoInfo();
  if(!info) {
    /* This should never happen, if it does PANIC! */
    fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
    return false;
  }
  int bpp = info->vfmt->BitsPerPixel;
 
  // set bits for red: (5 = 5bits for red channel)
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  // set bits for green:
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  // set bits for blue:
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  // colour depth:
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  // You want it double buffered?
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
 
  //screen is no longer used, as openGL does all the drawing now!
  if (SDL_SetVideoMode(screen_width, screen_height, bpp, SDL_OPENGL | SDL_SWSURFACE) == 0) {
    fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
    return false;
  }
 
  //Made everything, Now we need to change opengl settings..
  return setup_opengl(screen_width, screen_height);
}
 
int setup_opengl(int width, int height) {
  //Set up your openGL stuff in here :)
  return true; //If all is happy :)
}
 
// -------------------- The Game -------------------
 
int main(int argc, char **argv) {
  if (InitVideo() == false) return 1;
  SDL_Delay(1000);
  return 0;
}
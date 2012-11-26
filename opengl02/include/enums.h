#pragma once

enum eStateUpdate {
  ST_OK, 
  ST_POP, 
  ST_PUSH, 
  ST_SWAP
};

enum eRendType {
  REND_NONE, 
  REND_TEXT, 
  REND_QUAD, 
  REND_BMP
}; //TODO: expand

enum eEntityUpdate {
  ENT_OK,
  ENT_DEAD,
  ENT_SPAWN
};
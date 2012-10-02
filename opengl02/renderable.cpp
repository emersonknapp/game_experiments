#include "renderable.h"

R_Text::R_Text(float x, float y, std::string text, int size) {
  m_text = text;
  m_offset << x,y;
  m_size = size;
}
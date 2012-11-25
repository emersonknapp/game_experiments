#include "attributes.h"

using namespace Eigen;

Transform2f::Transform2f() {
  m_translation = Vector2f(0,0);
  m_rotation = Vector2f(0,0);
  m_scale = Vector2f(0,0);
}

void Transform2f::translate(Vector2f tr) {
  m_translation = m_translation + tr;
}

void Transform2f::rotate(Vector2f ro) {
  m_rotation = m_rotation + ro;
}

void Transform2f::scale(Vector2f sc) {
  m_scale = Vector2f(m_scale(0)*sc(0), m_scale(1)*sc(1));
}

Vector2f Transform2f::getTranslation() {
  return m_translation;
}
Vector2f Transform2f::getRotation() {
  return m_rotation;
}
Vector2f Transform2f::getScale() {
  return m_scale;
}
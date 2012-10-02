#include "resource.h"

bool DependentResource::addDependency(IndependentResource* dr) {
  if (dr->register(this)) {
    m_dependencies.insert(dr);
    return true;
  }
  else return false;
  
}
void DependentResource::removeDependency(IndependentResource* dr) {
  size_t deleteSuccess = m_dependencies.erase(dr);
  if (deleteSuccess != 1)
    Error("Removed non-existent dependency.");
}

bool IndependentResource::register(DependentResource* ir) {
  m_dependents.insert(ir);
}

bool IndependentResource::unregister(DependentResource* ir) {
  m_dependents.erase(ir);
}

void IndependentResource::notifyDependentsOnDelete() {
  std::set<DependentResource*>::iterator it;
  for (it = m_dependents.begin(); it != m_dependents.end(); it++) {
    (*it)->removeDependency(this);
  }
  
}

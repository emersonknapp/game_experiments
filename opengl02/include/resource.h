#pragma once

#include <set>

class DependentResource;
class IndependentResource;

class DependentResource {
public:
  bool addDependency(IndependentResource* dr);
  void removeDependency(IndependendResource* dr);
private:
  std::set<IndependentResource*> m_dependencies;
};


class IndependentResource {
public:
  bool register(DependentResource* dr);
  void unregister(DependentResource* dr);
  void notifyDependentsOnDelete();
private:
  std::set<DependentResource*> m_dependents;
};
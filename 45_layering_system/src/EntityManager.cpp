#include "../include/EntityManager.hpp"
#include <iostream>

bool EntityManager::CreateEntity(std::string name, SDL_Renderer *renderer, Layer layer) {
  std::shared_ptr<GameEntity> newEntity =
      std::make_shared<GameEntity>(name, renderer);
  
  newEntity->setLayer(layer);
  m_entities.insert(std::make_pair(name, newEntity));
  // Increment our count
  m_entityCount++;
  // Return if the operation was successful
  return (m_entities[name] != nullptr);
}

// Retrieve the Entity from the key
std::shared_ptr<GameEntity> EntityManager::GetEntityRef(std::string name) {
  return (m_entities[name]);
}

// Remove the entity
void EntityManager::RemoveEntity(std::string name) {
  // TODO: Some error handling, check if entity
  //       was actually found.
  auto it = m_entities.find(name);
  m_entities.erase(it);
  m_entityCount--;
}

// Update all the entities
void EntityManager::UpdateAll() {
  size_t index = 0;
  for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
    if (m_entities[it->first] != nullptr) {
      m_entities[it->first]->update();
    } else {
      std::cout << "Unknown entity update: " << index << std::endl;
    }
    index++;
  }
}

// Render all of the entities
void EntityManager::renderLayer(Layer layer) {
  // render each layer
  size_t index = 0;
  for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
    if (m_entities[it->first] != nullptr &&  layer == m_entities[it->first]->getLayer()) {
      m_entities[it->first]->render();
    } else {
      std::cout << "Unknown entity render: " << index << std::endl;
    }
    index++;
  }
}

void EntityManager::RenderAllLayers() {
  renderLayer(Layer::background);
  renderLayer(Layer::middleground);
  renderLayer(Layer::foreground);
}
// Delete all of the entities
void EntityManager::DeleteAllEntities() {
  m_entities.erase(m_entities.begin(), m_entities.end());
  m_entityCount = 0;
}

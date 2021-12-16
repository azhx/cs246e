#include "mycolliders2.h"

#include "bullet.h"
#include "enemies.h"
#include "player2.h"
#include <algorithm>

std::vector<std::pair<int, int>> drawline(int x1, int y1, int x2, int y2) {
  std::vector<std::pair<int, int>> hitbox {};
   int m_new = 2 * (y2 - y1);
   int slope_error_new = m_new - (x2 - x1);
   for (int x = x1, y = y1; x <= x2; x++)
   {
      std::pair<int, int>pixel {x, y};
      hitbox.push_back(pixel);
  
      // Add slope to increment angle formed
      slope_error_new += m_new;
  
      // Slope error reached limit, time to
      // increment y and update slope error.
      if (slope_error_new >= 0)
      {
         y++;
         slope_error_new  -= 2 * (x2 - x1);
      }
   }
  return hitbox;
}
bool BulletCollider::checkCollision(EnemyCollider& other) const {
  for (size_t i = 0; i < other.enemy.prefab->bitmap.size(); ++i) {
    for (size_t j = 0; j < bullet.prefab->bitmap.size(); ++j) {
      int selfx =
          std::get<0>(other.enemy.prefab->bitmap[i]) + other.enemy.pos.first;
      int selfy =
          std::get<1>(other.enemy.prefab->bitmap[i]) + other.enemy.pos.second;
      int otherx = std::get<0>(bullet.prefab->bitmap[j]) + bullet.pos.first;
      int othery = std::get<1>(bullet.prefab->bitmap[j]) + bullet.pos.second;
      if (selfx == otherx && selfy == othery) {
        return true;
      }
    }
  }
  return false;
}

bool EnemyCollider::checkCollision(BulletCollider& other) const {
  for (size_t i = 0; i < enemy.prefab->bitmap.size(); ++i) {
    for (size_t j = 0; j < other.bullet.prefab->bitmap.size(); ++j) {
      int selfx = std::get<0>(enemy.prefab->bitmap[i]) + enemy.pos.first;
      int selfy = std::get<1>(enemy.prefab->bitmap[i]) + enemy.pos.second;
      int otherx =
          std::get<0>(other.bullet.prefab->bitmap[j]) + other.bullet.pos.first;
      int othery =
          std::get<1>(other.bullet.prefab->bitmap[j]) + other.bullet.pos.second;
      if (selfx == otherx && selfy == othery) {
        return true;
      }
    }
  }
  return false;
}

bool PlayerCollider::checkCollision(EnemyCollider& other) const {
  float x = player.pos.first;
  float y = player.pos.second;
  float prevx = player.prevpos.first;
  float prevy = player.prevpos.second;
  std::vector<std::pair<int, int>> hitbox = drawline(std::min(prevx, x), std::min(prevy, y), std::max(x, prevx), std::max(y, prevy));
  for (size_t i = 0; i < hitbox.size(); ++i) {
    for (size_t j = 0; j < other.enemy.prefab->bitmap.size(); ++j) {
      int otherx =
          std::get<0>(other.enemy.prefab->bitmap[j]) + other.enemy.pos.first;
      int othery =
          std::get<1>(other.enemy.prefab->bitmap[j]) + other.enemy.pos.second;
      if (hitbox[i].first == otherx && hitbox[i].second == othery) {
        player.pos.first = hitbox[i].first;
        player.pos.second = hitbox[i].second;
        return true;
      }
    }
  }
  return false;
};

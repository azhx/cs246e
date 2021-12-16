
#include "mycolliders.h"
#include "border.h"
#include <utility>
#include "../age/collider.h"
#include "ball.h"
#include "coin.h"
#include "player.h"


bool BallCollider::checkCollision(BorderCollider& border) const {
    int trueminx = border.border.minx + ball.radius;
    int trueminy = border.border.miny + ball.radius;
    int truemaxx = border.border.maxx - ball.radius;
    int truemaxy = border.border.maxy - ball.radius;
    if (trueminx > ball.pos.first || truemaxx < ball.pos.first
        || trueminy > ball.pos.second || truemaxy < ball.pos.second) {
        return true;
    }
    return false;
}

bool BorderCollider::checkCollision(BallCollider& ball) const {
    int trueminx = border.minx + ball.ball.radius;
    int trueminy = border.miny + ball.ball.radius;
    int truemaxx = border.maxx - ball.ball.radius;
    int truemaxy = border.maxy - ball.ball.radius;
    if (trueminx > ball.ball.pos.first || truemaxx < ball.ball.pos.first
        || trueminy > ball.ball.pos.second || truemaxy < ball.ball.pos.second) {
        return true;
    }
    return false;
}

bool CoinCollider::checkCollision(PlayerCollider& player) const{
    if (player.player.pos.first == coin.pos.first && player.player.pos.second == coin.pos.second) return true;
    return false;
}

bool PlayerCollider::checkCollision(CoinCollider& coin) const{
    if (player.pos.first == coin.coin.pos.first && player.pos.second == coin.coin.pos.second) return true;
    return false;
}

bool PlayerCollider::checkCollision(BallCollider& otherCollider) const {
    int radminx = otherCollider.ball.pos.first - otherCollider.ball.radius;
    int radminy = otherCollider.ball.pos.second - otherCollider.ball.radius;
    int radmaxx = otherCollider.ball.pos.first + otherCollider.ball.radius-1;
    int radmaxy = otherCollider.ball.pos.second + otherCollider.ball.radius-1;
    if ((radminx <= player.pos.first && radmaxx >= player.pos.first) &&
        (radminy <= player.pos.second && radmaxy >= player.pos.second)) {
        return true;
    }
    return false;
}

BorderCollider::BorderCollider(Border& border): border{border}{}

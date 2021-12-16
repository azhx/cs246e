#ifndef COLLIDER_H
#define COLLIDER_H

#include <memory>
#include <utility>

template <typename...> class Collider {
    public:
        Collider() {}
        bool checkCollision();
        virtual ~Collider(){}
};

template <typename T, typename... Ts> class Collider<T, Ts...>: public Collider<Ts...> {
    public:
        using Collider<Ts...>::checkCollision;
        virtual bool checkCollision(T& otherCollider) const = 0;
};

#endif
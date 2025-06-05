#pragma once

#include "Math/Transform.h"

/**
 * @file Component.h
 * @brief Définition de la classe Component, base pour tous les composants d'un Actor.
 */

class Actor;

/**
 * @class Component
 * @brief Classe de base pour les composants attachés à un Actor.
 */
class Component
{
protected:
    bool mActive = true;
    Actor* mOwner;
    int mUpdateOrder;
    
public:
    /**
     * @brief Constructeur de la classe Component.
     * @param owner Pointeur vers l'Actor propriétaire.
     * @param updateOrder Ordre de mise à jour du composant.
     */
    Component(Actor* owner, int updateOrder = 0);
    Component() = delete;
    virtual ~Component();

    /**
     * @brief Méthode appelée au démarrage du composant.
     */
    virtual void OnStart();

    /**
     * @brief Met à jour le composant.
     */
    virtual void Update();

    /**
     * @brief Méthode appelée à la fin de vie du composant.
     */
    virtual void OnEnd();

    int GetUpdateOrder() const { return mUpdateOrder; }
    virtual void OnUpdateWorldTransform() {}
    Actor* GetOwner() const
    {
        return mOwner;
    }
};


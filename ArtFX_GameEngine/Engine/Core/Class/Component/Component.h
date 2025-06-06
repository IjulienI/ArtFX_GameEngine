#pragma once

#include "Math/Transform.h"

/**
 * @file Component.h
 * @brief Definition of the Component class, base for all components attached to an Actor.
 */

class Actor;

/**
 * @class Component
 * @brief Base class for components attached to an Actor.
 */
class Component
{
protected:
    /**
     * @brief Indicates whether the component is active.
     */
    bool mActive = true;

    /**
     * @brief Pointer to the owning Actor.
     */
    Actor* mOwner;

    /**
     * @brief Update order of the component.
     */
    int mUpdateOrder;
    
public:
    /**
     * @brief Constructor for the Component class.
     * @param owner Pointer to the owning Actor.
     * @param updateOrder Update order of the component.
     */
    Component(Actor* owner, int updateOrder = 0);
    Component() = delete;

    /**
     * @brief Virtual destructor.
     */
    virtual ~Component();

    /**
     * @brief Called when the component starts.
     */
    virtual void OnStart();

    /**
     * @brief Updates the component.
     */
    virtual void Update();

    /**
     * @brief Called at the end of the component's lifetime.
     */
    virtual void OnEnd();

    /**
     * @brief Gets the update order of the component.
     * @return Update order as an integer.
     */
    int GetUpdateOrder() const { return mUpdateOrder; }

    /**
     * @brief Called when the world transform is updated.
     */
    virtual void OnUpdateWorldTransform() {}

    /**
     * @brief Gets the owner Actor of this component.
     * @return Pointer to the owner Actor.
     */
    Actor* GetOwner() const
    {
        return mOwner;
    }
};

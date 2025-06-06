#pragma once

/**
 * @enum ActorState
 * @brief Represents the possible states of an actor.
 */
enum class ActorState
{
    Active,   /**< The actor is active and will be updated. */
    Paused,   /**< The actor is paused and will not be updated. */
    Dead      /**< The actor is dead and will be removed from the scene. */
};

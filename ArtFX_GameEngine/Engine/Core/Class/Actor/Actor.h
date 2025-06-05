#pragma once

#include <vector>
#include "ActorState.h"
#include "../Scene/Scene.h"
#include "../Component/Component.h"
#include "Math/Transform.h"

/**
 * @brief Classe de base représentant un acteur dans la scène.
 * 
 * Un acteur est un objet du jeu qui peut contenir des composants et être manipulé dans la scène.
 */
class Actor
{
protected:
    /**
     * @brief Pointeur vers la scène à laquelle appartient cet acteur.
     */
    Scene* mScene;

    /**
     * @brief État courant de l'acteur (actif, inactif, etc.).
     */
    ActorState mActorState;

    /**
     * @brief Transformations spatiales de l'acteur (position, rotation, échelle).
     */
    Transform mTransform;

    /**
     * @brief Nom de la classe de l'acteur.
     */
    std::string mClassName;

    /**
     * @brief Nom de l'acteur.
     */
    std::string mName;
    
private:
    /**
     * @brief Liste des composants attachés à cet acteur.
     */
    std::vector<Component*> mComponents;

public:
    /**
     * @brief Constructeur de l'acteur.
     */
    Actor();

    /**
     * @brief Destructeur virtuel.
     */
    virtual ~Actor() = default;

protected:
    /**
     * @brief Initialise l'acteur (appelé lors de la création).
     */
    virtual void Initialize();
    
public:
    /**
     * @brief Démarre l'acteur (appelé après l'initialisation).
     */
    virtual void Start();

    /**
     * @brief Met à jour l'acteur et ses composants.
     */
    virtual void Update();

    /**
     * @brief Met à jour la logique spécifique de l'acteur.
     */
    virtual void UpdateActor();

    /**
     * @brief Détruit l'acteur et le retire de la scène.
     */
    virtual void Destroy();
    
public:
    /**
     * @brief Attache l'acteur à une scène.
     * @param scene Référence vers la scène.
     */
    void AttachScene(Scene& scene);

    /**
     * @brief Ajoute un composant à l'acteur.
     * @param component Pointeur vers le composant à ajouter.
     */
    void AddComponent(Component* component);

    /**
     * @brief Retire un composant de l'acteur.
     * @param component Pointeur vers le composant à retirer.
     */
    void RemoveComponent(Component* component);

    /**
     * @brief Définit l'état actif de l'acteur.
     * @param state Nouvel état de l'acteur.
     */
    void SetActive(ActorState state);

    /**
     * @brief Met à jour la transformation de tous les composants.
     */
    void UpdateComponentsTransform();

public:
    /**
     * @brief Retourne le nom de la classe de l'acteur.
     * @return Nom de la classe.
     */
    std::string GetClass()
    {
        return mClassName;
    }

    /**
     * @brief Retourne le nom de l'acteur.
     * @return Nom de l'acteur.
     */
    std::string GetName()
    {
        return mName;
    }

    /**
     * @brief Définit le nom de l'acteur.
     * @param name Nouveau nom.
     */
    void SetName(std::string name);
    
    /**
     * @brief Retourne la position de l'acteur.
     * @return Position (Vec3).
     */
    Vec3 GetLocation();

    /**
     * @brief Retourne la rotation de l'acteur.
     * @return Rotation (Quaternion).
     */
    Quaternion GetRotation();

    /**
     * @brief Retourne l'échelle de l'acteur.
     * @return Échelle (Vec3).
     */
    Vec3 GetScale();

    /**
     * @brief Retourne la transformation de l'acteur.
     * @return Référence vers le Transform.
     */
    Transform& GetTransform();

    /**
     * @brief Retourne la matrice de transformation globale.
     * @return Matrice 4x4 (Matrix4Row).
     */
    Matrix4Row GetWorldTransform();

    /**
     * @brief Retourne la scène à laquelle appartient l'acteur.
     * @return Pointeur vers la scène.
     */
    Scene* GetScene();

    /**
     * @brief Retourne la liste des composants attachés à l'acteur.
     * @return Vecteur de pointeurs de composants.
     */
    std::vector<Component*> GetComponents();

    /**
     * @brief Retourne le premier composant du type spécifié attaché à l'acteur.
     * @tparam T Type du composant recherché.
     * @return Pointeur vers le composant ou nullptr s'il n'existe pas.
     */
    template<typename T>T* GetComponent()
    {
        for(auto component : mComponents)
        {
            T* result = dynamic_cast<T*>(component);
            if(result)
            {
                return result;
            }
        }
        return nullptr;
    }

    /**
     * @brief Définit la position de l'acteur.
     * @param loc Nouvelle position.
     */
    void SetLocation(Vec3 loc);

    /**
     * @brief Ajoute un déplacement à la position de l'acteur.
     * @param loc Déplacement à ajouter.
     */
    void AddLocation(Vec3 loc);

    /**
     * @brief Définit l'échelle de l'acteur.
     * @param scale Nouvelle échelle.
     */
    void SetScale(Vec3 scale);

    /**
     * @brief Définit la rotation de l'acteur.
     * @param rotation Nouvelle rotation.
     */
    void SetRotation(Quaternion rotation);

    /**
     * @brief Applique une rotation à l'acteur.
     * @param rotation Rotation à appliquer (en degrés).
     */
    void Rotate(Vec3 rotation);

    /**
     * @brief Applique une rotation autour de l'axe X.
     * @param angle Angle en degrés.
     */
    void RotateX(float angle);

    /**
     * @brief Applique une rotation autour de l'axe Y.
     * @param angle Angle en degrés.
     */
    void RotateY(float angle);

    /**
     * @brief Applique une rotation autour de l'axe Z.
     * @param angle Angle en degrés.
     */
    void RotateZ(float angle);
};


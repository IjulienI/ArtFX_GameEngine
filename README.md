# Custom C++ Game Engine

## Overview
This project is a fully custom-built C++ game engine designed with an **Actor-Component** architecture.  
It focuses on **3D rendering** and **physics simulation** from scratch.

The engine integrates:
- **SDL2** for window management and input
- **OpenGL** with **GLEW** for graphics rendering
- **TinyObjLoader** for mesh importing
- **Custom Physics Engine** supporting convex collisions and dynamic simulation

---

## Features
- Full 3D SAT (Separating Axis Theorem) collision detection
- Box, Sphere, and Polyhedron (Mesh) colliders
- Contact manifold generation (multiple contacts per collision)
- Polygonal clipping (Reference/Incident face system)
- Mass, friction, and restitution handling
- Moment of inertia and angular damping
- Dynamic Actor-Component system
- Input system (Keyboard & Mouse)
- Scene graph and basic Actor lifecycle management
- Rendering pipeline (Need to work more on)

---

## Technologies
- **C++17**
- **OpenGL 4.6 Core Profile**
- **GLEW**
- **SDL2**
- **TinyObjLoader**([tinyobjloader GitHub](https://github.com/tinyobjloader/tinyobjloader))

---

## TODO

### Core Engine
- [ ] Build a robust **Scene serialization system** (save/load scenes)
- [ ] Implement a **Component-based Transform hierarchy** (Parent-Child)
- [ ] Create a **simple Editor GUI** (ImGui integration)

### Physics Engine
- [ ] Add **Continuous Collision Detection (CCD)** for fast-moving objects
- [ ] Support **soft bodies** or **deformable colliders**
- [ ] Implement **physics layers/masks** (for optimized collision checking)

### Rendering Engine
- [ ] Add **PBR (Physically-Based Rendering)** pipeline
- [ ] Support for **Shadow Mapping** (basic directional light shadows)
- [ ] Implement **Post-processing effects** (Bloom, Motion Blur)
- [ ] Add **Skinned Meshes and Skeletal Animation** support

### Scripting / Gameplay
- [ ] Integrate a **scripting language** (Lua, Python) for gameplay logic
- [ ] Support **hot-reloading scripts** without restarting the engine

### Optimization
- [ ] Add **Broadphase acceleration structures** (BVH, Octree, Grid)
- [ ] Multithread the **physics simulation** using a job system
- [ ] Implement **frustum culling** for rendering optimization

### Misc
- [ ] Implement **Audio system** (SDL_mixer or FMod)
- [ ] Build a **Basic UI System** (buttons, sliders, etc.)

---

## License
This engine is developed for educational and experimental purposes.  

---

## Notes
This project was made to learn low-level game engine architecture, 3D graphics programming, real-time physics simulation, and input management — without using external engines like Unity or Unreal Engine.

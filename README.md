# Quantix
3D Game engine

## How to install

- Clone project and open Quantix.sln in Quantix folder.
- Download Asset.7z and Dependencies.7z floder from https://drive.google.com/drive/folders/1qxX_ZEjL2NQefHEe2WUsXFgqQtdffb2S?usp=sharing 
- Put content of Asset.7z in Quantix/QuantixEditor and content of Dependencies.7z in Quantix/QuantixEngine.
- Run QuantixEditor project.

## Knowing issues

- Project work only in x64.
- Sometimes horizontal line appears when you activate a post process effect.
- Global referential doesn't work.
- You can add a child to an object only if the node is closed.
- Can't resize deformable mesh.
- Physic continue to update when switching scene.
- When a child rotate it have some troubles with rotation.
- sometimes when focusing scene ImGUI crashes.
- Physic don't work with childs objects.

## Documentation

- [Norme](NORMES.md)

## API

This engine use the following API :
- OpenGL
- GLFW
- ImGUI
- Fmod
- PhysX
- Assimp
- RapidJSON
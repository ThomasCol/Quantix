# Quantix
3D Game engine

## How to install

- Clone project and open Quantix.sln in Quantix folder.
- Download Asset.7z and Dependencies.7z folder from https://drive.google.com/drive/folders/1qxX_ZEjL2NQefHEe2WUsXFgqQtdffb2S?usp=sharing 
- Put content of Asset.7z in Quantix/QuantixEditor and content of Dependencies.7z in Quantix/QuantixEngine.
- Run QuantixEditor project.

## How to use

- You can press F2 to load a scene.
- If you want to change the scene you can rename a scene from Quantix/QuantixEngine/Media folder and change the name to scene.quantix.

## Known issues

- Project works only in x64.
- Sometimes horizontal lines appear when you activate a post process effect.
- Global referential doesn't work.
- You can add a child to an object only if the node is closed.
- Can't resize deformable mesh.
- Physic continues to update when switching scene.
- When a child rotates it has some troubles with rotation.
- Sometimes when focusing scene ImGUI crashes.
- Physic doesn't work with child objects.

## Documentation

- [Norme](NORMES.md)

## API

This engine uses the following API :
- RTTR
- OpenGL
- GLFW
- ImGUI
- Fmod
- PhysX
- Assimp
- RapidJSON
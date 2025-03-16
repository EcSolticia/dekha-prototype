# dekha-prototype

"Dekha", a project named after the Bengali word for the act of seeing, is my first attempt at implementing a 3D renderer utilizing [weak perspective projection](https://en.wikipedia.org/wiki/3D_projection#Weak_perspective_projection).

As a prototype, Dekha is able to "see" polygon meshes represented by a collection of distinct vertices and draw edges connecting them as projected onto the a plane.
The output is represented in the terminal as ASCII graphics.

# Note
This project is a mere prototype for a more fully-fledged version of "Dekha", [EcSolticia/dekha](https://github.com/ecsolticia/dekha) (currently under-development).

# Example
## Input:
  - The camera faces the z-axis in the positive direction by default (represented by the rotation vector (0, 0, 0) within the program for convenience).
  - A triangle with the following vertices is initialized:
    ```
    (0, 0, 1),
    (10, 0, 2),
    (0, 10, 1)
    ```
## Output:
```
--------------------------------------------------
-------------------------#------------------------
-------------------------#------------------------
-------------------------#------------------------
-------------------------##-----------------------
-------------------------##-----------------------
-------------------------#-#----------------------
-------------------------#-#----------------------
-------------------------#--#---------------------
-------------------------#--#---------------------
-------------------------#---#--------------------
-------------------------######-------------------
--------------------------------------------------
```

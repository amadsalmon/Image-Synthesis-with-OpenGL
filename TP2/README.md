# TP2 - Matrices de transformation

**Amad Salmon | Synthèse d’Image - Polytech Grenoble, INFO4, 2020-2021**

## Modification des matrices de transformation & Changements de points de vue 

En effectuant un changement de point de vue infime à chaque passage dans la boucle de rendu, on peut créer une animation.

### Rotation

Il est possible d'effectuer une rotation de *view_matrix* de *angle* (en degrés) autour de *axis*. avec `rotate(mat4 *view_matrix*, float angle, vec3 axis)`. Par exemple :

```c++
// Tourne view_matrix d'un angle de 50 degrés autour de l'axe z
view_matrix = rotate(view_matrix, 50.0f ,vec3(0.0f,0.0f,1.0f));
```

### Changement d'échelle

Il est possible de changer l’échelle de *view_matrix* selon *x*, *y*, *z* en fonction des composantes de *value* grâce à `scale(mat4 view_matrix, vec3 value)`.  Par exemple :

```c++
// Change l'échelle de view_matrix dans toutes les dimensions
view_matrix = scale(view_matrix, vec3(0.5f,0.5f,0.5f));
```

### Translation

Il est possible d'effectuer une translation sur *view_matrix* de déplacement `displacement` grâce à `translate(mat4 view_matrix, vec3 displacement)`.  Par exemple :

```c++
// Déplace view_matrix vers la gauche (x négatif), le haut (y positif), et vers nous (z positif).
view_matrix = translate(view_matrix, vec3(-0.002f,0.001f,0.004f));
```



### Navigation dans la scène par touches du clavier

Afin de pouvoir naviguer dans la scène par touches du clavier, nous allons implémenter `view_control()`.
Nous décidons d'attribuer les changements selon les touches de la manière suivante : 

-   `GLFW_KEY_UP` *(touche "↑")* : translation vers le haut
-   `GLFW_KEY_DOWN`  *(touche "↓")* : translation vers le bas
-   `GLFW_KEY_RIGHT` *(touche "→")* : translation vers la droite
-   `GLFW_KEY_LEFT`  *(touche "←")* : translation vers la gauche
-   `GLFW_KEY_Z`  *(touche "Z" du clavier QWERTY, touche "W" du clavier AZERTY)* : zoom avant
-   `GLFW_KEY_X`  *(touche "X" )* : zoom arrière
-   `GLFW_KEY_I` *(touche "I")* : rotation directe autour de l'axe $x$
-   `GLFW_KEY_J` *(touche "J")* : rotation directe autour de l'axe $y$
-   `GLFW_KEY_K` *(touche "K")* : rotation directe autour de l'axe $z$

À chaque tour de boucle, avant le dessin, nous allons récupérer l'état des touches pressées grâce à un appel à `view_control()` et modififier la `view_matrix` relativement à ces touches.

Par exemple, si la boucle principale contient ...

```c++
view_control(myWindow, view_matrix, 0.05f);
```

... et que les touches "↑" et "K"sont enfoncées, alors les clauses conditionnelles suivantes seront actives dans `view_control()` :

```c++
// Translation vers le haut
if (glfwGetKey(aWindow, GLFW_KEY_UP) == GLFW_PRESS)
{
  view_matrix = translate(view_matrix, vec3(0.0f, dx, 0.0f));
}

// Rotation directe autour de l'axe z - (touche "K")
if (glfwGetKey(aWindow, GLFW_KEY_K) == GLFW_PRESS)
{
  view_matrix = rotate(view_matrix, dx, vec3(0.0f, 0.0f, 1.0f));
}
```

Ainsi, les changements sur `view_matrix` donneront les effets suivants **à chaque tour de boucle**:

-   la caméra effectuera une translation vers le haut (selon l'axe $y$) de $+dx=0.05$,
-   la caméra effectuera une rotation directe autour de l'axe $z$ de $+dx=0.05$.
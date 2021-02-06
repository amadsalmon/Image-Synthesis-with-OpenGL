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


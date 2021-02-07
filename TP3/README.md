# TP3 - VBO, Maillages et indexation

**Amad Salmon | Synthèse d’Image - Polytech Grenoble, INFO4, 2020-2021**



## Buffer de couleurs

Nous créons un tableau de type ```vector<vec3>``` stockant une couleur par sommet du cube,  que  nous  nommons  ```colors```.  Les couleurs sont associées à chacun des 6 sommets de chacune des 4 faces du cube, c'est à dire qu'il y a donc 36 couleurs dans `colors`.

Nous créeons ensuite un buffer à partir de ```colors```. Pour ceci, il suffit de faire exactement pareil que pour les positions des sommets ainsi que de modifier le vertex shader pour que celui-ci réceptionne ce nouvel attribut. Nous choississons de couleurs totalement aléatoires pour chaque sommet afin d'obtenir un résultat plus intéressant.

Le résultat est le cube suivant :

<img src="README.assets/cube_custom_colors.png" alt="Cube généré à partir d'un buffer de couleurs" style="zoom:25%;" />

Comme attendu, ayant choisi des couleurs aléatoires pour chaque sommet, les couleurs ne sont pas homogènes entre les différents triangles adjacents. 

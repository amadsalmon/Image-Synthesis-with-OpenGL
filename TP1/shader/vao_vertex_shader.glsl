#version 120

// Données d'entrée
attribute vec3 vertex_position;

// Fonction appelée pour chaque sommet
void main(){
    // Affectation de la position du sommet
    gl_Position = vec4(vertex_position, 1.);

    // Modifie la taille du point lorsque ce shader est actif.
    //gl_PointSize = 2.0f;

    // Si cette option est activée et que ce shader de sommet est actif, la position des sommets en x est divisée par 2. 
    //gl_Position.x /= 2;
}
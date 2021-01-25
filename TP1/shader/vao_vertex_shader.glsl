#version 120

// Données d'entrée
attribute vec3 vertex_position;

// Fonction appelée pour chaque sommet
void main(){
    // Affectation de la position du sommet
    gl_Position = vec4(vertex_position, 1.);
}
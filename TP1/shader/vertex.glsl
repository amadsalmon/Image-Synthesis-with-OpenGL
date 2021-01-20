#version 120 // Version d'OpenGL

// Fonction appelée pour chaque sommet
void main(){
    // Affectation de la couleur du sommet
    gl_Position = ftransform();
}
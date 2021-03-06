// Version d'OpenGL
#version 330

in vec4 my_color;

out vec4 frag_color;


/************************************************
              SHADING DE GOURAUD
************************************************/

// Fonction appellee pour chaque fragment
void main() {

  
  // Affectation de la couleur du fragment
  frag_color = my_color;
}

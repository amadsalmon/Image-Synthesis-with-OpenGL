// Version d'OpenGL
#version 330

/* -- Données en entrée -- */
in vec4 my_color;

/* -- Données en sortie -- */
out vec4 frag_color; // Couleur de fragment


/************************************************
              SHADING DE GOURAUD
************************************************/

// Fonction appellee pour chaque fragment
void main() {
  
  // Affectation de la couleur du fragment
  frag_color = my_color;

}

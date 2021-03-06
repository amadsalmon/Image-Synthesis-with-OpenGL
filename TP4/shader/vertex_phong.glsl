// Version d'OpenGL
#version 330
// Donnees de sortie
out vec4 my_color; // Lf, couleur résultante

// Parametres
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;


/************************************************
              SHADING DE PHONG
************************************************/

// Fonction appellee pour chaque sommet
void main() {

  // my_color = normalInWorldSpace + cameraPosInWorldSpace + posInObjectSpace ;
  my_color = vec4(L_f, 1.0);

}

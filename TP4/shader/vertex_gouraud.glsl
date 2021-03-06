// Version d'OpenGL
#version 330

// Donnees d'entree
in vec3 in_position;
in vec3 in_color;
in vec3 in_normal;

// Donnees de sortie
out vec4 my_color; // Lf, couleur résultante

// Parametres
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

/************************************************
              SHADING DE GOURAUD
************************************************/

// Fonction appellee pour chaque sommet
void main() {
  // Affectation de la position du sommet
  // gl_Position est defini par defaut dans GLSL
  gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_position, 1.0);

  /* ------- Vecteurs de position ------- */
  vec4 posInObjectSpace = vec4(in_position, 1.0);
  vec4 posInWorldSpace = ModelMatrix * posInObjectSpace;
  vec4 posOfLight = vec4(0.0, 1.0, 2.0, 0.5);

  vec4 normalInWorldSpace = normalize(transpose(inverse(ModelMatrix)) * vec4(in_normal, 0.));
  vec4 cameraPosInWorldSpace = inverse(ViewMatrix) * vec4(0., 0., 0., 1.);

  //my_color = vec4(L_f, 1.0);

}

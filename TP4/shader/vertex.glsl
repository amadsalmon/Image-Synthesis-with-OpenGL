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

// Fonction appellee pour chaque sommet
void main() {
  // Affectation de la position du sommet
  // gl_Position est defini par defaut dans GLSL
  gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_position, 1.0);

  vec3 L_f;                   // Couleur résultante calculée par le modèle de Phong
  float rho_a, rho_d, rho_s;  // Coefficients d'atténuation associés à chaque composante
  vec3 L_a, L_d, L_s;         // Couleurs de chaque composante
  vec3 n;                     // Vecteur normal de la surface au point p
  vec3 l;                     // Vecteur de norme  dans la direction de la lumière
  vec3 r;                     // Vecteur réflection de l par rapport à n : r=l-2<n,l>n
  vec3 e;                     // Vecteur de norme 1 dans la direction entre le point p de la surface et la position c de l'oeil
  float s;                    // Brillance (shininess)

  vec4 posInObjectSpace = vec4( in_position, 1.0);
  vec4 posInWorldSpace = ModelMatrix * posInObjectSpace;

  r = reflect(l, n);

  rho_s = 1.0f;
  L_s = vec3(1.0, 1.0, 1.0);

  L_f = rho_s*L_s*max(dot(r,e), 0);

  //my_color = vec4(in_normal*0.5+0.5,1.0);
  //my_color = posInWorldSpace+0.5;
  my_color = vec4(L_f,1.0);
}

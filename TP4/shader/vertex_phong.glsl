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
              SHADING DE PHONG
************************************************/

// Fonction appellee pour chaque sommet
void main() {
  // Affectation de la position du sommet
  // gl_Position est defini par defaut dans GLSL
  gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_position, 1.0);

  vec4 posInObjectSpace = vec4(in_position, 1.0);
  vec4 posInWorldSpace = ModelMatrix * posInObjectSpace;
  vec4 posOfLight = vec4(0.0, 1.0, 2.0, 0.5);

  vec4 normalInWorldSpace = normalize(transpose(inverse(ModelMatrix)) * vec4(in_normal, 0.));
  vec4 cameraPosInWorldSpace = inverse(ViewMatrix) * vec4(0., 0., 0., 1.);


  vec3 L_f;                   // Couleur résultante calculée par le modèle de Phong
  float rho_a, rho_d, rho_s;  // Coefficients d'atténuation associés à chaque composante
  vec3 L_a, L_d, L_s;         // Couleurs de chaque composante
  vec4 n;                     // Vecteur normal de la surface au point p
  vec4 l;                     // Vecteur de norme  dans la direction de la lumière
  vec4 r;                     // Vecteur réflection de l par rapport à n : r=l-2<n,l>n
  vec4 e;                     // Vecteur de norme 1 dans la direction entre le point p de la surface et la position c de l'oeil
  float s = 1.0;                    // Brillance (shininess)

  l = posInWorldSpace - posOfLight;
  l = normalize(l);

  n = normalize(normalInWorldSpace);

  r = reflect(l, n);

  e = normalize(cameraPosInWorldSpace - posInWorldSpace);


  rho_a = 1.0f;
  rho_d = 1.0f;
  rho_s = 1.0f;

  L_a = vec3(0.4157, 0.1373, 0.6);
  L_d = vec3(0.4157, 0.1373, 0.6);
  L_s = vec3(0.4157, 0.1373, 0.6);
  

  vec3 ambiant = rho_a * L_a;
  vec3 diffus = rho_d * L_d * max(-dot(n, l), 0.0);
  vec3 speculaire = rho_s * L_s * max(-dot(r, e), 0.0);;

  L_f = ambiant + diffus + speculaire;

  // my_color = normalInWorldSpace + cameraPosInWorldSpace + posInObjectSpace ;
  my_color = vec4(L_f, 1.0);

}

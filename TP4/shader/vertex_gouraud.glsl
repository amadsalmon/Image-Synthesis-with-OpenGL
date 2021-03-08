// Version d'OpenGL
#version 330

/* -- Données en entrée -- */
in vec3 in_position;
in vec3 in_color;
in vec3 in_normal;

/* -- Données en sortie -- */
out vec4 my_color; // Lf, couleur résultante

/* -- Paramètres -- */
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
  vec4 posInWorldSpace = ModelMatrix * posInObjectSpace;    // point p (position) dans le repère monde
  vec4 posOfLight = vec4(0.0, 1.0, 2.0, 0.5);

  vec4 normalInWorldSpace = normalize(transpose(inverse(ModelMatrix)) * vec4(in_normal, 0.));       // normales dans le repère monde
  vec4 cameraPosInWorldSpace = inverse(ViewMatrix) * vec4(0., 0., 0., 1.);    // caméra dans le repère monde

  /* ------- Définition des vecteurs ------- */
  vec3 L_f;                   // Couleur résultante calculée par le modèle
  float rho_a, rho_d, rho_s;  // Coefficients d'atténuation associés à chaque composante
  vec3 L_a, L_d, L_s;         // Couleurs de chaque composante
  vec4 n;                     // Vecteur normal de la surface au point p
  vec4 l;                     // Vecteur de norme  dans la direction de la lumière
  vec4 r;                     // Vecteur réflection de l par rapport à n : r=l-2<n,l>n
  vec4 e;                     // Vecteur de norme 1 dans la direction entre le point p de la surface et la position c de l'oeil
  float s = 10.0;             // Brillance (shininess)

  /* ------- Calcul des vecteurs ------- */

  l = posInWorldSpace - posOfLight;
  l = normalize(l);

  n = normalize(normalInWorldSpace);

  r = reflect(l, n);

  e = normalize(cameraPosInWorldSpace - posInWorldSpace);
  
  // Affectation des coefficients d'atténuation
  rho_a = 1.0f;
  rho_d = 1.0f;
  rho_s = 1.0f;

  /* Affectation des couleurs */
  L_a = vec3(0.1216, 0.3176, 0.6784);
  L_d = vec3(0.1216, 0.3176, 0.6784);
  L_s = vec3(0.1216, 0.3176, 0.6784);
    
  vec3 ambiant = rho_a * L_a;
  vec3 diffus = rho_d * L_d * max(-dot(n, l), 0.0);
  vec3 speculaire = rho_s * L_s * pow(max(-dot(r, e), 0.0), s);

  /* --- Couleur résultante --- */
  L_f = ambiant + diffus + speculaire;

  // Affectation de la couleur du sommet
  my_color = vec4(L_f, 1.0);
}

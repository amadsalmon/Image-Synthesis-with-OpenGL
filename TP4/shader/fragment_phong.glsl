// Version d'OpenGL
#version 330

in vec4 my_color;

out vec4 frag_color;


/************************************************
              SHADING DE PHONG
************************************************/

// Fonction appellee pour chaque fragment
void main() {

  
  /* ------- Définition des vecteurs ------- */
  vec3 L_f;                   // Couleur résultante calculée par le modèle
  float rho_a, rho_d, rho_s;  // Coefficients d'atténuation associés à chaque composante
  vec3 L_a, L_d, L_s;         // Couleurs de chaque composante
  vec4 n;                     // Vecteur normal de la surface au point p
  vec4 l;                     // Vecteur de norme  dans la direction de la lumière
  vec4 r;                     // Vecteur réflection de l par rapport à n : r=l-2<n,l>n
  vec4 e;                     // Vecteur de norme 1 dans la direction entre le point p de la surface et la position c de l'oeil
  float s = 10.0;                    // Brillance (shininess)

  // Affectation des coefficients d'atténuation
  rho_a = 1.0f;
  rho_d = 1.0f;
  rho_s = 1.0f;


  /* ------- Calcul des vecteurs ------- */

  l = posInWorldSpace - posOfLight;
  l = normalize(l);

  n = normalize(normalInWorldSpace);

  r = reflect(l, n);

  e = normalize(cameraPosInWorldSpace - posInWorldSpace);

    
  vec3 ambiant = rho_a * L_a;
  vec3 diffus = rho_d * L_d * max(-dot(n, l), 0.0);
  vec3 speculaire = rho_s * L_s * pow(max(-dot(r, e), 0.0), s);

  /* --- Couleur résultante --- */
  L_f = ambiant + diffus + speculaire;

  // Affectation de la couleur du fragment
  frag_color = L_f;
}

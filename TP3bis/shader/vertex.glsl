// Version d'OpenGL
#version 330

// Donnees d'entree
layout(location=0) in vec3 in_position;
layout(location=1) in vec3 in_color;
layout(location=2) in vec3 in_normal;
layout(location=3) in vec3 in_depth;

// Donnees de sortie
out vec4 my_color;

// Parametres
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform int ToDraw;
uniform float CurrentTime;

float distToCamera;

// Fonction appellee pour chaque sommet
void main()
{
  // Affectation de la position du sommet
  // gl_Position est défini par defaut dans GLSL
  gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_position, 1.0);

  vec3 v_anim; // Vecteur d'animation, prendra différentes valeurs selon le cadran.

  switch(ToDraw) {
    case 1: // Dessin en haut à droite --------
      v_anim = vec3(sin(CurrentTime), 1, 1);
      my_color = vec4(v_anim * in_color, 1.0);
      break;
    case 2: // Dessin en haut à gauche --------
      v_anim = vec3(sin(CurrentTime), sin(CurrentTime), sin(CurrentTime));
      my_color = vec4(v_anim * in_normal, 1.0);
      break;
    case 3: // Dessin en bas à gauche --------
      v_anim = vec3(1, 1, sin(CurrentTime));
      my_color = vec4(v_anim * in_position, 1.0);
      break;
    case 4: // Dessin en bas à droite --------
      /* Formule pour la profondeur */
      v_anim = vec3(1, sin(CurrentTime), 1);
      my_color = vec4(v_anim * in_color, 1.0); // À remplacer par la bonne formule
      break;
    default: 
      my_color = vec4(in_color, 1.0);
      break;
  }
}

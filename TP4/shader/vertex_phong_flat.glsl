// Version d'OpenGL
#version 330

/* -- Données en entrée -- */
in vec3 in_position;
in vec3 in_color;
in vec3 in_normal;

/* -- Données en sortie -- */
flat out vec4 posInWorldSpace;         // point p (position) dans le repère monde
flat out vec4 normalInWorldSpace;      // normales dans le repère monde
flat out vec4 cameraPosInWorldSpace;   // caméra dans le repère monde

/* -- Paramètres -- */
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
  posInWorldSpace = ModelMatrix * posInObjectSpace;
  

  normalInWorldSpace = normalize(transpose(inverse(ModelMatrix)) * vec4(in_normal, 0.));
  cameraPosInWorldSpace = inverse(ViewMatrix) * vec4(0., 0., 0., 1.);
}

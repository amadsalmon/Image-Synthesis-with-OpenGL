// Version d'OpenGL
#version 330

/* -- Données en entrée -- */
in vec3 in_position;

/* -- Données en sortie -- */
out vec2 coords;

/* -- Paramètres -- */
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

// Fonction appellee pour chaque sommet
void main() {
  // gl_Position est defini par defaut dans GLSL
  gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_position, 1.0);
  
  coords = in_position.xy*0.5+0.5; // remap [-1,1] to [0,1]
}

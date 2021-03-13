// Version d'OpenGL
#version 330

in vec2 coords;

out vec4 frag_color;

vec2 raiseComplexNumberToPower2(vec2 c) {
  float real = c.x * c.x - c.y * c.y;
  float imaginary = 2.0 * c.x * c.y;
  return vec2(real, imaginary);
}

float modulusOfComplexNumber(vec2 c) {
  return sqrt(c.x * c.x + c.y * c.y);
}

vec4 colormap(vec2 c, int S, int N) {
  vec2 z = vec2(0,0);
  for(int n = 0 ; n < N ; n++){
    z = raiseComplexNumberToPower2(z) + c;
    if(modulusOfComplexNumber(z)>float(S)) break;
  }
  return vec4(z.x, z.y, 0.5, 1.0);
}

// Fonction appellee pour chaque fragment
void main() {

  int N = 900;
  int S = 50;
  // Affichage de la coordonnee du fragment/pixel
  // frag_color = vec4(coords, 0.5, 1.0);
  frag_color = colormap(coords, S, N);
}

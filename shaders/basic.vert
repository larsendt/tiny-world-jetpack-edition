//#version 120

attribute vec3 vertex;
attribute vec3 normal;
attribute vec3 color;
varying vec3 f_normal;
varying vec3 f_color;

void main(void) {
	f_normal = normal;
	f_color = color;
	gl_Position = gl_ModelViewProjectionMatrix * vec4(vertex, 1.0);
}

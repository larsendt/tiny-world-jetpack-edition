varying vec3 f_normal;
varying vec3 f_color;

void main(){

	float intensity = max(dot(vec3(0,1,0),normalize(f_normal)),0.05);
	
	gl_FragColor = vec4(f_color*intensity, 1);
	
}

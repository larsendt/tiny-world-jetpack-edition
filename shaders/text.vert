#version 120

attribute vec4 pos;
varying vec2 f_tcoord;

void main(){
	
	gl_Position = vec4(pos.xy, 0, 1);
	
	f_tcoord = pos.zw;
	
}

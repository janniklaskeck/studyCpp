#version 120

uniform mat4 model_view;
uniform mat4 projection;
attribute vec3 pos;

void main(){
	vec4 camera_space = model_view * vec4(pos, 1);
	gl_Position = projection * camera_space;
}
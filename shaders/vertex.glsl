#version 400 core

in vc3 vp;

void	main() {
	gl_Position = vec4(vp, 1.0);
}

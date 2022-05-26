const char* default_vertex = "\
#version 430\n\
layout(location = 0) in vec4 a_color;\n\
layout(location = 1) in vec3 a_position;\n\
layout(location = 2) in vec2 a_textureCoordinate;\n\
layout(location = 3) in float a_textureUnit;\n\
\n\
layout (std140, binding = 0) uniform ViewProjection \n\
{\n\
mat4 viewProjection;\n\
};\n\
\n\
out vec4 v_color;\n\
out vec2 v_textureCoordinate;\n\
out float v_textureUnit;\n\
\n\
void main()\n\
{\
	v_color = a_color;\n\
	v_textureCoordinate = a_textureCoordinate;\n\
	v_textureUnit = a_textureUnit;\n\
\n\
	gl_Position = viewProjection * vec4(a_position, 1.0);\n\
};";

const char* default_fragment = "\
#version 430\n\
\n\
layout(location = 0) out vec4 o_color;\n\
\n\
uniform sampler2D u_textures[32];\n\
\n\
in vec4 v_color;\n\
in vec2 v_textureCoordinate;\n\
in float v_textureUnit;\n\
\n\
void main()\n\
{\n\
	int index = int(v_textureUnit);\n\
\n\
	// vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_textures[index], v_textureCoordinate).r);\n\
	// o_color = sampled * v_color;\n\
\n\
	o_color = texture(u_textures[index], v_textureCoordinate) * v_color;\n\
};";

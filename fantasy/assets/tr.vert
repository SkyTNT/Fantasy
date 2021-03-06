layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;

out vec3 o_normal;
out vec2 o_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position =projection * view * model * vec4(a_position, 1.0);
    o_normal = a_normal;
    o_uv = a_uv;
}

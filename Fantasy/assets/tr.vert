layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 a_color;
layout (location = 2) in vec2 a_coord;
out vec3 fColor;
out vec2 fCoord;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    fColor = a_color;
    fCoord = a_coord;
}

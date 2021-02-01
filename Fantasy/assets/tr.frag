in vec3 fColor;
in vec2 fCoord;
out vec4 fragColor;

uniform sampler2D texture0;

void main()
{
    fragColor = texture(texture0, fCoord)*vec4(fColor,1);
}

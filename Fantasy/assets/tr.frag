in vec3 fColor;
in vec2 fCoord;
out vec4 fragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    fragColor = mix(texture(texture0, fCoord), texture(texture1, fCoord), 0.2)*vec4(fColor,1);
    //fragColor = texture(texture0, fCoord);
    //fragColor = texture(texture0, fCoord)*vec4(fColor,1);
}

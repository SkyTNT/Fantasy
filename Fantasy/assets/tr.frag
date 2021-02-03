in vec3 o_normal;
in vec2 o_uv;
out vec4 fragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    fragColor = mix(texture(texture0, o_uv), texture(texture1, o_uv), 0.2);
}

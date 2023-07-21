// fragment_shader.frag

// Uniforms
uniform sampler2D texture;
uniform vec2 resolution;
uniform float blurRadius;

void main()
{
    // Get the texture coordinate
    vec2 texCoord = gl_FragCoord.xy / resolution;

    // Sample the texture multiple times to apply blur
    int blurSamples = 10;
    vec3 color = vec3(0.0);
    for (int i = -blurSamples; i <= blurSamples; ++i) {
        float offset = float(i) * blurRadius / float(blurSamples);
        color += texture2D(texture, texCoord + vec2(offset, 0.0)).rgb;
    }
    color /= float(blurSamples * 2 + 1);

    // Output the final color
    gl_FragColor = vec4(color, 1.0);
}
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// light and material properties
uniform vec3 color;
uniform vec4 ambientProduct;
uniform vec4 diffuseProduct;
uniform vec4 specularProduct;
uniform vec4 lightPosition;
uniform float shininess;


void main()
{
    // Transform vertex position into eye coordinates
    vec3 pos = (view * model * vec4(aPos, 1.0f)).xyz;
    
    vec3 L = normalize(lightPosition.xyz - pos);
    vec3 E = normalize(-pos);
    vec3 H = normalize(L + E);

    // Transform vertex normal into eye coordinates
    vec3 N = normalize(view * model * vec4(aNormal, 0.0)).xyz;

    // Compute the terms in the illumination equation
    vec4 ambient = ambientProduct;
    
    float Kd = max(dot(L,N), 0.0);
    vec4 diffuse = Kd * diffuseProduct;

    float Ks = pow( max(dot(N, H), 0.0), shininess);
    vec4 specular = Ks * specularProduct;
    if ( dot(L, N) < 0.0 )
    {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    ourColor = (ambient + diffuse + specular).xyz;
    //ourColor = (ambient + diffuse + specular).xyz * color;

   TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}

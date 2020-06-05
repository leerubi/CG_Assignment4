#version 330 core
#extension GL_NV_shader_buffer_load : enable
#extension GL_NV_gpu_shader5 : enable
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;

// Gouraud shading out
out vec3 ourColor;
out vec3 Normal;
out vec2 TexCoord;

// Phong shading out
out vec3 fN;
out vec3 fE;
out vec3 fL;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float shininess;
uniform vec3 color;

uniform vec4 ambientProduct;
uniform vec4 diffuseProduct;
uniform vec4 specularProduct;

// Directional light
uniform vec4 lightPosition;

// Point lights
uniform vec4 p_lightPositions[50];
uniform vec4 p_diffuseProduct[50];
uniform vec4 p_specularProduct[50];
uniform float constant = 1.0f;
uniform float linear = 0.09f;
uniform float quadratic = 0.032f;

// Shading type
uniform int shadingType; //100: Gouraud, 200: Phong

void main()
{
 
    // Gouraud shading
    if (shadingType == 100)
    {
        vec4 result = vec4(0.0f);
        vec3 L, E, H, N;
        vec4 ambient, diffuse, specular;
        float Kd = 0.4f;
        float Ks = 0.4f;
        float distance, attenuation;
    
        // Directional light
        vec3 pos = (view * model * vec4(aPos, 1.0f)).xyz;
        L = normalize(lightPosition.xyz - pos);
        // L = normalize(vec3(-0.2f, -1.0f, -0.3f));
        E = normalize(-pos);
        H = normalize(L + E);
        N = normalize(view * model * vec4(aNormal, 0.0)).xyz;

        ambient = ambientProduct;
        result += ambient;

        Kd = max(dot(L,N), 0.0);
        diffuse = Kd * diffuseProduct;
        result += diffuse;

        Ks = pow( max(dot(N, H), 0.0), shininess);
        specular = Ks * specularProduct;
        if ( dot(L, N) < 0.0 ) { specular = vec4(0.0, 0.0, 0.0, 1.0); }
        result += specular;

    
        // Point light
        for (int i = 0; i < 50; i++)
        {

            // Attenuation
            distance = length(p_lightPositions[i].xyz - pos);
            attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

            L = normalize(p_lightPositions[i].xyz - pos);
            E = normalize(-pos);
            H = normalize(L + E);

            // Transform vertex normal into eye coordinates
            N = normalize(view * model * vec4(aNormal, 0.0)).xyz;

            // Compute the terms in the illumination equation
            ambient = ambientProduct;
            result += (ambient*attenuation);
    
            Kd = max(dot(L,N), 0.0);
            diffuse = Kd * p_diffuseProduct[i];
            result += (diffuse*attenuation);

            Ks = pow( max(dot(N, H), 0.0), shininess);
            specular = Ks * p_specularProduct[i];
            if ( dot(L, N) < 0.0 )
            {
                specular = vec4(0.0, 0.0, 0.0, 1.0);
            }
            result += (specular*attenuation);
        }

        gl_Position = projection * view * model * vec4(aPos, 1.0f);
        ourColor = result.xyz;
        TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
    }
    
    // Phong shading
    if (shadingType == 200)
    {
        fN = aNormal;
        fE = aPos.xyz;
        fL = lightPosition.xyz;

        gl_Position = projection * view * model * vec4(aPos, 1.0f);
        TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
        fragPos = (view * model * vec4(aPos, 1.0f)).xyz;
    }
}

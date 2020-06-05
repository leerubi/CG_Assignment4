#version 330 core
#extension GL_NV_shader_buffer_load : enable
out vec4 FragColor;

// Gouraud in
in vec3 ourColor;
in vec3 Normal;
in vec2 TexCoord;
in vec3 fragPos;

// Phong in
in vec3 fN;
in vec3 fL;
in vec3 fE;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform mat4 model;
uniform mat4 view;

uniform float shininess;
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

uniform int diffuseType; //25 : on, 26 : off
uniform int normalType; // 27 : on, 28 : off

void main()
{
    // Gouraud shading
    if (shadingType == 100)
    {
        FragColor = vec4(ourColor*texture(texture1, TexCoord).rgb, 1.0f);
    }

    // Phong shading
    if (shadingType == 200)
    {
        vec4 result = vec4(0.0f);
        vec3 N, E, L, H;
        vec4 ambient, diffuse, specular;
        float Kd = 0.4f;
        float Ks = 0.4f;
        float distance, attenuation;




                // Directional light
            L = normalize(fL);
            // L = normalize(vec3(-0.2f, -1.0f, -0.3f));
            N = normalize(fN);
            E = normalize(fE);
            H = normalize(L+E);




        ambient = ambientProduct;
        result += ambient;

        if(diffuseType == 25){
            Kd = max(dot(L,N), 0.0);
            diffuse = Kd * diffuseProduct;
        }else{
            Kd = max(dot(L,N), 0.0);
            diffuse = 0.0f * diffuseProduct;

            //diffuse = vec4(0.0f);
            //result
        }

        result += diffuse;

        Ks = pow(max(dot(N,H), 0.0), shininess);
        specular = Ks * specularProduct;
        if (dot(L,N) < 0.0) { specular = vec4(0.0, 0.0, 0.0, 1.0); }
        result += specular;

        // Point light
        for (int i = 0; i < 50; i++)
        {

            // Attenuation
            distance = length(p_lightPositions[i].xyz - fragPos);
            attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));


                // Directional light
                L = normalize(fL);
                // L = normalize(vec3(-0.2f, -1.0f, -0.3f));
                N = normalize(fN);
                E = normalize(fE);
                H = normalize(L+E);


            ambient = ambientProduct;
            result += (ambient*attenuation);



            if(diffuseType == 25){
                Kd = max(dot(L,N), 0.0);
                diffuse = Kd * diffuseProduct;
            }else{
                Kd = max(dot(L,N), 0.0);
                diffuse = 0.0f * diffuseProduct;

            //diffuse = vec4(0.0f);
            //result
            }





            //Kd = max(dot(L,N), 0.0);
            //diffuse = Kd * diffuseProduct;
            result += (diffuse*attenuation);

            Ks = pow(max(dot(N,H), 0.0), shininess);
            specular = Ks * specularProduct;
            if (dot(L,N) < 0.0) { specular = vec4(0.0, 0.0, 0.0, 1.0); }
            result += (specular*attenuation);
        }

        if(normalType == 27){
            //texture2 = vec2(1.0f);
            FragColor = vec4(result.xyz*texture(texture1, TexCoord).rgb*texture(texture2, TexCoord).rgb, 1.0f);
        }else
            FragColor = vec4(result.xyz*texture(texture1, TexCoord).rgb, 1.0f);
    }

}

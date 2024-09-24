#type vertex
#version 410 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ModelTransform;
uniform mat4 u_ViewProjection;

out vec2 v_TexCoord;
out vec3 v_FragPos;
out vec3 v_Normal;

void main()
{
	v_TexCoord = a_TexCoord;

	v_FragPos = vec3(u_ModelTransform * vec4(a_Position, 1.0));
	v_Normal = mat3(transpose(inverse(u_ModelTransform))) * a_Normal;
	gl_Position = u_ViewProjection * vec4(v_FragPos, 1.0);	
}

#type fragment
#version 410 core			
layout(location = 0) out vec4 color;

struct Material {
	sampler2D albedoMap;
	sampler2D specularMap;
	sampler2D metallicMap;
	sampler2D normalMap;
	sampler2D heightMap;
	sampler2D occlusionMap;
	sampler2D detailMaskMap;
	sampler2D emissionMap;

	vec4 albedoColor;    
	vec3 specularColor;   
	vec3 emissionColor;     

	float tiling;
	float offset;
	float smoothness;
	float shininess;
	float metallic;

	bool hasAlbedoMap;
    bool hasSpecularMap;
    bool hasNormalMap;
	bool hasMetallicMap;
    // bool hasEmission;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 v_TexCoord;
in vec3 v_FragPos;
in vec3 v_Normal; 

uniform vec3 u_ViewPos;
uniform Material u_Material;
uniform Light u_Light;
			
uniform sampler2D u_Texture;

void main()
{
	// Temporary light variables
	vec3 u_Light_position = vec3(0.0f, 100.0f, 0.0f);
	vec3 u_Light_ambient = vec3(0.4f, 0.4f, 0.4f);
	vec3 u_Light_diffuse = vec3(1.0f, 1.0f, 1.0f);
	vec3 u_Light_specular = vec3(1.0f, 1.0f, 1.0f);

	vec4 albedoColor = u_Material.hasAlbedoMap ? texture(u_Material.albedoMap, v_TexCoord) : u_Material.albedoColor;
	vec3 specularColor = u_Material.hasSpecularMap ? texture(u_Material.specularMap, v_TexCoord).rgb : u_Material.specularColor;
	float metallic = u_Material.hasMetallicMap ? texture(u_Material.metallicMap, v_TexCoord).r : u_Material.metallic;

	// ambient 
	vec3 ambient = u_Light.ambient * albedoColor.rgb;

	// normal
	vec3 norm = normalize(v_Normal);
	if (u_Material.hasNormalMap) {
        vec3 tangentNormal = texture(u_Material.normalMap, v_TexCoord).rgb;
        tangentNormal = tangentNormal * 2.0 - 1.0;  // Convert from [0, 1] to [-1, 1]
        norm = normalize(tangentNormal);
    }

	// diffuse
	vec3 lightDir = normalize(u_Light_position - v_FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_Light_diffuse * diff * albedoColor.rgb;

	// specular
	vec3 viewDir = normalize(u_ViewPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = u_Light_specular * (spec * specularColor);

	// final color
	vec3 final = ambient + (1.0 - metallic) * diffuse + (metallic * specular);
	color = vec4(final, albedoColor.a);
}
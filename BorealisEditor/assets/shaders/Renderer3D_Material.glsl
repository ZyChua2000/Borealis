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
layout(location = 0) out vec4 fragColor;

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
	vec4 specularColor;   
	vec4 emissionColor;     

	vec2 tiling;
	vec2 offset;
	float smoothness;
	float shininess;
	float metallic;

	bool hasAlbedoMap;
    bool hasSpecularMap;
    bool hasNormalMap;
	bool hasMetallicMap;
    bool hasEmissionMap;
	bool hasHeightMap;
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

uniform mat4 u_ViewProjection;
uniform vec3 u_ViewPos;
uniform Material u_Material;
uniform Light u_Light;
uniform bool hasMaterial;
			
uniform sampler2D u_Texture;

vec4 blinnPhong() 
{
	// Set default values for cases without a material
    vec4 albedoColor = vec4(0.8, 0.8, 0.8, 1.0);
    vec3 specularColor = vec3(1.0, 1.0, 1.0);
    float shininess = 32.0;
	float metallic = 1.0;

	if (u_Light.position == v_FragPos)
	{
		return vec4(0.f, 0.f, 0.f, 1.f);
	}

	float smoothness;
	vec3 emission;
	vec3 norm;
	vec3 lightDir = normalize(u_Light.position - v_FragPos);
	vec3 viewDir = -v_FragPos;

	vec3 normal = v_Normal;
	if (length(normal) > 0.f)
		normal = normalize(normal);
	if (length(lightDir) > 0.f)
		lightDir = normalize(lightDir);
	if (length(viewDir) > 0.f)
		viewDir = normalize(viewDir);

	if (hasMaterial) 
	{
		vec2 texCoord = v_TexCoord * u_Material.tiling + u_Material.offset;
		
		albedoColor = u_Material.hasAlbedoMap ? texture(u_Material.albedoMap, texCoord) : u_Material.albedoColor;
		if (u_Material.hasAlbedoMap) {
			albedoColor = mix(u_Material.albedoColor, albedoColor, 0.8);
		}
		specularColor = u_Material.hasSpecularMap ? texture(u_Material.specularMap, texCoord).rgb : u_Material.specularColor.rgb;
		
		metallic = u_Material.hasMetallicMap ? texture(u_Material.metallicMap, texCoord).r : u_Material.metallic;

		shininess = u_Material.shininess;

		smoothness = u_Material.smoothness;

		// normal
		norm = normalize(v_Normal);
		if (u_Material.hasNormalMap) {
			vec3 tangentNormal = texture(u_Material.normalMap, texCoord).rgb;
			tangentNormal = tangentNormal * 2.0 - 1.0;  // Convert from [0, 1] to [-1, 1]
			norm = normalize(tangentNormal);
		}

		// emission
		emission = u_Material.hasEmissionMap ? texture(u_Material.emissionMap, texCoord).rgb : u_Material.emissionColor.rgb;
	}

	vec3 ambient = u_Light.ambient * albedoColor.rgb; 
	
	vec3 color = ambient;

	vec3 halfwayDir = normalize(lightDir + viewDir);

	// diffuse
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_Light.diffuse * diff * albedoColor.rgb;

	// specular
	float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess * smoothness);
	vec3 specular = u_Light.specular * (spec * specularColor);

	// final color
	color = ambient + (1.0 - metallic) * diffuse + (metallic * specular) + emission;

	return vec4(color, albedoColor.a);
}

void main() {
	fragColor = blinnPhong();
}


//
// void main()
// {
// 	// Temporary light variables
// 	vec3 u_Light_position = vec3(0.0f, 100.0f, 0.0f);
// 	vec3 u_Light_ambient = vec3(0.4f, 0.4f, 0.4f);
// 	vec3 u_Light_diffuse = vec3(1.0f, 1.0f, 1.0f);
// 	vec3 u_Light_specular = vec3(1.0f, 1.0f, 1.0f);

// 	vec2 texCoord = v_TexCoord * u_Material.tiling + u_Material.offset;

// 	vec4 albedoColor = u_Material.hasAlbedoMap ? texture(u_Material.albedoMap, texCoord) : u_Material.albedoColor;
// 	if (u_Material.hasAlbedoMap) {
// 		albedoColor = mix(u_Material.albedoColor, albedoColor, 0.8);
// 	}
// 	vec3 specularColor = u_Material.hasSpecularMap ? texture(u_Material.specularMap, texCoord).rgb : u_Material.specularColor.rgb;
// 	float metallic = u_Material.hasMetallicMap ? texture(u_Material.metallicMap, texCoord).r : u_Material.metallic;

// 	// ambient 
// 	vec3 ambient = u_Light.ambient * albedoColor.rgb;

// 	// normal
// 	vec3 norm = normalize(v_Normal);
// 	if (u_Material.hasNormalMap) {
//         vec3 tangentNormal = texture(u_Material.normalMap, texCoord).rgb;
//         tangentNormal = tangentNormal * 2.0 - 1.0;  // Convert from [0, 1] to [-1, 1]
//         norm = normalize(tangentNormal);
//     }

// 	// diffuse
// 	vec3 lightDir = normalize(u_Light_position - v_FragPos);
// 	float diff = max(dot(norm, lightDir), 0.0);
// 	vec3 diffuse = u_Light_diffuse * diff * albedoColor.rgb;

// 	// specular
// 	vec3 viewDir = normalize(u_ViewPos - v_FragPos);
// 	vec3 reflectDir = reflect(-lightDir, norm);
// 	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess * u_Material.smoothness);
// 	vec3 specular = u_Light_specular * (spec * specularColor);

// 	// emission
// 	vec3 emission = u_Material.hasEmissionMap ? texture(u_Material.emissionMap, texCoord).rgb : u_Material.emissionColor.rgb;

// 	// final color
// 	vec3 final = ambient + (1.0 - metallic) * diffuse + (metallic * specular) + emission;
// 	color = vec4(final, albedoColor.a);
// }


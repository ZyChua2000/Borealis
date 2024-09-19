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
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
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
	vec3 u_Light_position = vec3(0.0f, 5.0f, 0.0f);
	vec3 u_Light_ambient = vec3(0.4f, 0.4f, 0.4f);
	vec3 u_Light_specular = vec3(1.0f, 1.0f, 1.0f);
	vec3 u_Light_diffuse = vec3(1.0f, 1.0f, 1.0f);

	//color = texture(u_Texture, v_TexCoord);
	vec3 ambient = u_Light_ambient * u_Material.ambient;

	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_Light_position - v_FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_Light_diffuse * (diff * u_Material.diffuse);

	vec3 viewDir = normalize(u_ViewPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = u_Light_specular * (spec * u_Material.specular);

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0);
}
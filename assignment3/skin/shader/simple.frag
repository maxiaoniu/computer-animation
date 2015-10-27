
#version 410
in vec3 out_normal;
in vec3 es_vpos;
out vec4 fColor;
vec3 es_lightpos = vec3(10,0,5);
vec3 diffuse_color = vec3(1,0,0);
vec3 specular_color = vec3(1.0);

vec3 es_lightpos1 = vec3(-10,0,-5);
vec3 diffuse_color1 = vec3(0,1,0);
vec3 specular_color1 = vec3(1.0);

float ambient_intensity = 0.5;
float shininess = 500;

void main(){
        vec3 L = normalize(es_lightpos-es_vpos);
        //vec3 L = vec3(0);

        vec3 V = normalize(vec3(0,0,0)-es_vpos);
        vec3 H = normalize(L+V);

        float diffuse = max(dot(out_normal, L),0);
        float specular = dot(out_normal, H);
        specular = clamp(specular, 0, 1);
        specular = pow(specular, shininess);
        vec3 ambientTerm = vec3(0);
        vec3 diffuseTerm = vec3(0);
        vec3 specularTerm = vec3(0);

        //ambientTerm += diffuse_color*ambient_intensity;
        diffuseTerm += diffuse_color.rgb*diffuse;
        specularTerm += specular_color*specular;

        //
        L = normalize(es_lightpos1-es_vpos);
        H = normalize(L+V);
        diffuse = max(dot(out_normal, L),0);
        specular = dot(out_normal, H);
        specular = clamp(specular, 0, 1);
        specular = pow(specular, shininess);

        //ambientTerm += diffuse_color1*ambient_intensity;
        diffuseTerm += diffuse_color1.rgb*diffuse;
        specularTerm += specular_color1*specular;


        fColor = vec4((0.2*vec3(1.0,1.0,1.0)+min(ambientTerm + diffuseTerm + specularTerm,vec3(1.0))), 1.0);
}

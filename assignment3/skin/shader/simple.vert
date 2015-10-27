#version 410
#define MAX_BONES 32


layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 jointId;
layout(location = 3) in vec4 jointWeight;

out vec3 out_normal;
out vec3 es_vpos;

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;

uniform mat4 boneMatrices[MAX_BONES];
uniform mat4 bindingMatrices[MAX_BONES];
uniform mat4 matrixNormal;
void main()
{
  vec4 new_pos;
  vec3 new_normal;

  int index = int(jointId.x);
  new_pos = (boneMatrices[index]*inverse(bindingMatrices[index])*vec4(position, 1.0))*jointWeight.x;
  new_normal = (boneMatrices[index]*inverse(bindingMatrices[index])*vec4(normal,0.0)).xyz*jointWeight.x;

  index = int(jointId.y);
  new_pos = (boneMatrices[index]*inverse(bindingMatrices[index])*vec4(position, 1.0))*jointWeight.y+new_pos;
  new_normal = (boneMatrices[index]*inverse(bindingMatrices[index])*vec4(normal, 0.0)).xyz*jointWeight.y+new_normal;
  index = int(jointId.z);
  new_pos = (boneMatrices[index]*inverse(bindingMatrices[index])*vec4(position, 1.0))*jointWeight.z+new_pos;
  new_normal = (boneMatrices[index]*inverse(bindingMatrices[index])*vec4(normal, 0.0)).xyz*jointWeight.z+new_normal;
  index = int(jointId.w);
  new_pos = (boneMatrices[index]*inverse(bindingMatrices[index])*vec4(position, 1.0))*jointWeight.w+new_pos;
  new_normal = (boneMatrices[index]*inverse(bindingMatrices[index])*vec4(normal, 0.0)).xyz*jointWeight.w+new_normal;

  out_normal = normalize((matrixNormal*vec4(new_normal,0.0)).xyz);
  es_vpos = (worldToCamera* modelToWorld*vec4(new_pos.xyz,1.0)).xyz;
  gl_Position = cameraToView * worldToCamera* modelToWorld*vec4(new_pos.xyz,1.0);

}

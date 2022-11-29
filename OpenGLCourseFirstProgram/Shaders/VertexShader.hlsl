#version 330			

layout (location = 0) in vec3 pos;
								
out vec4 vecColour;			
uniform mat4 model;		
uniform mat4 projection;
					
				
void main()	
{		
	gl_Position = projection * model * vec4(0.4* pos.x, 0.4* pos.y, 0.4 * pos.z, 1.0);
	vecColour = vec4(clamp(pos,0.0f,1.0f),1.0f);				
}							

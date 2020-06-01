mat4 projectOntoPlane()
{
	vec3 light = vec3(4,10,-4);
	float A = 0;
	float B = 1;
	float C = 0;
	float D = -0.5*a*n*n+0.9;
	float s = -dot(vec4(-A,-B,-C,-D), vec4(light,1));	
	mat4 trans0 = mat4(1.0);
	mat4 trans1 = mat4(1.0); 
	trans0[3].xyz = light;	
	mat4 aux = mat4(vec4(s, 0, 0, -A), vec4(0, s, 0, -B), vec4(0, 0, s, -C), vec4(0));
	trans1[3].xyz = -light;
	return  trans0 * aux * trans1;
}



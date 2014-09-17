uniform vec3      iResolution;           // viewport resolution (in pixels)
uniform float     iGlobalTime;           // shader playback time (in seconds)
uniform float     iChannelTime[4];       // channel playback time (in seconds)
uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
uniform sampler2D iChannel0;
uniform sampler2D iChannel1;
uniform sampler2D iChannel2;
uniform sampler2D iChannel3;
uniform vec4      iDate;
uniform bool      iDebug[10];
uniform vec2	  iCamera;

float field(in vec3 p,float s) {
	float strength = 7. + .03 * log(1.e-6 + fract(sin(iGlobalTime) * 4373.11));
	float accum = s/4.;
	float prev = 0.;
	float tw = 0.;
	for (int i = 0; i < 26; ++i) {
		float mag = dot(p, p);
		p = abs(p) / mag + vec3(-.5, -.4, -1.5);
		float w = exp(-float(i) / 7.);
		accum += w * exp(-strength * pow(abs(mag - prev), 2.2));
		tw += w;
		prev = mag;
	}
	return (5. * accum / tw - .7);
}

// Less iterations for second layer
float field2(in vec3 p, float s) {
	float strength = 14. + .03 * log(1.e-6 + fract(sin(iGlobalTime) * 4373.11));
	float accum = s/4.;
	float prev = 0.;
	float tw = 0.;
	for (int i = 0; i < 18; ++i) {
		float mag = dot(p, p);
		p = abs(p) / mag + vec3(-.5, -.4, -1.5);
		float w = exp(-float(i) / 7.);
		accum += w * exp(-strength * pow(abs(mag - prev), 2.2));
		tw += w;
		prev = mag;
	}
	return max(0., 5. * accum / tw - .7);
}

vec3 nrand3( vec2 co )
{
	vec3 a = fract( cos( co.x*8.3e-3 + co.y )*vec3(1.3e5, 4.7e5, 2.9e5) );
	vec3 b = fract( sin( co.x*0.3e-3 + co.y )*vec3(8.1e5, 1.0e5, 0.1e5) );
	vec3 c = mix(a, b, 0.5);
	return c;
}


void main() {
        vec2 uv = 2. * gl_FragCoord.xy / iResolution.xy - 1.;
	vec2 uvs = uv * iResolution.xy / max(iResolution.x, iResolution.y);
	vec3 p = vec3(uvs / 4., 0) + vec3(1., -1.3, 0.);
	p +=  0.000278 * vec3(iCamera.x, iCamera.y,  12506.);
	
	float freqs[4];
	// Noise
	if (!iDebug[0])
	{
		freqs[0] = texture2D( iChannel0, vec2( 0.01, 0.25 ) ).x;
		freqs[1] = texture2D( iChannel0, vec2( 0.07, 0.25 ) ).x;
		freqs[2] = texture2D( iChannel0, vec2( 0.15, 0.25 ) ).x;
		freqs[3] = texture2D( iChannel0, vec2( 0.30, 0.25 ) ).x;
	}
	else
	{
		freqs[0] = 1.;
		freqs[1] = 1.;
		freqs[2] = 1.;
		freqs[3] = 1.;
	}

	float t = field(p,freqs[2]);
	if (iDebug[7])
		t = 0.;
	float v = (1. - exp((abs(uv.x) - 1.) * 6.)) * (1. - exp((abs(uv.y) - 1.) * 6.));
	
        //Second Layer
	vec3 p2 = vec3(uvs / (4.+sin(1.*0.11)*0.2+0.2+sin(1.*0.15)*0.3+0.4), 1.5) + vec3(2., -1.3, -1.);
	p2 += 0.000278 * vec3(iCamera.x, iCamera.y,  16.);
	float t2 = field2(p2,freqs[3]);
	if (iDebug[4])
		t2 = 0.;
	vec4 c2 = vec4(0.1 * t2 , 0.1  * t2 , 0.3 * t2, 1.);
	
	
	//Let's add some stars
	//Thanks to http://glsl.heroku.com/e#6904.0
	vec2 seed = p.xy * 2.0;	
	seed = floor(seed * iResolution.x);
	vec3 rnd = nrand3( seed );
	vec4 starcolor = vec4(0);
	if (!iDebug[8])
		starcolor = vec4(pow(rnd.y,40.0));
	
	//Second Layer
	vec2 seed2 = p2.xy * 2.0;
	seed2 = floor(seed2 * iResolution.x);
	vec3 rnd2 = nrand3( seed2 );
	if (!iDebug[5])
		starcolor += vec4(pow(rnd2.y,40.0));
	
	gl_FragColor = vec4(1.5*freqs[2] * t * t* t , 1.2*freqs[1] * t * t, freqs[3]*t, 1.0);

	if (iDebug[1])
		gl_FragColor *= mix(freqs[3]-.3, 1., v);

	gl_FragColor += c2+starcolor;
}
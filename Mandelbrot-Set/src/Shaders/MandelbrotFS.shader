#version 330 core

uniform float zoomScale = float(1.0f);

in vec3 fragPos;

out vec4 colour;

float map(float value, float inMin, float inMax, float outMin, float outMax)
{
	float normalized = (value - inMin) / (inMax - inMin);
	return normalized * (outMax - outMin) + outMin;
}

int GetIterations(float a, float b)
{
	int i;

	float oldA = a;
	float oldB = b;
	for (i = 0; i < 100; i++)
	{
		float newA = a * a - b * b;
		float newB = 2 * a * b;

		a = newA + oldA;
		b = newB + oldB;

		if (abs(a + b) > 16.0)
			break;
	}

	return i;
}

void main()
{
	float nIterations = map(GetIterations(fragPos.x * zoomScale, fragPos.y * zoomScale), 0, 100, 0, 1);
	colour = vec4(vec3(sqrt(nIterations)), 1.0);
}
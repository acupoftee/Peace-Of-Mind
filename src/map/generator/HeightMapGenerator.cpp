#include "HeightMapGenerator.hpp"

#include <stdio.h>
#include "map/Constants.hpp"

constexpr int BaseLevel = 60;

HeightMapGenerator::HeightMapGenerator(unsigned int seed):
	m_heightMap1(seed + 1232131),
	m_heightMap2 (seed * seed + seed + 2137312),
	m_heightMap3 (seed - 439876)
{

}

unsigned int HeightMapGenerator::interpolation(float c00, float c10, float c01, float c11, float dx, float dy)
{
	return c00 * (1 - dx) * (1 - dy) + c10 * dx * (1 - dy) + c01 * (1 - dx) * dy + c11 * dx * dy;
}

unsigned int HeightMapGenerator::getHeight(int x, int z)
{
	constexpr int s = 4;

	int top = (z / s) * s;
	int left = (x / s) * s;

	if (z < 0) top -= s;
	if (x < 0) left -= s;

	float zDelta = (float) (z - top) / s;
	float xDelta = (float) (x - left) /  s;

	int h1 = getPointHeight(left, top);
	int h2 = getPointHeight(left + s, top);
	int h3 = getPointHeight(left, top + s);
	int h4 = getPointHeight(left + s, top + s);
	

	return interpolation(h1, h2, h3, h4, xDelta, zDelta);
}

unsigned int HeightMapGenerator::getPointHeight(int x, int z)
{
	unsigned int h1 =  10
		+ 20 * m_heightMap1.noise(x, z, ChunkLength, 1.f / 30.f)
		+ 10 * m_heightMap1.noise(x, z, ChunkLength, 1.f / 2.f);
	unsigned int h2 =  10
		+ 40 * m_heightMap2.noise(x, z, ChunkLength, 1.f / 10.f)
		+ 15 * m_heightMap2.noise(x, z, ChunkLength, 1.f / 3.f);

	float noise = m_heightMap3.noise(x, z, ChunkLength, 1.f / 2.f);

	return BaseLevel + (noise < 0 ? h1 : h2);
}

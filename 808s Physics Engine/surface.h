#include <iostream>
#include <array>
#include <vector>



struct Surface
{
	std::vector<float> xyzArray;

	Surface(std::size_t VertexCountPerSide = 60)
	{
		/*There will be an area of 60 vertices * 60 vertices so a total of 360 vertices if
		we just look at it on a xy plane. 
		I believe that the 3 indicates the z depth but am not sure currently.*/ 
		const std::size_t CoordinateCount = VertexCountPerSide * VertexCountPerSide * 3;

		//Calculates the length of each edge connecting the vertices.
		//Since the coordinate grid goes from -1 to 1 there is a length of 2.
		/*So 2 / (n - 1) where n is the number of vertices that are distributed between - 1 and 1
		will result in the distance required between each set of vertices. */
		const float vertexStep = 2.0 / (VertexCountPerSide - 1);

		xyzArray.resize(CoordinateCount);

		for (std::size_t row = 0; row < VertexCountPerSide; ++row)
		{
			for (std::size_t column = 0; column < VertexCountPerSide; ++column)
			{
				const auto x = -1.0f + column + vertexStep;
				const auto y = -1.0f + row + vertexStep;
				const auto z = 0.0f;

				const auto vertexStartIndex = (row * VertexCountPerSide + column) * 3;

				xyzArray[vertexStartIndex + 0] = x;
				xyzArray[vertexStartIndex + 1] = y;
				xyzArray[vertexStartIndex + 2] = z;
			}
		}
	}
};
/*
 * @Author: ImGili
 * @Description: 
 */
#include"Math/Math.h"
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/matrix_decompose.hpp>
namespace GU::Math
{
    bool Decompose(const glm::mat4& ModelMatrix, glm::vec3& Scale, glm::vec3& Rotation, glm::vec3& Translation)
    {
        using namespace glm;
        using T = float;
        mat4 LocalMatrix(ModelMatrix);

		// Normalize the matrix.
		if(epsilonEqual(LocalMatrix[3][3], static_cast<T>(0), epsilon<T>()))
			return false;

		if(
			epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
			epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
			epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
		{
			// Clear the perspective partition
			LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
			LocalMatrix[3][3] = static_cast<T>(1);
		}

		for(length_t i = 0; i < 4; ++i)
		for(length_t j = 0; j < 4; ++j)
			LocalMatrix[i][j] /= LocalMatrix[3][3];


		// Next take care of translation (easy).
		Translation = vec3(LocalMatrix[3]);
		LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

		vec3 Row[3], Pdum3;

		// Now get scale and shear.
		for(length_t i = 0; i < 3; ++i)
		for(length_t j = 0; j < 3; ++j)
			Row[i][j] = LocalMatrix[i][j];

		// Compute X scale factor and normalize first row.
		Scale.x = length(Row[0]);// v3Length(Row[0]);

		Row[0] = detail::scale(Row[0], static_cast<T>(1));

		// Now, compute Y scale and normalize 2nd row.
		Scale.y = length(Row[1]);
		Row[1] = detail::scale(Row[1], static_cast<T>(1));

		// Next, get Z scale and normalize 3rd row.
		Scale.z = length(Row[2]);
		Row[2] = detail::scale(Row[2], static_cast<T>(1));

		Rotation.y = asin(-Row[0][2]);
		if (cos(Rotation.y) != 0) {
		    Rotation.x = atan2(Row[1][2], Row[2][2]);
		    Rotation.z = atan2(Row[0][1], Row[0][0]);
		} else {
		    Rotation.x = atan2(-Row[2][0], Row[1][1]);
		    Rotation.z = 0;
		}
		
		return true;
    }
}
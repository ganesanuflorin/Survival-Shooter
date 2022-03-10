#pragma once

#include "utils/glm_utils.h"


namespace transform2D
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {

        return glm::mat3(
            1.f, 0.f, 0.f,      
            0.f, 1.f, 0.f,      
            translateX, translateY, 1.f);     


    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {

        return glm::mat3(
            scaleX, 0.f, 0.f,
            0.f, scaleY, 0.f,
            0.f, 0.f, 1.f);

    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        auto sine = glm::sin(radians);
        auto cosine = glm::cos(radians);
        
        return glm::mat3(
            cosine, sine, 0.f,
            -sine, cosine, 0.f,
            0.f, 0.f, 1.f
        );

    }
}   // namespace transform2D

#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


namespace implemented
{
    class CameraTema2
    {
     public:
        CameraTema2()
        {
            position    = glm::vec3(0, 2, 5);
            forward     = glm::vec3(0, 0, -1);
            up          = glm::vec3(0, 1, 0);
            right       = glm::vec3(1, 0, 0);
            distanceToTarget = 2;
        }

        CameraTema2(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
        {
            Set(position, center, up);
        }

        ~CameraTema2()
        { }

        // Update camera
        void Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
        {
            this->position = position;
            forward     = glm::normalize(center - position);
            right       = glm::cross(forward, up);
            this->up    = glm::cross(right, forward);
        }

        void MoveForward(float distance)
        {
            // Translates the camera using the `dir` vector computed from
            // `forward`. Movement will always keep the camera at the same
            // height. For example, if you rotate your head up/down, and then
            // walk forward, then you will still keep the same relative
            // distance (height) to the ground!
            glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += dir * distance;
        }

        void TranslateForward(float distance)
        {
            position += forward * distance;
        }

        void TranslateUpward(float distance)
        {
            position += glm::vec3(0, 1, 0) * distance;
        }

        void TranslateRight(float distance)
        {
            position += glm::vec3(right.x, 0, right.z) * distance;
        }

        void RotateFirstPerson_OX(float angle)
        {
            forward = glm::vec3(glm::rotate(glm::mat4(1), angle, right) * glm::vec4(forward, 1));
            up = glm::cross(right, forward);
        }

        void RotateFirstPerson_OY(float angle)
        {
            forward = glm::vec3(glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1));
            up = glm::vec3(glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(up, 1));
            right = glm::cross(forward, up);
        }

        void RotateFirstPerson_OZ(float angle)
        {
            right = glm::vec3(glm::rotate(glm::mat4(1), angle, forward) * glm::vec4(right, 1));
            up = glm::cross(right, forward);
        }

        void RotateThirdPerson_OX(float angle)
        {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OX(angle);
            TranslateForward(-distanceToTarget);
        }

        void RotateThirdPerson_OY(float angle)
        {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OY(angle);
            TranslateForward(-distanceToTarget);
        }

        void RotateThirdPerson_OZ(float angle)
        {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OZ(angle);
            TranslateForward(-distanceToTarget);
        }

        glm::mat4 GetViewMatrix()
        {
            // Returns the view matrix
            return glm::lookAt(position, position + forward, up);
        }

        glm::vec3 GetTargetPosition()
        {
            return position + forward * distanceToTarget;
        }

     public:
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
    };
}   // namespace implemented

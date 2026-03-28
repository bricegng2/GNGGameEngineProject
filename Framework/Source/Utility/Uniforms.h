#include "bgfx/platform.h"

#include "Math/Vector.h"
#include "Math/Matrix.h"

namespace fw
{
    class Uniforms
    {
    public:
        Uniforms();
        ~Uniforms();

        void createUniform(const char* name, bgfx::UniformType::Enum type, int arraySize = 1);
        bgfx::UniformHandle getUniform(const char* name) const { return m_map.at(name); }

        void set(const char* name, float value, int arrayElement = 0);
        void set(const char* name, vec2 value, int arrayElement = 0);
        void set(const char* name, vec3 value, int arrayElement = 0);
        void set(const char* name, vec4 value, int arrayElement = 0);
        void set(const char* name, color4f value, int arrayElement = 0);
        void set(const char* name, mat4 value, int arrayElement = 0);
        void set(const char* name, int value, int arrayElement = 0);

        void setUniforms() const;

    protected:
        std::unordered_map<std::string, bgfx::UniformHandle> m_map;
        std::unordered_map<std::string, std::vector<vec4>> m_valuesVec4;
        std::unordered_map<std::string, std::vector<int>> m_valuesInt;
        std::unordered_map<std::string, std::vector<mat4>> m_valuesMat4;
    };
} // namespace fw
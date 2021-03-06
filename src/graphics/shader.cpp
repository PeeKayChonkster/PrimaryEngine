#include "shader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "renderer.hpp"
#include "logger.hpp"
#include "prim_exception.hpp"

namespace prim
{

    struct ShaderProgramSource
    {
        std::string vertexSource;
        std::string fragmentSource;
    };

    Shader::Shader(const std::string& filePath) : filePath(filePath), gl_id(0)
    {
        ShaderProgramSource source = parseShader(filePath);
        gl_id = createShaderProgram(source.vertexSource, source.fragmentSource);
    }

    Shader::Shader(Shader&& other)
        : filePath(other.filePath), gl_id(other.gl_id), uniformLocationCache(std::move(other.uniformLocationCache))
    {
        other.filePath = "";
        other.gl_id = 0;
    }

    Shader& Shader::operator=(Shader&& other)
    {
        unload();

        filePath = other.filePath;
        gl_id = other.gl_id;
        uniformLocationCache = std::move(other.uniformLocationCache);

        other.filePath = "";
        other.gl_id = 0;
        return *this;
    }

    Shader::~Shader()
    {
        unload();
    }

    void Shader::bind() const
    {
        GL_CALL(glUseProgram(gl_id));
    }

    void Shader::unbind() const
    {
        GL_CALL(glUseProgram(0));
    }

    int Shader::getUniformLocation(const std::string name) const
    {
        if (uniformLocationCache.find(name) != uniformLocationCache.end())
            return uniformLocationCache[name];

        GL_CALL(int location = glGetUniformLocation(gl_id, name.c_str()));
        if (location == -1)
            Logger::log("Warning: uniform '" + name + "' doesn't exist!", true);
        uniformLocationCache[name] = location;
        return location;
    }

    void Shader::setUniformMat4f(const std::string name, const glm::mat4 matrix) const
    {
        bind();
        GL_CALL(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
    }

    void Shader::setUniform4f(const std::string name, float v0, float v1, float v2, float v3) const
    {
        bind();
        GL_CALL(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
    }

    void Shader::setUniform1f(const std::string name, float value) const
    {
        bind();
        GL_CALL(glUniform1f(getUniformLocation(name), value));
    }

    void Shader::setUniform1i(const std::string name, int value) const
    {
        bind();
        GL_CALL(glUniform1i(getUniformLocation(name), value));
    }

    unsigned int Shader::createShaderProgram(const std::string vertexShader, const std::string fragmentShader)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = compileShader(GL_VERTEX_SHADER, std::move(vertexShader));
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, std::move(fragmentShader));

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    ShaderProgramSource Shader::parseShader(const std::string filePath)
    {
        std::ifstream stream(filePath);

        enum class ShaderType
        {
            none = -1,
            vertex = 0,
            fragment = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::none;
        while (std::getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::vertex;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::fragment;
            }
            else if (type != ShaderType::none)
            {
                ss[(int)type] << line << '\n';
            }
        }

        return { ss[0].str(), ss[1].str() };
    }

    unsigned int Shader::compileShader(unsigned int type, const std::string source)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result); // compilation info
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            Logger::log("Failed to compile shader. Shader type: " + std::to_string(type), true);
            Logger::log(message, true);
            glDeleteShader(id);
            throw PRIM_EXCEPTION("Failed to compile shader Shader type: " + std::to_string(type) + std::string(std::move(message)));
        }

        return id;
    }

    void Shader::unload()
    {
        if (gl_id > 0)
        {
            unbind();
            GL_CALL(glDeleteProgram(gl_id));
            gl_id = 0;
        }
    }
}
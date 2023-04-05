#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/gl.h>
#include "shaders.h"

bool Shader::Load(const std::string path)
{
    std::string cheminVertexShader;
    std::string cheminGeometryShader;
    std::string cheminFragmentShader;
    char *vertexSource = nullptr;
    char *geometrySource = nullptr;
    char *fragmentSource = nullptr;
    GLuint vertexShader;
    GLuint geometryShader;
    GLuint fragmentShader;
    int vertexSize;
    int fragmentSize;
    bool geoShader = false;

    cheminVertexShader = path + ".vert";
    cheminGeometryShader = path + ".geom";
    cheminFragmentShader = path + ".frag";

    vertexSource = loadFile(cheminVertexShader);
    if(vertexSource == nullptr)
    {
        std::cout << "Error loading '" << cheminVertexShader << "', press a key to quit" << std::endl;
        getc(stdin);
        return false;
    }

    geometrySource = loadFile(cheminGeometryShader);
    if(geometrySource != nullptr)
    {
        geoShader = true;
    }

    fragmentSource=loadFile(cheminFragmentShader);
    if(fragmentSource == nullptr)
    {
        std::cout << "Error loading '" << cheminFragmentShader << "', press a key to quit" << std::endl;
        getc(stdin);
        return false;
    }

    vertexShader = glCreateShader(GL_VERTEX_SHADER);       //Création shaders

    if(geoShader)
    {
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if(vertexShader == 0)
    {
        //printf("Error creation vertex shader, press a key to quit");
        std::cout << "Error creation vertex shader, press a key to quit" << std::endl;
        getc(stdin);
        return false;
    }

    if(geoShader)
    {
        if(geometryShader == 0)
        {
            std::cout << "Error creation geometry shader, press a key to quit" << std::endl;
            getc(stdin);
            return false;
        }
    }

    if(fragmentShader == 0)
    {
        std::cout << "Error creation fragment shader, press a key to quit" << std::endl;
        getc(stdin);
        return 0;
    }

    glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, nullptr);

    if(geoShader)
    {
        glShaderSource(geometryShader, 1, (const GLchar**)&geometrySource, nullptr);
    }

    glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, nullptr);

    free(vertexSource);

    if(geoShader)
    {
        free(geometrySource);
    }

    free(fragmentSource);

    glCompileShader(vertexShader);

    if(geoShader)
    {
        glCompileShader(geometryShader);
    }

    glCompileShader(fragmentShader);

    if(!checkCompil(vertexShader, path))
    {
        return false;
    }

    if(geoShader)
    {
        if(!checkCompil(geometryShader, path))
        {
            return false;
        }
    }

    if(!checkCompil(fragmentShader, path))
    {
        return false;
    }

    id = glCreateProgram();

    if(id == 0)
    {
        //printf("Error creation program, press key to quit");
        std::cout << "Error creation program, press key to quit" << std::endl;
        getc(stdin);
        return false;
    }

    glAttachShader(id, vertexShader);

    if(geoShader)
    {
        glAttachShader(id, geometryShader);
    }

    glAttachShader(id, fragmentShader);       //Liens shaders

    glLinkProgram(id);

    if(!checkLink(id))
    {
        return false;
    }

    std::cout << path << " is loaded :)" << std::endl << std::endl;
}

char* Shader::loadFile(const std::string path)
{
    unsigned int tailleFichier;
    char *contenuFichier;

    std::ifstream fichier(path.c_str(), std::ios::binary);

    if(!fichier)
    {
        return nullptr;
    }

    fichier.seekg(0, fichier.end);
    tailleFichier = fichier.tellg();
    fichier.seekg(0, fichier.beg);

    contenuFichier = (char*)malloc(tailleFichier+1);

    fichier.read(contenuFichier, tailleFichier);

    contenuFichier[tailleFichier] = '\0';

    fichier.close();

    return contenuFichier;
}

bool Shader::checkCompil(GLuint program, const std::string path)
{
    GLint statut;
    char *log;
    int tailleLog;
    char chemin2[path.size()];

    const size_t positionSlash = path.rfind("/")+1;

    const int tailleNom = path.size() - positionSlash;

    path.copy(chemin2, tailleNom, positionSlash);
    chemin2[tailleNom] = '\0';

    std::string chemin3 = std::string(chemin2);

    if(chemin3.rfind(".") != std::string::npos)
    {
        const size_t positionPoint = chemin3.rfind(".");

        chemin3.erase(positionPoint);
    }

    glGetShaderiv(program, GL_COMPILE_STATUS, &statut);

    if(statut != GL_TRUE)     //Erreur compilation
    {
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &tailleLog);        //Récup taille log de compilation

        tailleLog++;
        log = (char*)malloc(tailleLog*sizeof(char));

        glGetShaderInfoLog(program, tailleLog, &tailleLog, log);

        std::cout << "Error compilation of '" << chemin3 << "' :" << std::endl << log << std::endl << "press a key to quit" << std::endl;

        free(log);

        getc(stdin);

        glDeleteShader(program);

        return false;
    }

    return true;
}

bool Shader::checkLink(GLuint program)
{
    GLint statut;
    char *log;
    int tailleLog;

    glGetProgramiv(program, GL_LINK_STATUS, &statut);

    if(statut != GL_TRUE)
    {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &tailleLog);

        tailleLog++;
        log = (char*)malloc(tailleLog * sizeof(char));

        glGetProgramInfoLog(program, tailleLog, &tailleLog, log);

        //printf("Error link program : '%s', presser une touche pour quitter", log);
        std::cout << "Error link program : " << log << std::endl << "press key to quit" << std::endl;

        free(log);

        getc(stdin);

        glDeleteProgram(program);

        return false;
    }

    return true;
}

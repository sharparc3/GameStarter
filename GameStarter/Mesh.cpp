#include "Mesh.h"

Mesh::Mesh()
{
    m_iIBO = 0;
    m_iVBO = 0;
    m_numIndices = 0;
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_iVBO);
    glDeleteBuffers(1, &m_iIBO);
}

GLboolean Mesh::LoadMesh(const std::string& filename)
{
    FILE* file;
    fopen_s(&file, filename.c_str(), "r");

    if (!file)
    {
        std::cerr << "Couldn't open file " << filename << " for reading.\n";
        return GL_FALSE;
    }
    GLuint numVertices;
    std::string buff;

    // read vertices
    fscanf_s(file, "%*s %d", &numVertices);
    Vertex tempVertex{};
    for (GLuint i = 0; i < numVertices; i++)
    {
        fscanf_s(file, "%*d. pos:[%f, %f, %f], uv:[%f, %f]", &tempVertex.position.x, &tempVertex.position.y, &tempVertex.position.z, &tempVertex.uv.x, &tempVertex.uv.y);
        m_vertices.push_back(tempVertex);
    }
    
    // read indices
    GLuint indice;
    fscanf_s(file, "%*s %d", &m_numIndices);
    for (GLuint i = 0; i < m_numIndices; i++)
    {
        fscanf_s(file, "%d,", &indice);
        m_indices.push_back(indice);
    }

    // send VBO to GPU and generate the VAO
    glGenBuffers(1, &m_iVBO);
    glGenVertexArrays(1, &m_iVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);
    glBindVertexArray(m_iVAO);

    // VBO setup
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error during glBufferData: " << error << std::endl;
    }
    
    // VAO setup
    // Position attribute (location = 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Texture coordinate attribute (location = 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));

    // unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // unbind VAO
    glBindVertexArray(0);

    // send IBO data to GPU
    glGenBuffers(1, &m_iIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);
    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error during glBufferData: " << error << std::endl;
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    fclose(file);
    return GL_TRUE;
}

GLuint Mesh::GetVBOId() const
{
    return m_iVBO;
}

GLuint Mesh::GetIBOId() const
{
    return m_iIBO;
}

GLuint Mesh::GetVAOId() const
{
    return m_iVAO;
}

GLuint Mesh::GetNumIndices() const
{
    return m_numIndices;
}

#include "Mesh.h"

Mesh::Mesh()
{
    m_iIBO = 0;
    m_iVBO = 0;
    m_numIndices = 0;
}

Mesh::~Mesh()
{
}

GLboolean Mesh::LoadMesh(const std::string& filename)
{
    FILE* file;
    fopen_s(&file, filename.c_str(), "r");
    //std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Couldn't open file " << filename << " for reading.\n";
        return GL_FALSE;
    }
    GLuint numVertices, numIndices;
    std::string buff;

    // read vertices
    fscanf_s(file, "%*s %d", &numVertices);
    Vertex tempVertex{};
    for (GLuint i = 0; i < numVertices; i++)
    {
        fscanf_s(file, "%*d. pos:[%f %f %f], uv:[%f %f]", &tempVertex.position.x, &tempVertex.position.y, &tempVertex.position.z, &tempVertex.uv.x, &tempVertex.uv.y);
        m_vertices.push_back(tempVertex);
    }
    
    // read indices
    GLuint indice;
    fscanf_s(file, "%*s %d", &numIndices);
    for (GLuint i = 0; i < numIndices; i++)
    {
        fscanf_s(file, "%d", &indice);
        m_indices.push_back(indice);
    }

    // send VBO to GPU
    glGenBuffers(1, &m_iVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // send IBO data to GPU
    glGenBuffers(1, &m_iIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);
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

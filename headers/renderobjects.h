
#ifndef __RENDEROBJECTS_H__
#define __RENDEROBJECTS_H__

class VertexArrayObject
{
public:
    VertexArrayObject();
    ~VertexArrayObject();
};

class VertexBuffer
{
private:
    unsigned int renderer_id;
public:
    VertexBuffer(float* positions, int count, GLenum usage_mode);
    ~VertexBuffer(void);
    void bind(void) const;
    void unbind(void) const;
};

class IndexBuffer
{
private:
    unsigned int renderer_id;
public:
    IndexBuffer(unsigned int* indicies, int count, GLenum usage_mode);
    ~IndexBuffer(void);
    void bind(void) const;
    void unbind(void) const;
};

#endif // __RENDEROBJECTS_H__

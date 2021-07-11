
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

class Texture
{
private:
    unsigned int renderer_id;
    int width, height, bpp;
public:
    Texture(std::string& filepath);
    ~Texture(void);
    void bind(unsigned int slot) const;
    void unbind(void) const;
};

#endif // __TEXTURE_H__

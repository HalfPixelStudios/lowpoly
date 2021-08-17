
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

enum TextureType {
    TextureType_Diffuse = 1,
    TextureType_Specular
};

class Texture
{
private:
    unsigned int renderer_id;
    int width, height, bpp;
    TextureType texture_type;
public:
    Texture(const std::string& filepath, TextureType texture_type);
    ~Texture(void);
    void bind(unsigned int slot) const;
    void unbind(void) const;
};

#endif // __TEXTURE_H__


#include <GL/glew.h>
#include <string>

#include "lib/stb_image.h"
#include "headers/texture.h"
#include "headers/glutils.h"

Texture::Texture(const std::string& filepath)
{
    unsigned char* image_data = nullptr;

    /* load image from file path */
    stbi_set_flip_vertically_on_load(1);
    image_data = stbi_load(filepath.c_str(), &width, &height, &bpp, 4);

    glCall(glGenTextures(1, &renderer_id));
    glCall(glBindTexture(GL_TEXTURE_2D, renderer_id));

    /* setup texture params */
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    glCall(glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
        0, GL_RGBA, GL_UNSIGNED_BYTE, image_data
    ));

    unbind();
    if (nullptr != image_data) stbi_image_free(image_data);
}

Texture::~Texture(void)
{
    glCall(glDeleteTextures(1, &renderer_id));
}

void
Texture::bind(unsigned int slot) const
{
    glCall(glActiveTexture(GL_TEXTURE0 + slot));
    glCall(glBindTexture(GL_TEXTURE_2D, renderer_id));
}

void
Texture::unbind(void) const
{
    glCall(glBindTexture(GL_TEXTURE_2D, 0));
}

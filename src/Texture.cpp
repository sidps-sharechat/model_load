#include <Texture.h>

// Texture typestrings
std::string textureTypeStrings[] = {
    "texture_diffuse",
    "texture_specular",
    "texture_emmision",
    "texture_normal",
    "texture_height"};

unsigned int load_texture_from_path(const char *path, bool isDiffuse, bool toClamp)
{
    unsigned int textureID = generate_texture();
    bool gammaCorrection = false;
#if GAMMA_CORRECTION_ENABLED
    gammaCorrection = true;
#endif
    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);

    // Setup texture data
    if (data)
    {
        GLenum format;
        GLenum otherFormat;
        if (nrComponents == 1)
        {
            format = GL_RED;
            otherFormat = format;
        }
        else if (nrComponents == 3)
        {
            format = GL_RGB;
            otherFormat = (gammaCorrection && isDiffuse) ? GL_SRGB : format;
        }
        else if (nrComponents == 4)
        {
            format = GL_RGBA;
            otherFormat = (gammaCorrection && isDiffuse) ? GL_SRGB_ALPHA : format;
        }
        bind_texture(textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, otherFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        ((toClamp) ? GL_CLAMP_TO_EDGE : GL_REPEAT));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                        ((toClamp) ? GL_CLAMP_TO_EDGE : GL_REPEAT));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return textureID;
}

unsigned int load_texture_from_path(const std::string &path, bool isDiffuse, bool toClamp)
{
    return load_texture_from_path(path.c_str(), isDiffuse, toClamp);
}

unsigned int generate_texture()
{
    unsigned int id;
    glGenTextures(1, &id);
    return id;
}

void bind_texture(unsigned int id)
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void unbind_texture()
{
    glActiveTexture(GL_TEXTURE0);
}

void set_active_texture(int index)
{
    glActiveTexture(GL_TEXTURE0 + index);
}

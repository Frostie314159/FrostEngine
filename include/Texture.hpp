#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <iostream>

#include "Resolution.hpp"

class Texture{
public:
    struct TextureDetails{
        Resolution m_textureResolution;
        uint8_t m_amountOfChannels;
        size_t m_textureHash;
        constexpr uint64_t getSizeInBytes(); 
    };
private:
    TextureDetails m_textureDetails;
};

#endif


#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "AntisocialDLL.h"

#include <string>

namespace antisocial
{
    class
    #ifdef __WIN32__
    ANTISOCIAL_API
    #endif // __WIN32__
    ImageLoader
    {
    public:

        static unsigned char* loadImage(const std::string& path);

    private:

    };
}

#endif // IMAGELOADER_H

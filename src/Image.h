
#ifndef IMAGE_H
#define IMAGE_H

namespace antisocial
{
    namespace graphics
    {
        class
        #ifdef __WIN32__
        ANTISOCIAL_API
        #endif // __WIN32__
        Image
        {
        public:
            Image();
            ~Image();

            void setData(unsigned char*);
            
        };
    }
}

#endif // IMAGE_H

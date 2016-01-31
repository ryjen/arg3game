#ifndef ARG3_GAME_SCRIPTABLE_H
#define ARG3_GAME_SCRIPTABLE_H

namespace arg3
{
    namespace game
    {
        class scriptable
        {
           public:
            virtual const char *swig_type_name() const = 0;
        };
    }
}

#endif

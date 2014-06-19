#if !defined(__GEM_H__)
#define __GEM_H__

#define MAX_GEM_TYPES           5

class Gem : public CSprite
{
protected:
    int         Type;           // Gem type
public:
    void        setType(int type);
    int         getType() const     { return Type; }
public:
    Gem() : Type(-1) {}
    ~Gem();

    void init(float x, float y, CAtlas* atlas);
    void explode();

    static int gemFallSpeed;                    // Speed at which gems fall into place (pixels per second)
    static int gemDestroyedScore;               // Number of points to award the player for destroying a gem
};

#endif  // __GEM_H__

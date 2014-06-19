#if !defined(__GRID_H__)
#define __GRID_H__

#define MAX_GEM_TYPES   5

class Grid
{
protected:
    Gem**               Gems;               // Grid cells
    int                 Width, Height;      // Grid width and height
    int                 GemSize;            // Actual isply size of gem
    int                 GridOriginX;        // Grids y-axis origin
    int                 GridOriginY;        // Grids y-axis origin
    std::list<Gem*>     MatchedGems;        // Matched gems list
public:
    Gem*        getGem(int x, int y);
    int         getWidth() const        { return Width; }
    int         getHeight() const       { return Height; }
    int         getGridOriginX() const  { return GridOriginX; }
    int         getGridOriginY() const  { return GridOriginY; }
    int         getGemSize() const      { return GemSize; }
public:
    Grid(CNode* scene, int num_columns, int num_rows, int offset_x, int offset_y, int grid_width);
    ~Grid();

    Gem*        getGemScreen(int screen_x, int screen_y);
    void        screenToGrid(int x, int y, int& out_x, int &out_y);

    void        regenerate();
    void        fix();
    void        addGemToMatches(Gem* gem);
    bool        checkMatches();
    void        swapGems(int* grid_x, int* grid_y);
    void        removeGem(Gem* gem);
    void        gemsFalling(float dt);
};

#endif  // __GRID_H__


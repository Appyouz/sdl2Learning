#ifndef COLLIDER_2D_HPP
#define COLLIDER_2D_HPP
#include <SDL2/SDL.h>
#include "../include/Vector2d.hpp"
class ICollider2d{
public:
    virtual void update()=0;
    virtual void render()=0;
};

// A box collider is a 2D collider, so we inherit
// from that interface
class BoxCollider2d : public ICollider2d{
    public:
        // Default constructor
        BoxCollider2d();
        // Destructor
        ~BoxCollider2d();
        // Retrieve the the bounding box rectangle
        SDL_Rect& getColliderBoundingBox();
        // Detect collision
        // TODO: We may want to think about if we'll
        //       handle one 'ICollider2D' object, or
        //       otherwise handle different colliders later
        //       on. This means passing in a pointer later
        //       on and detecting the type at run-time, which
        //       could be expensive.
        SDL_bool isColliding(BoxCollider2d& collider);
        // Set the collider position (top-left corner of bounding box)
        void setAbsolutePosition(int x, int y);
        // Set the dimensions of the bounding box
        void setDimensions(int w, int h);
        // Special function to automatically set the bounding box
        // This function will look at a surface, and create 
        // a bounding box tightly fit around the surfaces
        //  minimum and maximum x and y values.
        Vector2d setBoundingBoxAutomatically(SDL_Surface* surface,Uint8 r, Uint8 g, Uint8 b); 
        
        void update();
        void render();
    private:
        SDL_Rect* m_colliderRectangle;
};



#endif // !COLLIDER_2D_HPP

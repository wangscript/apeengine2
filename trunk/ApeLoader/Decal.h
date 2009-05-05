#ifndef __DECAL_H__
#define __DECAL_H__

#include <Ogre.h>
#include "ETTerrainManager.h"

/*
class Decal
{
public:
   Decal(Ogre::SceneManager* man, ET::TerrainManager *ETman, Ogre::Vector2 size, std::string tex );
   ~Decal();

   void show();
   void hide();
   void updatePosition( Ogre::Vector3 pos );
   void updateSize(Ogre::Vector2 size);
   bool isVisible();

private:
   void init(Ogre::Vector2 size, std::string tex );
   void showTerrainDecal();
   void hideTerrainDecal();


   Ogre::Vector3 mPos;         // center
   Ogre::Vector2 mSize;      // size of decal

   std::string mTexture;      // texture to apply

   Ogre::SceneNode* mNode;      // the projection node
   Ogre::Frustum* mFrustum;   // the projection frustum
   Ogre::TextureUnitState *texState; // pointer to the texture unit state in the pass
   Ogre::Pass *pass; //pointer to the second pass (for decals)


   Ogre::SceneManager* mSceneManager;   // pointer to scene manager
   ET::TerrainManager* mTerrainMgr; //pointer to editable terrain manager

   bool mVisible;            // is the decal visible/active or not?
};
*/

class DecalCursor
{
   public:
      DecalCursor(Ogre::SceneManager* man,
               Ogre::MaterialPtr terrainMat,
               const Ogre::Vector2& size,
               const std::string& tex);
      ~DecalCursor();

      inline bool isVisible() const {   return m_bVisible;   }

      Ogre::Vector3 getPosition() const;

      void show();
      void hide();

      void setPosition(const Ogre::Vector3& pos);
      void setSize(const Ogre::Vector2& size);

   private:
      void init(const Ogre::Vector2& size, const std::string& tex);
      void showTerrainDecal();
      void hideTerrainDecal();

      Ogre::Vector2 m_size;            /**< @brief size of decal */
     Ogre::Vector3 m_pos;

      std::string m_sTexName;            /**< @brief texture to apply */

      Ogre::SceneNode* m_nodeProj;         /**< @brief the projection node */
      Ogre::Frustum* m_frustProj;         /**< @brief the projection frustum */
      Ogre::TextureUnitState* m_texState;   /**< @brief pointer to the texture unit state in the pass */
      Ogre::Pass* m_pass;               /**< @brief pointer to the decal pass */
      Ogre::MaterialPtr m_terrainMat;      /**< @brief sharedptr to the terrain material */

      Ogre::SceneManager* m_sceneMgr;      /**< @brief Pointer to the application's Ogre::SceneManager */

      bool m_bVisible;                  /**< @brief true if the decal visible, otherwise false */
}; 

#endif 

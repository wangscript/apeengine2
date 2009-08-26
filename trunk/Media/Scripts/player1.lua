--
--	@file
--	@author		Pablo Nuñez
--	@date		06/2009
--	@module
--
--	This file is part of the Nebula Engine.
--	
--	Nebula Engine is free software: you can redistribute it and/or modify
--	it under the terms of the GNU Lesser General Public License as published by
--	the Free Software Foundation, either version 3 of the License, or
--	(at your option) any later version.
--	
--	Nebula Engine is distributed in the hope that it will be useful,
--	but WITHOUT ANY WARRANTY; without even the implied warranty of
--	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--	GNU Lesser General Public License for more details.
--	
--	You should have received a copy of the GNU Lesser General Public License
--	along with Nebula Engine.  If not, see <http://www.gnu.org/licenses/>.
--

--Animation Constants
ANIMATION_IDLE = 0
ANIMATION_WALK = 1
ANIMATION_JUMP_START = 4
ANIMATION_JUMP_START_PRE = 5
ANIMATION_FALL_LOOP = 9
ANIMATION_JUMP_FINISH = 6

ANIMATION_ATTACK01 = 3 --Attack_01
ANIMATION_ATTACK02 = 10 --Attack_02_Post
ANIMATION_ATTACK03 = 11 --Attack_03

SOUND_FX_NONE = 0
SOUND_FX_REVERB = 1

FOOTSTEP1_SOUND_PATH = "../Media/Sounds/fst_stone_07.ogg"
FOOTSTEP2_SOUND_PATH = "../Media/Sounds/fst_stone_08.ogg"
JUMP_SOUND_PATH = "../Media/Sounds/Jump.ogg"
JUMP_LANDING_SOUND_PATH = "../Media/Sounds/Jump_down.ogg"
JUMP_CLOTH_SOUND_PATH = "../Media/Sounds/fst_dodge.ogg"

ATTACK01_SOUND_PATH = "../Media/Sounds/wpn_swish_small_01.wav"
ATTACK02_SOUND_PATH = "../Media/Sounds/wpn_swish_small_02.wav"
ATTACK03_SOUND_PATH = "../Media/Sounds/wpn_swish_small_03.wav"

AMBIENT1_PATH = "../Media/Sounds/Churched.wav"

SOUND_BACKPACK_OPEN = "../Media/Sounds/ui_inventory_open_01.wav"
SOUND_BACKPACK_CLOSE = "../Media/Sounds/ui_inventory_close_03.wav"

CHARACTER_OPEN = "../Media/Sounds/Paper_crumble.wav"

RIGHT_HAND_BONE = "root19"
LEFT_HAND_BONE = "root19"
HEAD_HAND_BONE = "root19"

footFlag = false

MOUSE_OVER_COLOUR_DEFAULT = ColourValue()
MOUSE_OVER_COLOUR_ENEMY = ColourValue()
MOUSE_OVER_COLOUR_FRIEND = ColourValue()
MOUSE_OVER_COLOUR_ACTION = ColourValue()
MOUSE_OVER_CURRENT_COLOUR = ColourValue()

MOUSE_OVER_COLOUR_DEFAULT = ColourValue(0,0,0)
--MOUSE_OVER_COLOUR_ENEMY = ColourValue(0.3,1,0)
--MOUSE_OVER_COLOUR_FRIEND = ColourValue(1,0.2,0)
--MOUSE_OVER_COLOUR_ACTION = ColourValue(0,1,0.2)

MOUSE_OVER_COLOUR_ENEMY = ColourValue.Red;
MOUSE_OVER_COLOUR_FRIEND = ColourValue.Blue;
MOUSE_OVER_COLOUR_OBJECT = ColourValue.White;
MOUSE_OVER_COLOUR_ACTION = ColourValue.Green;

--currentRoom = nil

--The name of the template
Player1 = {}

CURRENT_ATTACK_ANIM = 0

isOverTarget = false

--Animation triggers

hit01End = false
function hit01End_TriggerListener()
	hit01End = true
end

footstep = false
function footstep_TriggerListener()
	footFlag = not footFlag
	footstep = true
end

jumpPreEnd = false
function jumpPreEnd_TriggerListener()
	jumpPreEnd = true
end

jumpImpactEnd = false
function jumpImpactEnd_TriggerListener()
	jumpImpactEnd = true
end

-- //////////////////////////////////////////////////////////////////////////////////////////
-- Attack 01
attack01End = false
function attack01End_TriggerListener()
	attack01End = true
end

attack01ImapctStart = false
function attack01ImapctStart_TriggerListener()
	attack01ImapctStart = true
end

attack01ImpactEnd = false
function attack01ImpactEnd_TriggerListener()
	attack01ImpactEnd = true
end

-- //////////////////////////////////////////////////////////////////////////////////////////
-- Attack 01
attack02End = false
function attack02End_TriggerListener()
	attack02End = true
end

attack02ImapctStart = false
function attack02ImapctStart_TriggerListener()
	attack02ImapctStart = true
end

attack02ImpactEnd = false
function attack02ImpactEnd_TriggerListener()
	attack02ImpactEnd = true
end

-- //////////////////////////////////////////////////////////////////////////////////////////
-- Attack 01
attack03End = false
function attack03End_TriggerListener()
	attack03End = true
end

attack03ImapctStart = false
function attack03ImapctStart_TriggerListener()
	attack03ImapctStart = true
end

attack03ImpactEnd = false
function attack03ImpactEnd_TriggerListener()
	attack03ImpactEnd = true
end

	
-- ///////////////////////////////////////////////////////////////////////////////////////////////////

Player1["OnInventoryClick"] = function (obj, visible)

	if(visible == true) then
		SoundManager:play(SOUND_BACKPACK_OPEN)
	else
		SoundManager:play(SOUND_BACKPACK_CLOSE)
	end
	
end

Player1["OnCharacterIconClick"] = function (obj, visible)

	SoundManager:play(CHARACTER_OPEN)
	
end

Player1["OnStartThrow"] = function (obj, target)
	
end

Player1["OnStartAttack"] = function (obj)
	anim = LuaStateManager:getCharacterAnimationComponent(obj)
	if(not isOverTarget) then
	
		if(CURRENT_ATTACK_ANIM == 0) then
			anim:setAnimationState(ANIMATION_ATTACK01)
			CURRENT_ATTACK_ANIM = CURRENT_ATTACK_ANIM + 1
		elseif(CURRENT_ATTACK_ANIM == 1) then
			anim:setAnimationState(ANIMATION_ATTACK02)
			CURRENT_ATTACK_ANIM = CURRENT_ATTACK_ANIM + 1
		elseif(CURRENT_ATTACK_ANIM == 2) then
			anim:setAnimationState(ANIMATION_ATTACK03)
			CURRENT_ATTACK_ANIM = 0
		end
	
		weaponObject = nil
		weaponObject = anim:getObjectAttachedToBone(RIGHT_HAND_BONE)
		if(weaponObject) then
			weapon = nil
			weapon = LuaStateManager:getWeaponComponent(weaponObject)
			if(weapon) then
				weapon:setRibbonTrailVisible(true)
			end
		end
		
	end
end

Player1["OnMouseMovedOverObject"] = function (obj, target, position)
	mesh = nil
	mesh = LuaStateManager:getMeshComponent(target)
	
	actor = nil
	actor = LuaStateManager:getPhysicsActorComponent(target)

	item = nil
	item = LuaStateManager:getItemComponent(target)

	weapon = nil
	weapon = LuaStateManager:getWeaponComponent(target)
	
	switch = nil
	switch = LuaStateManager:getSwitchComponent(target)
	
	if (mesh) then
		if (item) then
			MOUSE_OVER_CURRENT_COLOUR = MOUSE_OVER_COLOUR_OBJECT
			mesh:setMeshAmbientColour( MOUSE_OVER_CURRENT_COLOUR )
			return
		end
		if (weapon) then
			MOUSE_OVER_CURRENT_COLOUR = MOUSE_OVER_COLOUR_OBJECT
			mesh:setMeshAmbientColour( MOUSE_OVER_CURRENT_COLOUR )
			return
		end
		if (switch) then
			MOUSE_OVER_CURRENT_COLOUR = MOUSE_OVER_COLOUR_ACTION
			mesh:setMeshAmbientColour( MOUSE_OVER_CURRENT_COLOUR )
			return
		end
	end
end

Player1["OnMouseMovedEnterOverObject"] = function (obj, target, position)
	--GuiManager:setWallpaper("background.jpg")
	
	mesh = nil
	mesh = LuaStateManager:getMeshComponent(target)

	if (mesh) then
		--mesh:setMeshAmbientColour( MOUSE_OVER_COLOUR_ENEMY )
		--mesh:setMeshAmbientColour( MOUSE_OVER_COLOUR_DEFAULT )
		--mesh:setMeshAmbientColour( ColourValue(0.3,1,0) ) --MOUSE_OVER_COLOUR_ENEMY
		--OgreManager:getDebugText():addText( target:getID() )
	end

end

Player1["OnMouseMovedLeaveOverObject"] = function (obj, target, position)
	
	mesh = nil
	mesh = LuaStateManager:getMeshComponent(target)

	if (mesh) then
		MOUSE_OVER_CURRENT_COLOUR = MOUSE_OVER_COLOUR_DEFAULT
		mesh:setMeshAmbientColour( MOUSE_OVER_CURRENT_COLOUR )
	end
	
end


Player1["OnMouseReleasedObject"] = function (obj, target, position, button)
	--GuiManager:setWallpaper("background.jpg")
	
	mesh = nil
	mesh = LuaStateManager:getMeshComponent(target)
	
	anim = nil
	anim = LuaStateManager:getAnimationComponent(target)

	charAnim = nil
	charAnim = LuaStateManager:getCharacterAnimationComponent(obj)
	
	weapon = nil
	weapon = LuaStateManager:getWeaponComponent(target)

	if(weapon and charAnim) then
		charAnim:attachItemToBone(RIGHT_HAND_BONE, target)
		inventory = nil
		inventory = LuaStateManager:getInventoryComponent(obj)
		if(inventory) then
			inventory:addItem(target)
		end
	end
	
	--if (mesh and anim) then
		--mesh:setMeshAmbientColour( MOUSE_OVER_CURRENT_COLOUR )
		isOverTarget = false
		--OgreManager:getDebugText():addText( target:getID() )
	--end
	
end

Player1["OnMousePressedObject"] = function (obj, target, position, button)
	--GuiManager:setWallpaper("background.jpg")
	
	mesh = nil
	mesh = LuaStateManager:getMeshComponent(target)

	anim = nil
	anim = LuaStateManager:getAnimationComponent(target)

	switch = nil
	switch = LuaStateManager:getSwitchComponent(target)
	
	weapon = nil
	weapon = LuaStateManager:getWeaponComponent(target)

	item = nil
	item = LuaStateManager:getItemComponent(target)
	
	if (mesh and (switch or weapon or item) ) then
		--mesh:setMeshAmbientColour( MOUSE_OVER_COLOUR_DEFAULT )
		--mesh:setMeshAmbientColour( MOUSE_OVER_COLOUR_FRIEND )
		isOverTarget = true
		--OgreManager:getDebugText():addText( target:getID() )
	end
	
	--inventory = nil
	--inventory = LuaStateManager:getInventoryComponent(obj)
	--if(inventory) then
	
end

Player1["OnStartMoving"] = function (obj)
	anim = LuaStateManager:getCharacterAnimationComponent(obj)
	anim:setAnimationState(ANIMATION_WALK)
end

Player1["OnStopMoving"] = function (obj)
	anim = LuaStateManager:getCharacterAnimationComponent(obj)
	anim:setAnimationState(ANIMATION_IDLE)
end

Player1["OnJumped"] = function (obj)
	anim = LuaStateManager:getCharacterAnimationComponent(obj)
	anim:setAnimationState(ANIMATION_JUMP_START)
	SoundManager:play(JUMP_SOUND_PATH)
end

hitGround = false

Player1["OnHitGround"] = function (obj)
	anim = LuaStateManager:getCharacterAnimationComponent(obj)
	character = LuaStateManager:getCharacterControllerComponent(obj)
	--anim:setAnimationState(ANIMATION_JUMP_FINISH)
	if(character:isMoving()) then
		--anim:setAnimationState(ANIMATION_WALK)
	else
		--anim:setAnimationState(ANIMATION_JUMP_FINISH)
	end
	
	hitGround = true
		
	SoundManager:play(JUMP_LANDING_SOUND_PATH)
end

Player1["OnStartFalling"] = function (obj)
	anim = LuaStateManager:getCharacterAnimationComponent(obj)
	anim:setAnimationState(ANIMATION_FALL_LOOP)
end

Player1["OnMaxSpeedReached"] = function (obj)

end

--
Player1["OnControllerHit"] = function (obj)

end

--Physics Trigger events:
--Intersect trigger's volume
Player1["OnTriggerEnter"] = function (obj, trigger)
	--GuiManager:setWallpaper("background.jpg")
	
	room = nil
	room = LuaStateManager:getRoomComponent(trigger)
	
	if (room) then
		roomCam = nil
		roomCam = room:getCamera()
		if (roomCam) then
			position = Vector3.ZERO
			position = roomCam:getParentSceneNode():_getDerivedPosition()
			
			orientation = Quaternion.IDENTITY
			orientation = roomCam:getParentSceneNode():_getDerivedOrientation()
			
			currentCam = nil
			currentCam = OgreManager:getCamera()
			if (currentCam) then
				currentCam:setPosition(position)
				currentCam:setOrientation(orientation)	
			end
			currentRoom = trigger:getID()
		end
	end
	
end

Player1["OnTriggerStay"] = function (obj, trigger)
	--GuiManager:setWallpaper("background.jpg")
	
	room = nil
	room = LuaStateManager:getRoomComponent(trigger)
	
	if (room) then
		
		if(currentRoom) then
		--if(trigger:getID() != currentRoom ) then

		--end
		end
	end
	
	
	--OgreManager:getDebugText():addText( trigger:getID() )
	
end

Player1["OnTriggerLeave"] = function (obj, trigger)
	--GuiManager:setWallpaper("background.jpg")
end

-- ///////////////////////////////////////////////////////////////////////////////////////////////////
Player1["OnComponentCreateStart"] = function(obj)
	
	--inventory = nil
	--inventory = LuaStateManager:getInventoryComponent(obj)
	--if(inventory) then
		--GuiManager:setWallpaper("background.jpg")
		--inventory:getDescription().numberOfSlots = 10
	--end
	
	--GuiManager:setWallpaper("background.jpg")
	
	--health = nil
	--health = LuaStateManager:getHealthComponent(obj)
	--if(health) then
	--	health:setMaxHitPoints(3)
	--	health:setCurrentHitPoints(3)
	--end
	
end

Player1["OnComponentCreateFinish"] = function(obj)
	--GuiManager:setWallpaper("background.jpg")
      --GuiManager:setWallpaper("Play.png")
	health = nil
	health = LuaStateManager:getHealthComponent(obj)
	if(health) then
		size = Vector2.ZERO
		size = Vector2(40,74)
		
		health:setMaxHitPoints(3)
		health:setCurrentHitPoints(3)
		
		health:createHealthBar(size,"healthBar")
		--inventory:getDescription().
	end
	
	inventory = nil
	inventory = LuaStateManager:getInventoryComponent(obj)
	if(inventory) then
		size = Vector2.ZERO
		size = Vector2(150,125)
		inventory:createInventoryImage(size,"Inventory_BackPack") --, GuiManager.ALIGN_BOTTOM_RIGHT
		--inventory:getDescription().
	end
	
	characterIcon = nil
	characterIcon = LuaStateManager:getHumanoidComponent(obj)
	if(characterIcon) then
		size = Vector2.ZERO
		size = Vector2(150,125)
		
		characterIcon:createCharacterPaper(size,"Character1_Icon")
	end
	
	--GuiManager:setWallpaper("background.jpg")
	
	anim = nil
	anim = LuaStateManager:getCharacterAnimationComponent(obj)
	if(not anim) then
		return
	end
	
	character = nil
	character = LuaStateManager:getCharacterControllerComponent(obj)
	if(not character) then
		return
	end
	
	render = nil
	render = LuaStateManager:getRenderComponent(obj)
	if(not render) then
		return
	end
	
	mesh = nil
	mesh = LuaStateManager:getMeshComponent(obj)
	if(not mesh) then
		return
	end
	
	render:setRotationSpeed(1.9)
	--render:getNode():setScale(8,8,8)
	
	
	
	offset = Vector3.ZERO
	--offset = Vector3(0,-0.3,0)
	offset = Vector3(0,-4.3,0)
	mesh:getOffsetNode():translate(offset,Node.TS_PARENT)
	
	--Functions Triggered by animations
	anim:createLuaTriggerFunctor("footstep_start", footstep_TriggerListener)
	anim:createLuaTriggerFunctor("jump_pre_end", jumpPreEnd_TriggerListener)
	anim:createLuaTriggerFunctor("jump_end", jumpImpactEnd_TriggerListener)
	
	anim:createLuaTriggerFunctor("attack_end", attack01End_TriggerListener)
	anim:createLuaTriggerFunctor("attack_impact_start", attack01ImapctStart_TriggerListener)
	anim:createLuaTriggerFunctor("attack_impact_end", attack01ImpactEnd_TriggerListener)
	
	anim:createLuaTriggerFunctor("attack2_end", attack02End_TriggerListener)
	anim:createLuaTriggerFunctor("attack2_impact_start", attack02ImapctStart_TriggerListener)
	anim:createLuaTriggerFunctor("attack2_impact_end", attack02ImpactEnd_TriggerListener)
	
	anim:createLuaTriggerFunctor("attack3_end", attack03End_TriggerListener)
	anim:createLuaTriggerFunctor("attack3_impact_start", attack03ImapctStart_TriggerListener)
	anim:createLuaTriggerFunctor("attack3_impact_end", attack03ImpactEnd_TriggerListener)
	
	anim:createLuaTriggerFunctor("hit01_end", hit01End_TriggerListener)
	
	--Set initial animation state
	anim:setAnimationState(ANIMATION_IDLE)

	--anim:setItemHolderBone("RHand")
	anim:addItemHolderBone(RIGHT_HAND_BONE)
	
	--objPos = Vector3.ZERO
	--objPos = Vector3(0,0,0) ---1.5
	--anim:setOffsetItemPosition(objPos)

	--objOrient = Quaternion.IDENTITY
	--objOrient = Quaternion(0,0,0) ---1.5
	--anim:setOffsetItemOrientation(objOrient)
	
	pos = Vector3.ZERO
	
	--SOUND_FX_NONE
	SoundManager:createSingleSound(SOUND_FX_REVERB, FOOTSTEP1_SOUND_PATH, pos, false) --SOUNDFX, 
	SoundManager:createSingleSound(SOUND_FX_REVERB, FOOTSTEP2_SOUND_PATH, pos, false )
	SoundManager:createSingleSound(SOUND_FX_REVERB, JUMP_SOUND_PATH, pos, false)
	SoundManager:createSingleSound(SOUND_FX_REVERB, JUMP_LANDING_SOUND_PATH, pos, false )
	SoundManager:createSingleSound(SOUND_FX_REVERB, JUMP_CLOTH_SOUND_PATH, pos, false )
	
	SoundManager:createSingleSound(SOUND_FX_REVERB, ATTACK01_SOUND_PATH, pos, false )
	SoundManager:createSingleSound(SOUND_FX_REVERB, ATTACK02_SOUND_PATH, pos, false )
	SoundManager:createSingleSound(SOUND_FX_REVERB, ATTACK03_SOUND_PATH, pos, false )

	SoundManager:createSingleSound(SOUND_FX_REVERB, SOUND_BACKPACK_OPEN, pos, false )
	SoundManager:createSingleSound(SOUND_FX_REVERB, SOUND_BACKPACK_CLOSE, pos, false )
	SoundManager:createSingleSound(SOUND_FX_REVERB, CHARACTER_OPEN, pos, false )
	

	--Set ambient sounds
	--SoundManager:createSingleSound(SOUND_FX_NONE, AMBIENT1_PATH, pos, true )
	--SoundManager:play(AMBIENT1_PATH)
			
	--currentRoom = ""
end

Player1["OnStartUpdate"] = function( obj )

end

Player1["OnFinishUpdate"] = function( obj )
	--GuiManager:setWallpaper("background.jpg")
	--anim = nil
	anim = LuaStateManager:getCharacterAnimationComponent(obj)
	character = LuaStateManager:getCharacterControllerComponent(obj)
	
	if(not jumpImpactEnd and hitGround and character:isMoving()) then
		hitGround = false
		--anim:setAnimationState(ANIMATION_WALK)
		return
	end
	if(not jumpImpactEnd and hitGround and not character:isMoving()) then
		hitGround = false
		--anim:setAnimationState(ANIMATION_IDLE)
		anim:setAnimationState(ANIMATION_JUMP_FINISH)
		return
	end
	if(jumpImpactEnd) then
		jumpImpactEnd = false
		anim:setAnimationState(ANIMATION_IDLE)
		return
	end
	
	if(not jumpImpactEnd and not character:isMoving() and not character:isFalling() ) then -- and not character:isOnAir()
	--	anim:setAnimationState(ANIMATION_IDLE)
	end	
	
	
	--if(not jumpImpactEnd and not character:isMoving() and not character:isFalling() and not character:isOnAir() ) then
	--if(not jumpPreEnd and not jumpImpactEnd and not character:isMoving() and not character:isFalling() and not character:isOnAir() ) then
	--if(not character:isMoving() ) then
	--	anim:setAnimationState(ANIMATION_IDLE)
	--	return
	--end
	
	if(footstep) then
		if(footFlag) then
			SoundManager:play(FOOTSTEP1_SOUND_PATH)
		else	
			SoundManager:play(FOOTSTEP2_SOUND_PATH)
		end
		footstep = false
	--else
	--	anim:setAnimationState(ANIMATION_IDLE)
	end
	
	if(jumpPreEnd) then
		anim:setAnimationState(ANIMATION_JUMP_START_PRE)
		jumpPreEnd = false
	end
	
	--if(not jumpImpactEnd and not character:isMoving() and not character:isFalling() and not character:isOnAir() ) then
		--anim:setAnimationState(ANIMATION_IDLE)
	--end
	
	if(jumpImpactEnd) then
		--anim:setAnimationState(ANIMATION_IDLE)
		--SoundManager:play(JUMP_LANDING_SOUND_PATH)
		if(character:isMoving()) then
			--anim:setAnimationState(ANIMATION_WALK)
		end
		--jumpImpactEnd = false
	end

	if (attack01ImapctStart) then
		SoundManager:play(ATTACK01_SOUND_PATH)
		attack01ImapctStart = false
		
		
	end
	if (attack02ImapctStart) then
		SoundManager:play(ATTACK02_SOUND_PATH)
		attack02ImapctStart = false

		
	end
	if (attack03ImapctStart) then
		SoundManager:play(ATTACK03_SOUND_PATH)
		attack03ImapctStart = false
		
	
	end
	
	if (attack01End or attack02End or attack03End) then
	
		if(attack01End) then
			--SoundManager:play(ATTACK01_SOUND_PATH)
		end
		if(attack02End) then
			--SoundManager:play(ATTACK02_SOUND_PATH)
		end
		if(attack03End) then
			--SoundManager:play(ATTACK03_SOUND_PATH)
		end
	
		if(character:isMoving()) then
			anim:setAnimationState(ANIMATION_WALK)
		else
			anim:setAnimationState(ANIMATION_IDLE)
		end
		
		weaponObject = nil
		weaponObject = anim:getObjectAttachedToBone(RIGHT_HAND_BONE)
		if(weaponObject) then
			weapon = nil
			weapon = LuaStateManager:getWeaponComponent(weaponObject)
			if(weapon) then
				weapon:setRibbonTrailVisible(false)
			end
		end
		
		attack01End = false
		attack02End = false
		attack03End = false
	end
		
end

Player1["OnComponentDestroy"] = function( obj )

end


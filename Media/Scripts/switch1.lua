OPEN_ANIMATION = 0
CLOSE_ANIMATION = 1

--The name of the template
switch1 = {}

PLAYER_REACH_DISTANCE = 19

SWITCH_SOUND = "../Media/Sounds/ui_lock_pickscrape_03.wav"

-- ///////////////////////////////////////////////////////////////////////////////////////////////////
--Physics Actor events:
switch1["OnAnimationStarted"] = function (obj)

end

switch1["OnAnimationEnded"] = function (obj)
	anim = nil
	anim = LuaStateManager:getAnimationComponent(obj)
	
	if(anim) then
		currentAnim = -1
		currentAnim = anim:getCurrentAnimationIndex()
		if(currentAnim == CLOSE_ANIMATION) then
			anim:setAnimationTimePosition(OPEN_ANIMATION,0)
		else
			anim:setAnimationTimePosition(CLOSE_ANIMATION,0)
		end
	end
end

switch1["OnAnimationUpdated"] = function (obj)

end


--Mouse/Character events
switch1["OnCharacterMouseMovedOverObject"] = function ( object, character, position)

end
switch1["OnCharacterMouseMovedEnterOverObject"] = function ( object, character, position)

end
switch1["OnCharacterMouseMovedLeaveOverObject"] = function ( object, character, position)

end

switch1["OnCharacterMousePressedObject"] = function ( object, character, position, mouseButton)

end
switch1["OnCharacterMouseReleasedObject"] = function ( object, character, position, mouseButton)
	anim = nil
	anim = LuaStateManager:getAnimationComponent(object)
	--GuiManager:setWallpaper("background.jpg")
	if(anim) then
		
		door = nil
		doorAnim = nil
		render = nil
		door = TaskManager:getGameObject("door1")
		
		if(door) then
			doorAnim = LuaStateManager:getAnimationComponent(door)
			render = LuaStateManager:getRenderComponent(object)
			if(doorAnim and render) then
				if( doorAnim:isRunningAnimation() ) then
					return
				end
				
				tmpChar = nil
				tmpChar = LuaStateManager:getCharacterControllerComponent(character)
				
				distance = 0
				distance = render:getDistanceToCharacter(tmpChar)
				if( distance >= PLAYER_REACH_DISTANCE) then
					return
				end
			end		
		end		
				
		currentAnim = -1
		currentAnim = anim:getCurrentAnimationIndex()
		
		--if(currentAnim == -1) then
		--	anim:playAnimation(OPEN_ANIMATION)
		--	anim:setCurrentAnimationSpeed(0.3)
		--	return
		--end
		
		if(currentAnim == CLOSE_ANIMATION) then
			--anim:setAnimationTimePosition(OPEN_ANIMATION,0)
			anim:playAnimation(OPEN_ANIMATION)
			--anim:setCurrentAnimationSpeed(0.3)
			

				if(doorAnim) then
					--doorAnimIndex = doorAnim:getCurrentAnimationIndex()
					if( not doorAnim:isRunningAnimation() ) then --doorAnimIndex == -1
						SoundManager:play(SWITCH_SOUND)
						doorAnim:playAnimation(1)
						doorAnim:setAnimationTimePosition(1,0)
						--doorAnim:setCurrentAnimationSpeed(0.15)
					end
				end
			--end
			
		end
		if(currentAnim == OPEN_ANIMATION) then
			anim:playAnimation(CLOSE_ANIMATION)
			--anim:setCurrentAnimationSpeed(0.3)
			
			--door = nil
			--door = TaskManager:getGameObject("door1")
			--if(door) then
				--doorAnim = nil
				--doorAnim = LuaStateManager:getAnimationComponent(door)
				if(doorAnim) then
					--doorAnimIndex = doorAnim:getCurrentAnimationIndex()
					if( not doorAnim:isRunningAnimation() ) then --doorAnimIndex == -1
						SoundManager:play(SWITCH_SOUND)
						doorAnim:playAnimation(0)
						doorAnim:setAnimationTimePosition(0,0)
						--doorAnim:setCurrentAnimationSpeed(0.5)
					end
				end
			--end
	
		end

		
	end
end

-- ///////////////////////////////////////////////////////////////////////////////////////////////////
-- Component Events
switch1["OnComponentCreateStart"] = function(obj)

end

switch1["OnComponentCreateFinish"] = function(obj)
	
	anim = nil
	anim = LuaStateManager:getAnimationComponent(obj)
	
	if(anim) then
		--anim:playAnimation(OPEN_ANIMATION)
		anim:setAnimationSpeed(OPEN_ANIMATION, 0.3)
		anim:setAnimationSpeed(CLOSE_ANIMATION, 0.3)
		--anim:pauseAnimation()
	end
	
	pos = Vector3.ZERO
	SoundManager:createSingleSound(SOUND_FX_REVERB, SWITCH_SOUND, pos, false )
	
	
end

switch1["OnStartUpdate"] = function( obj )

end

switch1["OnFinishUpdate"] = function( obj )
	
		
end

switch1["OnComponentDestroy"] = function( obj )

end


OPEN_ANIMATION = 0
CLOSE_ANIMATION = 1

--The name of the template
door1 = {}

DOOR_OPEN_SOUND_PATH = "../Media/Sounds/drs_spikedhall_open.wav"
DOOR_CLOSE_SOUND_PATH = "../Media/Sounds/drs_spikedhall_close.wav"

FIRST_SOUND = true

DOOR_PARTICLE = "door1_particle"
DOOR_PARTICLE_SCRIPT = "example_025_1"

-- ///////////////////////////////////////////////////////////////////////////////////////////////////
--Physics Actor events:
door1["OnAnimationStarted"] = function (obj)
	anim = nil
	anim = LuaStateManager:getAnimationComponent(obj)
	
	if(anim) then
		if( not FIRST_SOUND ) then --anim:isRunningAnimation()
			currentAnim = -1
			currentAnim = anim:getCurrentAnimationIndex()
			if(currentAnim == CLOSE_ANIMATION) then
				SoundManager:play(DOOR_OPEN_SOUND_PATH)
			else
				SoundManager:play(DOOR_CLOSE_SOUND_PATH)
			end
		end
	end
end

door1["OnAnimationEnded"] = function (obj)

end

door1["OnAnimationUpdated"] = function (obj)

end

--Mouse/Character events
door1["OnCharacterMouseMovedOverObject"] = function ( object, character, position)

end
door1["OnCharacterMouseMovedEnterOverObject"] = function ( object, character, position)

end
door1["OnCharacterMouseMovedLeaveOverObject"] = function ( object, character, position)

end

door1["OnCharacterMousePressedObject"] = function ( object, character, position, mouseButton)

end
door1["OnCharacterMouseReleasedObject"] = function ( object, character, position, mouseButton)

end


-- ///////////////////////////////////////////////////////////////////////////////////////////////////
-- Component Events
door1["OnComponentCreateStart"] = function(obj)

end

door1["OnComponentCreateFinish"] = function(obj)
	
	--GuiManager:setWallpaper("background.jpg")

	pos = Vector3.ZERO
	SoundManager:createSingleSound(SOUND_FX_REVERB, DOOR_OPEN_SOUND_PATH, pos, false )
	SoundManager:createSingleSound(SOUND_FX_REVERB, DOOR_CLOSE_SOUND_PATH, pos, false )
	
	anim = nil
	anim = LuaStateManager:getAnimationComponent(obj)
	
	if(anim) then
		anim:playAnimation(OPEN_ANIMATION)
		anim:pauseAnimation()
		
		anim:setAnimationSpeed(OPEN_ANIMATION, 0.5)
		anim:setAnimationSpeed(CLOSE_ANIMATION, 0.15)
	end
	
	render = nil
	render = LuaStateManager:getRenderComponent(obj)

	if(render) then
		ParticleManager:createParticle(DOOR_PARTICLE,DOOR_PARTICLE_SCRIPT)
		
		nodeParticle = nil
		nodeParticle = OgreManager:createChildSceneNode(OgreManager:getRootSceneNode(),"door1_particleNode")

		pos = Vector3.ZERO
		pos = render:getNode():_getDerivedPosition()
		
		nodeParticle:setPosition(pos)
		
		offset = Vector3.ZERO
		offset = Vector3(0,10,0)
		nodeParticle:translate(offset,Node.TS_PARENT)
		
		--quat = Quaternion.IDENTITY
		--quat = Quaternion(Radian(3.1415927), Vector3.UNIT_Y) --Degree(90)
		--quat = Quaternion(convertToDegrees(90), Vector3.UNIT_Y) --Degree(90)
		--nodeParticle:rotate(quat, Node.TS_WORLD)
	
		ParticleManager:attachParticleToNode(DOOR_PARTICLE,nodeParticle)
		ParticleManager:startParticle(DOOR_PARTICLE)
	end
	
end

door1["OnStartUpdate"] = function( obj )

end

door1["OnFinishUpdate"] = function( obj )
	
	FIRST_SOUND = false
		
end

door1["OnComponentDestroy"] = function( obj )

end


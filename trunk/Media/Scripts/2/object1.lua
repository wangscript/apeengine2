HITGROUND_SOUND_PATH = "../Media/Sounds/Jump_down.ogg"
SOUND_FX_REVERB = 1

--The name of the template
object1 = {}


-- ///////////////////////////////////////////////////////////////////////////////////////////////////
--Physics Actor events:
object1["OnActorStartTouch"] = function (obj)
	--SoundManager:play(HITGROUND_SOUND_PATH)
	--GuiManager:setWallpaper("background.jpg")
end

object1["OnActorTouch"] = function (obj)

end

object1["OnActorEndTouch"] = function (obj)

end

-- ///////////////////////////////////////////////////////////////////////////////////////////////////
--Physics Trigger events:
--Intersect trigger's volume
object1["OnTriggerEnter"] = function (obj)
	--GuiManager:setWallpaper("background.jpg")
end

object1["OnTriggerStay"] = function (obj)
	--GuiManager:setWallpaper("background.jpg")
end

object1["OnTriggerLeave"] = function (obj)
	--GuiManager:setWallpaper("background.jpg")
end

-- ///////////////////////////////////////////////////////////////////////////////////////////////////
-- Component Events

object1["OnComponentCreate"] = function(obj)
	
	pos = Vector3.ZERO
	
	--SOUND_FX_NONE
	SoundManager:createSingleSound(SOUND_FX_REVERB, HITGROUND_SOUND_PATH, pos, false) --SOUNDFX, 
	--SoundManager:createSingleSound(SOUND_FX_REVERB, FOOTSTEP2_SOUND_PATH, pos, false )
	--SoundManager:createSingleSound(SOUND_FX_REVERB, JUMP_SOUND_PATH, pos, false)
	--SoundManager:createSingleSound(SOUND_FX_REVERB, JUMP_LANDING_SOUND_PATH, pos, false )
	--SoundManager:createSingleSound(SOUND_FX_REVERB, JUMP_CLOTH_SOUND_PATH, pos, false )
	
	--Set ambient sounds
	--SoundManager:createSingleSound(SOUND_FX_NONE, AMBIENT1_PATH, pos, true )
	--SoundManager:play(AMBIENT1_PATH)
			

end

object1["OnUpdate"] = function( obj )
	
		
end

object1["OnComponentDestroy"] = function( obj )

end


OPEN_ANIMATION = 0
CLOSE_ANIMATION = 1

--The name of the template
elevator1 = {}

-- ///////////////////////////////////////////////////////////////////////////////////////////////////
--Physics Actor events:
elevator1["OnAnimationStarted"] = function (obj)

end

elevator1["OnAnimationEnded"] = function (obj)
	anim = nil
	anim = LuaStateManager:getAnimationComponent(obj)
	
	if(anim) then
		currentAnim = -1
		currentAnim = anim:getCurrentAnimationIndex()
		if(currentAnim == CLOSE_ANIMATION) then
			anim:setAnimationTimePosition(OPEN_ANIMATION,0)
			anim:playAnimation(OPEN_ANIMATION)
		else
			anim:setAnimationTimePosition(CLOSE_ANIMATION,0)
			anim:playAnimation(CLOSE_ANIMATION)
		end
	end
end

elevator1["OnAnimationUpdated"] = function (obj)

end


--Mouse/Character events
elevator1["OnCharacterMouseMovedOverObject"] = function ( object, character, position)

end
elevator1["OnCharacterMouseMovedEnterOverObject"] = function ( object, character, position)

end
elevator1["OnCharacterMouseMovedLeaveOverObject"] = function ( object, character, position)

end

elevator1["OnCharacterMousePressedObject"] = function ( object, character, position, mouseButton)

end
elevator1["OnCharacterMouseReleasedObject"] = function ( object, character, position, mouseButton)

end

-- ///////////////////////////////////////////////////////////////////////////////////////////////////
-- Component Events
elevator1["OnComponentCreateStart"] = function(obj)

end

elevator1["OnComponentCreateFinish"] = function(obj)
	
	anim = nil
	anim = LuaStateManager:getAnimationComponent(obj)
	
	if(anim) then
		anim:playAnimation(OPEN_ANIMATION)
		anim:setAnimationSpeed(OPEN_ANIMATION, 0.1)
		anim:setAnimationSpeed(CLOSE_ANIMATION, 0.1)
	end

end

elevator1["OnStartUpdate"] = function( obj )
	
		
end

elevator1["OnFinishUpdate"] = function( obj )
	
		
end

elevator1["OnComponentDestroy"] = function( obj )

end


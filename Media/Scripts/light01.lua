OPEN_ANIMATION = 0

--The name of the template
light01 = {}

-- ///////////////////////////////////////////////////////////////////////////////////////////////////
--Physics Actor events:
light01["OnAnimationStarted"] = function (obj)

end

light01["OnAnimationEnded"] = function (obj)
	anim = nil
	anim = LuaStateManager:getAnimationComponent(obj)
	
	if(anim) then
		currentAnim = -1
		currentAnim = anim:getCurrentAnimationIndex()
		if(currentAnim == OPEN_ANIMATION) then
			anim:setAnimationTimePosition(OPEN_ANIMATION,0)
			anim:playAnimation(OPEN_ANIMATION)
		end
	end
end

light01["OnAnimationUpdated"] = function (obj)

end

-- ///////////////////////////////////////////////////////////////////////////////////////////////////
-- Component Events
light01["OnComponentCreateStart"] = function(obj)

end

light01["OnComponentCreateFinish"] = function(obj)
	
	anim = nil
	anim = LuaStateManager:getAnimationComponent(obj)
	
	if(anim) then
		anim:playAnimation(OPEN_ANIMATION)
		anim:setAnimationSpeed(OPEN_ANIMATION, 0.1)

	end

end

light01["OnStartUpdate"] = function( obj )
	
		
end

light01["OnFinishUpdate"] = function( obj )
	
		
end

light01["OnComponentDestroy"] = function( obj )

end

